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


    
def find_type(file_fb_name):
    global comment
    comment = 0
    for line in file_fb_name.input(fb_name, inplace=1):
        if '//' in line:
            start = line.find('//')
            line_temp = line[:start]
        else:
            line_temp = line
        clear_line = ''
        str_object = str_class(clear_line,line_temp)
        find_comment(str_object)
        if len(str_object.clear_line):
            if str_object.clear_line[-1] == line[-1]:
                buff = buff + str_object.clear_line
            else:
                buff = buff + str_object.clear_line+'\n'
        print(line,end='')
    print(buff)



def add_function():
    current = 0
    fb_have_c = []
    fb_have_h = []
    for current in range(123):
        IN=0
        VAR=0
        OUT=0
        if (current <= 9):
            fb_name = 'fb0000'+str(current)+'.h'
        elif (current <= 99):
            fb_name = 'fb000'+str(current)+'.h'
        else:
            fb_name = 'fb00'+str(current)+'.h'


def main():
     add_function()



def correct_exist_fb(name,fb_have):
    message = ''
    try:
        for line in fileinput.input(name, inplace=1):
            include_stm = re.compile('^\s*\#include\s+[\<\"]stm32\/stm32f20x\.h[\>\"]',re.ASCII)
            include_cortex = re.compile('^\s*\#include\s+[\<\"]cortexm3\_macro\.h[\>\"]',re.ASCII)#include <cortexm3_macro.h>
            include_pakmanager = re.compile('^\s*\#include\s+[\<\"]\.\.\/pakmanager\.h[\>\"]',re.ASCII)#include <pakmanager.h>
            include_arc = re.compile('^\s*\#include\s+[\<\"]\.\.\/arc\.h[\>\"]',re.ASCII)#include <arc.h>
            include_rtm_mw = re.compile('^\s*\#include\s+[\<\"]\.\.\/rtm_mw\.h[\>\"]',re.ASCII)#include "../rtm_mw.h"
            include_modbus = re.compile('^\s*\#include\s+[\<\"]\.\.\/modbus\.h[\>\"]',re.ASCII)#include "../modbus.h"
            include_rf = re.compile('^\s*\#include\s+[\<\"]\.\.\/rf\.h[\>\"]',re.ASCII)#include "../rf.h"

            stm = include_stm.search(line)
            cortex = include_cortex.search(line)
            arc = include_arc.search(line)
            pakmanager = include_pakmanager.search(line)
            rtm_mw = include_rtm_mw.search(line)
            modbus = include_modbus.search(line)
            rf = include_rf.search(line)

            if cortex or stm or arc or pakmanager or rtm_mw or modbus or rf: 
                message = 'find #include in '+name +'\n'
                print('',end='')
            else:
                print(line,end='')
        fb_have.append(name)
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def substitute_attribute(name):
    message = ''
    try:
        for line in fileinput.input(name, inplace=1):
            line = re.sub('\_\_attribute\_\_\s*\([\)\(\w]+\)', '', line)
            print(line,end='')
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')

def substitute_parametr(file_name,str_before,str_to):
    message = ''
    str_before_t = '([\w\W^])'+str_before+'([\w\W])'
    str_to_t = '\g<1>'+str_to+'\g<2>'
    try:
        for line in fileinput.input(file_name, inplace=1):
            line_temp = line
            line = re.sub(str_before_t,str_to_t, line)
            print(line,end='')
            if line_temp != line:
                message += 'replace'+str_before+'in file'+file_name+'\n'
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+file_name+'\n')
    sys.stdout.write(message)


def delete_line_from_exist_file(name,type_str):
    message = ''
    try:
        for line in fileinput.input(name, inplace=1):
            one = re.compile(type_str,re.ASCII)
            two = one.search(line)
            if two:
                message = 'find non valid type in '+name +'\n'
                print('',end='')
            else:
                print(line,end='')
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def add_fb_include(name,fb_have):
    message = ''
    try:
        for line in fileinput.input(name, inplace=1):
            include_kernel = re.compile('\#include\s+[\<\"]kernel\.h[\>\"]',re.ASCII)
            kernel = include_kernel.match(line)
            if kernel:
                message = 'find #include kernel '+name +'\n'
                print(line,end='')
                for fb in fb_have:
                    print('#include \"FB\\'+fb+'\"\n',end='')
            else:
                print(line,end='')
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)


def add_string_to(name,str_name):
    message = ''
    not_add = 1
    try:
        for line in fileinput.input(name, inplace=1):
            if not_add:
                not_add = 0
                print(str_name+'\n',end='')
            else:
                print(line,end='')
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def add_string_to_after(file_name,str_print,str_find):
    message = ''
    not_add = 1
    try:
        for line in fileinput.input(file_name, inplace=1):
            one = re.compile(str_find,re.ASCII)
            two = one.search(line)
            if not_add and two:
                not_add = 0
                print(line,end='')
                print(str_print+'\n',end='')
                message = 'add string after'
            else:
                print(line,end='')
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    if not_add:
        sys.stdout.write('dont find string after in'+file_name +'\n')
    sys.stdout.write(message)


def handing_fb_delete(fb_name,current):
    fb_not_testing = [33,34,35,36,103,104,105,108,109,110,111,118,119,120,121,122] 
    if current in fb_not_testing:
        delete_function_fb(fb_name)


def delete_function_fb(fb_name):
    message = ''
    add_str = 0
    try:
        for line in fileinput.input(fb_name, inplace=1):
            if add_str==0:
                add_str+=1
                function_name = 'void '+fb_name[0:-2]+'_exec(void){}'
                print(function_name,end='')
                message = 'delete fb '+fb_name +'\n'
        fileinput.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)








          


def RTM64CRC16(pbuffer , Len):
  """CRC16 for RTM64"""
  CRC = 0x0000
  k = 0
  while (k < Len):
    CRC = (CRC^(((pbuffer[k])<<8)&0xFFFF))
    k+=1
    i=8
    while (i):
      i-=1
      if (CRC & 0x8000): CRC = (((CRC<<1)&0xFFFF)^0x1021)
      else: CRC = ((CRC<<1)&0xFFFF)
  return CRC
def crc16(pck,len):
  """CRC16 for modbus"""
  CRC = 0xFFFF
  i = 0
  while ( i < len ):
    CRC ^= pck[i]
    i+=1
    j = 0 
    while ( j < 8):
       j+=1
       if ( (CRC & 0x0001) == 1 ): CRC = ((CRC >> 1)&0xFFFF) ^ 0xA001;
       else: CRC >>= 1;
  return (CRC&0xFFFF)
def RTM64ChkSUM(pbuffer,Len):
  """ CheckSum RTM64"""
  sum = 0
  i = 0
  while (i<Len):
    sum = sum + pbuffer[i]
    i+=1
  return sum
def int_to_char(cmd_x):
  """char to string array confersion"""
  i = 0
  cmd_r = ['~']
  while (i<len(cmd_x)):
    cmd_r += chr(int(cmd_x[i]))
    i+=1
  return cmd_r[1:]
def char_to_int(cmd_x,lenth):
  """char to string array confersion"""
  i = 0
  cmd_r = [0 for x in range(lenth)]
  while (i<lenth):
    cmd_r[i]=ord(cmd_x[i])
    i+=1
  return cmd_r
def print_hex(cmd,lenth):
  i = 0
  hexf=[0 for x in range(lenth)]
  while (i<lenth):
    hexf[i] = (hex(cmd[i]))
    i+=1
  print (hexf)
if __name__ == "__main__":
    'add function returned size struct FB'
    main()
