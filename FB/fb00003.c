/* ФБ "Логическое исключающее ИЛИ" (основной файл) */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00003.h"

void fb00003_exec (void)
{
	
	u8 n, i;
	fb00003_IN_type *IN = (fb00003_IN_type *) FBInputs;
	fb00003_OUT_type *OUT = (fb00003_OUT_type *) FBOutputs;

	n = 0;

	if((FB_N_In <= MaxInputs) && (FB_N_In > 1)) {
		if(FB_N_In == 2) {
			OUT->Out.Data.bit = IN->Inputs[0].Data.bit ^ IN->Inputs[1].Data.bit;
		} else {
			OUT->Out.Data.bit = 0;
			for(i = 0; i < FB_N_In; i++) {
				if(IN->Inputs[i].Data.bit)
					n++;
			}
			OUT->Out.Data.bit = (n && (n!=2)) ? 1 : 0;
		}
	} else
		OUT->Out.Data.bit = 0;
}
