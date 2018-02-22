/* ФБ "Архиватор R7 "Протокол работы объекта" (тип 17, подтип 7)" */
 
 
#include <time.h>
#include "../vars.h"
 
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00052.h"
/*Создвет архив с кодом события(байт),4 байтами описания события
*и стандартным 6 байтным временем 
*/            
void fb00052_exec(void) {
	fb00052_IN_type *IN = (fb00052_IN_type *) FBInputs;
	fb00052_OUT_type *OUT = (fb00052_OUT_type *) FBOutputs;
  
	u8 R7Buff[R7_BodySize];

	OUT->Ok.Data.bit = 0;

	if (IN->CmdARX.Data.bit) { // Если архивирование замера разрешено
    // Проверяем что все правильного типа
		if (((IN->EventID.Type & DataTypeMask)!= KodFloat32) && \
			((IN->DD0.Type & DataTypeMask) == KodInt8) && \
        	((IN->DD1.Type & DataTypeMask) == KodInt8) && \
          	((IN->DD2.Type & DataTypeMask) == KodInt8) && \
            ((IN->DD3.Type & DataTypeMask) == KodInt8) ) {
		
			R7Buff[0] = 0;                                        // Номер канала
			R7Buff[1] = 0;                        // В R5 здесь были номера последней записанной
			R7Buff[2] = 0;                        // и последней прочитанной записей R5
			R7Buff[3] = 7;                        // Тип записи (из R5) = 7 (Протокол работы объекта)
			R7Buff[4] = IN->EventID.Data.uint8;   // Код события
			R7Buff[5] = IN->DD0.Data.uint8;       // DD0
			R7Buff[6] = IN->DD1.Data.uint8;       // DD1
			R7Buff[7] = IN->DD2.Data.uint8;       // DD2
			R7Buff[8] = IN->DD3.Data.uint8;       // DD3
			R7Buff[9] = FB32blok.vars.Cnt1Sec;      // Время события - сек
			R7Buff[10] = FB32blok.vars.Cnt1Min;     // Время начала - мин
			R7Buff[11] = FB32blok.vars.Cnt1Chas;    // Время начала - час
			R7Buff[12] = FB32blok.vars.Cnt1Den;     // Время начала - день
			R7Buff[13] = FB32blok.vars.Cnt1Mes;     // Время начала - мес
			R7Buff[14] = FB32blok.vars.Cnt1God;     // Время начала - год c 1980
			R7Buff[15] = 0;                       // "xxx"
			R7Buff[16] = 0;                       // "xxx"
     
			for (char k=17; k<R7_BodySize; k++)
				R7Buff[k] = 0;
     
			NewQ_Arc_R7(R7Buff, 17);  // Передаём тело архива архиватору
			OUT->Ok.Data.bit = 1;
		}  
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00052_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00052_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00052_OUT_type);
    default:
        return 0;
    }
}
