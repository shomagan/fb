/* ФБ "Преобразователь UInt32/Float -> 2x UInt16" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00073.h"

void fb00073_exec(void) {

	fb00073_IN_type *IN = (fb00073_IN_type *) FBInputs;
	fb00073_OUT_type *OUT = (fb00073_OUT_type *) FBOutputs;
    
	OUT->HiWord.Data.uint16 = (u16) (IN->Input.Data.uint32 >> 16);
	OUT->LoWord.Data.uint16 = (u16) (IN->Input.Data.uint32 & 0xFFFF);

}
