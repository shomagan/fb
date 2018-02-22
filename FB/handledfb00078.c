/* ФБ "Счётчик c ограничением по макс. приращению входа" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00078.h"

void fb00078_exec(void) {

	fb00078_IN_type *IN = (fb00078_IN_type *) FBInputs;
	fb00078_VAR_type *VAR = (fb00078_VAR_type *) FBVars;
	fb00078_OUT_type *OUT = (fb00078_OUT_type *) FBOutputs;
  
	if (IN->Reset.Data.bit)   // Reset
		OUT->Counter.Data.uint32 = VAR->Value_Old.Data.uint32 = VAR->Enable_Old.Data.bit = 0;
	else {
		if (VAR->Enable_Old.Data.bit) { // Enable_Old = 1 // Нужно считать
			if ((IN->Value.Type & DataTypeMask) == KodFloat32) {
				if ((IN->Value.Data.float32 > VAR->Value_Old.Data.float32) && (VAR->Value_Old.Data.float32)) {
					if ((IN->MaxIncrement.Data.float32 == 0) || ((IN->Value.Data.float32 - VAR->Value_Old.Data.float32) <= IN->MaxIncrement.Data.float32))
						OUT->Counter.Data.float32 += (IN->Value.Data.float32 - VAR->Value_Old.Data.float32);
				}
			} else {
				if ((IN->Value.Data.uint32 > VAR->Value_Old.Data.uint32) && (VAR->Value_Old.Data.uint32)) {
					if ((IN->MaxIncrement.Data.uint32 == 0) || ((IN->Value.Data.uint32 - VAR->Value_Old.Data.uint32) <= IN->MaxIncrement.Data.uint32))
						OUT->Counter.Data.uint32 += (IN->Value.Data.uint32 - VAR->Value_Old.Data.uint32);
				}
			}
		}

		VAR->Value_Old.Data.uint32 = IN->Value.Data.uint32;
		VAR->Enable_Old.Data.bit = IN->Enable.Data.bit;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00078_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00078_IN_type);
    case(1):
        return sizeof(fb00078_VAR_type);
    case(2):
        return sizeof(fb00078_OUT_type);
    default:
        return 0;
    }
}
