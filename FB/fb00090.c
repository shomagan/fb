/* �� "����� � ���" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00090.h"
void fb00090_exec()
{
  
fb00090_IN_type *IN = (fb00090_IN_type *) (&FBInputs);
fb00090_VAR_type *VAR = (fb00090_VAR_type *) &FBVars;
fb00090_OUT_type *OUT = (fb00090_OUT_type *) &FBOutputs;


VAR->SecTimer.Data.uint8++;

if (IN->ActuatorTime.Data.uint32 < 3)
	IN->ActuatorTime.Data.uint32 = 3;
	else if(IN->ActuatorTime.Data.uint32 >100) // ������������ ����� �������� ���������
		IN->ActuatorTime.Data.uint32 = 100;

if (IN->TimeNonStop.Data.uint32 < 5)
	IN->TimeNonStop.Data.uint32 = 5;
	else if(IN->TimeNonStop.Data.uint32 > 1600)//������������ ����� ���������� ����� 1600 ��� 
		IN->TimeNonStop.Data.uint32 = 1600;

if (IN->APV_Interval.Data.uint32 < 30)
	IN->APV_Interval.Data.uint32 = 30;
	else if(IN->APV_Interval.Data.uint32 >43200) //������������ ����� ����������� �� ���  12 ����� 
	IN->APV_Interval.Data.uint32 = 43200;
if (KernelInfo.EventFlags.Bit.CfgFirstExec)///1 ����������
{
//	OUT->stUprav.Data.bit = 1;
	OUT->State.Data.uint32 = 0;
	OUT->Control_ON.Data.bit = OUT->Control_OFF.Data.bit = 0;
	OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;//������ �� ����� ��������� �������� ���������?
	OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
	OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
	OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
	OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;
}
else{
/////////////////////////////////////////////��������� �������������� ������
    if (IN->Dist_mode.Data.bit)     //��������� ��������������� ���������� ���� ���
    {
    	OUT->State.Data.uint32 |= s00090_Dist;
    	if (IN->APV_TryNum.Data.uint16 > 0)	OUT->State.Data.uint32 |= s00090_APVon;
    	else OUT->State.Data.uint32 &= ~s00090_APVon;
    }
    else OUT->State.Data.uint32 &= ~s00090_Dist;//
         
    if (IN->Alarm.Data.bit)//��������� �����
    	OUT->State.Data.uint32 |= s00090_Alarm;
    else
    	OUT->State.Data.uint32 &= ~s00090_Alarm;
    //
    if (IN->Block.Data.bit)//����������
    	OUT->State.Data.uint32 |= s00090_Block;
    else
    	OUT->State.Data.uint32 &= ~s00090_Block;
    //		
    if (IN->Actuator.Data.bit)//� ������ ��������� ���������
    	OUT->State.Data.uint32 |= s00090_Actuator;//
    else
    	OUT->State.Data.uint32 &= ~s00090_Actuator;
    //

		if ((OUT->State.Data.uint32 & s00090_Dist)==0) //������������� ���������� n� �����������
    {
			OUT->stUprav.Data.bit = 0;
			OUT->State.Data.uint32 &= s00090_UpravMask;
			OUT->Control_ON.Data.bit = OUT->Control_OFF.Data.bit = 0;
			OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
			OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
			OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
			OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
			OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;
		}
   	else{ //������������� ���������� ��� �����������         	 
/*
����� ����������,������ ������� ����������� ������ ��������� �������, ������ "����������� 
������������ ��������� ���������" ��������� �� ��������� �� ������� ������� ����������
*/
			if (OUT->State.Data.uint32 & (s00090_flBlock|s00090_flAlarm|s00090_ActuatorFail_ON|s00090_ActuatorFail_OFF)) {
				OUT->stUprav.Data.bit = 0;
				}
			else OUT->stUprav.Data.bit = 1;
//            
//            ����� ������
			if  (IN->Reset.Data.bit) //Reset - �������
      {
		//	OUT->stUprav.Data.bit = 0;
  			OUT->State.Data.uint32  &= ~(s00090_flBlock|s00090_flAlarm|s00090_ActuatorFail_ON|s00090_ActuatorFail_OFF);
  			OUT->Control_ON.Data.bit = OUT->Control_OFF.Data.bit = 0;
  			OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
  			OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
  			OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
  			OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
  			OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;
			}
//����� ��������� ���������� 
			if (OUT->State.Data.uint32 & s00090_Block)
   		{ 
        if (((OUT->State.Data.uint32 &  s00090_flBlock ) == 0)) 
				{
   				OUT->State.Data.uint32 |= s00090_flBlock;
  				if (IN->Actuator.Data.bit||((OUT->State.Data.uint32 & s00090_WaitActuator) && (OUT->State.Data.uint32 & s00090_ExpectActuator)))//�������� ���������� �� ��������� ��� ���� ������� ������� ��
   				{
      			OUT->State.Data.uint32 |= s00090_Need_OFF;
      			OUT->State.Data.uint32 &= ~s00090_Need_ON;
   				}else 
          	OUT->State.Data.uint32 &= ~(s00090_WaitActuator|s00090_Need_OFF|s00090_Need_ON|s00090_ExpectActuator);
        }
			}
