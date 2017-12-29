/* ФБ "Алгебраическое деление" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00017.h"

void fb00017_exec(void) {

	fb00017_IN_type *IN = (fb00017_IN_type *) FBInputs;
	fb00017_OUT_type *OUT = (fb00017_OUT_type *) FBOutputs;
	u8 NotNULL = 0, DivFloat = 0, ValFloat = 0;

	ValFloat = ((IN->Value.Type & DataTypeMask) == KodFloat32) ? 1 : 0;
  
	if ((IN->Divider.Type & DataTypeMask) == KodFloat32) {
		DivFloat = 1;
		if (IN->Divider.Data.float32 != 0)
			NotNULL = 1;
	} else {
		DivFloat = 0;
		if (IN->Divider.Data.uint32 != 0)
			NotNULL = 1;
	}
    
	if (NotNULL) {
		switch (OUT->Output.Type & DataTypeMask) {
		case KodInt8:
		case KodInt16:
		case KodInt32:
		case KodTime32:
			if((DivFloat) && (ValFloat))
				OUT->Output.Data.uint32 = (u32) (IN->Value.Data.float32 / IN->Divider.Data.float32);
			else if((DivFloat) && (!ValFloat))
				OUT->Output.Data.uint32 = (u32) (IN->Value.Data.uint32 / IN->Divider.Data.float32);
			else if((!DivFloat) && (ValFloat))
				OUT->Output.Data.uint32 = (u32) (IN->Value.Data.float32 / IN->Divider.Data.uint32);
			else
				OUT->Output.Data.uint32 = IN->Value.Data.uint32 / IN->Divider.Data.uint32;
			break;
		case KodFloat32:
			if((DivFloat) && (ValFloat))
				OUT->Output.Data.float32 = IN->Value.Data.float32 / IN->Divider.Data.float32;      
			else if((DivFloat) && (!ValFloat))
				OUT->Output.Data.float32 = (float)((float)IN->Value.Data.uint32 / (float)IN->Divider.Data.float32);
			else if((!DivFloat) && (ValFloat))
				OUT->Output.Data.float32 = (float)((float)IN->Value.Data.float32 / IN->Divider.Data.uint32);
			else
				OUT->Output.Data.float32 = (float)((float)IN->Value.Data.uint32 / IN->Divider.Data.uint32);
			break;
		default:
			OUT->Output.Data.uint32 = 0;
			break;    
		}
		OUT->Error.Data.bit = 0;
	} else {
		OUT->Output.Data.uint32 = 0;
		OUT->Error.Data.bit = 1;
	}
}
