/* ФБ "Вход - выход сквозной" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"
#include "handledfb00117.h"

void fb00117_exec(void) {

	fb00117_IN_type *IN = (fb00117_IN_type *) FBInputs;
	fb00117_OUT_type *OUT = (fb00117_OUT_type *) FBOutputs;
	u8 i;
	
	for (i=0; (i<(FB_N_In))&&(i<FB_N_Out); i++) {
		OUT->Output[i].Data.uint32 = IN->Input[i].Data.uint32;
	}	
	
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00117_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00117_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00117_OUT_type);
    default:
        return 0;
    }
}
