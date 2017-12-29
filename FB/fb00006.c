/* ФБ "Побитовое ИЛИ" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00006.h"

void fb00006_exec(void) {
	fb00006_IN_type *IN = (fb00006_IN_type *) FBInputs;
	fb00006_OUT_type *OUT = (fb00006_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = IN->In1.Data.uint32 | IN->In2.Data.uint32;

}
