/* ФБ "Счётчик" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00037.h"

void fb00037_exec(void)
{

  fb00037_IN_type *IN = (fb00037_IN_type *) FBInputs;
  fb00037_VAR_type *VAR = (fb00037_VAR_type *) FBVars;
  fb00037_OUT_type *OUT = (fb00037_OUT_type *) FBOutputs;
  
  if (IN->Reset.Data.bit || KernelInfo.EventFlags.Bit.CfgFirstExec) {  // Reset
		//if ((OUT->Counter.Type & DataTypeMask) == KodFloat32) {OUT->Counter.Data.float32=0;}
			//else {OUT->Counter.Data.uint32 = VAR->Value_Old.Data.uint32 = VAR->Enable_Old.Data.bit = 0;}
		OUT->Counter.Data.uint32 = 0;
  } else {
    if (VAR->Enable_Old.Data.bit) { // Enable_Old = 1 // Нужно считать
      if ((IN->Value.Type & DataTypeMask) == KodFloat32) {
        if ((VAR->Value_Old.Data.float32)){
          OUT->Counter.Data.float32 += (IN->Value.Data.float32 - VAR->Value_Old.Data.float32);}
      } else {
        if ((IN->Value.Data.uint32 > VAR->Value_Old.Data.uint32) && (VAR->Value_Old.Data.uint32)){
          OUT->Counter.Data.uint32 += (IN->Value.Data.uint32 - VAR->Value_Old.Data.uint32);}
      }
    }
		//VAR->Value_Old.Data.float32 = IN->Value.Data.float32;
    VAR->Value_Old.Data.uint32 = IN->Value.Data.uint32;
    VAR->Enable_Old.Data.bit = IN->Enable.Data.bit;
  }
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00037_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00037_IN_type);
    case(1):
        return sizeof(fb00037_VAR_type);
    case(2):
        return sizeof(fb00037_OUT_type);
    default:
        return 0;
    }
}
