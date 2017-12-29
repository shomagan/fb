/* ФБ двухчасовка (счётчик-архиватор) */
#define MEGA12
#include <time.h>

#ifdef MEGA12
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "../kernel.h"
#include "fb00093.h"

void fb00093_exec(void){
  unsigned int Time, NowTime;
  unsigned int Proshlo;
  struct tm *ptmx;
  char R7Buff[R7_BodySize];
  
  fb00093_IN_type *IN = (fb00093_IN_type *) &FBInputs;
  fb00093_OUT_type *OUT = (fb00093_OUT_type *) &FBOutputs;
  if (FB_N_In==3){
    IN->CounterHour.Data.uint8 = 0;
  }
  IN->CounterHour.Data.uint8 = IN->CounterHour.Data.uint8 > 23 ? 0:IN->CounterHour.Data.uint8;
  
#ifdef MEGA12
  if (KernelInfo.EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#else 
  if (EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#endif
  {
    OUT->StartTime.Data.uint32 = GetSystemTime_t();
    if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
      OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
    }else{
      OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;  
    }
  }
  if (IN->Period.Data.uint16 < 3){//если замер меньше 3 минут фб не в работе
    if ((IN->CounterIn.Type  & DataTypeMask)!= KodFloat32){
      OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
      OUT->CounterOut.Data.uint32 = 0;//сброс счётчика ТИ
    }else{
      OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;
      OUT->CounterOut.Data.float32  = 0;//сброс счётчика ТИ
    }
    OUT->OK.Data.bit = 0;
    OUT->StartTime.Data.uint32 = GetSystemTime_t();
  }else{
    if (OUT->OK.Data.bit){//было формирование архива
      if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
        OUT->CounterOut.Data.uint32 = 0;//сброс счётчика ТИ        
      }else{
        OUT->CounterOut.Data.float32 = 0;
      }
      OUT->OK.Data.bit = 0;
    }
    if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
      if(IN->CounterIn.Data.uint32 != OUT->OldCounterIn.Data.uint32){//если было изменение
        if((IN->CounterIn.Data.uint32 > OUT->OldCounterIn.Data.uint32) || //было приращение или переполнение
          ((IN->CounterIn.Data.uint32 <= 0x000000ff) && (OUT->OldCounterIn.Data.uint32 > 0xffffff00))){
          OUT->CounterOut.Data.uint32 += IN->CounterIn.Data.uint32 - OUT->OldCounterIn.Data.uint32;
        }//иначе считаем, что был сброс входящего счётчика
        OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
      }
    }else{
      if(IN->CounterIn.Data.float32 != OUT->OldCounterIn.Data.float32){//если было изменение
        if(OUT->OldCounterIn.Data.float32!=0.0){
          OUT->CounterOut.Data.float32 += IN->CounterIn.Data.float32 - OUT->OldCounterIn.Data.float32;
        }
        OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;
      }
    }
  #ifdef MEGA12
    if(FB32blok.vars.Cnt1Sec==0)
  #else 
    if (SystemTime.sec == 0)//чтобы не заниматься ненужными вычислениями идём дальше только в 0 секунд
  #endif
    {
      NowTime = GetSystemTime_t();
      //замер заканчивается, если а)прошёл заданный период, но не двухчасовка,
      //б) период=120 и граница двухчасовки, но прошло не менее 5 минут
      //при двухчасовках - выравнивание к началу суток происходит автоматически автоматически
      //в) ошибка сохранения OUT->StartTime (делаем архив длительностью 65535)
      //g) переиод ==1440 то делаем двухчасовку в начале суток
      if (NowTime >= OUT->StartTime.Data.uint32){
        Proshlo = (NowTime - OUT->StartTime.Data.uint32)/60;
      } else {
        Proshlo = 0x0000ffff;
      }
  #ifdef MEGA12
      if (((Proshlo >= IN->Period.Data.uint16) && (IN->Period.Data.uint16 != 120)) || (Proshlo >= 0x0000ffff)
        || ((Proshlo >= 5) && (IN->Period.Data.uint16 == 120) &&
            (FB32blok.vars.Cnt1Min < 5) && (((FB32blok.vars.Cnt1Chas+IN->CounterHour.Data.uint8) & 1)==0))
        || ((Proshlo >= 5) && (IN->Period.Data.uint16 == 1440) && 
            (FB32blok.vars.Cnt1Sec==0)&&(FB32blok.vars.Cnt1Min==0)&&(FB32blok.vars.Cnt1Chas==IN->CounterHour.Data.uint8)))
  #else 
      if (((Proshlo >= IN->Period.Data.uint16) && (IN->Period.Data.uint16 != 120)) || (Proshlo >= 0x0000ffff)
        || ((Proshlo >= 5) && (IN->Period.Data.uint16 == 120) && 
            (SystemTime.min < 5) && (((SystemTime.hour+IN->CounterHour.Data.uint8) & 1)==0))
        || ((Proshlo >= 5) && (IN->Period.Data.uint16 == 1440) &&
            (FB32blok.vars.Cnt1Sec==0)&&(FB32blok.vars.Cnt1Min==0)&&(FB32blok.vars.Cnt1Chas==IN->CounterHour.Data.uint8)))
  #endif
      {
  #ifdef MEGA12
        if (1) //если есть место в очереди на архивирование
  #else
        if (ArcQCount < ArcQsize) //если есть место в очереди на архивирование
  #endif
        {
          Time = OUT->StartTime.Data.uint32;
          ptmx = localtime(&Time);    // Преобразование времени из UNIX-формата
          R7Buff[0] = 0;                                        // Номер канала
          R7Buff[1] = 0;                                        // В R5 здесь были номера последней записанной
          R7Buff[2] = 0;                                        // и последней прочитанной записей R5
          R7Buff[3] = 2;                                        // Тип записи (из R5) = 2 (БГ)
          R7Buff[4] = IN->CntNum.Data.uint8;                    // Номер счётчика
          R7Buff[5] = (char) (OUT->CounterOut.Data.uint32);       // Счётчик мл.
          R7Buff[6] = (char) (OUT->CounterOut.Data.uint32 >> 8); // Счётчик
          R7Buff[7] = (char) (OUT->CounterOut.Data.uint32 >> 16);// Счётчик
          R7Buff[8] = (char) (OUT->CounterOut.Data.uint32 >> 24);// Счётчик ст.
          R7Buff[9] = ptmx->tm_sec;                             // Время начала - сек
          R7Buff[10] = ptmx->tm_min;                            // Время начала - мин
          R7Buff[11] = ptmx->tm_hour;                           // Время начала - час
          R7Buff[12] = ptmx->tm_mday;                           // Время начала - день
          R7Buff[13] = ptmx->tm_mon+1;                          // Время начала - мес
          R7Buff[14] = ptmx->tm_year-80;                        // Время начала - год c 1980
          R7Buff[15] = (char) (Proshlo);                        // Длительность в минутах мл.
          R7Buff[16] = (char) (Proshlo >> 8);                   // Длительность в минутах ст.
          for (char k=17; k<R7_BodySize; k++)
            R7Buff[k] = 0;
          NewQ_Arc_R7(R7Buff, 17);  // Передаём тело архива архиватору
          OUT->OK.Data.bit = 1;
          OUT->StartTime.Data.uint32 = NowTime;
        }//иначе попробуем следующий раз
      }
    }
  }
}
