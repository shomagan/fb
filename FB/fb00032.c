/* ФБ "Запись в I2C-модуль" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00032.h"


void fb00032_exec(void) {
/*	fb00032_IN_type *IN = (fb00032_IN_type *) FBInputs;

	vu8 WrBuffer[MaxWrBufferSize];
	vu16 i_reg = 0, i_byte = 0;
	vu8 TypeSize;

  if (IN->Cmd_write.Data.bit)
  {
    while ((i_byte < IN->NumBytes.Data.uint16) && (i_byte < MaxWrBufferSize))
    {
      TypeSize = VarSize(IN->In[i_reg].Type);
      memcpy((WrBuffer + i_byte), (char*)&(IN->In[i_reg].Data.uint32), TypeSize);
      i_byte += TypeSize;
      i_reg++;
    }
    NewTWI_QItem(TWICommCodeFB_Write, IN->Module_adress.Data.uint16, IN->Internal_adress.Data.uint16, IN->NumBytes.Data.uint16, 0, WrBuffer);
  }
*/
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00032_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00032_IN_type);
    case(1):
        return 0;
    case(2):
        return 0;
    default:
        return 0;
    }
}
