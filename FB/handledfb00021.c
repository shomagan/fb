/* ФБ "Компаратор" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00021.h"

void fb00021_exec(void) {

	fb00021_IN_type *IN = (fb00021_IN_type *) FBInputs;
	fb00021_OUT_type *OUT = (fb00021_OUT_type *) FBOutputs;

	switch (IN->Input.Type & DataTypeMask) {
	case KodInt8:
	case KodInt16:
	case KodInt32:
	case KodTime32:
		OUT->OutUp.Data.bit = (IN->Input.Data.uint32 > IN->UpperLimit.Data.uint32) ? 1 : 0;
		OUT->OutLow.Data.bit = (IN->Input.Data.uint32 < IN->LowerLimit.Data.uint32) ? 1 : 0;
		break;
	case KodFloat32:
		OUT->OutUp.Data.bit = (IN->Input.Data.float32 > IN->UpperLimit.Data.float32) ? 1 : 0;
		OUT->OutLow.Data.bit = (IN->Input.Data.float32 < IN->LowerLimit.Data.float32) ? 1 : 0;
		break;
	default:
		OUT->OutUp.Data.bit = OUT->OutLow.Data.bit = 0;
		break;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00021_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00021_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00021_OUT_type);
    default:
        return 0;
    }
}
