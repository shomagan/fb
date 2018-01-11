/* ФБ "Запись системной настройки" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00057.h"

void fb00057_exec(void) {

	fb00057_IN_type *IN = (fb00057_IN_type *) FBInputs;
	fb00057_OUT_type *OUT = (fb00057_OUT_type *) FBOutputs;
  
	if (IN->ToWrite.Data.bit)
		OUT->ErrorCode.Data.uint16 = SetSystemOption(IN->Address.Data.uint32, IN->Value.Data.uint16);

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00057_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00057_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00057_OUT_type);
    default:
        return 0;
    }
}
