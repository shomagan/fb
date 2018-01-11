// ФБ "Счетчик БГ" 
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00091.h"

void fb00091_exec (void)
{
	fb00091_IN_type * IN = (fb00091_IN_type *) FBInputs;		// входа
	fb00091_VAR_type * VARS = (fb00091_VAR_type *) FBVars;	// переменные
	fb00091_OUT_type * OUT = (fb00091_OUT_type *) FBOutputs;	// выхода
	
	u32 CntDiff;
	
	time_t Time;
	struct tm tmx;
	
	u8 flMakeSutArch;
		//bit0 - =1 сформировать архив за интервал
		//bit1 - =1 перекинуть текущие сутки в прошлые и обнулить текущие
	CntDiff = 0;
	VARS->CntTicksSec.Data.uint8++;	// инкрементируем счетчик тиков обнаружения секунды
  flMakeSutArch = 0;

	
	if (OUT->ArhInvEna.Data.bit) { // держим признак актуальности архивных данных 1 такт выполнения
		OUT->ArhInvEna.Data.bit = 0;
		OUT->ArhInvPeretok.Data.bit = 0;
	}
	
	if (VARS->EnaOld.Data.bit != 0) { // EnaOld = 1 // Нужно считать
		if ((IN->CounterDI.Data.uint32 > VARS->CounterDIOld.Data.uint32) && (VARS->CounterDIOld.Data.uint32)) {
			
			CntDiff = (IN->CounterDI.Data.uint32 - VARS->CounterDIOld.Data.uint32); // определим приращение счетчика
		}
			
		VARS->CounterMinOld.Data.uint32 += CntDiff;		// минутный счетчик

		if (IN->EnaPeretok.Data.bit) { //если считать необходимо перетоки
			if (IN->PeretokDI.Data.bit) { // нет условия начала счета перетоков (насос работает)
				OUT->CNTInvT.Data.uint32 += CntDiff;	// интервальный счетчик
			} else { // есть условие начала счета перетоков (насос не работает)
				OUT->CNTInvTif.Data.uint32 += CntDiff;	// счетчик перетоков за текущий интервал
			}
		} else { // если перетоки не нужны
			OUT->CNTInvT.Data.uint32 += CntDiff;	// интервальный счетчик
		}
		
		OUT->CNTIntegrTS.Data.uint32 += CntDiff;	// интегральный за текущие сутки счетчик
			
		if (VARS->CntTicksSec.Data.uint8 == ((u8)(KernelInfo.FBkernelRate & 0xff))) { // если прошла секунда
			// обработаем расходы
			if (VARS->CntSeconds.Data.uint8 >= 60) {
				Time = IN->UNIXTime.Data.uint32;	// время в формате Unix
				struct tm* pTmx;
        pTmx = localtime(&Time);    // Преобразование времени из UNIX-формата
        tmx = *pTmx;


				OUT->MinCntDiff.Data.uint32 = VARS->CounterMinOld.Data.uint32 - OUT->MinCnt.Data.uint32; // посчитаем изменеие минутного
				OUT->MinCnt.Data.uint32 = VARS->CounterMinOld.Data.uint32; // сохраним старое значение минутного расхода
				VARS->CounterMinOld.Data.uint32 = 0;
				VARS->CntSeconds.Data.uint8 = 0;
				VARS->CntMinutes.Data.uint16++;
				
				if (OUT->MinCntDiff.Data.uint32 > IN->AvarRashod.Data.uint32) {
					OUT->flAvarRash.Data.bit = 1;
				} else {
					OUT->flAvarRash.Data.bit = 0;
				}

				if (IN->Ena2Hours.Data.bit) { // если стоит флаг выравнивания по двухчасовкам
					if ((tmx.tm_min == 0) && ((tmx.tm_hour % 2) == 0)) {	// проверим что наступил четный час
						flMakeSutArch |= BIT(0); // необходимо сформировать архив и начать новую двучасовку (интервал)
					}
				} else if (VARS->CntMinutes.Data.uint16 >= IN->IntervalCNT.Data.uint16) { // если закончился интервал
					flMakeSutArch |= BIT(0); // необходимо сформировать архив и начать новый интервал
				}
				
				if (IN->EnaNullNull.Data.bit) { // если необходимо выровнять в 00:00
					if ((tmx.tm_min == 0) && (tmx.tm_hour == 0)) { // проверим что наступили новые сутки
						flMakeSutArch |= BIT(0); // необходимо сформировать архив и начать новый интервал
						flMakeSutArch |= BIT(1); // необходимо перекинуть в прошлые сутки и начать новые
					}
				}
			}
		}
		
		if (flMakeSutArch & BIT(0)) {
			OUT->ArhInvEna.Data.bit = 1;	// архив за интервал готов
			OUT->ArhInvTimeBeg.Data.uint32 = VARS->TimeBeg.Data.uint32; // время начала замера для архива
			OUT->ArhInvDuration.Data.uint16 = VARS->CntMinutes.Data.uint16; // длительность замера для архива в минутах
			OUT->ArhCNTInvT.Data.uint32 = OUT->CNTInvT.Data.uint32; // счетчик за текущий интервал для архива
			
			if (IN->EnaPeretok.Data.bit) { // если учитывать перетоки
				OUT->ArhInvPeretok.Data.bit = 1;
				OUT->ArhCNTInvTif.Data.uint32 = OUT->CNTInvTif.Data.uint32; // вычислим переток
				OUT->CNTInvPif.Data.uint32 = OUT->CNTInvTif.Data.uint32; // сохраним переток в прошлом интервале
				OUT->CNTInvTif.Data.uint32 = 0; // обнулим текущий переток
			}
			
			OUT->CNTInvP.Data.uint32 = OUT->CNTInvT.Data.uint32; // счетчик за текущий интервал сохраним в прошлом
			OUT->CNTInvT.Data.uint32 = 0; // обнулим счетчик за текущий нтервал
			VARS->TimeBeg.Data.uint32 = IN->UNIXTime.Data.uint32; // запомним время начала текущего замера
			VARS->CntMinutes.Data.uint16 = 0; // обнулим длительность замера
			flMakeSutArch &= ~BIT(0);
		}
		
		if  (flMakeSutArch & BIT(1)) {
			OUT->CNTIntegrPS.Data.uint32 = OUT->CNTIntegrTS.Data.uint32; // сохраним текущий суточный счетчик в предыдущих сутках
			OUT->CNTIntegrTS.Data.uint32 = 0; // обнулим текущий суточный счетчик
			flMakeSutArch &= ~BIT(1);
		}
	} else {
		VARS->EnaOld.Data.bit = 0;
		VARS->CntTicksSec.Data.uint8 = 0;
		VARS->CounterMinOld.Data.uint32 = 0;
		VARS->CntMinutes.Data.uint16 = 0;
		VARS->TimeBeg.Data.uint32 = IN->UNIXTime.Data.uint32;
		
		OUT->MinCnt.Data.uint32 = 0;
		OUT->MinCntDiff.Data.uint32 = 0;
		OUT->CNTInvT.Data.uint32 = 0;
		OUT->CNTInvP.Data.uint32 = 0;
		OUT->CNTIntegrTS.Data.uint32 = 0;
		OUT->CNTIntegrPS.Data.uint32 = 0;
		OUT->CNTInvTif.Data.uint32 = 0;
		OUT->CNTInvPif.Data.uint32 = 0;
		OUT->ArhInvEna.Data.bit = 0;
		OUT->ArhInvDuration.Data.uint32 = 0;
		OUT->ArhInvTimeBeg.Data.uint32 = 0;
		OUT->ArhInvPeretok.Data.bit = 0;
		OUT->flAvarRash.Data.bit = 0;
	}
	
	VARS->CounterDIOld.Data.uint32 = IN->CounterDI.Data.uint32;
	VARS->EnaOld.Data.bit = IN->Enable.Data.bit;
	
	if (VARS->CntTicksSec.Data.uint8 == ((u8)(KernelInfo.FBkernelRate & 0xff))) { // обнулим счетчик тиков обнаружения секунды
		VARS->CntTicksSec.Data.uint8 = 0;
		VARS->CntSeconds.Data.uint8++;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00091_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00091_IN_type);
    case(1):
        return sizeof(fb00091_VAR_type);
    case(2):
        return sizeof(fb00091_OUT_type);
    default:
        return 0;
    }
}
