/* ФБ "Одновибратор по фронту" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00043.h"

void fb00043_exec(void) {

	fb00043_IN_type *IN = (fb00043_IN_type *) FBInputs;
	fb00043_VAR_type *VAR = (fb00043_VAR_type *) FBVars;
	fb00043_OUT_type *OUT = (fb00043_OUT_type *) FBOutputs;
  
	if (OUT->Out.Data.bit) { // OUT="1"
		if (OUT->Timer.Data.uint32)   // Отсчитываем импульс
			OUT->Timer.Data.uint32--; 
    
		if (!OUT->Timer.Data.uint32)  // Время удержания закончилось
			OUT->Out.Data.bit = 0;      // Импульс отсчитан - обнуляем выход
	}

	if ((IN->In.Data.bit) && (VAR->In_Old.Data.bit == 0)) {    // IN="1", IN_Old="0" // Фронт
		OUT->Out.Data.bit = 1;
		OUT->Timer.Data.uint32 = IN->Tics.Data.uint32;
	}
  
	VAR->In_Old.Data.bit = IN->In.Data.bit;   // Обновляем состояние In_Old
}

/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00043_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00043_IN_type);
    case(1):
        return sizeof(fb00043_VAR_type);
    case(2):
        return sizeof(fb00043_OUT_type);
    default:
        return 0;
    }
}
