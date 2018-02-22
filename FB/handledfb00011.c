/* ФБ "Беззнаковое целое -> Float32" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00011.h"

void fb00011_exec(void) {
	fb00011_IN_type *IN = (fb00011_IN_type *) FBInputs;
	fb00011_OUT_type *OUT = (fb00011_OUT_type *) FBOutputs;
  
	OUT->Output.Data.float32 = Void2Float32 (&IN->Value);
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00011_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00011_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00011_OUT_type);
    default:
        return 0;
    }
}
