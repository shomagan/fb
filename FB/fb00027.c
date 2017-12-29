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
