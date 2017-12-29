/* ФБ "Преобразователь Int->Float32" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00074.h"

void fb00074_exec(void) {

	fb00074_IN_type *IN = (fb00074_IN_type *) FBInputs;
	fb00074_OUT_type *OUT = (fb00074_OUT_type *) FBOutputs;
    
	OUT->Output.Data.float32 = (Flo32) IN->Input.Data.uint32;

}
