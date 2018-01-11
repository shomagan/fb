/*Мультиплексор DI*/
#include "../vars.h"
#include <string.h>
#include "../kernel.h"
#include "../regs.h"

#include "fb00106.h"
#define BIT(x)	(1<<(x))

void fb00106_exec(void)
{
	fb00106_IN_type *IN = (fb00106_IN_type *) FBInputs;
	fb00106_OUT_type *OUT = (fb00106_OUT_type *) FBOutputs;
	
	vu8 i, j;
	vu16 Nbit;
	OUT->Error.Data.bit=0;
	
	if ((IN->Nbit.Type & DataTypeMask)==KodInt8){
    Nbit = IN->Nbit.Data.uint8; 
  }else{
    Nbit = IN->Nbit.Data.uint16;
  } // Проверка на тип
	
	if (Nbit && (Nbit<256)) { // Проверка на размер и на 0
		Nbit--;  							//Nbit отсчет с 1 DI. 
   	if (Nbit>16){
 			i=(Nbit)/16;
 			j=Nbit-i*16;
 			if ((IN->Kanal[i].Data.uint16 & BIT(j))){
        OUT->OUT.Data.bit=1; 
      }else{
        OUT->OUT.Data.bit=0;
      }
   	}else{
			if ((IN->Kanal[0].Data.uint16 & BIT(Nbit))){
        OUT->OUT.Data.bit=1; 
      }else{
        OUT->OUT.Data.bit=0;
      }
  	}
	}else{
    OUT->Error.Data.bit=1; // Ошибка!
  }
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00106_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00106_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00106_OUT_type);
    default:
        return 0;
    }
}
