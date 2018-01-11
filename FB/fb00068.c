/* ФБ "Автомат управления приводом по Кнап" */


#define MEGA12 1
//#define FB68_DEBUG


#ifdef MEGA12
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
 #define BIT(x)	(0x00000001<<(x))
#endif

#include "../kernel.h"
#include "fb00068.h"


void fb00068_exec(void){
  LedErrorOn(100);
#if KNAP_CONTROL
  
  fb00068_IN_type *IN = (fb00068_IN_type *) FBInputs;
  fb00068_VAR_type *VAR = (fb00068_VAR_type *) FBVars;
  fb00068_OUT_type *OUT = (fb00068_OUT_type *) FBOutputs;

  vu8 i;//для расчета срденего кнап за последние несколько
  vu32 DaySec;       // vu32 // секунд с начала суток
  vu16 input_mask,MinuteOnDay;  // маска ипсользуемая для входов
  vu8 time_fb68=0;  //внутреннее управление
  vu16 FiltPressure; 
//---Protect---
  IN->KnapCalc.Data.uint8 = (IN->KnapCalc.Data.uint8>0&&(IN->KnapCalc.Data.uint8<40)) ? IN->KnapCalc.Data.uint8 : 10;
  IN->KnapIgnor.Data.uint8 = (IN->KnapIgnor.Data.uint8<2) ? 2 : IN->KnapIgnor.Data.uint8;
  for(i=0;i<(TIME_PERIOD_NUMBER*2);i++)
  {
    if (IN->Time[i].Data.uint16 >= 1440) {IN->Time[i].Data.uint16=0xFFFF;}
  }

#ifdef MEGA12
  if (KernelInfo.EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#else 
  if (EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#endif
  {
    VAR->ActuatorRestartCnt.Data.uint32 =(IN->ActuatorRestart.Data.uint32>10)?10:IN->ActuatorRestart.Data.uint32;
    OUT->State.Data.uint32 = 0;
    OUT->State.Data.uint32 |=BIT(BEFORSTART);
    OUT->TimerBeforeStart.Data.uint8 = (IN->TimeBeforeStart.Data.uint8<20) ? 20 : IN->TimeBeforeStart.Data.uint8;
    OUT->CntRestartSP.Data.uint16 = IN->SP_Num.Data.uint16;
    OUT->CntRestartAPV.Data.uint16 = IN->APV_Num.Data.uint16;
    OUT->CntIgnor.Data.uint16 = IN->KnapIgnor.Data.uint16;
    OUT->KNAPTimer.Data.uint16 = 0;
//---WATT
    if (OUT->WattPreviuDay.Data.uint32 == 0xFFFFFFFF){OUT->WattPreviuDay.Data.float32 =0;}          // uint32 // watt/hours
    if (OUT->WattCurrentDay.Data.uint32 == 0xFFFFFFFF){OUT->WattCurrentDay.Data.float32=0;}
//---WATT
  }  
//---servis---
  input_mask = IN->DigitInput.Data.uint16 ^ IN->DigitInversion.Data.uint16;//инверсируем входы
#ifdef MEGA12
  if((VAR->KernelClk.Data.uint32%KernelInfo.FBkernelRate)==0){
    FiltPressure = FILTPRESSURE*KernelInfo.FBkernelRate;//пересчет секунд в такты
#else
  if((VAR->KernelClk.Data.uint32%FBkernelRate)==0){
    FiltPressure = FILTPRESSURE*FBkernelRate;//пересчет секунд в такты
#endif
  
    VAR->SecTimer.Data.uint32++;
    time_fb68|=BIT(SEC);
  }else{
    time_fb68&=~BIT(SEC);
  }
  if ((time_fb68&BIT(SEC))&&((VAR->SecTimer.Data.uint32%60)==0)){
    VAR->MinTimer.Data.uint32++;
    time_fb68|=BIT(MINUT);
  }else{
    time_fb68&=~BIT(MINUT);
  }
#ifdef MEGA12
 	DaySec = (FB32blok.vars.Cnt1Chas * 3600) + (FB32blok.vars.Cnt1Min * 60) + FB32blok.vars.Cnt1Sec;
  MinuteOnDay = FB32blok.vars.Cnt1Chas * 60 + FB32blok.vars.Cnt1Min;
#else 
  DaySec = (SystemTime.hour*3600) + (SystemTime.min*60) + SystemTime.sec;
  MinuteOnDay = SystemTime.hour * 60 + SystemTime.min;
#endif
//---statustica knap---
  if (time_fb68&BIT(SEC)){
    if (input_mask & BIT(ACTUATOR)) {
      if (OUT->KNAPTimer.Data.uint16<0xFFFE) OUT->KNAPTimer.Data.uint16++;
      if (OUT->KNAPTimer.Data.uint16 > IN->KNAPTime.Data.uint16)
        OUT->State.Data.uint32 |= BIT(KNAP_LOSS);
      else 
        OUT->State.Data.uint32 &= ~BIT(KNAP_LOSS);
    }else {
      OUT->State.Data.uint32 &= ~BIT(KNAP_LOSS);
    }
    if (OUT->State.Data.uint32&BIT(START_TIME)){
      if(OUT->DisregardTimer.Data.uint16!=0){
        OUT->DisregardTimer.Data.uint16--;
      }else{
        OUT->State.Data.uint32&=~BIT(START_TIME);
      }
    }
  }
  if(IN->KnapOK.Data.bit){
    VAR->KnapCalc.Data.uint32++;
    OUT->CntIgnor.Data.uint16 = (OUT->CntIgnor.Data.uint16>0) ? (--OUT->CntIgnor.Data.uint16) : OUT->CntIgnor.Data.uint16;
    OUT->Knap.Data.uint8 = IN->Knap.Data.uint8;
    if (VAR->KnapCalc.Data.uint32 <= IN->KnapCalc.Data.uint8){//еще не набрали нужного количества
      VAR->Knap_Summ.Data.uint16 = VAR->Knap_Summ.Data.uint16+IN->Knap.Data.uint8;
      OUT->KnapAverage.Data.uint8 = VAR->Knap_Summ.Data.uint16/(VAR->KnapCalc.Data.uint32);
    }else{//расчет среднего
      VAR->Knap_Summ.Data.uint16 = VAR->Knap_Summ.Data.uint16-OUT->KnapAverage.Data.uint8+OUT->Knap.Data.uint8;
      OUT->KnapAverage.Data.uint8 = VAR->Knap_Summ.Data.uint16/(IN->KnapCalc.Data.uint8);//расчет среднего из последних IN->KnapCalc.Data.uint8
    }
  }
//---statustica pusk---
  if(time_fb68&BIT(MINUT)){
    OUT->LastSostTimer.Data.uint32++;
    if (input_mask & BIT(ACTUATOR)){//статистика состояния пускателя
      OUT->FullOperationTimer.Data.uint32++;
      OUT->DayUpTimer.Data.uint16++;
    }else{
      OUT->FullDownTimer.Data.uint32++;
      OUT->State.Data.uint32 |=BIT(BEFORSTART);
      OUT->TimerBeforeStart.Data.uint8 = (IN->TimeBeforeStart.Data.uint8<20) ? 20 : IN->TimeBeforeStart.Data.uint8;
    }
  }
  if (DaySec==0){
    if(OUT->DayUpTimer.Data.uint16!=0) OUT->PrevDayUpTimer.Data.uint16=OUT->DayUpTimer.Data.uint16;
    OUT->DayUpTimer.Data.uint16=0;
  }
  if ((VAR->Input_mask.Data.uint16 & BIT(ACTUATOR))!=(input_mask & BIT(ACTUATOR))){//изменилось состояние пускателя
    VAR->KnapCalc.Data.uint32 = 0;
    OUT->LastSostTimer.Data.uint32=0;
  }

//---SP---
  if(IN->KnapOK.Data.bit){
    OUT->KNAPTimer.Data.uint16 = 0;
    if (OUT->Knap.Data.uint8 < IN->KnapPorog.Data.uint8){
      if(VAR->KnapCalc.Data.uint32 > IN->KnapIgnor.Data.uint8){//расчет СП
        VAR->KnapFail.Data.uint8++;
        if (VAR->KnapFail.Data.uint8 > IN->KnapCalc.Data.uint8){
          OUT->State.Data.uint32 |=BIT(SP);
        }
      }
    }else{
      OUT->CntRestartSP.Data.uint16 = IN->SP_Num.Data.uint16;//норм востанавливаем количество
      OUT->State.Data.uint32 &=~BIT(SP);
      VAR->KnapFail.Data.uint8=0;      
    }
  }
//---RESSURE---проверяем условия выхода давления за рамки, аварийные флаги выставляются 
              //независимо от флагов разрешений
  if(IN->InputPressure.Data.uint16 > IN->MaxPressure.Data.uint16){
    VAR->PRESSURE_FILT.Data.uint16++;
    if(VAR->PRESSURE_FILT.Data.uint16>FiltPressure) {
      OUT->State.Data.uint32|=BIT(PRESSURE_BIG);
      VAR->PRESSURE_FILT.Data.uint16=FiltPressure+1;
    }
    OUT->State.Data.uint32&=~BIT(PRESSURE_LOW);
  }else if(IN->InputPressure.Data.uint16 < IN->MinPressure.Data.uint16){
    VAR->PRESSURE_FILT.Data.uint16++;
    if(VAR->PRESSURE_FILT.Data.uint16>FiltPressure){
      OUT->State.Data.uint32|=BIT(PRESSURE_LOW);
      VAR->PRESSURE_FILT.Data.uint16=FiltPressure+1;
    }
    OUT->State.Data.uint32&=~BIT(PRESSURE_BIG);  
  }else{
    OUT->State.Data.uint32&=~BIT(PRESSURE_BIG);  
    OUT->State.Data.uint32&=~BIT(PRESSURE_LOW);  
    VAR->PRESSURE_FILT.Data.uint16 = 0;
  }
//---(расщестка отрабатывать выключение пускателя в случае возникноваени 
//    условия срыва подачи и\или аварии по давлению)---
// если в этом блоке изменяем значения таймеров OUT->SPTimer.Data.uint16
  // и OUT->APVTimer.Data.uint16 если они больше 0, то произойдет останов
  // 
  if (!(IN->Mode.Data.uint8 & BIT(ENABLE_SP))){
    OUT->SPTimer.Data.uint16=0;
    OUT->CntRestartSP.Data.uint16 = IN->SP_Num.Data.uint16;
    OUT->CntIgnor.Data.uint16 = IN->KnapIgnor.Data.uint16;  
    OUT->State.Data.uint32 &=~BIT(SP_MODE);
  }else if (input_mask&BIT(ACTUATOR)){
    OUT->State.Data.uint32 |=BIT(SP_MODE);
    if (!(OUT->State.Data.uint32&BIT(START_TIME))){
      if(OUT->State.Data.uint32 & BIT(SP)){OUT->SPTimer.Data.uint16=IN->SPTime.Data.uint16;}
    }
  }else{
    OUT->State.Data.uint32 |=BIT(SP_MODE);
    OUT->CntIgnor.Data.uint16 = IN->KnapIgnor.Data.uint16;  
    if ((time_fb68&BIT(MINUT))&&(OUT->SPTimer.Data.uint16!=0)){
      if (OUT->SPTimer.Data.uint16>1){
        OUT->SPTimer.Data.uint16--;
      }else{
        if (OUT->CntRestartSP.Data.uint16 > 0){
          OUT->CntRestartSP.Data.uint16--;
          OUT->State.Data.uint32 &=~BIT(SP);
          OUT->SPTimer.Data.uint16=0;//таймер СП вышел      
        }else{
          OUT->SPTimer.Data.uint16=1;//всегда 1 пока не пересбросим
        }
      }
    }
  }

  if (!(IN->Mode.Data.uint8&BIT(ENABLE_PRESSURE))){
    OUT->APVTimer.Data.uint16=0;
    OUT->CntRestartAPV.Data.uint16 = IN->APV_Num.Data.uint16;
    OUT->State.Data.uint32 &=~BIT(PRESSURE_MODE);
  }else if (input_mask&BIT(ACTUATOR)){
    OUT->State.Data.uint32 |=BIT(PRESSURE_MODE);
    if (!(OUT->State.Data.uint32&BIT(START_TIME))){
      if(OUT->State.Data.uint32 & BIT(PRESSURE_BIG)){OUT->APVTimer.Data.uint16=IN->DownTimeBigPressure.Data.uint16;}
      if(OUT->State.Data.uint32 & BIT(PRESSURE_LOW)){OUT->APVTimer.Data.uint16=IN->DownTimeLowPressure.Data.uint16;}
      if (IN->Protection.Data.bit){
        OUT->APVTimer.Data.uint16=IN->DownTimeBigPressure.Data.uint16;
        OUT->State.Data.uint32 |=BIT(EXTERNAL_PROTECT);
      }else OUT->State.Data.uint32 &=~BIT(EXTERNAL_PROTECT);
    }
  }else{
    OUT->State.Data.uint32 |=BIT(PRESSURE_MODE);
    if ((time_fb68&BIT(MINUT))&&(OUT->APVTimer.Data.uint16!=0)){
      if (OUT->APVTimer.Data.uint16>1){
        OUT->APVTimer.Data.uint16--;
      }else{
        if (OUT->CntRestartAPV.Data.uint16 > 0){
          OUT->CntRestartAPV.Data.uint16--;
          OUT->APVTimer.Data.uint16=0;//таймер СП вышел      
          OUT->State.Data.uint32&=~BIT(PRESSURE_BIG);  
          OUT->State.Data.uint32&=~BIT(PRESSURE_LOW);  
        }else{
          OUT->APVTimer.Data.uint16=1;//всегда 1 пока не пересбросим
        }
      }
    }
  }
//---режимы---  
  if(input_mask&BIT(ARM_BUTTON)){ //в ручном режиме 
    OUT->State.Data.uint32&= ~BIT(PUSK_ACTUATOR);
  }else if(input_mask&BIT(AVTO_BUTTON)){//в автоматическом режиме
    if(IN->Mode.Data.uint8 & OPERATOR_MODE){//управление оператором
      if (!(OUT->State.Data.uint32 & BIT(OPERATOR))){
#ifdef MEGA12
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#else 
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#endif
        OUT->State.Data.uint32 |=BIT(OPERATOR);
        OUT->State.Data.uint32 &=~BIT(TIMER);
        OUT->State.Data.uint32 &=~BIT(TIME);
      }
      if(IN->Mode.Data.uint8&BIT(PUSK)){
        OUT->State.Data.uint32|=BIT(PUSK_ACTUATOR);
      }else{
        OUT->TimerBeforeStart.Data.uint8 = IN->TimeBeforeStart.Data.uint8;
        OUT->State.Data.uint32&=~BIT(PUSK_ACTUATOR);
      }
    }
    else{//упраление контроллером смотрим какие подрежимы работают
      OUT->State.Data.uint32 &=~BIT(OPERATOR);
      if (IN->Mode.Data.uint8 & TIME_MODE){//режим работы по расписанию 
        if(!(OUT->State.Data.uint32 & BIT(TIME))){
#ifdef MEGA12
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#else 
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#endif
        }
        OUT->State.Data.uint32 |=BIT(TIME);
        if (IN->Mode.Data.uint8 & BIT(PUSK)){
          OUT->State.Data.uint32&=~BIT(TIMING_PUSK);//убираем включение 
          for(i=0;i<TIME_PERIOD_NUMBER;i++)
          {
            if ((IN->Time[i].Data.uint16 !=0xFFFF)&&(IN->Time[i+5].Data.uint16 !=0xFFFF)){
              if (IN->Time[i].Data.uint16 < IN->Time[i+5].Data.uint16){ 
                if ((MinuteOnDay >= IN->Time[i].Data.uint16)&&(MinuteOnDay <= IN->Time[i+5].Data.uint16)){
                  OUT->State.Data.uint32|=BIT(TIMING_PUSK);//попали в интервал
                  OUT->State.Data.uint32|=BIT(i+16);//отмечаем интервал в который попали
                  break;
                }else {OUT->State.Data.uint32&=~BIT(i+16);}//отмечаем интервал в который попали
              }else if (IN->Time[i].Data.uint16 > IN->Time[i+5].Data.uint16){
                if (((MinuteOnDay >= IN->Time[i].Data.uint16)&&(MinuteOnDay <= 1439))||
                    (MinuteOnDay <= IN->Time[i+5].Data.uint16)){
                  OUT->State.Data.uint32|=BIT(TIMING_PUSK);//попали в интервал
                  OUT->State.Data.uint32|=BIT(i+16);//отмечаем интервал в который попали
                  break;
                }else {OUT->State.Data.uint32&=~BIT(i+16);}//отмечаем интервал в который попали
              } 
            }
          }
        }
      }else{
        OUT->State.Data.uint32 &=~BIT(TIME);
        OUT->State.Data.uint32|=BIT(TIMING_PUSK);
      }
      if (IN->Mode.Data.uint8 & TIMER_MODE){//режим работы - периодический
        if(!(OUT->State.Data.uint32 & BIT(TIMER))){
#ifdef MEGA12
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#else 
        OUT->FirstStartTime.Data.uint32 = GetSystemTime_t();
#endif
        }
        OUT->State.Data.uint32 |=BIT(TIMER);
        if((IN->Mode.Data.uint8 & BIT(PUSK)) &&(OUT->State.Data.uint32&BIT(TIMING_PUSK))){
          if(OUT->DownTimer.Data.uint16 == 0 && OUT->UpTimer.Data.uint16 == 0){
            OUT->State.Data.uint32 |=BIT(PUSK_ACTUATOR);
            OUT->UpTimer.Data.uint16 = IN->UpTime.Data.uint16;
            OUT->State.Data.uint32 |=BIT(UP_TIME);
            OUT->State.Data.uint32 &=~BIT(DOWN_TIME);
          }
          if (OUT->DownTimer.Data.uint16 != 0 && OUT->UpTimer.Data.uint16 == 0){//накопление
            OUT->State.Data.uint32 &=~BIT(PUSK_ACTUATOR);
            if (time_fb68&BIT(MINUT)) OUT->DownTimer.Data.uint16--;
            if (OUT->DownTimer.Data.uint16 == 0){
              OUT->UpTimer.Data.uint16 = IN->UpTime.Data.uint16;                
              OUT->State.Data.uint32 |=BIT(PUSK_ACTUATOR);
              OUT->State.Data.uint32 |=BIT(UP_TIME);
              OUT->State.Data.uint32 &=~BIT(DOWN_TIME);
            }
          }else if (OUT->UpTimer.Data.uint16 != 0 && OUT->DownTimer.Data.uint16 == 0){//работа
            OUT->State.Data.uint32 |=BIT(PUSK_ACTUATOR);
            if (time_fb68&BIT(MINUT)) OUT->UpTimer.Data.uint16--;
            if (OUT->UpTimer.Data.uint16 == 0){
              OUT->DownTimer.Data.uint16 = IN->DownTime.Data.uint16;                
              OUT->State.Data.uint32 &=~BIT(PUSK_ACTUATOR);
              OUT->State.Data.uint32 |=BIT(DOWN_TIME);
              OUT->State.Data.uint32 &=~BIT(UP_TIME);
            }
          }
        }else{
          OUT->TimerBeforeStart.Data.uint8 = IN->TimeBeforeStart.Data.uint8;
          OUT->State.Data.uint32 &=~BIT(PUSK_ACTUATOR);
          OUT->DownTimer.Data.uint16 = 0; 
          OUT->UpTimer.Data.uint16 = 0;
          OUT->State.Data.uint32 &=~BIT(DOWN_TIME);
          OUT->State.Data.uint32 &=~BIT(UP_TIME);
        }
      }else{
        OUT->State.Data.uint32 &=~BIT(TIMER);
        OUT->DownTimer.Data.uint16 = 0; 
        OUT->UpTimer.Data.uint16 = 0;
        OUT->State.Data.uint32 &=~BIT(DOWN_TIME);
        OUT->State.Data.uint32 &=~BIT(UP_TIME);
        if((IN->Mode.Data.uint8 & BIT(PUSK))&&(OUT->State.Data.uint32&BIT(TIMING_PUSK))){   //если без таймера то включаем по требованию
          OUT->State.Data.uint32|=BIT(PUSK_ACTUATOR);
        }else{
          OUT->State.Data.uint32&=~BIT(PUSK_ACTUATOR);
        }
      }
    }
    //независимо от того в каком режиме находимся проверяем наличие аварий
    if (((OUT->SPTimer.Data.uint16!=0))     //таймеры имеют какое либо значение только в случае разрешения 
        ||((OUT->APVTimer.Data.uint16!=0))){//соответсвующих защит или аварий
      OUT->State.Data.uint32 &=~BIT(PUSK_ACTUATOR);
      OUT->DownTimer.Data.uint16 = 0; 
      OUT->UpTimer.Data.uint16 = 0;
    }
  }else{
    OUT->State.Data.uint32&= ~BIT(PUSK_ACTUATOR);
  }
//---Actuator---принимает (OUT->State.Data.uint32&BIT(Actuator))
  if ((OUT->State.Data.uint32&BIT(PUSK_ACTUATOR))&&(OUT->State.Data.uint32 & BIT(BEFORSTART))){
    OUT->State.Data.uint32 &=~BIT(PUSK_ACTUATOR);
    if(time_fb68&BIT(SEC)){
      if ((--OUT->TimerBeforeStart.Data.uint8)==0){//если вышло время 
        OUT->State.Data.uint32 &=~BIT(BEFORSTART); //то не останавливаем включение
        OUT->State.Data.uint32 |=BIT(PUSK_ACTUATOR);
      }    
    }
  }
  if (IN->Mode.Data.uint8 & IMPULSE){ //импульсный режим 
    OUT->State.Data.uint32 |=BIT(IMPULSE_MODE);
    if ((OUT->State.Data.uint32&BIT(PUSK_ACTUATOR))!=(input_mask & BIT(ACTUATOR))){
      if ((OUT->State.Data.uint32&BIT(PUSK_ACTUATOR)) && IN->ActuatorRestart.Data.uint32 && VAR->ActuatorTimer.Data.uint32==0){
        VAR->ActuatorRestartCnt.Data.uint32--;
        VAR->ActuatorTimer.Data.uint32=(IN->ActuatorTime.Data.uint32<3)?3:IN->ActuatorTime.Data.uint32;
        OUT->ActuatorOn.Data.bit = 1;
        OUT->ActuatorOff.Data.bit = 0;
        OUT->State.Data.uint32|=BIT(START_TIME);
        OUT->DisregardTimer.Data.uint16 = IN->DisregardTime.Data.uint16;      // uint16 // обратный Таймер работы
      }
      if (!(OUT->State.Data.uint32&BIT(PUSK_ACTUATOR))){
        OUT->ActuatorOn.Data.bit = 0;
        OUT->ActuatorOff.Data.bit = 1;
      }
    }else{
      OUT->ActuatorOn.Data.bit = 0;
      OUT->ActuatorOff.Data.bit = 0;
      if (input_mask & BIT(ACTUATOR)){//дождались
        VAR->ActuatorRestartCnt.Data.uint32=(IN->ActuatorRestart.Data.uint32>10)?10:IN->ActuatorRestart.Data.uint32;
        VAR->ActuatorTimer.Data.uint32=0;
      }  
    }
    if (time_fb68&BIT(SEC)){
      if (VAR->ActuatorTimer.Data.uint32){
        VAR->ActuatorTimer.Data.uint32--;
        if(VAR->ActuatorTimer.Data.uint32==0){//недождались
          OUT->ActuatorOn.Data.bit = 0;
          OUT->ActuatorOff.Data.bit = 0;
        }
      }
    }
  }else{                                  //обычный режим
    OUT->State.Data.uint32 &=~BIT(IMPULSE_MODE);
    if (!(OUT->ActuatorOn.Data.bit) && (OUT->State.Data.uint32&BIT(PUSK_ACTUATOR))){

      OUT->State.Data.uint32|=BIT(START_TIME);
      OUT->DisregardTimer.Data.uint16 = IN->DisregardTime.Data.uint16;      // uint16 // обратный Таймер работы
    }
    OUT->ActuatorOn.Data.bit =(OUT->State.Data.uint32&BIT(PUSK_ACTUATOR))?1:0;
    OUT->ActuatorOff.Data.bit= 0 ;
    VAR->ActuatorTimer.Data.uint32=0;
  }
//---WATT
  if ((DaySec == 0)&&(time_fb68&BIT(SEC))){
    OUT->WattPreviuDay.Data.float32 = OUT->WattCurrentDay.Data.float32;          // uint32 // watt/hours
    OUT->WattCurrentDay.Data.float32=0;
  }
  if((time_fb68&BIT(MINUT))){ // мощность на следующей минуте
    OUT->WattCurrentDay.Data.float32 +=(float)(0.016666666) * IN->Watt[2].Data.uint16;
  }
//---WATT
  VAR->Input_mask.Data.uint16 = input_mask ;
  VAR->KernelClk.Data.uint32++;
#endif
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00068_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00068_IN_type);
    case(1):
        return sizeof(fb00068_VAR_type);
    case(2):
        return sizeof(fb00068_OUT_type);
    default:
        return 0;
    }
}
