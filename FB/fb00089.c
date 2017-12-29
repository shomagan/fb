// ФБ "Счетчик входных импульсов" 
#include "../vars.h"
#include "../regs.h"

#include "fb00089.h"

void fb00089_exec (void)
{
  fb00089_IN_type *IN = (fb00089_IN_type *) FBInputs;
  fb00089_VAR_type *VAR = (fb00089_VAR_type *) FBVars;
  fb00089_OUT_type *OUT = (fb00089_OUT_type *) FBOutputs;
  if (KernelInfo.EventFlags.Bit.CfgFirstExec){  // Первое исполнение конфигурации
    VAR->Input.Data.bit = 0;  
  }
  if (IN->Enable.Data.bit){
  	if (IN->Input.Data.bit && (VAR->Input.Data.bit == 0)){
      VAR->Input.Data.bit = 1;
 			OUT->Output.Data.uint32++;
  	}
  }
  if (IN->Reset.Data.bit)
  	OUT->Output.Data.uint32 = 0;

  if (IN->Input.Data.bit == 0)
  	VAR->Input.Data.bit = 0 ;
}
