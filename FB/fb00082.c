/* ФБ "ПИД" */
#include "../kernel.h"
#include <math.h>
#ifdef MEGA12
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "fb00082.h"
#define IntegralAccum 2
void fb00082_exec() {
	fb00082_IN_type *IN = (fb00082_IN_type *) FBInputs;
	fb00082_VAR_type *VAR = (fb00082_VAR_type *) FBVars;
	fb00082_OUT_type *OUT = (fb00082_OUT_type *) FBOutputs;
	float Ei_fb82; //"невязка" и её изменение
  float dU_KP_fb82;  
  float dU_KI_fb82;
  float dU_KD_fb82;  
  float U_Out_fb82,dU_Out_fb82;  
  IN->DelayTime.Data.uint32 = (IN->DelayTime.Data.uint32==0)?1:IN->DelayTime.Data.uint32;//проверка
#ifdef MEGA12
  if (KernelInfo.EventFlags.Bit.CfgFirstExec){///1 выполнение
#else 
  if (EventFlags.Bit.CfgFirstExec){ //первое исполнение ФБ
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
    Ei_fb82 = IN->RequireValue.Data.float32 - IN->CurrentValue.Data.float32;    //гистерезис не реагирования
    if ((Ei_fb82 > -IN->GistTube.Data.float32)&&(Ei_fb82 < IN->GistTube.Data.float32)) {Ei_fb82 = 0.0;}
    if (VAR->NumberTick.Data.uint32 != 0){
#ifdef MEGA12
      dU_KP_fb82 = IN->kP.Data.float32 * ((Ei_fb82 - VAR->prevEi.Data.float32)*KernelInfo.FBkernelRate);
#else 
      dU_KP_fb82 = IN->kP.Data.float32 * ((Ei_fb82 - VAR->prevEi.Data.float32)*FBkernelRate);
#endif
      dU_KI_fb82 = IN->kI.Data.float32 * Ei_fb82;
      if (VAR->NumberTick.Data.uint32 >= 2){  //добавим дифф составляющию только после 3 такта
#ifdef MEGA12
        dU_KD_fb82 = IN->kD.Data.float32 * ((Ei_fb82 - 2*VAR->prevEi.Data.float32 + VAR->prevEi1.Data.float32)*KernelInfo.FBkernelRate);
#else 
        dU_KD_fb82 = IN->kD.Data.float32 * ((Ei_fb82 - 2*VAR->prevEi.Data.float32 + VAR->prevEi1.Data.float32)*FBkernelRate);
#endif

      }else{
        dU_KD_fb82 = 0.0;
      }
    }else{  //при первом расчете расчитываем только Коэфф пропорциональности
      dU_KP_fb82 = IN->kP.Data.float32 * (Ei_fb82); //при включении PID не делим на dT
      if (IN->Position.Data.float32 > 100.0f){VAR->prevUo.Data.float32  = 100.0f;}
      if (IN->Position.Data.float32 < 0.0f){VAR->prevUo.Data.float32  = 0.0f;}
      else{ VAR->prevUo.Data.float32  = IN->Position.Data.float32; }
      dU_KI_fb82 = 0.0f;
      dU_KD_fb82 = 0.0f;
    }
    dU_Out_fb82 = dU_KP_fb82 + dU_KI_fb82 - dU_KD_fb82;
    if (dU_Out_fb82 > 100.0f) dU_Out_fb82 = 100.0f;
    else if (dU_Out_fb82 < -100.0f) dU_Out_fb82 = -100.0f;
    if (IN->ReverseU.Data.bit) dU_Out_fb82 = -dU_Out_fb82;
    U_Out_fb82 = VAR->prevUo.Data.float32 + dU_Out_fb82 ;
 		VAR->prevEi1.Data.float32 = VAR->prevEi.Data.float32;
 		VAR->prevEi.Data.float32 = Ei_fb82;
    if (U_Out_fb82 > 100.0f + IntegralAccum) VAR->prevUo.Data.float32 = 100.0f + IntegralAccum;
    else if (U_Out_fb82 < 0.0f - IntegralAccum) VAR->prevUo.Data.float32 = 0.0f - IntegralAccum;
    else VAR->prevUo.Data.float32 = U_Out_fb82;
		OUT->Test.Data.float32 = dU_Out_fb82;
    VAR->NumberTick.Data.uint32++;
  }else{
    VAR->prevEi1.Data.float32 =  0.0f;
    VAR->prevEi.Data.float32  =  0.0f;
    VAR->NumberTick.Data.uint32= 0.0f;
    if (IN->Position.Data.float32 > 100.0f){VAR->prevUo.Data.float32  = 100.0f;}
    if (IN->Position.Data.float32 < 0.0f){VAR->prevUo.Data.float32  = 0.0f;}
    else{ VAR->prevUo.Data.float32  = IN->Position.Data.float32; }
  }
//выдаем значение на выход 
  if (VAR->NumberTick.Data.uint32==1||(VAR->NumberTick.Data.uint32%IN->DelayTime.Data.uint32==0)){
    if (VAR->prevUo.Data.float32 > 99.5f) OUT->Output.Data.float32 = 100.0f;
    else if (VAR->prevUo.Data.float32 <= 0.5f) OUT->Output.Data.float32 = 0.0f;
    else OUT->Output.Data.float32 = VAR->prevUo.Data.float32 ;
  }
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00082_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00082_IN_type);
    case(1):
        return sizeof(fb00082_VAR_type);
    case(2):
        return sizeof(fb00082_OUT_type);
    default:
        return 0;
    }
}
