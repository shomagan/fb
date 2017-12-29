/* ФБ "Чтение системной настройки" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00056.h"

void fb00056_exec(void) {
	fb00056_IN_type *IN = (fb00056_IN_type *) FBInputs;
	fb00056_OUT_type *OUT = (fb00056_OUT_type *) FBOutputs;
  
	u16 TempValue;

	switch (OUT->Value.Type & DataTypeMask) {
	case KodInt8:
	case KodInt16:
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32, &TempValue);
  	OUT->Value.Data.uint16 = TempValue; 
    break;
	case KodInt32:
	case KodTime32:
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32, &TempValue);
  	OUT->Value.Data.uint32 = TempValue;
  	OUT->ErrorCode.Data.uint16 = GetSystemOption (IN->Address.Data.uint32+1, &TempValue);
  	OUT->Value.Data.uint32 |= ((u32)(TempValue))<<16; 
		break;
	case KodFloat32:
    LedErrorOn(100);
		break;
	default:
		break;    
	}

}
