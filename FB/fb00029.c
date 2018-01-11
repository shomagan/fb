/* ФБ "Триггер со сбросом через N тактов" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00029.h"

void fb00029_exec (void)
{
	fb00029_IN_type *IN = (fb00029_IN_type *) FBInputs;
	fb00029_VAR_type *VAR = (fb00029_VAR_type *) FBVars;
	fb00029_OUT_type *OUT = (fb00029_OUT_type *) FBOutputs;

	if (VAR->Tics.Data.uint32) {
		OUT->Output.Data.bit = 1;
		VAR->Tics.Data.uint32--;
	} else {
		OUT->Output.Data.bit = 0;
	}
 	if (IN->Input.Data.bit)
 		VAR->Tics.Data.uint32 = IN->SetTime.Data.uint32;
	
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00029_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00029_IN_type);
    case(1):
        return sizeof(fb00029_VAR_type);
    case(2):
        return sizeof(fb00029_OUT_type);
    default:
        return 0;
    }
}
