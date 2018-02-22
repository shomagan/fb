/* ФБ "Фильтр дискретный" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00067.h"

void fb00067_exec(void) {

	fb00067_IN_type *IN = (fb00067_IN_type *) FBInputs;
	fb00067_VAR_type *VAR = (fb00067_VAR_type *) FBVars;
	fb00067_OUT_type *OUT = (fb00067_OUT_type *) FBOutputs;
  
	if (KernelInfo.EventFlags.Bit.CfgFirstExec) OUT->Dout.Data.bit = IN->Din.Data.bit;

	if(IN->Din.Data.bit != OUT->Dout.Data.bit) {
		if (VAR->Timer.Data.uint32 < IN->Ust.Data.uint32) VAR->Timer.Data.uint32++;
		else{
			OUT->Dout.Data.bit = IN->Din.Data.bit;
		}
	}
	else VAR->Timer.Data.uint32 = 0;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00067_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00067_IN_type);
    case(1):
        return sizeof(fb00067_VAR_type);
    case(2):
        return sizeof(fb00067_OUT_type);
    default:
        return 0;
    }
}
