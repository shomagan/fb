#include "../kernel.h"
#include "handledfb00104.h"
void fb00104_exec(void){}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00104_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00104_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00104_OUT_type);
    default:
        return 0;
    }
}
