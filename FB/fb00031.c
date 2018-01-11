/* ФБ "Чтение из I2C-модуля" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00031.h"

void fb00031_exec(void) {
/*	fb00031_IN_type *IN = (fb00031_IN_type *) FBInputs;
	fb00031_OUT_type *OUT = (fb00031_OUT_type *) FBOutputs;


  TWI_stack_type *QPointer;
  unsigned short int i_reg = 0, i_byte = 0;
  unsigned char TypeSize;

  OUT->ReadedOK.Data.bit = 0;
  QPointer = FindReadByFB(TWIReceived, IN->Module_adress.Data.uint8, IN->Internal_adress.Data.uint16, IN->NumBytes.Data.uint16 );

  if (QPointer) // На запрос был ответ
  {
    while (IN->NumBytes.Data.uint16 > i_byte)
    {
      TypeSize = VarSize(OUT->Out[i_reg].Type);
      memcpy((char*)(&OUT->Out[i_reg].Data.uint32), (QPointer->pBuffer + i_byte), TypeSize);
      i_byte += TypeSize;
      i_reg++;
    }

    QPointer->State = TWIFree;
    OUT->ReadedOK.Data.bit = 1;
  }
  else if (IN->Enable.Data.bit) // Разрешено чтение из модуля
  {
    NewTWI_QItem(TWICommCodeFB_ReadByFB, IN->Module_adress.Data.uint16, IN->Internal_adress.Data.uint16, IN->NumBytes.Data.uint16, 0, 0);
    OUT->ReadedOK.Data.bit = 0;
  }
*/
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00031_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00031_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00031_OUT_type);
    default:
        return 0;
    }
}
