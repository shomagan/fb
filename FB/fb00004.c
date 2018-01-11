/* ФБ "Логическое НЕ" (основной файл) */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "FB00004.h"

void FB00004_exec(void) {
    fb00004_IN_type *IN = (fb00004_IN_type *) FBInputs;
    fb00004_OUT_type *OUT = (fb00004_OUT_type *) FBOutputs;

    OUT->Out.Data.bit = (IN->In1.Data.bit) ? 0 : 1;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00004_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00004_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00004_OUT_type);
    default:
        return 0;
    }
}