//��������� �������� ������(2
//������ ����������� ���������� ����� ��������� ���m��� CntNonStop
			if ((OUT->State.Data.uint32 & s00090_Alarm ) && ((OUT->State.Data.uint32 & s00090_flAlarm)==0) && (OUT->State.Data.uint32 & s00090_Actuator))
			{
        OUT->State.Data.uint32 |= s00090_WaitAPV;
  			if (OUT->CntNonStop.Data.uint32) 
        {
        	if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
					OUT->CntNonStop.Data.uint32--;
					}
        }
        else 
        {
 		
   				OUT->State.Data.uint32 &= ~s00090_WaitAPV;//����� ��������� ������� ����� �������� ����������
         	OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;//?APV_Timer
   				OUT->State.Data.uint32 |= s00090_flAlarm;
   				OUT->State.Data.uint32 &= ~s00090_ReinitAPV;
   				VAR->CntReinitAPV.Data.uint32 = IN->TimeNonStop.Data.uint32 << 2;
          if (IN->Actuator.Data.bit||((OUT->State.Data.uint32 & s00090_WaitActuator) && (OUT->State.Data.uint32 & s00090_ExpectActuator)))//�������� ���������� �� ��������� ��� ���� ������� ������� ��
   			  {
   				  OUT->State.Data.uint32 |= s00090_Need_OFF;
   				  OUT->State.Data.uint32 &= ~s00090_Need_ON;
   				}else OUT->State.Data.uint32 &= ~(s00090_WaitActuator|s00090_Need_OFF|s00090_Need_ON|s00090_ExpectActuator);
   			} 
			}
			else
			{ 
			OUT->State.Data.uint32 &= ~s00090_WaitAPV; 
			OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;                        
			}
//��������� 
			if (IN->Cmd_ON.Data.bit&&(!(OUT->State.Data.uint32 & s00090_Need_OFF))) 
		  {
				if (IN->Cmd_OFF.Data.bit)
				{
				  OUT->State.Data.uint32 &= ~s00090_ReinitAPV;
				  OUT->State.Data.uint32 &= ~s00090_Need_ON;
				}else if (!(IN->Actuator.Data.bit)){
				  OUT->State.Data.uint32 |= s00090_Need_ON;
				  OUT->State.Data.uint32 &= ~s00090_Need_OFF;
				}
			}
//���������� 
			if (IN->Cmd_OFF.Data.bit && (!((OUT->State.Data.uint32 & s00090_WaitActuator) && (!(OUT->State.Data.uint32 & s00090_ExpectActuator)))))
		  {
				if (IN->Actuator.Data.bit || ((OUT->State.Data.uint32 & s00090_WaitActuator) && (OUT->State.Data.uint32 & s00090_ExpectActuator)))//�������� ���������� �� ��������� ��� ���� ������� ������� ��
				{
				  OUT->State.Data.uint32 |= s00090_Need_OFF;
				  OUT->State.Data.uint32 &= ~s00090_Need_ON;
				}
			}
//������������� ��� �������, �������� ������ ��������� ��������� s00090_WaitActuator, ������ 1 � ExpectActuator  � �������� ��������
			if (OUT->State.Data.uint32 & s00090_Need_ON) 
			{
				if ((OUT->State.Data.uint32|s00090_APVon|s00090_ReinitAPV|s00090_Alarm)==s00090_StartMaskAPV){
					OUT->State.Data.uint32 |= (s00090_WaitActuator | s00090_ExpectActuator | s00090_WaitImpONOFF);
					OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
					OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
					OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
				}
				OUT->State.Data.uint32 &= ~s00090_Need_ON;				
			}                    
//������ 0 � ExpectActuator ����� ��������� �������� �������� ������
			if (OUT->State.Data.uint32 & s00090_Need_OFF) {//���� ���������� 
				if (!(OUT->State.Data.uint32&(s00090_ActuatorFail_OFF | s00090_ActuatorFail_ON)))
        {
					OUT->State.Data.uint32 &= ~s00090_ExpectActuator;
					OUT->State.Data.uint32 |= (s00090_WaitActuator | s00090_WaitImpONOFF);
					OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
					OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
					OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
			  }
			  OUT->State.Data.uint32 &= ~s00090_WaitAPV;
	      OUT->State.Data.uint32 &= ~s00090_Need_OFF;
			}
