/* �� "���" */
#define MEGA12

#ifdef MEGA12
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "../kernel.h"
#include "fb00099.h"
#define IntegralAccum 2
void fb00099_exec() {
	fb00099_IN_type *IN = (fb00099_IN_type *) FBInputs;
	fb00099_VAR_type *VAR = (fb00099_VAR_type *) FBVars;
	fb00099_OUT_type *OUT = (fb00099_OUT_type *) FBOutputs;
	float Ei_fb99; //"�������" � � ���������
  float dU_KP_fb99;  
  float dU_KI_fb99;
  float dU_KD_fb99;  
  float U_Out_fb99,dU_Out_fb99;  
#ifdef MEGA12
  if (KernelInfo.EventFlags.Bit.CfgFirstExec){///1 ����������
#else 
  if (EventFlags.Bit.CfgFirstExec){ //������ ���������� ��
#endif
    VAR->prevEi1.Data.float32 = 0.0;
    VAR->prevEi.Data.float32  = 0.0;
    VAR->NumberTick.Data.uint32=0.0;
  }
  if (IN->Rezet.Data.bit){
    VAR->prevEi1.Data.float32 = 0.0;
    VAR->prevEi.Data.float32  = 0.0;
    VAR->NumberTick.Data.uint32=0.0;
    VAR->prevUo.Data.float32 = IN->Position.Data.float32;
  }
  if (IN->Enable.Data.bit){
    Ei_fb99 = IN->RequireValue.Data.float32 - IN->CurrentValue.Data.float32;    //���������� �� ������������
    if ((Ei_fb99 > -IN->GistTube.Data.float32)&&(Ei_fb99 < IN->GistTube.Data.float32)) {Ei_fb99 = 0.0;}
    if (VAR->NumberTick.Data.uint32 != 0){
#ifdef MEGA12
      dU_KP_fb99 = IN->kP.Data.float32 * ((Ei_fb99 - VAR->prevEi.Data.float32)*KernelInfo.FBkernelRate);
#else 
      dU_KP_fb99 = IN->kP.Data.float32 * ((Ei_fb99 - VAR->prevEi.Data.float32)*FBkernelRate);
#endif
      dU_KI_fb99 = IN->kI.Data.float32 * Ei_fb99;
      if (VAR->NumberTick.Data.uint32 >= 2){  //������� ���� ������������ ������ ����� 3 �����
#ifdef MEGA12
        dU_KD_fb99 = IN->kD.Data.float32 * ((Ei_fb99 - 2*VAR->prevEi.Data.float32 + VAR->prevEi1.Data.float32)*KernelInfo.FBkernelRate);
#else 
        dU_KD_fb99 = IN->kD.Data.float32 * ((Ei_fb99 - 2*VAR->prevEi.Data.float32 + VAR->prevEi1.Data.float32)*FBkernelRate);
#endif

      }else{
        dU_KD_fb99 = 0.0;
      }
    }else{  //��� ������ ������� ����������� ������ ����� ������������������
      dU_KP_fb99 = IN->kP.Data.float32 * (Ei_fb99); //��� ��������� PID �� ����� �� dT
      if (IN->Position.Data.float32 > 100.0){VAR->prevUo.Data.float32  = 100.0;}
      if (IN->Position.Data.float32 < 0.0){VAR->prevUo.Data.float32  = 0.0;}
      else{ VAR->prevUo.Data.float32  = IN->Position.Data.float32; }
      dU_KI_fb99 = 0.0;
      dU_KD_fb99 = 0.0;
    }
    dU_Out_fb99 = dU_KP_fb99 + dU_KI_fb99 + dU_KD_fb99;
    if (dU_Out_fb99 > 100.0) dU_Out_fb99 = 100.0;
    else if (dU_Out_fb99 < -100.0) dU_Out_fb99 = -100.0;
    if (IN->ReverseU.Data.bit) dU_Out_fb99 = -dU_Out_fb99;
    U_Out_fb99 = VAR->prevUo.Data.float32 + dU_Out_fb99 ;
 		VAR->prevEi1.Data.float32 = VAR->prevEi.Data.float32;
 		VAR->prevEi.Data.float32 = Ei_fb99;
    if (U_Out_fb99 > 100.0 + IntegralAccum) VAR->prevUo.Data.float32 = 100.0 + IntegralAccum;
    else if (U_Out_fb99 < 0.0 - IntegralAccum) VAR->prevUo.Data.float32 = 0.0 - IntegralAccum;
    else VAR->prevUo.Data.float32 = U_Out_fb99;
		OUT->Test.Data.float32 = dU_Out_fb99;
    VAR->NumberTick.Data.uint32++;
  }else{
    VAR->prevEi1.Data.float32 =  0.0;
    VAR->prevEi.Data.float32  =  0.0;
    VAR->NumberTick.Data.uint32= 0.0;
    if (IN->Position.Data.float32 > 100.0){VAR->prevUo.Data.float32  = 100.0;}
    if (IN->Position.Data.float32 < 0.0){VAR->prevUo.Data.float32  = 0.0;}
    else{ VAR->prevUo.Data.float32  = IN->Position.Data.float32; }
  }
//������ �������� �� ����� 
  if (VAR->prevUo.Data.float32 > 99.5) OUT->Output.Data.float32 = 100.0;
  else if (VAR->prevUo.Data.float32 <= 0.5) OUT->Output.Data.float32 = 0.0;
  else OUT->Output.Data.float32 = VAR->prevUo.Data.float32 ;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00099_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00099_IN_type);
    case(1):
        return sizeof(fb00099_VAR_type);
    case(2):
        return sizeof(fb00099_OUT_type);
    default:
        return 0;
    }
}
