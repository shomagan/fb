/* ФБ "Синхронизатор времени" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00044.h"

void fb00044_exec(void) {

	fb00044_IN_type *IN = (fb00044_IN_type *) FBInputs;

	if (IN->Enable.Data.bit)
		SysTimeWriteUNIX (IN->Time.Data.uint32);
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00044_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00044_IN_type);
    case(1):
        return 0;
    case(2):
        return 0;
    default:
        return 0;
    }
}
