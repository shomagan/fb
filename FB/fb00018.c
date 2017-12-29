/* ФБ "Алгебраическое возведение в степень" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00018.h"

void fb00018_exec(void) {

	fb00018_IN_type *IN = (fb00018_IN_type *) FBInputs;
	fb00018_OUT_type *OUT = (fb00018_OUT_type *) FBOutputs;
  
	u16 i;
  
	OUT->Overflow.Data.bit = 0;
  
	if ((IN->Power.Type & DataTypeMask) != KodFloat32) {
		if (IN->Power.Data.uint32 == 0) {
			if ((OUT->Output.Type & DataTypeMask) == KodFloat32)
				OUT->Output.Data.float32 = 1.0;
			else
				OUT->Output.Data.uint32 = 1;
		} else {
			switch (OUT->Output.Type & DataTypeMask) {
			case KodInt8:
			case KodInt16:
			case KodInt32:
				if ((IN->Value.Type & DataTypeMask) == KodFloat32)
					OUT->Output.Data.uint32 = (u32) IN->Value.Data.float32;
				else
					OUT->Output.Data.uint32 = IN->Value.Data.uint32;
        
				for (i = 1; i < (IN->Power.Data.uint32); i++) {
					if ((IN->Value.Type & DataTypeMask) == KodFloat32)
						OUT->Output.Data.uint32 *= IN->Value.Data.float32;
					else
						OUT->Output.Data.uint32 *= IN->Value.Data.uint32;
          
					if (OverflowInInt (OUT->Output.Type, OUT->Output.Data.uint32)) {
						OUT->Overflow.Data.bit = 1;
						break;
					}
				}
				break;
			case KodFloat32:
				if((IN->Value.Type & DataTypeMask) == KodFloat32)
					OUT->Output.Data.float32 = IN->Value.Data.float32;
				else
					OUT->Output.Data.float32 = IN->Value.Data.uint32;
       
				for(i = 1; i < (IN->Power.Data.uint32); i++) {
					if((IN->Value.Type & DataTypeMask) == KodFloat32)
						OUT->Output.Data.float32 *= IN->Value.Data.float32;
					else
						OUT->Output.Data.float32 *= IN->Value.Data.uint32;
				}
				break;
			default:
				OUT->Output.Data.uint32 = 0;
				break;    
			}
		}
	} else
		OUT->Output.Data.uint32 = 0;

}
