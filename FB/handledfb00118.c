#include "../kernel.h"
#include "handledfb00118.h"
void fb00118_exec(void){}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00118_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00118_IN_type);
    case(1):
        return sizeof(fb00118_VAR_type);
    case(2):
        return sizeof(fb00118_OUT_type);
    default:
        return 0;
    }
}
