// ФБ "Счетчик входных импульсов" 
 
 
#include "../vars.h"
#include "../regs.h"

#include "handledfb00089.h"

#include "../kernel.h"
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
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00089_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00089_IN_type);
    case(1):
        return sizeof(fb00089_VAR_type);
    case(2):
        return sizeof(fb00089_OUT_type);
    default:
        return 0;
    }
}
