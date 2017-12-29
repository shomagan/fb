/* ФБ "RS-триггер с приоритетным 0" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00041.h"

void fb00041_exec(void) {

	fb00041_IN_type *IN = (fb00041_IN_type *) FBInputs;
	fb00041_OUT_type *OUT = (fb00041_OUT_type *) FBOutputs;

	if (((IN->R.Type & DataTypeMask)==KodBit) && ((IN->S.Type & DataTypeMask)==KodBit)) { // Если на входах битовые значения
		if (IN->R.Data.bit) {      // Reset
			OUT->T.Data.bit = 0;
			OUT->nT.Data.bit = 1;
		} else if (IN->S.Data.bit) { // Set
			OUT->T.Data.bit = 1;
			OUT->nT.Data.bit = 0;
		}
	}
}
