/* ФБ "Таймер: секунд от начала периода" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00027.h"

void fb00027_exec (void)
{

	fb00027_IN_type *IN = (fb00027_IN_type *) FBInputs;
	fb00027_VAR_type *VAR = (fb00027_VAR_type *) FBVars;
	fb00027_OUT_type *OUT = (fb00027_OUT_type *) FBOutputs;

	if (IN->Reset.Data.bit)
		VAR->StartTime.Data.uint32 = GetSystemTime_t();
  
	OUT->PeriodTime.Data.uint32 = GetSystemTime_t() - VAR->StartTime.Data.uint32;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00027_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00027_IN_type);
    case(1):
        return sizeof(fb00027_VAR_type);
    case(2):
        return sizeof(fb00027_OUT_type);
    default:
        return 0;
    }
}
