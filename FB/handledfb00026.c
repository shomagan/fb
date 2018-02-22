/* ФБ "Системное время: секунд от начала суток" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00026.h"

void fb00026_exec(void) {

	fb00026_OUT_type *OUT = (fb00026_OUT_type *) FBOutputs;

	OUT->SystemTime.Data.uint32 = (FB32blok.vars.Cnt1Chas * 3600) + (FB32blok.vars.Cnt1Min * 60) + FB32blok.vars.Cnt1Sec;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00026_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00026_OUT_type);
    default:
        return 0;
    }
}
