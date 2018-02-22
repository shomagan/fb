/* ФБ "Преобразователь в массив" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00060.h"

void fb00060_exec(void) {
	fb00060_IN_type *IN = (fb00060_IN_type *) FBInputs;
	fb00060_OUT_type *OUT = (fb00060_OUT_type *) FBOutputs;
	
	u16 i;
	
	for (i = 0; i < FB_N_In; i++)
		OUT->Output[i].Data.uint32 = IN->Input[i].Data.uint32;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00060_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00060_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00060_OUT_type);
    default:
        return 0;
    }
}
