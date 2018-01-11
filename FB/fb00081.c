/* ФБ "Весовой импульс с счетчика" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00081.h"

void fb00081_exec(void) {
/*	fb00078_IN_type *IN = (fb00078_IN_type *) FBInputs;
	fb00078_VAR_type *VAR = (fb00078_VAR_type *) FBVars;
	fb00078_OUT_type *OUT = (fb00078_OUT_type *) FBOutputs;
*/
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00081_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00081_IN_type);
    case(1):
        return sizeof(fb00081_VAR_type);
    case(2):
        return sizeof(fb00081_OUT_type);
    default:
        return 0;
    }
}
