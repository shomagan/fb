/* �� ����������� (�������-���������) */
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
  if (KernelInfo.EventFlags.Bit.CfgFirstExec) //������ ���������� ��
#else 
  if (EventFlags.Bit.CfgFirstExec) //������ ���������� ��
#endif
  {
    OUT->StartTime.Data.uint32 = GetSystemTime_t();
    if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
      OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
    }else{
      OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;  
    }
  }
  if (IN->Period.Data.uint16 < 3){//���� ����� ������ 3 ����� �� �� � ������
    if ((IN->CounterIn.Type  & DataTypeMask)!= KodFloat32){
      OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
      OUT->CounterOut.Data.uint32 = 0;//����� �������� ��
    }else{
      OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;
      OUT->CounterOut.Data.float32  = 0;//����� �������� ��
    }
    OUT->OK.Data.bit = 0;
    OUT->StartTime.Data.uint32 = GetSystemTime_t();
  }else{
    if (OUT->OK.Data.bit){//���� ������������ ������
      if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
        OUT->CounterOut.Data.uint32 = 0;//����� �������� ��        
      }else{
        OUT->CounterOut.Data.float32 = 0;
      }
      OUT->OK.Data.bit = 0;
    }
    if ((IN->CounterIn.Type & DataTypeMask)!= KodFloat32){
      if(IN->CounterIn.Data.uint32 != OUT->OldCounterIn.Data.uint32){//���� ���� ���������
        if((IN->CounterIn.Data.uint32 > OUT->OldCounterIn.Data.uint32) || //���� ���������� ��� ������������
          ((IN->CounterIn.Data.uint32 <= 0x000000ff) && (OUT->OldCounterIn.Data.uint32 > 0xffffff00))){
          OUT->CounterOut.Data.uint32 += IN->CounterIn.Data.uint32 - OUT->OldCounterIn.Data.uint32;
        }//����� �������, ��� ��� ����� ��������� ��������
        OUT->OldCounterIn.Data.uint32 = IN->CounterIn.Data.uint32;
      }
    }else{
      if(IN->CounterIn.Data.float32 != OUT->OldCounterIn.Data.float32){//���� ���� ���������
        if(OUT->OldCounterIn.Data.float32!=0.0){
          OUT->CounterOut.Data.float32 += IN->CounterIn.Data.float32 - OUT->OldCounterIn.Data.float32;
        }
        OUT->OldCounterIn.Data.float32 = IN->CounterIn.Data.float32;
      }
    }
  #ifdef MEGA12
    if(FB32blok.vars.Cnt1Sec==0)
  #else 
    if (SystemTime.sec == 0)//����� �� ���������� ��������� ������������ ��� ������ ������ � 0 ������
  #endif
    {
      NowTime = GetSystemTime_t();
      //����� �������������, ���� �)������ �������� ������, �� �� �����������,
      //�) ������=120 � ������� �����������, �� ������ �� ����� 5 �����
      //��� ������������ - ������������ � ������ ����� ���������� ������������� �������������
      //�) ������ ���������� OUT->StartTime (������ ����� ������������� 65535)
      //g) ������� ==1440 �� ������ ����������� � ������ �����
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
        if (1) //���� ���� ����� � ������� �� �������������
  #else
        if (ArcQCount < ArcQsize) //���� ���� ����� � ������� �� �������������
  #endif
        {
          Time = OUT->StartTime.Data.uint32;
          ptmx = localtime(&Time);    // �������������� ������� �� UNIX-�������
          R7Buff[0] = 0;                                        // ����� ������
          R7Buff[1] = 0;                                        // � R5 ����� ���� ������ ��������� ����������
          R7Buff[2] = 0;                                        // � ��������� ����������� ������� R5
          R7Buff[3] = 2;                                        // ��� ������ (�� R5) = 2 (��)
          R7Buff[4] = IN->CntNum.Data.uint8;                    // ����� ��������
          R7Buff[5] = (char) (OUT->CounterOut.Data.uint32);       // ������� ��.
          R7Buff[6] = (char) (OUT->CounterOut.Data.uint32 >> 8); // �������
          R7Buff[7] = (char) (OUT->CounterOut.Data.uint32 >> 16);// �������
          R7Buff[8] = (char) (OUT->CounterOut.Data.uint32 >> 24);// ������� ��.
          R7Buff[9] = ptmx->tm_sec;                             // ����� ������ - ���
          R7Buff[10] = ptmx->tm_min;                            // ����� ������ - ���
          R7Buff[11] = ptmx->tm_hour;                           // ����� ������ - ���
          R7Buff[12] = ptmx->tm_mday;                           // ����� ������ - ����
          R7Buff[13] = ptmx->tm_mon+1;                          // ����� ������ - ���
          R7Buff[14] = ptmx->tm_year-80;                        // ����� ������ - ��� c 1980
          R7Buff[15] = (char) (Proshlo);                        // ������������ � ������� ��.
          R7Buff[16] = (char) (Proshlo >> 8);                   // ������������ � ������� ��.
          for (char k=17; k<R7_BodySize; k++)
            R7Buff[k] = 0;
          NewQ_Arc_R7(R7Buff, 17);  // ������� ���� ������ ����������
          OUT->OK.Data.bit = 1;
          OUT->StartTime.Data.uint32 = NowTime;
        }//����� ��������� ��������� ���
      }
    }
  }
}
