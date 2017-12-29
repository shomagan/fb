/* ФБ "Преобразователь 2x UInt16 -> UInt32/Float" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00075.h"

void fb00075_exec(void) {
	fb00075_IN_type *IN = (fb00075_IN_type *) FBInputs;
	fb00075_OUT_type *OUT = (fb00075_OUT_type *) FBOutputs;
    
	OUT->Output.Data.uint32 = IN->LoWord.Data.uint16 | ((u32)IN->HiWord.Data.uint16 << 16);

}
