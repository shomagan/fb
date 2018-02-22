/* ФБ "Преобразователь UInt16 -> 2x UInt8" */

 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00063.h"

void fb00063_exec(void) {

	fb00063_IN_type *IN = (fb00063_IN_type *) FBInputs;
	fb00063_OUT_type *OUT = (fb00063_OUT_type *) FBOutputs;
    
	OUT->HiByte.Data.uint8 = (u8) (IN->Input.Data.uint16 >> 8);
	OUT->LoByte.Data.uint8 = (u8) (IN->Input.Data.uint16 & 0xFF);

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00063_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00063_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00063_OUT_type);
    default:
        return 0;
    }
}
