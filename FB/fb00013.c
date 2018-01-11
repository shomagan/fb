/* ФБ "Float32 -> целое (отброс дробной части)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00013.h"

void fb00013_exec (void)
{
	
	fb00013_IN_type *IN = (fb00013_IN_type *) FBInputs;
	fb00013_OUT_type *OUT = (fb00013_OUT_type *) FBOutputs;
  
	switch (OUT->Output.Type & DataTypeMask) {
	case KodBit:
		OUT->Output.Data.bit = (IN->Input.Data.float32 != 0) ? 1 : 0;
		break;
	case KodInt8:
	case KodInt16:
	case KodInt32:
		OUT->Output.Data.uint32 = (u32) IN->Input.Data.float32;
		break;    
	default:
		OUT->Output.Data.float32 = IN->Input.Data.float32;
		break;    
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00013_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00013_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00013_OUT_type);
    default:
        return 0;
    }
}
