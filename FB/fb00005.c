/* ФБ "Побитовое И" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00005.h"

void fb00005_exec(void) {
	fb00005_IN_type *IN = (fb00005_IN_type *) FBInputs;
	fb00005_OUT_type *OUT = (fb00005_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = IN->In1.Data.uint32 & IN->In2.Data.uint32;
}
