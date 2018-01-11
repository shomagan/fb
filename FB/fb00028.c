/* ФБ "Длительность импульса (в тактах)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00028.h"

void fb00028_exec (void)
{

	fb00028_IN_type *IN = (fb00028_IN_type *) FBInputs;
	fb00028_VAR_type *VAR = (fb00028_VAR_type *) FBVars;
	fb00028_OUT_type *OUT = (fb00028_OUT_type *) FBOutputs;

	if ((IN->Input.Type & DataTypeMask) == KodBit) { // Входная величина должна быть дискретной!
		OUT->Output.Data.uint32 = VAR->Counter.Data.uint32;   // Выводим счётчик

		if (IN->Input.Data.bit)           // На входе "1"
			VAR->Counter.Data.uint32++;     // Считаем длительность
		else                              // На входе "0"
			VAR->Counter.Data.uint32 = 0;   // Обнуляем счётчик
	} else
		OUT->Output.Data.uint32 = 0;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00028_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00028_IN_type);
    case(1):
        return sizeof(fb00028_VAR_type);
    case(2):
        return sizeof(fb00028_OUT_type);
    default:
        return 0;
    }
}
