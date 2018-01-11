"""
type 
---------------
bit 7 000 bit
bit 6 001 uit8
bit 5 010 uint16
      011 uint32
      100 float
      101 time
---------------
value
---------------
bit 2 0 variable
      1 array
---------------
destination
---------------
bit 1 00 const
bit 0 01 input
      10 output
      11 input_variable
"""
import sys, os, threading, atexit,io,time
import msvcrt as m
import struct
import json
import argparse
#def hextoascii():
TYPE_SECTION = {
    'BINAR_CONFIG_TYPE':0,
    'SP_CONFIG_TYPE':1,
    'VISUAL_CONFIG_TYPE':2
}
FB_CANCEL = 0xff
SELECT_TYPE_MASK = 0x03
ARRAY_TYPE_MASK = 0x04
VALUE_TYPE_MASK = 0xe0
TYPE_VARIABLE = {'bit'     :0b00000000,
                 'uint8'   :0b00100000,
                 'uint16'  :0b01000000,
                 'uint32'  :0b01100000,
                 'float'   :128,
                 'time'    :160,
                 'variable':0b00000000,
                 'array'   :0b00000100,
                 'const'   :0b00000000,
                 'input'   :0b00000001,
                 'outpt'   :0b00000010,
                 'in_vb'   :0b00000011,
}
TYPE_VARIABLE_I = {0b00000000:'bit',
                 0b00100000:'uint8',
                 0b01000000:'uint16',
                 0b01100000:'uint32',
                 128:'float',
                 160:'time',
                 0b00000000:'variable',
                 0b00000100 :'array'  ,
                 0b00000000 :'const'  ,
                 0b00000001:'input',
                 0b00000010 :'output',
                 0b00000011 :'internal' 
}
__description__ = 'Decompiler for fb32 format to json'
def main():
    parser = argparse.ArgumentParser(description=__description__)
    parser.add_argument('fb')
    args = parser.parse_args()


    time_start=time.time()
