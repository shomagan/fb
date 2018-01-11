/* ФБ "Триггер со сбросом" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00042.h"

void fb00042_exec(void) {

	fb00042_IN_type *IN = (fb00042_IN_type *) FBInputs;
	fb00042_OUT_type *OUT = (fb00042_OUT_type *) FBOutputs;
  
	if ((IN->In.Type & DataTypeMask)==KodBit) { // Если на входе битовое значение
		if((IN->In.Data.bit) && (OUT->Out.Data.bit))
			OUT->ROut.Data.bit = 0;
	
		OUT->Out.Data.bit = IN->In.Data.bit;
	}
}

/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00042_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00042_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00042_OUT_type);
    default:
        return 0;
    }
}
