/* ФБ "Системное время: секунд от начала минуты" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00024.h"

void fb00024_exec(void) {

	fb00024_OUT_type *OUT = (fb00024_OUT_type *) FBOutputs;
  
	OUT->SystemTime.Data.uint32 = FB32blok.vars.Cnt1Sec;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00024_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00024_OUT_type);
    default:
        return 0;
    }
}
