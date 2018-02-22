import sys
import os
import threading 
import atexit
import io
import msvcrt as m
import re
import fileinput
#def hextoascii():

def main():
    current = 0
    fb_have_c = []
    fb_have_h = []
    while 1:
        current+=1
        if current == 126:
            break
        if (current <= 9):
            fb_name = 'fb0000'+str(current)+'.c'
        elif (current <= 99):
            fb_name = 'fb000'+str(current)+'.c'
        else:
            fb_name = 'fb00'+str(current)+'.c'
        handing_fb_delete(fb_name,current)
        correct_exist_fb(fb_name,fb_have_c)
        try: 
            os.rename(fb_name, fb_name+'bak')
        except FileNotFoundError: 
            print('file not found')
        substitute_parametr('handled'+fb_name,'MaxLenRTM64Block','64')
        substitute_parametr('handled'+fb_name,'MaxPacketLen','256')
        substitute_parametr('handled'+fb_name,'cstFBInputsNum','256')
        substitute_parametr('handled'+fb_name,'cstFBVarsNum','298')
        substitute_parametr('handled'+fb_name,'cstFBOutputsNum','256')

        fb_name= fb_name[0:-1]+'h'
        correct_exist_fb(fb_name,fb_have_h)
        try: 
            os.rename(fb_name, fb_name+'bak')
        except FileNotFoundError: 
            print('file not found')
        substitute_parametr('handled'+fb_name,'MaxLenRTM64Block','64')
        substitute_parametr('handled'+fb_name,'MaxPacketLen','256')
        substitute_parametr('handled'+fb_name,'cstFBInputsNum','256')
        substitute_parametr('handled'+fb_name,'cstFBVarsNum','298')
        substitute_parametr('handled'+fb_name,'cstFBOutputsNum','256')
     


def correct_exist_fb(name,fb_have):
    message = ''
    try:
        file_opened = open(name,'r', encoding="utf-8")
        file_write = open('handled'+name,'w', encoding="utf-8")
        for line in file_opened:
            h_name= name[0:-1]+'h'
            line = re.sub('^\s*\#include\s+[\<\"]((fb|FB)\d{5}).h[\>\"]', '#include \"handled\g<1>.h\"', line)
            include_stm = re.compile('^\s*\#include\s+[\<\"]stm32\/stm32f20x\.h[\>\"]')
            include_cortex = re.compile('^\s*\#include\s+[\<\"]cortexm3\_macro\.h[\>\"]')#include <cortexm3_macro.h>
            include_pakmanager = re.compile('^\s*\#include\s+[\<\"]\.\.\/pakmanager\.h[\>\"]')#include <pakmanager.h>
            include_arc = re.compile('^\s*\#include\s+[\<\"]\.\.\/arc\.h[\>\"]')#include <arc.h>
            include_rtm_mw = re.compile('^\s*\#include\s+[\<\"]\.\.\/rtm_mw\.h[\>\"]')#include "../rtm_mw.h"
            include_modbus = re.compile('^\s*\#include\s+[\<\"]\.\.\/modbus\.h[\>\"]')#include "../modbus.h"
            include_rf = re.compile('^\s*\#include\s+[\<\"]\.\.\/rf\.h[\>\"]')#include "../rf.h"
            stm = include_stm.search(line)
            cortex = include_cortex.search(line)
            arc = include_arc.search(line)
            pakmanager = include_pakmanager.search(line)
            rtm_mw = include_rtm_mw.search(line)
            modbus = include_modbus.search(line)
            rf = include_rf.search(line)
            if cortex or stm or arc or pakmanager or rtm_mw or modbus or rf: 
                message += 'find '+line[:-1]+'in '+name+' \n'
                file_write.write(' '+'\n')
            else:
                file_write.write(line)
        fb_have.append(name)
        file_opened.close()
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def substitute_attribute(name):
    message = ''
    try:
        temp_buff = ''
        file_opened = open(name,'r', encoding="utf-8")
        for line in file_opened:
            line = re.sub('\_\_attribute\_\_\s*\([\)\(\w]+\)', '', line)
            temp_buff +=line
        file_opened.close()
        file_write = open(name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')

def substitute_parametr(file_name,str_before,str_to):
    message = ''
    str_before_t = '([\w\W^])'+str_before+'([\w\W])'
    str_to_t = '\g<1>'+str_to+'\g<2>'
    try:
        temp_buff = ''
        file_opened = open(file_name,'r', encoding="utf-8")
        for line in file_opened:
            line_temp = line
            line = re.sub(str_before_t,str_to_t, line)
            temp_buff += line
            if line_temp != line:
                message += 'replace'+str_before+'in file'+file_name+'\n'
        file_opened.close()

        file_write = open(file_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+file_name+'\n')
    sys.stdout.write(message)


def delete_line_from_exist_file(name,type_str):
    message = ''
    try:
        temp_buff = ''
        file_opened = open(name,'r', encoding="utf-8")
        for line in file_opened:
            one = re.compile(type_str)
            two = one.search(line)
            if two:
                message = 'find non valid type in '+name +'\n'
            else:
                temp_buff += line
        file_opened.close()
        file_write = open(file_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def add_fb_include(name,fb_have):
    message = ''
    try:
        temp_buff = ''
        file_opened = open(name,'r', encoding="utf-8")
        for line in file_opened:
            include_kernel = re.compile('\#include\s+[\<\"]kernel\.h[\>\"]')
            kernel = include_kernel.match(line)
            if kernel:
                message = 'find #include kernel '+name +'\n'
                temp_buff +=line
                for fb in fb_have:
                    temp_buff+=('#include \"FB\\'+fb+'\"\n')
            else:
                temp_buff+=line
        file_opened.close()
        file_write = open(name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)


def add_string_to(name,str_name):
    message = ''
    not_add = 1
    try:
        temp_buff = ''
        file_opened = open(name,'r', encoding="utf-8")
        for line in file_opened:
            if not_add:
                not_add = 0
                temp_buff+=(str_name+'\n')
            else:
                temp_buff+=line
        file_opened.close()
        file_write = open(name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    sys.stdout.write(message)

def add_string_to_after(file_name,str_print,str_find):
    message = ''
    not_add = 1
    try:
        temp_buff = ''
        file_opened = open(name,'r', encoding="utf-8")
        for line in file_opened:
            one = re.compile(str_find)
            two = one.search(line)
            if not_add and two:
                not_add = 0
                temp_buff+=line
                temp_buff+=(str_print+'\n')
                message = 'add string after'
            else:
                temp_buff+=line
        file_opened.close()
        file_write = open(file_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()

    except FileNotFoundError: 
        sys.stdout.write('dont find '+name +'\n')
    if not_add:
        sys.stdout.write('dont find string after in'+file_name +'\n')
    sys.stdout.write(message)


def handing_fb_delete(fb_name,current):
    fb_not_testing = [33,34,35,36,103,104,105,108,109,110,111,118,119,120,121,122,123,124,125] 
    if current in fb_not_testing:
        delete_function_fb(fb_name)


def delete_function_fb(fb_name):
    message = ''
    add_str = 0
    try:
        temp_buff = ''
        file_opened = open(fb_name,'r', encoding="utf-8")
        for line in file_opened:
            if add_str==0:
                add_str+=1
                function_name = 'void '+fb_name[0:-2]+'_exec(void){}'
                temp_buff+=function_name
                message = 'delete fb '+fb_name +'\n'
        file_opened.close()
        file_write = open(fb_name,'w', encoding="utf-8")
        file_write.write(temp_buff)
        file_write.close()
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
    'read and change parametr'
    main()