#  fb_name = open('fb_name.txt','r')
#  fb_namber_to_name = fb_name.readlines()
     
    fb32 = open (args.fb,'rb')
    fb32_b = fb32.read()
    fb32.close()
    print("config size",len(fb32_b))
    config_head = ConfigHead()
    point = config_head.set_config_head(fb32_b)

    if config_head.crc:
        interp_section = SectionHead(point)
        interp_section.set_section_head(config_head.SectionNumber,fb32_b,config_head.Size)
        interp_section.print_section_head_info()
        if interp_section.Pozition:
            interp_section.sheduler_init(fb32_b)
            pt_byte = 0
            FB_array = []
            while (pt_byte < interp_section.size_im_conf):
                FB_pt = FB(((interp_section.im_conf[pt_byte])<<8)|(interp_section.im_conf[pt_byte+1]),len(FB_array))
                pt_byte += 2
                type_var = interp_section.im_conf[pt_byte]
                pt_byte +=1
                if (type_var == FB_CANCEL):
                    FB_array.append(FB_pt)
                    continue
                if (type_var & TYPE_VARIABLE['array']):
                    '''array '''
                    if (type_var & SELECT_TYPE_MASK) == TYPE_VARIABLE['const']:
                        '''const'''
                        size_array = (interp_section.im_conf[pt_byte]<<8)|interp_section.im_conf[pt_byte + 1]
                        pt_byte +=2
                        for i in range(size_array):
                            if (((type_var & 0xE0) == TYPE_VARIABLE['bit']) |\
                                ((type_var & 0xE0) == TYPE_VARIABLE['uint8'])):
                                FB_pt.new_var(interp_section.im_conf[pt_byte],type_var,1,config_head)
                                pt_byte +=1
                            elif((type_var&0xE0 == TYPE_VARIABLE['uint16'])):
                                FB_pt.new_var(interp_section.im_conf[pt_byte]<<8|\
                                              interp_section.im_conf[pt_byte+1],type_var,1,config_head)
                                pt_byte +=2
                            elif((type_var&0xE0 == TYPE_VARIABLE['uint32'])|
                                ((type_var&0xE0 == TYPE_VARIABLE['time']))):
                                FB_pt.new_var((interp_section.im_conf[pt_byte])|\
                                              (interp_section.im_conf[pt_byte+1]<<8)|\
                                              (interp_section.im_conf[pt_byte+2]<<16)|\
                                              (interp_section.im_conf[pt_byte+3]<<24),type_var,1,config_head)
                                pt_byte +=4
                            elif((type_var&0xE0 == TYPE_VARIABLE['float'])):
                                value = (interp_section.im_conf[pt_byte])|\
                                        (interp_section.im_conf[pt_byte+1]<<8)|\
                                        (interp_section.im_conf[pt_byte+2]<<16)|\
                                        (interp_section.im_conf[pt_byte+3]<<24)
                                flo32 = struct.pack('I',value)
                                float_temp = struct.unpack('f',flo32)
                                FB_pt.new_var(float_temp,type_var,1,config_head)
                                pt_byte +=4
                    else:
                        '''addres'''
                        size_array = (interp_section.im_conf[pt_byte]<<8)|\
                                      interp_section.im_conf[pt_byte + 1]
                        pt_byte +=2
                        addres_array = (interp_section.im_conf[pt_byte]<<8)|\
                                        interp_section.im_conf[pt_byte+1]
                        pt_byte +=2
                        FB_pt.new_var(addres_array,type_var,size_array,config_head)
                else:
                    if type_var & SELECT_TYPE_MASK == TYPE_VARIABLE['const']:
                        if (((type_var & 0xE0) == TYPE_VARIABLE['bit']) |\
                            ((type_var & 0xE0) == TYPE_VARIABLE['uint8'])):
                            FB_pt.new_var(interp_section.im_conf[pt_byte],type_var,1,config_head)
                            pt_byte +=1
                        elif((type_var&0xE0 == TYPE_VARIABLE['uint16'])):
                            FB_pt.new_var(interp_section.im_conf[pt_byte]<<8|\
                                          interp_section.im_conf[pt_byte+1],type_var,1,config_head)
                            pt_byte +=2
                        elif((type_var&0xE0 == TYPE_VARIABLE['uint32'])|
                            ((type_var&0xE0 == TYPE_VARIABLE['time']))):
                            FB_pt.new_var((interp_section.im_conf[pt_byte])|\
                                          (interp_section.im_conf[pt_byte+1]<<8)|\
                                          (interp_section.im_conf[pt_byte+2]<<16)|\
                                          (interp_section.im_conf[pt_byte+3]<<24),type_var,1,config_head)
                            pt_byte +=4
                        elif((type_var&0xE0 == TYPE_VARIABLE['float'])):
                            value = (interp_section.im_conf[pt_byte])|\
                                    (interp_section.im_conf[pt_byte+1]<<8)|\
                                    (interp_section.im_conf[pt_byte+2]<<16)|\
                                    (interp_section.im_conf[pt_byte+3]<<24)
                            flo32 = struct.pack('I',value)
                            float_temp = struct.unpack('f',flo32)
                            FB_pt.new_var(float_temp,type_var,1,config_head)
                            pt_byte +=4
                    else:
                        '''addres'''
                        addres_array = (interp_section.im_conf[pt_byte]<<8)|\
                                        interp_section.im_conf[pt_byte+1]
                        pt_byte +=2
                        FB_pt.new_var(addres_array,type_var,1,config_head)
            pt_byte = 0
            while (pt_byte < interp_section.size_fb_conf):
                FB_pt = FB(interp_section.fb_conf[pt_byte]|(interp_section.fb_conf[pt_byte+1]<<8),len(FB_array))
                pt_byte += 2
                while 1:
                    type_var = interp_section.fb_conf[pt_byte]
                    pt_byte +=1
                    if (type_var == FB_CANCEL):
                        FB_array.append(FB_pt)
                        break
                    if (type_var & TYPE_VARIABLE['array']):
                        '''array '''
                        if (type_var & SELECT_TYPE_MASK)==TYPE_VARIABLE['const']:
                            '''const'''
                            size_array = (interp_section.fb_conf[pt_byte]<<8)|interp_section.fb_conf[pt_byte + 1]
                            pt_byte +=2
                            for i in range(size_array):
                                if (((type_var & 0xE0) == TYPE_VARIABLE['bit']) |\
                                    ((type_var & 0xE0) == TYPE_VARIABLE['uint8'])):
                                    FB_pt.new_var(interp_section.fb_conf[pt_byte],type_var,1,config_head)
                                    pt_byte +=1
                                elif((type_var&0xE0 == TYPE_VARIABLE['uint16'])):
                                    FB_pt.new_var(interp_section.fb_conf[pt_byte]<<8|\
                                                  interp_section.fb_conf[pt_byte+1],type_var,1,config_head)
                                    pt_byte +=2
                                elif((type_var&0xE0 == TYPE_VARIABLE['uint32'])|
                                    ((type_var&0xE0 == TYPE_VARIABLE['time']))):
                                    FB_pt.new_var((interp_section.fb_conf[pt_byte])|\
                                                  (interp_section.fb_conf[pt_byte+1]<<8)|\
                                                  (interp_section.fb_conf[pt_byte+2]<<16)|\
                                                  (interp_section.fb_conf[pt_byte+3]<<24),type_var,1,config_head)
                                    pt_byte +=4
                                elif((type_var&0xE0 == TYPE_VARIABLE['float'])):
                                    value = (interp_section.fb_conf[pt_byte])|\
                                            (interp_section.fb_conf[pt_byte+1]<<8)|\
                                            (interp_section.fb_conf[pt_byte+2]<<16)|\
                                            (interp_section.fb_conf[pt_byte+3]<<24)
                                    flo32 = struct.pack('I',value)
                                    float_temp = struct.unpack('f',flo32)
                                    FB_pt.new_var(float_temp,type_var,1,config_head)
                                    pt_byte +=4
                        else:
                            '''addres'''
                            size_array = (interp_section.fb_conf[pt_byte]<<8)|\
                                          interp_section.fb_conf[pt_byte + 1]
                            pt_byte +=2
                            addres_array = (interp_section.fb_conf[pt_byte]<<8)|\
                                            interp_section.fb_conf[pt_byte+1]
                            pt_byte +=2
                            FB_pt.new_var(addres_array,type_var,size_array,config_head)

                    else:
                        if type_var & SELECT_TYPE_MASK==TYPE_VARIABLE['const']:
                            if (((type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['bit']) or\
                                ((type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['uint8'])):
                                FB_pt.new_var(interp_section.fb_conf[pt_byte],type_var,1,config_head)
                                pt_byte +=1
                            elif(type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['uint16']:
                                FB_pt.new_var(interp_section.fb_conf[pt_byte]<<8 |\
                                              interp_section.fb_conf[pt_byte+1],type_var,1,config_head)
                                pt_byte +=2
                            elif((type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['uint32']) or\
                                ((type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['time']):
                                FB_pt.new_var((interp_section.fb_conf[pt_byte])|\
                                              (interp_section.fb_conf[pt_byte+1]<<8)|\
                                              (interp_section.fb_conf[pt_byte+2]<<16)|\
                                              (interp_section.fb_conf[pt_byte+3]<<24),type_var,1,config_head)
                                pt_byte +=4
                            elif (type_var & VALUE_TYPE_MASK) == TYPE_VARIABLE['float']:
                                value = (interp_section.fb_conf[pt_byte])|\
                                        (interp_section.fb_conf[pt_byte+1]<<8)|\
                                        (interp_section.fb_conf[pt_byte+2]<<16)|\
                                        (interp_section.fb_conf[pt_byte+3]<<24)
                                flo32 = struct.pack('I',value)
                                float_temp = struct.unpack('f',flo32)
                                FB_pt.new_var(float_temp,type_var,1,config_head)
                                pt_byte +=4
                            else:
                                print("error value type",type_var,TYPE_VARIABLE['float'])
                        else:
                            '''addres'''
                            addres_array = interp_section.fb_conf[pt_byte]|\
                                            (interp_section.fb_conf[pt_byte+1]<<8)
                            pt_byte +=2
                            FB_pt.new_var(addres_array,type_var,1,config_head)
            for i in range(len(FB_array)):
                FB_array[i].print()
    config_head.print_config_head_info()            



class ConfigHead:
    '''
    info about full config data(consist per section)
        typedef struct ConfigHead{
            u32 Size;
            u32 Version;
            u32 TimeLastUpdate;
            u8  Avtor[16];
            u8 SectionNumber;
        }ConfigHead_t;
    '''
    self_size = 29
    Size = 0
    Version = 0
    TimeLastUpdate = 0 #u32
    Avtor = [0 for i in range(16)] #u8 * 16
    SectionNumber = 0 #u8 
    crc = 0
    address_array = {}
    full_table = {}
    def __init__(self):
        self.Size = 0
    def set_config_head(self,fb32):
        i=0
        self.Size = ((fb32[i])|(fb32[i+1]<<8)|(fb32[i+2]<<16)|(fb32[i+3]<<24))
        print("fb size",self.Size)
        i+=4
        self.Version = ((fb32[i])|(fb32[i+1]<<8)|(fb32[i+2]<<16)|(fb32[i+3]<<24))
        i+=4
        self.TimeLastUpdate = ((fb32[i])|(fb32[i+1]<<8)|(fb32[i+2]<<16)|(fb32[i+3]<<24))
        i+=4
        self.Avtor = [fb32[k+i] for k in range(16)]
        i+=16
        self.SectionNumber = fb32[i]
        i+=1
        self.crc = fb32[self.Size-2]|(fb32[self.Size-1]<<8)
        check_crc = check_file_crc(fb32, self.Size-2)
        if self.crc != check_crc:
            print('not correct crc',hex(self.crc),hex(check_crc))
            self.crc = 0
        else:
            print('correct crc',hex(self.crc),hex(check_crc))
        return i
    def print_config_head_info(self):
        print(str(self.__dict__))
        print(self.address_array)
        json_address_array = json.dumps(self.address_array)
        print(json_address_array)
        json_address_array_file = open ('json_address_array.json','w')
        json_address_array_file.write(json_address_array)
        json_address_array_file.close()
        print(self.full_table)
        json_full = json.dumps(self.full_table)
        print(json_full)
        json_full_file = open ('json_full.json','w')
        json_full_file.write(json_full)
        json_full_file.close()



class SectionHead:
    ''' info about kernel sheduler section
        typedef struct SectionHead{
          u32 Pozition;
          u8  Type;
          u32 LengthSection;
          u8  ServiceFlag[3];
          u32 Rezerv;
        }SectionHead_t;
    '''
    point = 0
    self_size = 16
    Pozition = 0 #u32
    Type = 0 # u8
    LenghtSection = 0 #u32
    ServiceFlag = [0 for i in range(3)] #u8*3
    Rezerv = 0 #u32
    def __init__(self,point):
        self.point = point

    def set_section_head(self,section_number,fb32,config_len):
        self.Pozition = 0
        for i in range(section_number):
            self.Type = fb32[self.point+4]
            if self.Type == TYPE_SECTION['BINAR_CONFIG_TYPE']:
                self.Pozition = fb32[self.point]|(fb32[self.point+1]<<8)|\
                                (fb32[self.point+2]<<16)|(fb32[self.point+3]<<24)
                self.point+=4
                self.Type = fb32[self.point]
                self.point+=1
                self.LenghtSection = fb32[self.point]|(fb32[self.point+1]<<8)|\
                                (fb32[self.point+2]<<16)|(fb32[self.point+3]<<24)
                self.point+=4
                self.ServiceFlag = [fb32[self.point+k] for k in range(3)]
                self.point+=3
                self.Rezerv = fb32[self.point]
                self.point+=1
                if self.LenghtSection > config_len:
                    self.Pozition = 0
                print('interpretator position',self.Pozition)
                return self.Pozition
            else:
                self.point += self.self_size
        print('interpretator not finded')
    def sheduler_init(self,fb32):
        self.size_conf =(fb32[self.Pozition])|((fb32[self.Pozition+1])<<8)
        print("size_conf",self.size_conf)
        self.size_im_conf = (fb32[self.Pozition+2])|((fb32[self.Pozition+3])<<8)
        self.im_conf = fb32[self.Pozition+4:self.Pozition+4+self.size_im_conf]
        self.size_fb_conf = (fb32[self.Pozition+4+self.size_im_conf])|((fb32[self.Pozition+5+self.size_im_conf])<<8)
        print("size_fb_conf",self.size_fb_conf)
        self.fb_conf = fb32[self.Pozition+6+1+self.size_im_conf:self.Pozition+6+1+self.size_im_conf+self.size_fb_conf]

    def print_section_head_info(self):
        print(str(self.__dict__))


class FB:

    def __init__(self,type_number,order_number):
        self.type_number = type_number
        self.order_number = order_number
        self.name = "noname"
        self.common_variable_number = 0
        self.input_variable_number = 0
        self.input_variable = {}
        self.var_variable_number = 0
        self.var_variable   = {}
        self.out_variable_number = 0
        self.out_variable   = {}

    def new_var(self,address_or_const,type_var,size,config_head):
        if (type_var & SELECT_TYPE_MASK==TYPE_VARIABLE['const']):
            if (type_var & SELECT_TYPE_MASK == TYPE_VARIABLE['input']) or\
               (type_var & SELECT_TYPE_MASK == TYPE_VARIABLE['const']):      
                self.input_variable[self.input_variable_number] = (address_or_const,'const')
                self.input_variable_number += 1
            elif type_var & SELECT_TYPE_MASK == 2:
                self.out_variable[self.out_variable_number] = (address_or_const,'const')
                self.out_variable_number += 1
                print("BUG REPORT:UNCORECT TYPE const in OUT \n")
            elif type_var & SELECT_TYPE_MASK == 3:
                self.var_variable[self.var_variable_number] = (address_or_const,'const')
                self.var_variable_number += 1
            else:
                print("BUG REPORT:UNCORECT TYPE \n")
 
            if (str(self.order_number)+'-'+str(self.type_number)) in config_head.full_table:
                config_head.full_table[str(self.order_number)+'-'+str(self.type_number)].append({TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK]:(self.common_variable_number,address_or_const)})
            else:
                config_head.full_table[str(self.order_number)+'-'+str(self.type_number)]=[{TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK]:(self.common_variable_number,address_or_const)}]

            self.common_variable_number += 1
        else:
            if (type_var & SELECT_TYPE_MASK == TYPE_VARIABLE['input']) or\
               (type_var & SELECT_TYPE_MASK == TYPE_VARIABLE['const']):      
                self.input_variable[self.input_variable_number] = (address_or_const,'addr')
                self.input_variable_number += 1
            elif type_var & SELECT_TYPE_MASK == 2:
                self.out_variable[self.out_variable_number] = (address_or_const,'addr')
                self.out_variable_number += 1
            elif type_var & SELECT_TYPE_MASK == 3:
                self.var_variable[self.var_variable_number] = (address_or_const,'addr')
                self.var_variable_number += 1
            else:
                print("BUG REPORT:UNCORECT TYPE \n")

            if address_or_const in config_head.address_array:
                config_head.address_array[address_or_const].append((self.type_number,self.order_number,TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK]))
            else:
                config_head.address_array[address_or_const]=[(self.type_number,self.order_number,TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK])]

            if (str(self.order_number)+'-'+str(self.type_number)) in config_head.full_table:
                config_head.full_table[str(self.order_number)+'-'+str(self.type_number)].append({TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK]:(self.common_variable_number,address_or_const)})
            else:
                config_head.full_table[str(self.order_number)+'-'+str(self.type_number)]=[{TYPE_VARIABLE_I[type_var & SELECT_TYPE_MASK]:(self.common_variable_number,address_or_const)}]

            self.common_variable_number += 1

    def print(self):
        print("fb number",self.type_number)
        print(self.input_variable_number,self.var_variable_number,self.out_variable_number)
        for i in range(self.input_variable_number):
            print("input #",i,self.input_variable[i])
        for i in range(self.var_variable_number):
            print("var #",i,self.var_variable[i])
        for i in range(self.out_variable_number):
            print("out #",i,self.out_variable[i])

