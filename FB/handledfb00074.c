/* ФБ "Преобразователь Int->Float32" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00074.h"

void fb00074_exec(void) {

	fb00074_IN_type *IN = (fb00074_IN_type *) FBInputs;
	fb00074_OUT_type *OUT = (fb00074_OUT_type *) FBOutputs;
    
	OUT->Output.Data.float32 = (Flo32) IN->Input.Data.uint32;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00074_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00074_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00074_OUT_type);
    default:
        return 0;
    }
}
