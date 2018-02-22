/* ФБ преобразовать 2хuint16 -> uint32 */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00092.h"

void fb00092_exec(void)
{

	fb00092_IN_type *IN = (fb00092_IN_type *) FBInputs;
	fb00092_OUT_type *OUT = (fb00092_OUT_type *) FBOutputs;
  
	OUT->OutNum.Data.uint32 = (u32)(((IN->BigIn16.Data.uint16 << 16) & 0xffff0000) | IN->LitIn16.Data.uint16);
 }
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00092_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00092_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00092_OUT_type);
    default:
        return 0;
    }
}
