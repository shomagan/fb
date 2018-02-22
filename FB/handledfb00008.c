/* ФБ "Побитовое НЕ" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00008.h"

void fb00008_exec(void) {
	fb00008_IN_type *IN = (fb00008_IN_type *) FBInputs;
	fb00008_OUT_type *OUT = (fb00008_OUT_type *) FBOutputs;

	OUT->Out.Data.uint32 = ~IN->In1.Data.uint32;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00008_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00008_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00008_OUT_type);
    default:
        return 0;
    }
}
