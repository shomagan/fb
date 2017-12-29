/* ФБ "Логическое НЕ" (основной файл) */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "FB00004.h"

void FB00004_exec(void) {
	FB00004_IN_type *IN = (FB00004_IN_type *) FBInputs;
	FB00004_OUT_type *OUT = (FB00004_OUT_type *) FBOutputs;

	OUT->Out.Data.bit = (IN->In1.Data.bit) ? 0 : 1;
}
