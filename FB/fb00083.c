/* ФБ "Архиватор R7 "Состояние DI КП КТПН" (тип 18)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00083.h"
/*создает архив подробного состояния КП КТПН
* NChan;		// uint8	// Номер канала
* AuthorArch;		// byte     // Инициатор создания архива
* SostDI;		// uint16   // Текущее состояние DI
* PrevSostDI;		// uint16   // Предыдущее состояние DI
* DurationSostDI;		// uint32   // Продолжительность предыдущего состояния DI
* EventTime;		// time     // Время возникновения события
*/
void fb00083_exec(void) {
	fb00083_IN_type *IN = (fb00083_IN_type *) FBInputs;
	fb00083_OUT_type *OUT = (fb00083_OUT_type *) FBOutputs;

	u8 R7Buff[R7_BodySize];		//Размер тела архива =54
	u8 k;
	
	OUT->Ok.Data.bit = 0;

	if (IN->CmdArch.Data.bit) {		// Если архивирование замера разрешено
		// Проверяем что все входы целочисленные
		if (((IN->AuthorArch.Type & DataTypeMask) != KodFloat32) && ((IN->SostDI.Type & DataTypeMask) != KodFloat32) && \
			((IN->PrevSostDI.Type & DataTypeMask) != KodFloat32) && ((IN->DurationSostDI.Type & DataTypeMask) != KodFloat32) && \
			((IN->EventTime.Type & DataTypeMask) != KodFloat32)) {
			
      
			R7Buff[0] = IN->NChan.Data.uint8;
			R7Buff[1] = IN->AuthorArch.Data.uint8;		// Инициатор архива

			R7Buff[2] = (u8) (IN->SostDI.Data.uint16 & 0xFF);		// Младший байт SostDI
			R7Buff[3] = (u8) (IN->SostDI.Data.uint16 >> 8);		// Старший байт SostDI
			R7Buff[4] = (u8) (IN->PrevSostDI.Data.uint16 & 0xFF);		// Младший байт PrevSostDI
			R7Buff[5] = (u8) (IN->PrevSostDI.Data.uint16 >> 8);		// Старший байт PrevSostDI

			R7Buff[6] = (u8) (IN->DurationSostDI.Data.uint32 & 0xFF);  	// Длительность предыдущего состояния мл.
			R7Buff[7] = (u8) (IN->DurationSostDI.Data.uint32 >> 8);		//
			R7Buff[8] = (u8) (IN->DurationSostDI.Data.uint32 >> 16);		//
			R7Buff[9] = (u8) (IN->DurationSostDI.Data.uint32 >> 24);		// Длительность предыдущего состояния ст.

			R7Buff[10] = (u8) (IN->EventTime.Data.uint32 & 0xFF);		// Время возникновения события мл.
			R7Buff[11] = (u8) (IN->EventTime.Data.uint32 >> 8);		// 
			R7Buff[12] = (u8) (IN->EventTime.Data.uint32 >> 16);		// 
			R7Buff[13] = (u8) (IN->EventTime.Data.uint32 >> 24);		// Время возникновения события ст.

			for (k = 14; k < R7_BodySize; k++) R7Buff[k] = 0;

			NewQ_Arc_R7(R7Buff, 18);		// Передаём тело архива архиватору
			OUT->Ok.Data.bit = 1;
		}  
	}
}
