/* ФБ "Среднее за N тактов" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00019.h"

void fb00019_exec(void) {

	fb00019_IN_type *IN = (fb00019_IN_type *) FBInputs;
	fb00019_VAR_type *VAR = (fb00019_VAR_type *) FBVars;
	fb00019_OUT_type *OUT = (fb00019_OUT_type *) FBOutputs;

	if ((IN->N.Type & DataTypeMask) != KodFloat32) {
		if (VAR->I.Data.uint32 >= IN->N.Data.uint32) {
			if ((OUT->Output.Type & DataTypeMask) == KodFloat32)
				OUT->Output.Data.float32 = VAR->Summ.Data.float32 / VAR->I.Data.uint32;
			else
				OUT->Output.Data.uint32 = VAR->Summ.Data.uint32 / VAR->I.Data.uint32;
      
			VAR->I.Data.uint32 = 0;
			VAR->Summ.Data.uint32 = 0;
		} else {
			if ((OUT->Output.Type & DataTypeMask) != KodFloat32)
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
*/    unsigned int fb00019_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00019_IN_type);
    case(1):
        return sizeof(fb00019_VAR_type);
    case(2):
        return sizeof(fb00019_OUT_type);
    default:
        return 0;
    }
}
