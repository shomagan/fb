/* ФБ "Преобразователь 2x UInt16 -> UInt32/Float" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00075.h"

void fb00075_exec(void) {
	fb00075_IN_type *IN = (fb00075_IN_type *) FBInputs;
	fb00075_OUT_type *OUT = (fb00075_OUT_type *) FBOutputs;
    
	OUT->Output.Data.uint32 = IN->LoWord.Data.uint16 | ((u32)IN->HiWord.Data.uint16 << 16);

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00075_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00075_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00075_OUT_type);
    default:
        return 0;
    }
}
