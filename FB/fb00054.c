/* ФБ "Компоновщик данных в блоки" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00054.h"

void fb00054_exec(void)
{
	fb00054_IN_type *IN = (fb00054_IN_type *) FBInputs;
	fb00054_OUT_type *OUT = (fb00054_OUT_type *) FBOutputs;

	sTempInput TempInput;

	u16 InIdx, OutByteIdx, BlokByteIdx;

	u8 MaskNum;          // Номер входа с маской
	u8 MaskBit;          // Номер бита в текущей маске
	u8 InVarSize;        // Размер текущей входной переменной в байтах
	u8 i;
	
	OutByteIdx = 0;
	
	for (InIdx=0; InIdx < (FB_N_In-FB54_InMaskSize-2); InIdx++) { // Пробегаемся по входам
		InVarSize = VarSize(IN->InArrays[InIdx].Type);
		TempInput.in32 = IN->InArrays[InIdx].Data.uint32;

		MaskNum = InIdx / FB54_Mask_FlagsNum; // Вычисляем номер входа с масками
		MaskBit = InIdx % FB54_Mask_FlagsNum; // Вычисляем номер бита в этом входе

		if (IN->Masks[MaskNum].Data.uint32 & (1 << MaskBit)) {  // Если текущий байт нужно включить в выходной блок
			if ((IN->inBlokSize.Data.uint32 - BlokByteIdx) < InVarSize) { // Не хватает места в текущем блоке
				BlokByteIdx = 0;  // Обнуляем индекс в текущем блоке
				OutByteIdx += (IN->inBlokSize.Data.uint32-BlokByteIdx);
			}
      
			for (i = 0; i < InVarSize; i++) {
				if(IN->BigEndian.Data.bit)   // BigEndian
					OUT->Bloks[OutByteIdx].Data.uint8 = TempInput.in8[InVarSize-i];
				else    	                         // LittleEndian
					OUT->Bloks[OutByteIdx].Data.uint8 = TempInput.in8[i];

				BlokByteIdx++;
			}
		}
		InIdx++;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00054_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00054_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00054_OUT_type);
    default:
        return 0;
    }
}
