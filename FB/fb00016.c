/* ФБ "Алгебраическое умножение" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00016.h"

void fb00016_exec(void) {

	fb00016_IN_type *IN = (fb00016_IN_type *) FBInputs;
	fb00016_OUT_type *OUT = (fb00016_OUT_type *) FBOutputs;
  
	switch (OUT->Output.Type & DataTypeMask) {
	case KodInt8:
	case KodInt16:
	case KodInt32:
	case KodTime32:
		if(((IN->In1.Type & DataTypeMask) == KodFloat32) && ((IN->In2.Type & DataTypeMask) == KodFloat32))
			OUT->Output.Data.uint32 = (u32) (IN->In1.Data.float32 * IN->In2.Data.float32);
		else if(((IN->In1.Type & DataTypeMask) == KodFloat32) && ((IN->In2.Type & DataTypeMask) != KodFloat32))
			OUT->Output.Data.uint32 = (u32) (IN->In1.Data.float32 * IN->In2.Data.uint32);
		else if(((IN->In1.Type & DataTypeMask) != KodFloat32) && ((IN->In2.Type & DataTypeMask) == KodFloat32))
			OUT->Output.Data.uint32 = (u32) (IN->In1.Data.uint32 * IN->In2.Data.float32);
		else
			OUT->Output.Data.uint32 = IN->In1.Data.uint32 * IN->In2.Data.uint32;

		OUT->Overflow.Data.bit = OverflowInInt(OUT->Output.Type, OUT->Output.Data.uint32);
		break;
	case KodFloat32:
		if(((IN->In1.Type & DataTypeMask) == KodFloat32) && ((IN->In2.Type & DataTypeMask) == KodFloat32))
			OUT->Output.Data.float32 = IN->In1.Data.float32 * IN->In2.Data.float32;
		else if(((IN->In1.Type & DataTypeMask) == KodFloat32) && ((IN->In2.Type & DataTypeMask) != KodFloat32))
			OUT->Output.Data.float32 = IN->In1.Data.float32 * IN->In2.Data.uint32;
		else if(((IN->In1.Type & DataTypeMask) != KodFloat32) && ((IN->In2.Type & DataTypeMask) == KodFloat32))
			OUT->Output.Data.float32 = IN->In1.Data.uint32 * IN->In2.Data.float32;
		else
			OUT->Output.Data.float32 = IN->In1.Data.uint32 * IN->In2.Data.uint32;

		OUT->Overflow.Data.bit = (IsCorrectFloat(OUT->Output.Data.float32)) ? 0 : 1;
		break;
	default:
		OUT->Output.Data.uint32 = 0;
		break;    
	}

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00016_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00016_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00016_OUT_type);
    default:
        return 0;
    }
}
