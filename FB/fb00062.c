/* ФБ "Фиксатор переменной (ОЗУ)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00062.h"

void fb00062_exec(void) {

	fb00062_IN_type *IN = (fb00062_IN_type *) FBInputs;
	fb00062_OUT_type *OUT = (fb00062_OUT_type *) FBOutputs;

	u16 i;
	
	if (IN->Fix.Data.bit) {
		if((FB_N_In<50)&&(FB_N_In>0)){		// Ограничение количества входов.
			for (i = 0; i<(FB_N_In-1); i++) OUT->Var_Out[i].Data.uint32 = IN->Var_In[i].Data.uint32;
		}
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00062_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00062_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00062_OUT_type);
    default:
        return 0;
    }
}
