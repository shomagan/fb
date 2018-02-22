/* ФБ "Побитовое И" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00005.h"

void fb00005_exec(void) {
	fb00005_IN_type *IN = (fb00005_IN_type *) FBInputs;
	fb00005_OUT_type *OUT = (fb00005_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = IN->In1.Data.uint32 & IN->In2.Data.uint32;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00005_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00005_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00005_OUT_type);
    default:
        return 0;
    }
}
