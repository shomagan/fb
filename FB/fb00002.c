/* ФБ "Логическое ИЛИ" (основной файл) */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00002.h"

void fb00002_exec(void) {
	u8	i;
	
	fb00002_IN_type *IN = (fb00002_IN_type *) FBInputs;
	fb00002_OUT_type *OUT = (fb00002_OUT_type *) FBOutputs;
    
	if((FB_N_In <= MaxInputs) && (FB_N_In > 1)) {
		OUT->Out.Data.bit = 0;
		for(i = 0; i < FB_N_In; i++) {
			if(IN->Inputs[i].Data.bit) {
				OUT->Out.Data.bit = 1;
				break;
			}
		}
	} else
		OUT->Out.Data.bit = 0;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00002_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00002_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00002_OUT_type);
    default:
        return 0;
    }
}
