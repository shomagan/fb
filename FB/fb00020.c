/* ФБ "Среднее за N секунд" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00020.h"

void fb00020_exec (void)
{

	fb00020_IN_type *IN = (fb00020_IN_type *) FBInputs;
	fb00020_VAR_type *VAR = (fb00020_VAR_type *) FBVars;
	fb00020_OUT_type *OUT = (fb00020_OUT_type *) FBOutputs;

	if((IN->N.Type & DataTypeMask) != KodFloat32) {
		if ((GetSystemTime_t () - VAR->StartTime.Data.uint32) > IN->N.Data.uint32) { // N секунд прошло
			if((OUT->Output.Type & DataTypeMask) == KodFloat32)
				OUT->Output.Data.float32 = VAR->Summ.Data.float32 / IN->N.Data.uint32;
			else
				OUT->Output.Data.uint32 = VAR->Summ.Data.uint32 / IN->N.Data.uint32;
      
			VAR->StartTime.Data.uint32 = GetSystemTime_t();
			VAR->I.Data.uint32 = VAR->Summ.Data.uint32 = 0;
		} else if ((GetSystemTime_t () - VAR->StartTime.Data.uint32) > VAR->I.Data.uint32) { // Сменилась секунда
			if((OUT->Output.Type & DataTypeMask) != KodFloat32)
				VAR->Summ.Data.float32 += IN->Value.Data.float32;
			else
				VAR->Summ.Data.uint32 += IN->Value.Data.uint32;
      
			VAR->I.Data.uint32++;
		}
	} else
		OUT->Output.Data.uint32 = 0;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00020_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00020_IN_type);
    case(1):
        return sizeof(fb00020_VAR_type);
    case(2):
        return sizeof(fb00020_OUT_type);
    default:
        return 0;
    }
}
