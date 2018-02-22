/* ФБ "Преобразователь UInt32/Float -> 2x UInt16" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00073.h"

void fb00073_exec(void) {

	fb00073_IN_type *IN = (fb00073_IN_type *) FBInputs;
	fb00073_OUT_type *OUT = (fb00073_OUT_type *) FBOutputs;
    
	OUT->HiWord.Data.uint16 = (u16) (IN->Input.Data.uint32 >> 16);
	OUT->LoWord.Data.uint16 = (u16) (IN->Input.Data.uint32 & 0xFFFF);

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00073_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00073_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00073_OUT_type);
    default:
        return 0;
    }
}
