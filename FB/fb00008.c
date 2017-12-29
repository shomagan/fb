/* ФБ "Побитовое НЕ" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00008.h"

void fb00008_exec(void) {
	fb00008_IN_type *IN = (fb00008_IN_type *) FBInputs;
	fb00008_OUT_type *OUT = (fb00008_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = ~IN->In1.Data.uint32;
}