def write_property(FB_property,decompile):
    decompile.write (FB_property.name+'#'+str(FB_property.number)+'\n')
    if (len(FB_property.const)>0):
        for(key,value) in FB_property.const.items():
            decompile.write (key+'&'+str(value)+'\n')
    if (len(FB_property.input_variable)>0):
        for key in FB_property.input_variable:
            decompile.write (key+'&'+str(FB_property.input_variable[key])+'\n')
    if (len(FB_property.var_variable)>0):
        for key in FB_property.var_variable:
            decompile.write (key+'&'+str(FB_property.var_variable[key])+'\n')
    if (len(FB_property.out_variable)>0):
        for key in FB_property.out_variable:
            decompile.write (key+'&'+str(FB_property.out_variable[key])+'\n')

def fbparser(fb,len_fb):
    return array + len_fb

def check_file_crc(file_fb, length):
    temp_buff=[0 for i in range(64)]
    bytes_current = 0
    tmpcrc = 0x0000
    while length:
        tmpcrc = ((tmpcrc >> 8) | (tmpcrc << 8))&0xffff
        tmpcrc ^= file_fb[bytes_current]&0xffff
        bytes_current+=1
        tmpcrc ^= ((tmpcrc & 0x00ff) >> 4)&0xffff
        tmpcrc ^= ((tmpcrc << 8) << 4)&0xffff
        tmpcrc ^= (((tmpcrc & 0x00ff) << 4) << 1)&0xffff
        length-=1;
    return tmpcrc;


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
def str_to_c(cmd_x,lenth):
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
    main()
