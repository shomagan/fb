/* ФБ "Архиватор R7 "Замер БГ" (тип 17, подтип 2)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00048.h"

/*Запись Номера счетчика(байт),значение счетчика(4 байта)
 *время начала замера(6 байт)длительностьв мин(2 байта)
 *37 байт не используются 
*/
void fb00048_exec(void)
{
	fb00048_IN_type *IN = (fb00048_IN_type *) FBInputs;
	fb00048_OUT_type *OUT = (fb00048_OUT_type *) FBOutputs;

	time_t Time;
	struct tm tmx;
  struct tm* pTmx;
	u8 R7Buff[R7_BodySize];
	u8 k;

	OUT->Ok.Data.bit = 0;

	if (IN->CmdARX.Data.bit) {// Если архивирование замера разрешено
		// Проверяем что все входы целочисленные
		if (((IN->CntNum.Type & DataTypeMask)!= KodFloat32) && \
			((IN->StartTime.Type & DataTypeMask)!= KodFloat32) && ((IN->CntTime.Type & DataTypeMask)!= KodFloat32)) {
			
			Time = IN->StartTime.Data.uint32;
      pTmx = localtime(&Time);    // Преобразование времени из UNIX-формата
      tmx = *pTmx;
      
			R7Buff[0] = 0;                                        // Номер канала
			R7Buff[1] = 0;                                        // В R5 здесь были номера последней записанной
			R7Buff[2] = 0;                                        // и последней прочитанной записей R5
			R7Buff[3] = 2;                                        // Тип записи (из R5) = 2 (БГ)
			R7Buff[4] = IN->CntNum.Data.uint8;                    // Номер счётчика
			R7Buff[5] = (u8) (IN->Counter.Data.uint32 & 0xFF);  // Счётчик мл.
			R7Buff[6] = (u8) (IN->Counter.Data.uint32 >> 8);    // Счётчик
			R7Buff[7] = (u8) (IN->Counter.Data.uint32 >> 16);   // Счётчик
			R7Buff[8] = (u8) (IN->Counter.Data.uint32 >> 24);   // Счётчик ст.
			R7Buff[9] = tmx.tm_sec;                             // Время начала - сек
			R7Buff[10] = tmx.tm_min;                            // Время начала - мин
			R7Buff[11] = tmx.tm_hour;                           // Время начала - час
			R7Buff[12] = tmx.tm_mday;                           // Время начала - день
			R7Buff[13] = tmx.tm_mon+1;                          // Время начала - мес
			R7Buff[14] = tmx.tm_year-80;                        // Время начала - год c 1980
			R7Buff[15] = (u8) (IN->CntTime.Data.uint16 & 0xFF); // Длительность в минутах мл.
			R7Buff[16] = (u8) (IN->CntTime.Data.uint16 >> 8);   // Длительность в минутах ст.

			for (k = 17; k < R7_BodySize; k++)
				R7Buff[k] = 0;

			NewQ_Arc_R7(R7Buff, 17);  // Передаём тело архива архиватору
			OUT->Ok.Data.bit = 1;
		}else{//type mismatch
      LedErrorOn(100);
    }      
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00048_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00048_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00048_OUT_type);
    default:
        return 0;
    }
}
