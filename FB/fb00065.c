/* ФБ "Преобразователь массива uint16_BE->массив uint8" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00065.h"

void fb00065_exec(void)
{

	fb00065_IN_type *IN = (fb00065_IN_type *) FBInputs;
	fb00065_OUT_type *OUT = (fb00065_OUT_type *) FBOutputs;

	u16 i;
	
	for (i = 0; i < (FB_N_In-1); i++) {
		if((i<<1) > FB_N_Out)
			break;
		if(IN->BigEndian.Data.bit) {  // Необходимо разворачивать пары байт (массив BigEndian регистров)
			OUT->Output[i<<1].Data.uint8 = (u8) (IN->Input[i].Data.uint16 >> 8);
			OUT->Output[(i<<1)+1].Data.uint8 = (u8) (IN->Input[i].Data.uint16 & 0xFF);
		} else {
			OUT->Output[i<<1].Data.uint8 = (u8) (IN->Input[i].Data.uint16 & 0xFF);
			OUT->Output[(i<<1)+1].Data.uint8 = (u8) (IN->Input[i].Data.uint16 >> 8);
		}
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00065_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00065_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00065_OUT_type);
    default:
        return 0;
    }
}
