/* ФБ "Чтение системной настройки" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00056.h"

void fb00056_exec(void) {
	fb00056_IN_type *IN = (fb00056_IN_type *) FBInputs;
	fb00056_OUT_type *OUT = (fb00056_OUT_type *) FBOutputs;
  
	u16 TempValue;
	switch (OUT->Value.Type & DataTypeMask) {
	case KodInt8:
	case KodInt16:
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32, &TempValue);
  	OUT->Value.Data.uint16 = TempValue; 
    break;
	case KodInt32:
	case KodTime32:
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32, &TempValue);
  	OUT->Value.Data.uint32 = TempValue;
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32+1, &TempValue);
  	OUT->Value.Data.uint32 |= ((u32)(TempValue))<<16; 
		break;
	case KodFloat32:
    LedErrorOn(100);
		break;
	default:
		break;    
	}

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00056_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00056_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00056_OUT_type);
    default:
        return 0;
    }
}
