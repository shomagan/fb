/* ФБ "Логическое И" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00001.h"

void fb00001_exec(void) {
	u8	i;
	
	fb00001_IN_type *IN = (fb00001_IN_type *) FBInputs;
	fb00001_OUT_type *OUT = (fb00001_OUT_type *) FBOutputs;
    
	if((FB_N_In <= MaxInputs) && (FB_N_In > 1)) {
		OUT->Out.Data.bit = 1;
		for(i = 0; i < FB_N_In; i++) {
			if(!IN->Inputs[i].Data.bit) {
				OUT->Out.Data.bit = 0;
				break;
			}
		}
	} else{
  	OUT->Out.Data.bit = 0;
  }
}
