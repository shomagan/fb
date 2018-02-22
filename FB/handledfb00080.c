/* ФБ "Задвижка" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00080.h"

void fb00080_exec(void) {
/*	fb00078_IN_type *IN = (fb00078_IN_type *) FBInputs;
	fb00078_VAR_type *VAR = (fb00078_VAR_type *) FBVars;
	fb00078_OUT_type *OUT = (fb00078_OUT_type *) FBOutputs;
*/
	fb00080_IN_type *IN = (fb00080_IN_type *) FBInputs;
	fb00080_VAR_type *VAR = (fb00080_VAR_type *) FBVars;
	fb00080_OUT_type *OUT = (fb00080_OUT_type *) FBOutputs;

//	unsigned char NeedImpuls;
	unsigned int varSost;

	if(KernelInfo.EventFlags.Bit.CfgFirstExec) { //первый запуск
		OUT->OutOpen.Data.bit = 0;
		OUT->OutClose.Data.bit = 0;
		OUT->OutStop.Data.bit = 0;
		OUT->Timer.Data.uint16 = 0;
		OUT->Sost.Data.uint16 = 0;
		VAR->SecTimer.Data.uint8 = 0;
		VAR->ImpulsTime.Data.uint8 = 0;
		varSost = 0;
	} else { // не первый запуск

		VAR->SecTimer.Data.uint8++;

//		NeedImpuls = (VAR->ImpulsTime.Data.uint8 > 0) ? 1 : 0;

		varSost = OUT->Sost.Data.uint16;

		if(IN->Dist.Data.bit == 0) { //Если местный режим
			varSost = 0;
			OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
			OUT->OutOpen.Data.bit = 0;
			OUT->OutClose.Data.bit = 0;
			OUT->OutStop.Data.bit = 0;
			VAR->ImpulsTime.Data.uint16 = 0;
		} else { //Если дистанционный режим
			varSost |= s00080_DIST;
			if(IN->CmdStop.Data.bit || IN->Alarmed.Data.bit) { //Если команда стоп или авария
				OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
				OUT->OutStop.Data.bit = 1;		//Выдать импульс на выход СТОП
//				NeedImpuls = 1;
				VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Время импульса удержания управляющего сигнала в сек.
				OUT->OutClose.Data.bit = 0;		//сбросить выход управления ЗАКРЫТЬ
				OUT->OutOpen.Data.bit = 0;		//сбросить выход управления ОТКРЫТЬ
				varSost &= ~s00080_OPENING;		//сбросить флаг ОТКРЫВАЕТСЯ
				varSost &= ~s00080_CLOSING;		//сбросить флаг ЗАКРЫВАЕТСЯ

			} else { // отработка команд открытия и закрытия
				if((IN->CmdOpen.Data.bit) && (!(varSost & s00080_CLOSING))) { // Если Команда открыть, и не ЗАКРЫВЕТСЯ
					if(!IN->Opened.Data.bit&&(!OUT->OutStop.Data.bit)) {	//и не ОТКРЫТА
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Время импульса удержания управляющего сигнала в сек.
						OUT->OutOpen.Data.bit = 1;	//выдать управляющий импульс на выход ОТКРЫТЬ
						varSost |= s00080_OPENING;	//выставиить флаг ОТКРЫВЕТСЯ
						varSost &= ~s00080_CLOSING;	//сбросить флаг ЗАКРЫВАЕТСЯ
						varSost &= ~s00080_AVARMUFTA;	//сбросить флаг АВАРИЯ ПО МУФТЕ
						varSost &= ~s00080_AVARVPHOPEN;	//сбросит флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ОТКРЫТИЯ
						varSost &= ~s00080_AVARVPHCLOSE;	//сбросить флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ЗАКРЫТИЯ
					}
				}
				if((IN->CmdClose.Data.bit) && (!(varSost & s00080_OPENING))) { // Если Команда закрыть, и не открывается
					if(!IN->Closed.Data.bit&&(!OUT->OutStop.Data.bit)) {	//и не ЗАКРЫТА
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Время импульса удержания управляющего сигнала в сек.
						OUT->OutClose.Data.bit = 1;	//выдать управляющий импульс на выход ЗАКРЫТЬ
						varSost |= s00080_CLOSING;	//выставить флаг ЗАКРЫВАЕТСЯ
						varSost &= ~s00080_OPENING;	//сбросить флаг ОТКРЫВАЕТСЯ
						varSost &= ~s00080_AVARMUFTA; //сбросить флаг АВАРИЯ ПО МУФТЕ
						varSost &= ~s00080_AVARVPHOPEN;	//сбросит флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ОТКРЫТИЯ
						varSost &= ~s00080_AVARVPHCLOSE; //сбросить флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ЗАКРЫТИЯ
					}
				}
			}
		
//			if(NeedImpuls) { // Отработка импульса удержания управляющего сигнала открытия, закрытия, стоп
 			if(VAR->ImpulsTime.Data.uint8 == 0) { //Время удержаняи  импульса вышло?
 				OUT->OutClose.Data.bit = 0;		// если вышло, то сбросить управляющие выходы Закрытия Открытия Стоп
 				OUT->OutOpen.Data.bit = 0;
 				OUT->OutStop.Data.bit = 0;
 			} else {
 				if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
 					VAR->ImpulsTime.Data.uint8--;	//если не вышло, то декременировать счетчик секунд удержания управляющего импульса
 				}
 			}
//			}
			
			if(varSost & s00080_OPENING) {	//если задвижка ОТКРЫВЕТСЯ
				if(OUT->Timer.Data.uint16 == 0) {	//если закончилось ВРЕМЯ ПОЛНОГО ХОДА
					varSost &= ~s00080_OPENING;	//сбросить флаг ОТКРЫВАЕТСЯ
					varSost |= s00080_AVARVPHOPEN;	//выставить флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ОТКРЫТИЯ
					OUT->OutStop.Data.bit = 1;		//выдать импульс на выход СТОП
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else { //время полного хода не вышло
					if(IN->Opened.Data.bit) { //Если задвижка ОТКРЫТА
						varSost &= ~s00080_OPENING;	//сбросить флаг открывается
						varSost &= ~s00080_AVARVPHOPEN;	//сбросить флаг АВАРИЯ НЕ ДОЖДАЛИТЬ ОТКРЫТИЯ
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//если не вышло время полного хода, то декрементировать счетчик секунд времени полного хода
						}	
					}
				}
			}
			
			if(varSost & s00080_CLOSING) {	//если задвижка ЗАКРЫВАЕТСЯ
				if(OUT->Timer.Data.uint16 == 0) {	//если закончилось ВРЕМЯ ПОЛНОГО ХОДА
					varSost &= ~s00080_CLOSING;	//сбросит флаг ЗАКРЫВАЕТСЯ
					varSost |= s00080_AVARVPHCLOSE;	//выставить флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ЗАКРЫТИЯ
					OUT->OutStop.Data.bit = 1;	//выдать импульс на выход СТОП
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else {	//время полного хода не вышло
					if(IN->Closed.Data.bit) {	//Если задвижка ЗАКРЫТА
						varSost &= ~s00080_CLOSING;	//сбросит флаг ЗАКРЫВАЕТСЯ
						varSost &= ~s00080_AVARVPHCLOSE;	//сбросить флаг АВАРИЯ НЕ ДОЖДАЛИСЬ ЗАКРЫТИЯ
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//если не вышло время полного хода, то декрементировать счетчик секунд времени полного хода
						}	
					}
				}
			}
		}
	} //не первый запуск

	if(IN->Alarmed.Data.bit) {		//изменить состояние АВАРИИ ПО МУФТЕ в соответсвии с входом
		varSost |= s00080_AVARMUFTA;
	} else {
		varSost &= ~s00080_AVARMUFTA;
	}

	if(IN->Opened.Data.bit) {		//изменить состояние ОТКРЫТА в соответсвии с входом
		varSost |= s00080_OPENED;
	} else {
		varSost &= ~s00080_OPENED;
	}

	if(IN->Closed.Data.bit) {		//изменить состояние ЗАКРЫТА в соответсвии с входом
		varSost |= s00080_CLOSED;
	} else {
		varSost &= ~s00080_CLOSED;
	}

	if(IN->Uon.Data.bit) {			//изменить состояние НАЛИЧИЕ НАПРЯЖЕНИЯ соответсвии с входом
		varSost |= s00080_UON;
	} else {
		varSost &= ~s00080_UON;
	}

	OUT->Sost.Data.uint16 = varSost;

	if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
		VAR->SecTimer.Data.uint8 = 0;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00080_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00080_IN_type);
    case(1):
        return sizeof(fb00080_VAR_type);
    case(2):
        return sizeof(fb00080_OUT_type);
    default:
        return 0;
    }
}
