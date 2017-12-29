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
