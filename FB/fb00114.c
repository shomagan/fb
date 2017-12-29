/* ФБ "Преобразователь UInt32 -> 4x UInt8" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"
#include "fb00114.h"

void fb00114_exec(void) {

	fb00114_IN_type *IN = (fb00114_IN_type *) FBInputs;
	fb00114_OUT_type *OUT = (fb00114_OUT_type *) FBOutputs;
    
	OUT->One.Data.uint8 = (u8) (IN->Input.Data.uint32 >> 24);
	OUT->Two.Data.uint8 = (u8) (IN->Input.Data.uint32 >> 16);
	OUT->Three.Data.uint8 = (u8) (IN->Input.Data.uint32 >> 8);
	OUT->Four.Data.uint8 = (u8) (IN->Input.Data.uint32);	

}
