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
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00114_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00114_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00114_OUT_type);
    default:
        return 0;
    }
}