////////////////////////////////////////////
	if (OUT->State.Data.uint32 & s00090_WaitActuator) {//�������� ��������� 
/////////////////////////////////////////////////////////////*
    if (OUT->CntActRestart.Data.uint16)//������ ������� �������
    { 
      if (OUT->State.Data.uint32 & s00090_WaitImpONOFF) //���� �������� ��� ����� �����
      {
        if (OUT->CntImpONOFF.Data.uint8 == 0) //� ������ ���������
        {
//          OUT->State.Data.uint32 &= ~s00090_WaitImpONOFF;
          OUT->Control_ON.Data.bit = 0;
          OUT->Control_OFF.Data.bit =0;
        } 
        else
        {
          if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate)
          OUT->CntImpONOFF.Data.uint8--;

          if (OUT->State.Data.uint32 & s00090_ExpectActuator) {//� �����������, ��� �������, ��������� ��������
            OUT->Control_ON.Data.bit = 1;
            OUT->Control_OFF.Data.bit = 0;
          } else
          {
            OUT->Control_ON.Data.bit = 0;
            OUT->Control_OFF.Data.bit = 1;
          }
        }
      }                
      /////////////////////////////////////////////////////////**                    
      if (OUT->CntActTime.Data.uint32)
      {
        if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) OUT->CntActTime.Data.uint32--;//?????
      } 
      else//��������� ��������� �������� ����� ������� �������� ���������
      {
        OUT->CntActRestart.Data.uint16--;
        OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
        OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
        if ((OUT->State.Data.uint32 & s00090_ExpectActuator) && (IN->Actuator.Data.bit)) //��������� �������� ���������� �������� � ��������� ��������� � ������ ����� ������� �������� ���������
        {
          OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
          OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
          OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
          OUT->State.Data.uint32 &= ~(s00090_WaitActuator | s00090_WaitImpONOFF | s00090_ExpectActuator);
        }
        else if ((!(OUT->State.Data.uint32 & s00090_ExpectActuator)) && (!(IN->Actuator.Data.bit))) 
        {
          OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
          OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
          OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
          OUT->State.Data.uint32 &= ~(s00090_WaitActuator | s00090_WaitImpONOFF | s00090_ExpectActuator);
        }
      }
      /////////////////////////////////////////////////////////**                    

    }else{
  /////////////////////////////////////////////////////////////*� ������ ��������� �������� CntActRestart     
      if (OUT->State.Data.uint32 & s00090_ExpectActuator) 
      {
        OUT->State.Data.uint32 |= s00090_ActuatorFail_ON;
        OUT->State.Data.uint32 |= s00090_WaitImpSTOP;
        OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
        OUT->State.Data.uint32 &= ~s00090_ReinitAPV;
      }
      else
      {
        OUT->State.Data.uint32 &= ~s00090_ReinitAPV;   
        OUT->State.Data.uint32 |= s00090_ActuatorFail_OFF;
      }
        OUT->State.Data.uint32 &= ~(s00090_WaitActuator | s00090_ExpectActuator | s00090_WaitImpONOFF);
        OUT->Control_ON.Data.bit = 0;
        OUT->Control_OFF.Data.bit = 0;
    }
	}
////////////////////////////////////////////���������� ���� �������� ���������
//////////////////////////////////////////////
  if (OUT->State.Data.uint32 & s00090_WaitImpSTOP) 
  {
    if (OUT->CntImpONOFF.Data.uint8)             
    {
      if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) 	OUT->CntImpONOFF.Data.uint8--;
      OUT->Control_OFF.Data.bit = 1;//1
      OUT->Control_ON.Data.bit = 0;
    }
    else //0
    {
      OUT->Control_OFF.Data.bit = 0;
      OUT->Control_ON.Data.bit = 0;
      OUT->State.Data.uint32 &= ~s00090_WaitImpSTOP;					
    }
  }
/////////////////////////////////////���� ��� 
  if (((OUT->State.Data.uint32|s00090_ReinitAPV|s00090_Alarm) == s00090_APVMask2ON) )//if  { ((!(OUT->State.Data.uint32 & s00090_APVMask1OFF)) || (!(OUT->State.Data.uint32 & s00090_APVMask2OFF))))
  {
    if (OUT->APV_TryCnt.Data.uint16) 
    {
    if (OUT->APV_Timer.Data.uint32) 
      {
      if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) OUT->APV_Timer.Data.uint32--;
      } 
      else 
      {
        OUT->APV_TryCnt.Data.uint16--;
        OUT->State.Data.uint32 &= ~(s00090_flAlarm ); //���������� ���
        OUT->State.Data.uint32 |= s00090_ReinitAPV;   
      }
    }
    else  OUT->State.Data.uint32 |= s00090_APV_TryCnt_Null;
  }
  if ((OUT->State.Data.uint32 & s00090_ReinitAPV)) 
  {
    if (VAR->CntReinitAPV.Data.uint32 == 0) 
    {
      OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
      OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;//?APV_Timer
      OUT->State.Data.uint32 &= ~s00090_ReinitAPV;
    } 
    else if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate)VAR->CntReinitAPV.Data.uint32--;
  }
}

if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) //����� ������� ������� ������, ����������� � ����� �����
   	VAR->SecTimer.Data.uint8 = 0;

}
}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00090_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00090_IN_type);
    case(1):
        return sizeof(fb00090_VAR_type);
    case(2):
        return sizeof(fb00090_OUT_type);
    default:
        return 0;
    }
}
