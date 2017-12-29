/* ФБ "Преобразователь в массив" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00060.h"

void fb00060_exec(void) {
	fb00060_IN_type *IN = (fb00060_IN_type *) FBInputs;
	fb00060_OUT_type *OUT = (fb00060_OUT_type *) FBOutputs;
	
	u16 i;
	
	for (i = 0; i < FB_N_In; i++)
		OUT->Output[i].Data.uint32 = IN->Input[i].Data.uint32;
}
