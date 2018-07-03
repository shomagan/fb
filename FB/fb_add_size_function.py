import sys
import os
import threading 
import atexit
import io
import msvcrt as m
import re
import fileinput
#def hextoascii():
global comment


class str_class(object):
    def __init__(self,clear_line,restline):
        self.clear_line = clear_line
        self.restline = restline


def find_comment(str_object):
    global comment
    if comment:
        start = str_object.restline.find('*/')
        if start ==-1:
            return str_object
        else:
            comment = 0
            if start < len(str_object.restline)-3:
                str_object.restline = str_object.restline[start+2:]
                find_comment(str_object)
            else:
                return str_object
    else: 
        start = str_object.restline.find('/*')
        if start == -1:
            str_object.clear_line = str_object.clear_line + str_object.restline
            return str_object
        else :
            if start > 0:
                str_object.clear_line = str_object.clear_line + str_object.restline[:start]
                str_object.restline = str_object.restline[start+2:]
            comment = 1
            start = str_object.restline.find('*/')
            if start ==-1:
                return str_object
            else:
                comment = 0
                if start < len(str_object.restline)-3:
                    str_object.restline = str_object.restline[start+2:]
                    find_comment(str_object)
                else:
                    return str_object

    
def find_type_and_add_delarate(file_fb_name):
    global comment
    comment = 0
    type_c = 0x00
    num_lines = sum(1 for line in open('handled'+file_fb_name, encoding="utf-8"))
    num_lines=num_lines-1
    try:
        temp_buff = ''
        file_opened = open('handled'+file_fb_name,'r', encoding="utf-8")
        for line in file_opened:
            if '//' in line:
                start = line.find('//')
                line_temp = line[:start]
            else:
                line_temp = line
            clear_line = ''
            str_object = str_class(clear_line,line_temp)
            find_comment(str_object)
            if len(str_object.clear_line):
                in_type =file_fb_name[:-2] + '_IN_type' 
                var_type =file_fb_name[:-2] + '_VAR_type' 
                out_type =file_fb_name[:-2] + '_OUT_type' 
                if in_type in str_object.clear_line:
                    type_c = type_c | 0x01
                if var_type in str_object.clear_line:
                    type_c = type_c | 0x02
                if out_type in str_object.clear_line:
                    type_c = type_c | 0x04
            temp_buff += line
            if num_lines:
                num_lines-=1
            else:
                str_t = 'u32 '+file_fb_name[:-2]+'_var_size(u8 type);\n'
                temp_buff += str_t
        file_opened.close()
        file_write = open('handled'+file_fb_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()

    except FileNotFoundError: 
        sys.stdout.write('dont find '+file_fb_name +'\n')

    return type_c


def add_function():
    fb_have_c = []
    fb_have_h = []
    for current in range(1,126):
        try:
            if (current <= 9):
                fb_name = 'fb0000'+str(current)+'.h'
                fb_name_c = 'fb0000'+str(current)+'.c'
            elif (current <= 99):
                fb_name = 'fb000'+str(current)+'.h'
                fb_name_c = 'fb000'+str(current)+'.c'
            else:
                fb_name = 'fb00'+str(current)+'.h'
                fb_name_c = 'fb00'+str(current)+'.c'
            type_c = find_type_and_add_delarate(fb_name)
            if type_c==0:
                print("error fb struct name")
            add_fb_include(fb_name_c)
            num_lines = sum(1 for line in open('handled'+fb_name_c, encoding="utf-8"))
            num_lines=num_lines-1
            temp_buff = ''
            file_opened = open('handled'+fb_name_c,'r', encoding="utf-8")
            for line in file_opened:
                temp_buff +=line
                if num_lines:
                    num_lines=num_lines-1
                else:
                    if type_c & 0x01:
                        in_str = '        return sizeof('+fb_name[:-2]+'_IN_type);\n'
                    else:
                        in_str = '        return 0;\n'
                    if type_c & 0x02:
                        out_str = '        return sizeof('+fb_name[:-2]+'_VAR_type);\n'
                    else:
                        out_str = '        return 0;\n'
                    if type_c & 0x04:
                        var_str = '        return sizeof('+fb_name[:-2]+'_OUT_type);\n'
                    else:
                        var_str = '        return 0;\n'

                    str_t = '/*\n  type 0 - IN,1- VAR,2 - OUT\n  return size struct, or 0 if struct not\n*/'+\
                            '    unsigned int '+fb_name[:-2]+'_var_size(unsigned char type) {\n'+\
                            '    switch(type){\n'+\
                            '    case(0):\n'+\
                            in_str+\
                            '    case(1):\n'+\
                            out_str+\
                            '    case(2):\n'+\
                            var_str+\
                            '    default:\n'+\
                            '        return 0;\n'+\
                            '    }\n'+\
                            '}\n'
                    temp_buff += str_t  
            file_opened.close()
            file_write = open('handled'+fb_name_c,'w', encoding="utf-8")
            file_write.write(temp_buff)
            file_write.close()
            
        except FileNotFoundError: 
            sys.stdout.write('dont find '+'handled'+fb_name +'\n')
def add_fb_include(fb_name):
    message = ''
    kernel_finded = 0
    include_fb_finded = 0
    try:
        temp_buff = ''
        file_opened = open('handled'+fb_name,'r', encoding="utf-8")
        print('add_fb_i')
        for line in file_opened:
            include_kernel = re.compile('^\s*\#include\s+[\<\"]\.\.\/kernel\.h[\>\"]',re.ASCII)
            kernel_find = include_kernel.match(line)
            if kernel_find:
                kernel_finded = 1
            include_fb = re.compile('^\s*\#include\s+[\<\"]'+'handled'+fb_name[:-2]+'\.h[\>\"]',re.ASCII)
            include_fb_find = include_fb.match(line)
            if include_fb_find:
                include_fb_finded = 1
            func = re.compile('^\s*void\s+'+fb_name[:-2]+'\_exec',re.ASCII)
            func_find = func.match(line)
            if func_find:
                if kernel_finded:
                    message = 'find #include kernel '+fb_name +'\n'
                else:
                    message = 'didnt find #include kernel '+fb_name +'\n'
                    temp_buff += '#include \"../kernel.h\"\n'
                if include_fb_finded:
                    message = 'find #include fb '+fb_name +'\n'
                else:
                    message = 'didnt find #include fb '+fb_name +'\n'
                    temp_buff +='#include \"'+'handled'+fb_name[:-2]+'.h\"\n'
                temp_buff += line
            else:
                temp_buff += line
        file_opened.close()
        file_write = open('handled'+fb_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()

    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def main():
     add_function()

if __name__ == "__main__":
    'add function returned size struct FB'
    main()
