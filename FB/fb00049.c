/* ФБ "Архиватор R7 "Изменение состояния объекта" (тип 17, подтип 4)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"


#include "fb00049.h"
/*Создает архив при изменении входной переменной uint16
*архив содержит новое и старое значение плюс время события
*/
void fb00049_exec(void) {
	fb00049_IN_type *IN = (fb00049_IN_type *) FBInputs;
	fb00049_OUT_type *OUT = (fb00049_OUT_type *) FBOutputs;
  
	u8 R7Buff[R7_BodySize];

	OUT->Ok.Data.bit = 0;

	if (IN->Enable.Data.bit) { // Если архивирование замера разрешено
		// Проверяем что все входы целочисленные

		if (((IN->Sost16.Type & DataTypeMask)!= KodFloat32) && ((OUT->OldSost16.Type & DataTypeMask)!= KodFloat32)) {
			if (IN->Sost16.Data.uint16 != OUT->OldSost16.Data.uint16) {
				R7Buff[0] = 0;                                            // Номер канала
				R7Buff[1] = 0;                                            // В R5 здесь были номера последней записанной
				R7Buff[2] = 0;                                            // и последней прочитанной записей R5
				R7Buff[3] = 4;                                            // Тип записи (из R5) = 4 (Состояние объекта)
				R7Buff[4] = 0;                                            // "xxx"
				R7Buff[5] = (char) (IN->Sost16.Data.uint16 & 0xFF);       // Состояние новое мл.
				R7Buff[6] = (char) (IN->Sost16.Data.uint16 >> 8);         // Состояние новое ст.
				R7Buff[7] = (char) (OUT->OldSost16.Data.uint16 & 0xFF);   // Состояние старое мл.
				R7Buff[8] = (char) (OUT->OldSost16.Data.uint16 >> 8);     // Состояние старое ст.
				R7Buff[9] = FB32blok.vars.Cnt1Sec;      // Время события - сек
				R7Buff[10] = FB32blok.vars.Cnt1Min;     // Время начала - мин
				R7Buff[11] = FB32blok.vars.Cnt1Chas;    // Время начала - час
				R7Buff[12] = FB32blok.vars.Cnt1Den;     // Время начала - день
				R7Buff[13] = FB32blok.vars.Cnt1Mes;     // Время начала - мес
				R7Buff[14] = FB32blok.vars.Cnt1God;     // Время начала - год c 1980
				R7Buff[15] = 0;                                           // "xxx"
				R7Buff[16] = 0;                                           // "xxx"
       
				for (char k=17; k<R7_BodySize; k++)
					R7Buff[k] = 0;
        
				NewQ_Arc_R7(R7Buff, 17);  // Передаём тело архива архиватору
				OUT->Ok.Data.bit = 1;
			}
		}  
	}
	OUT->OldSost16.Data.uint16 = IN->Sost16.Data.uint16;
}
