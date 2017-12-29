/* ФБ "фильтр универсальный" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00115.h"

void reset_value(fb00115_IN_type *IN,fb00115_OUT_type *OUT,fb00115_VAR_type *VAR){
  VAR->TikTimer.Data.uint32 = 0;
	switch (IN->Input.Type & DataTypeMask) {   // Тип входа
		case KodBit:
		case KodInt8:
		case KodInt16:
		case KodInt32:
		case KodTime32:
      if ((OUT->Output.Type & DataTypeMask)==KodFloat32){
        OUT->Output.Data.float32 = (float)IN->Input.Data.uint32;
      }else{
        OUT->Output.Data.uint32 = IN->Input.Data.uint32;
      }
      VAR->OldOutput.Data.float32 = (float)IN->Input.Data.uint32;
			break;
    case KodFloat32:
      if ((OUT->Output.Type & DataTypeMask)==KodFloat32){
        OUT->Output.Data.float32 = IN->Input.Data.float32;
      }else{
        OUT->Output.Data.uint32 = (u32)IN->Input.Data.float32;
      }
      VAR->OldOutput.Data.float32 = IN->Input.Data.float32;
      break;
    default:
      break;
	}
}

void fb00115_exec(void) {
  float current_value,previu_value,value;
  float tik_transformed;
	float FilterTime;

	fb00115_IN_type *IN = (fb00115_IN_type *) FBInputs;
	fb00115_OUT_type *OUT = (fb00115_OUT_type *) FBOutputs;
	fb00115_VAR_type *VAR = (fb00115_VAR_type *) FBVars;    
  if ((FB_N_In!=4)||(FB_N_Vars!=2)||(FB_N_Out!=1)){
    LedErrorOn(30);
  }

  if (KernelInfo.EventFlags.Bit.CfgFirstExec){  // Первое исполнение конфигурации
    reset_value(IN,OUT,VAR);  
  }else if (IN->Enable.Data.bit){
    if (IN->Reset.Data.bit){
      reset_value(IN,OUT,VAR);
    }else{
      if (VAR->TikTimer.Data.uint32){
        VAR->TikTimer.Data.uint32--;
      }else{
        tik_transformed = (float)IN->FilterTime.Data.uint16/25.0;
        VAR->TikTimer.Data.uint32 = tik_transformed*KernelInfo.FBkernelRate;
				FilterTime = (float)IN->FilterTime.Data.uint16;
        FilterTime = (FilterTime<1)?1:FilterTime;
        current_value = ((IN->Input.Type  & DataTypeMask)==KodFloat32)?IN->Input.Data.float32:(float)(IN->Input.Data.uint32);
        previu_value = ((OUT->Output.Type & DataTypeMask)==KodFloat32)?OUT->Output.Data.float32:(float)(OUT->Output.Data.uint32);
        value = ((FilterTime-1.0)*previu_value)/(FilterTime)+(current_value/FilterTime);
        if ((OUT->Output.Type & DataTypeMask)==KodFloat32){
          OUT->Output.Data.float32 = value ;
        }else{
          OUT->Output.Data.uint32 = (u32)value;
        }
      }      
    }
  }else{
    reset_value(IN,OUT,VAR);
  }
}

