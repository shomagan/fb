#include "../kernel.h"
#include "handledfb00122.h"
void fb00122_exec(void){}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00122_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00122_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00122_OUT_type);
    default:
        return 0;
    }
}
