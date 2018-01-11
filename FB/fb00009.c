/* ФБ "Беззнаковое целое -> Набор битов" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00009.h"

void fb00009_exec(void) {
	
	fb00009_IN_type *IN = (fb00009_IN_type *) FBInputs;
	fb00009_OUT_type *OUT = (fb00009_OUT_type *) FBOutputs;

	u8 i;
	
	switch (IN->Input.Type & DataTypeMask) {   // Тип входа
		case KodBit:
			OUT->Bits[0].Data.bit = (IN->Input.Data.bit) ? 1 : 0;
			break;
		case KodInt8:
			for(i = 0; i < 8; i++)
				OUT->Bits[i].Data.bit = (IN->Input.Data.uint8 & (1<<i)) ? 1 : 0;
				break;
		case KodInt16:
			for(i = 0; i < 16; i++)
				OUT->Bits[i].Data.bit = (IN->Input.Data.uint16 & (1<<i)) ? 1 : 0;
				break;
		case KodInt32:
		case KodTime32:
			for(i = 0; i < 32; i++)
				OUT->Bits[i].Data.bit = (IN->Input.Data.uint32 & (1<<i)) ? 1 : 0;
			break;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00009_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00009_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00009_OUT_type);
    default:
        return 0;
    }
}
