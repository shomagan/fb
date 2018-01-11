/* ФБ "Массив int8/16 -> 1 bit/int/float" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00055.h"

void fb00055_exec(void) {
	fb00055_IN_type *IN = (fb00055_IN_type *) FBInputs;
	fb00055_OUT_type *OUT = (fb00055_OUT_type *) FBOutputs;

	u8 InputType = IN->InArray[0].Type;
	u8 InputNum = 0;
	u8 i;
	sTempValue TempValue;

	OUT->Out.Data.uint32 = 0;
  
	if (InputType) {
		// Определяем размер входного массива и тип элементов
		for (i=1; i < FB55_InArrayMaxSize; i++)
			if (IN->InArray[i].Type == InputType)
				InputNum++;

		// Заполняем объединение
		if (IN->BigEndian.Data.bit) { // BigEndian
			if ((InputType & DataTypeMask)==KodInt8) {       // Массив байт
				for(i = 1; i < 4; i++)
					TempValue.in8[i] = IN->InArray[i].Data.uint8;
			} else if ((InputType & DataTypeMask) == KodInt16) { // Массив 2-байтных слов int16
				TempValue.in16[0] = IN->InArray[0].Data.uint16;
				TempValue.in16[1] = IN->InArray[1].Data.uint16;
			} else                                            // Массив 4-байтных слов
				TempValue.in32 = IN->InArray[0].Data.uint32;
		} else {                           // LittleEndian
			if ((InputType & DataTypeMask) == KodInt8) {       // Массив байт
				for (i=1; i < 4; i++)
					TempValue.in8[3-i] = IN->InArray[3-i].Data.uint8;
			} else if((InputType & DataTypeMask) == KodInt16) { // Массив 2-байтных слов int16
				TempValue.in16[0] = IN->InArray[1].Data.uint16;
				TempValue.in16[1] = IN->InArray[0].Data.uint16;
			} else                                            // Массив 4-байтных слов
				TempValue.in32 = IN->InArray[0].Data.uint32;
		}
    
		// Выдаём значение на выход
		switch (OUT->Out.Type & DataTypeMask) {
		case KodInt8:
			OUT->Out.Data.uint8 = TempValue.in8[0];
			break;
		case KodInt16:
			OUT->Out.Data.uint16 = TempValue.in16[0];
			break;
		case KodInt32:
			OUT->Out.Data.uint32 = TempValue.in32;
			break;
		case KodFloat32:
			OUT->Out.Data.float32 = TempValue.fl32;
			break;
		}
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00055_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00055_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00055_OUT_type);
    default:
        return 0;
    }
}
