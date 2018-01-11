#include "../kernel.h"
#include "fb00105.h"
void fb00105_exec(void){}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00105_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00105_IN_type);
    case(1):
        return sizeof(fb00105_VAR_type);
    case(2):
        return sizeof(fb00105_OUT_type);
    default:
        return 0;
    }
}
