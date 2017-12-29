/* ФБ "Детектор изменений" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00069.h"

void fb00069_exec(void) {

	fb00069_IN_type *IN = (fb00069_IN_type *) FBInputs;
	fb00069_OUT_type *OUT = (fb00069_OUT_type *) FBOutputs;

	u16 i;
	
	OUT->Detected.Data.bit = 0;
  
	for(i = 0; i < FB_N_In; i++) {
		if(IN->Input[i].Data.uint32 != OUT->Output[i].Data.uint32) {
			OUT->Detected.Data.bit = 1;
			OUT->Output[i].Data.uint32 = IN->Input[i].Data.uint32;
		}
	}  

}
