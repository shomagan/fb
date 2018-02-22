/* ФБ "Логическое НЕ" (основной файл) */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledFB00004.h"

void FB00004_exec(void) {
	FB00004_IN_type *IN = (FB00004_IN_type *) FBInputs;
	FB00004_OUT_type *OUT = (FB00004_OUT_type *) FBOutputs;

	OUT->Out.Data.bit = (IN->In1.Data.bit) ? 0 : 1;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00004_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return 0;
    default:
        return 0;
    }
}
