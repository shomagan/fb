/* ФБ "Вход - выход сквозной" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"
#include "fb00117.h"

void fb00117_exec(void) {

	fb00117_IN_type *IN = (fb00117_IN_type *) FBInputs;
	fb00117_OUT_type *OUT = (fb00117_OUT_type *) FBOutputs;
	u8 i;
	
	for (i=0; (i<(FB_N_In))&&(i<FB_N_Out); i++) {
		OUT->Output[i].Data.uint32 = IN->Input[i].Data.uint32;
	}	
	
}
