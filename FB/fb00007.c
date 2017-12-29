/* ФБ "Побитовое исключающее ИЛИ" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00007.h"

void fb00007_exec(void) {
	fb00007_IN_type *IN = (fb00007_IN_type *) FBInputs;
	fb00007_OUT_type *OUT = (fb00007_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = IN->In1.Data.uint32 ^ IN->In2.Data.uint32;
}
