/* ФБ "Присутствие I2C-модуля на шине" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00039.h"

void fb00039_exec(void) {
/*	fb00039_IN_type *IN = (fb00039_IN_type *) FBInputs;
	fb00039_OUT_type *OUT = (fb00039_OUT_type *) FBOutputs;

	if(IN->ModuleAddr.Data.uint8 > 1) { // Не COM1/COM2
		if (IN->ModuleAddr.Data.uint8 & 0x01) // Адрес модуля нечётный - недопустимый
			OUT->Connected.Data.bit = 0;
		else	                                    // Адрес чётный - допустимый
			OUT->Connected.Data.bit = TWIModulePresented(IN->ModuleAddr.Data.uint8);
	} else // Первые 2 адреса заняты внутренними портами
		OUT->Connected.Data.bit = 1; // Всегда присутствуют в CPU32
*/
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00039_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00039_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00039_OUT_type);
    default:
        return 0;
    }
}
