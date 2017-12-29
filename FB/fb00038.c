/* ФБ "ГЗУ (Башнефть) v.1" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00038.h"

void fb00038_exec(void) {
  LedErrorOn(50);

	/*fb00038_IN_type *IN = (fb00038_IN_type *) FBInputs;
	fb00038_VAR_type *VAR = (fb00038_VAR_type *) FBVars;
	fb00038_OUT_type *OUT = (fb00038_OUT_type *) FBOutputs;

	OUT->GP_ON.Data.bit = OUT->GP_OFF.Data.bit = OUT->EndPeriod.Data.bit = 0;
	OUT->TimerOut.Data.uint16 = OUT->TimerUstOut.Data.uint16 = 0;

//------------------------------------------------------------------------------  
	if (IN->Enable.Data.bit) { // Разрешена работа ГЗУ
//------------------------------------------------------------------------------  
		if (IN->Hold.Data.bit)   // Hold = 1
			OUT->GZUsost.Data.uint16 |= Holded;
		else {                        // Hold = 0
			OUT->GZUsost.Data.uint16 &= ~Holded;
			if ((IN->GP_enabled.Data.bit) && ((OUT->GZUsost.Data.uint16 & GP_En) == 0)) { // Включился (разрешился) ГП
				OUT->GZUsost.Data.uint16 = 0;
				VAR->TryCount.Data.uint8 = 0;
				VAR->APV_TryCount.Data.uint8 = 0;
			}
			OUT->GZUsost.Data.uint16 |= Enabled;
      
//------------------------------------------------------------------------------    
			if (IN->CmdManual.Data.bit) { // Команда ручного замера
//------------------------------------------------------------------------------    
				if ((IN->ManualOtvNum.Data.uint8) && (IN->ManualOtvNum.Data.uint8 <= IN->GZU_OtvNum.Data.uint8)) {
					OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked);
          
					if (OUT->GZUsost.Data.uint16 & Zamer)
						OUT->EndPeriod.Data.bit = 1;
          
					OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // Сбрасываем статусы
          
					if ((IN->KodPSM.Data.uint8 & 0x0F) == IN->ManualOtvNum.Data.uint8) {  // Стоим на нужном отводе
						OUT->GZUsost.Data.uint16 |= Reverse;
						OUT->GP_OFF.Data.bit = 1;
						VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
						if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
							VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F) - 1;
						else if (IN->KodPSM.Data.uint8 & 0x0F)
							VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
					}
					OUT->TekOtvod.Data.uint8 = IN->ManualOtvNum.Data.uint8;
          
					VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
					OUT->GZUsost.Data.uint16 |= Manual;
				}
			}
      
//------------------------------------------------------------------------------    
			if (IN->CmdStopReset.Data.bit && (OUT->GZUsost.Data.uint16 & (Stop | FullStop))) { // Команда сброса СТОПа
//------------------------------------------------------------------------------    
				OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // Сбрасываем стоп, выставляем автомат

				if (OUT->GZUsost.Data.uint16 & Zamer)
					OUT->EndPeriod.Data.bit = 1;
				
				OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // Сбрасываем статусы
				OUT->GZUsost.Data.uint16 |= Reverse;
				OUT->GP_OFF.Data.bit = 1;
				VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
				VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
        
				if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
					VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F) - 1;
				else if (IN->KodPSM.Data.uint8 & 0x0F)
					VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
			}

//------------------------------------------------------------------------------    
			if (IN->CmdSwitchOtv.Data.bit) {// Команда перевода отвода
//------------------------------------------------------------------------------    
       
				OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // Сбрасываем стоп, выставляем автомат
        
				if (OUT->GZUsost.Data.uint16 & Zamer) {
					OUT->EndPeriod.Data.bit = 1;

				}
        
				if (OUT->GZUsost.Data.uint16 & Reverse)
					OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Zamer | Kluch);  // Перевод будет по окончанию обратного хода
				else	
					OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // Немедленный перевод
        
				VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
				OUT->GZUsost.Data.uint16 |= NeedPerevod;
			}
      
//------------------------------------------------------------------------------  
      // Не СТОП
			if (!(OUT->GZUsost.Data.uint16 & (Stop | FullStop))) {
//------------------------------------------------------------------------------  
				if (VAR->Timer1.Data.uint32)
					VAR->Timer1.Data.uint32--;
        
//------------------------------------------------------------------------------  
				if ((OUT->GZUsost.Data.uint16 & (Stab | Forward | Reverse | Zamer)) == 0) {// Ещё ничего не делаем
//------------------------------------------------------------------------------  
         
					if (((IN->KodPSM.Data.uint8 & 0x0F) == 0) || ((IN->KodPSM.Data.uint8 & 0x0F) > IN->GZU_OtvNum.Data.uint8))
						OUT->GZUsost.Data.uint16 |= NeedPerevod;
          
					if (OUT->GZUsost.Data.uint16 & NeedPerevod) {// нужен перевод отвода
						if (IN->GP_enabled.Data.bit) {  // Работа ГП разрешена
							OUT->GZUsost.Data.uint16 &= ~NeedPerevod;
							OUT->GZUsost.Data.uint16 |= Forward;
							OUT->GP_ON.Data.bit = 1;
							VAR->Timer1.Data.uint32 = IN->ForwardTime.Data.uint16 * KernelInfo.FBkernelRate;

							if (IN->KodPSM.Data.uint8 & 0x0F)
								VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
						} else {                             // Работа ГП запрещена, переходим в ручной режим
							if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
								VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
							else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
								VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;
              
							OUT->GZUsost.Data.uint16 &= ~NeedPerevod;
							OUT->GZUsost.Data.uint16 |= (Reverse | Manual);
							OUT->GP_OFF.Data.bit = 1;
							VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
						}
					} else {
					// (Циклическая работа и нужно замерять текущий отвод ИЛИ ручной режим и стоим на нужном отводе)
						if ((((OUT->GZUsost.Data.uint16 & Manual) == 0) && (IN->OtvMask.Data.uint16 & (1 << ((IN->KodPSM.Data.uint8 & 0x0F) - 1)))) || \
							(((OUT->GZUsost.Data.uint16 & Manual)) && ((IN->KodPSM.Data.uint8 & 0x0F) == OUT->TekOtvod.Data.uint8))) {
							OUT->GZUsost.Data.uint16 |= Stab;
							VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * KernelInfo.FBkernelRate;
							VAR->Timer2.Data.uint32 = 0;
							OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
							VAR->TryCount.Data.uint8 = 0;

              
							if (IN->KodPSM.Data.uint8 & 0x0F)
							VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
						} else {// Нужны переводы отвода
							OUT->GZUsost.Data.uint16 |= NeedPerevod;
						}
					}
          
				} else if (OUT->GZUsost.Data.uint16 & Forward) {                           // Прямой ход
					if ((!VAR->Timer1.Data.uint32) || (!IN->GP_enabled.Data.bit)) {
						OUT->GZUsost.Data.uint16 &= ~Forward;
						OUT->GZUsost.Data.uint16 |= Reverse;
						OUT->GP_OFF.Data.bit = 1;
						VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
					}
					OUT->TimerOut.Data.uint16 = (KernelInfo.FBkernelRate) ? (IN->ForwardTime.Data.uint16 - (VAR->Timer1.Data.uint32 / KernelInfo.FBkernelRate)) : 0;
					OUT->TimerUstOut.Data.uint16 = IN->ForwardTime.Data.uint16;
				} else if (OUT->GZUsost.Data.uint16 & Reverse) {                            // Обратный ход
					if (!VAR->Timer1.Data.uint32) {
						OUT->GZUsost.Data.uint16 &= ~Reverse;
            
						if (OUT->GZUsost.Data.uint16 & NeedPerevod) // нужен перевод отвода (была копанда переключения отвода)
							OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // Будет перевод отвода
						else {
							if (((OUT->GZUsost.Data.uint16 & Kluch) == 0) || ((OUT->GZUsost.Data.uint16 & Manual) == 0)) {
								// Проверка правильной очерёдности переключения
								//--------------------------------------------------------------------
								if (VAR->KodPSMOld.Data.uint8 == (IN->KodPSM.Data.uint8 & 0x0F))  
									OUT->GZUsost.Data.uint16 |= (GPbraked | Stop);        // Неисправен ГП (изм=0)
								else if (((IN->KodPSM.Data.uint8 & 0x0F) == 0) || ((IN->KodPSM.Data.uint8 & 0x0F) > IN->GZU_OtvNum.Data.uint8)) 
									OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // Неисправен датчик ПСМ
								else if (VAR->KodPSMOld.Data.uint8 >= IN->GZU_OtvNum.Data.uint8) {// Если прошлый отвод последний в кругу
									if ((IN->KodPSM.Data.uint8 & 0x0F) > 1) 
										OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // Неисправен датчик ПСМ
								} else if ((IN->KodPSM.Data.uint8 & 0x0F) != (VAR->KodPSMOld.Data.uint8 + 1)) 
									OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // Неисправен датчик ПСМ
								//--------------------------------------------------------------------
							}
              
							if ((OUT->GZUsost.Data.uint16 & (PSMbraked | GPbraked | Stop)) == 0) { // нет СТОПа ГЗУ из-за неисправного датчика ПСМ
                
								if ((OUT->GZUsost.Data.uint16 & Manual) == 0) { // Циклическая работа, проверка отвода
									OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
                  
									if (IN->OtvMask.Data.uint16 & (1 << ((IN->KodPSM.Data.uint8 & 0x0F) - 1))) {// Нужно замерять данный отвод
										OUT->GZUsost.Data.uint16 |= Stab;
										VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * KernelInfo.FBkernelRate;
										VAR->Timer2.Data.uint32 = 0;
										VAR->TryCount.Data.uint8 = 0;
									} else {
										if (VAR->TryCount.Data.uint8 < IN->TryNum.Data.uint8) {
											OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // Будет перевод отвода
											OUT->GZUsost.Data.uint16 |= NeedPerevod;
											VAR->TryCount.Data.uint8++;
										} else {
											OUT->GZUsost.Data.uint16 |= (Stop | TryCnt0);
											VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * KernelInfo.FBkernelRate;  // Если только что перешли в СТОП - взводим Timer2 (как счётчик интервала АПВ)
										}
									}
								} else {   // Ручной замер
									if (OUT->GZUsost.Data.uint16 & Manual1Cnt)
										OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F); 

									if ((IN->KodPSM.Data.uint8 & 0x0F) == OUT->TekOtvod.Data.uint8) { // Стоим на нужном отводе, начинаем стабилизацию и замер
										OUT->GZUsost.Data.uint16 |= Stab;
										VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * KernelInfo.FBkernelRate;
										VAR->Timer2.Data.uint32 = 0;
										VAR->TryCount.Data.uint8 = 0;
									} else {   // Нужны ещё переключения
										if (VAR->TryCount.Data.uint8 < IN->TryNum.Data.uint8) {
											OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // Будет перевод отвода
											OUT->GZUsost.Data.uint16 |= NeedPerevod;
											VAR->TryCount.Data.uint8++;
										} else {
											OUT->GZUsost.Data.uint16 |= (Stop | TryCnt0);
											VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * KernelInfo.FBkernelRate;  // Если только что перешли в СТОП - взводим Timer2 (как счётчик интервала АПВ)
										}
									}
								}
							} else {
								if (OUT->GZUsost.Data.uint16 & Stop)
									VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * KernelInfo.FBkernelRate;  // Если только что перешли в СТОП - взводим Timer2 (как счётчик интервала АПВ)
							}
						}
					}
					OUT->TimerOut.Data.uint16 = (KernelInfo.FBkernelRate) ? (IN->ReverseTime.Data.uint16 - (VAR->Timer1.Data.uint32 / KernelInfo.FBkernelRate)) : 0;
					OUT->TimerUstOut.Data.uint16 = IN->ReverseTime.Data.uint16;
				} else if (OUT->GZUsost.Data.uint16 & Stab) {                           // Стабилизация
					if (!VAR->Timer1.Data.uint32) {
						OUT->GZUsost.Data.uint16 &= ~Stab;
						OUT->GZUsost.Data.uint16 |= Zamer;
					} else {
						if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) {// Во время стабилизации изменился код ПСМ
							OUT->GZUsost.Data.uint16 |= Kluch;
						} else {
							OUT->GZUsost.Data.uint16 &= ~Kluch;
							VAR->Timer2.Data.uint16 = 0;
						}
            
						if (OUT->GZUsost.Data.uint16 & Kluch) {
							if (++VAR->Timer2.Data.uint16 > (KluchDelay * KernelInfo.FBkernelRate)) { // 15 секунд держится новый код ПСМ
								if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
									VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
								else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
									VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;
                
								OUT->GZUsost.Data.uint16 &= ~Stab;
								OUT->GZUsost.Data.uint16 &= ~Kluch;
								OUT->GZUsost.Data.uint16 |= (Reverse | Manual | Manual1Cnt);
								OUT->GP_OFF.Data.bit = 1;
								OUT->EndPeriod.Data.bit = 1;
								VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
							}
						}
					}	
					OUT->TimerOut.Data.uint16 = (KernelInfo.FBkernelRate) ? IN->StabTime.Data.uint16 - (VAR->Timer1.Data.uint32 / KernelInfo.FBkernelRate) : 0;
					OUT->TimerUstOut.Data.uint16 = IN->StabTime.Data.uint16;
				} else if (OUT->GZUsost.Data.uint16 & Zamer) {                           // Замер
					if ((IN->EndPeriod.Data.bit) && ((OUT->GZUsost.Data.uint16 & Kluch)==0)) {
            
						if (OUT->GZUsost.Data.uint16 & Manual) { // Ручной замер
							if (OUT->GZUsost.Data.uint16 & Manual1Cnt)
								OUT->GZUsost.Data.uint16 = VAR->TryCount.Data.uint8 = 0;
						} else {                                     // Циклическая работа
							OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // Будет перевод отвода
							OUT->GZUsost.Data.uint16 |= NeedPerevod;
							VAR->TryCount.Data.uint8 = 0;
						}
					} else {
						if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) {// Во время замера изменился код ПСМ
							OUT->GZUsost.Data.uint16 |= Kluch;
						} else {
							OUT->GZUsost.Data.uint16 &= ~Kluch;
							VAR->Timer2.Data.uint16 = 0;
						}
					}
          
					if (OUT->GZUsost.Data.uint16 & Kluch) {
						if (++VAR->Timer2.Data.uint16 > (KluchDelay * KernelInfo.FBkernelRate)) { // 15 секунд держится новый код ПСМ
							if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
								VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
							else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
								VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;
              
							OUT->GZUsost.Data.uint16 &= ~Zamer;
							OUT->GZUsost.Data.uint16 &= ~Kluch;
							OUT->GZUsost.Data.uint16 |= (Reverse | Manual | Manual1Cnt);
							OUT->GP_OFF.Data.bit = 1;
							OUT->EndPeriod.Data.bit = 1;
							VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
						}
					}
				}
			} else { // СТОП
				if ((OUT->GZUsost.Data.uint16 & FullStop) == 0) { // Если не полный СТОП
					if (VAR->APV_TryCount.Data.uint8 >= IN->APV_TryNum.Data.uint8) { // Кончились попытки АПВ ГЗУ
						OUT->GZUsost.Data.uint16 |= FullStop;
					} else {
						if (VAR->Timer2.Data.uint32) {
							VAR->Timer2.Data.uint32--;
						} else {
							VAR->APV_TryCount.Data.uint8++;
							OUT->GZUsost.Data.uint16 &= ~(Stop | PSMbraked | GPbraked | TryCnt0 | Kluch);
							OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // Сбрасываем статусы
              
							VAR->TryCount.Data.uint8 = 0;
							VAR->Timer1.Data.uint32 = 0;
						}
					}
				}
        
				if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) {// Во время СТОПа изменился код ПСМ
					OUT->TekOtvod.Data.uint8 = VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F); 
					OUT->GZUsost.Data.uint16 |= Kluch;
					VAR->Timer1.Data.uint32 = 0;
				}
        
				if (OUT->GZUsost.Data.uint16 & Kluch) {
					if (++VAR->Timer1.Data.uint32 > (KluchDelay * KernelInfo.FBkernelRate)) { // 15 секунд держится новый код ПСМ
						if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
							VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
						else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
							VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;
            
						OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // Сбрасываем стоп, выставляем автомат
						OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // Сбрасываем статусы
						OUT->GZUsost.Data.uint16 |= (Reverse | Manual);
						OUT->GP_OFF.Data.bit = 1;
						VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * KernelInfo.FBkernelRate;
					}
				}
			}
      
			if ((OUT->GZUsost.Data.uint16 & Stop) && ((OUT->GZUsost.Data.uint16 & Kluch) == 0))  // Если СТОП не было перевода ключём
				OUT->TekOtvod.Data.uint8 = IN->KodPSM.Data.uint8 & 0x0F;
		}
	} else { // Enable = 0
    
		OUT->GZUsost.Data.uint16 &= ~Enabled;
		OUT->GZUsost.Data.uint16 = 0;
		VAR->Timer1.Data.uint32 = VAR->Timer2.Data.uint32 = 0;
		VAR->APV_TryCount.Data.uint8 = 0;
		OUT->EndPeriod.Data.bit = 1;
	}
  
	if (IN->GP_enabled.Data.bit)
		OUT->GZUsost.Data.uint16 |= GP_En;
	else
		OUT->GZUsost.Data.uint16 &= ~GP_En;

	OUT->Counting.Data.bit = ((OUT->GZUsost.Data.uint16 & Zamer) && ((OUT->GZUsost.Data.uint16 & Kluch)==0)) ? 1 : 0;
  */
}
