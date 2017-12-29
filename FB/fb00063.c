/* ФБ "Преобразователь UInt16 -> 2x UInt8" */

#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00063.h"

void fb00063_exec(void) {

	fb00063_IN_type *IN = (fb00063_IN_type *) FBInputs;
	fb00063_OUT_type *OUT = (fb00063_OUT_type *) FBOutputs;
    
	OUT->HiByte.Data.uint8 = (u8) (IN->Input.Data.uint16 >> 8);
	OUT->LoByte.Data.uint8 = (u8) (IN->Input.Data.uint16 & 0xFF);

}
