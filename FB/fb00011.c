/* ФБ "Беззнаковое целое -> Float32" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00011.h"

void fb00011_exec(void) {
	fb00011_IN_type *IN = (fb00011_IN_type *) FBInputs;
	fb00011_OUT_type *OUT = (fb00011_OUT_type *) FBOutputs;
  
	OUT->Output.Data.float32 = Void2Float32 (&IN->Value);
}
