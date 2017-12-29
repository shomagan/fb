/* ФБ "Чтение из батарейного домена" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00085.h"

void fb00085_exec(void) {
	fb00085_IN_type *IN = (fb00085_IN_type *) FBInputs;
	fb00085_OUT_type *OUT = (fb00085_OUT_type *) FBOutputs;


	if (IN->Address.Data.uint16 < MAX_BAT_MEM_SIZE) {
		OUT->Value.Data.uint32 = BateryMemFB32[IN->Address.Data.uint16];
	}

}
