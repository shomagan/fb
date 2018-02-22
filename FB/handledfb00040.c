/* ФБ "Селектор (с обнулением выходов)" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00040.h"

void fb00040_exec (void)
{

	fb00040_IN_type *IN = (fb00040_IN_type *) FBInputs;
	fb00040_OUT_type *OUT = (fb00040_OUT_type *) FBOutputs;
  
	u8 i;
	
	for (i = 0; i<Channels; i++)
		OUT->Outputs[i].Data.uint32 = 0;

	// Проверка типа входа Channel
	if ((IN->Channel.Type & DataTypeMask) != KodFloat32) {
		if (IN->Channel.Data.uint32 < Channels) // № канала не превышает кол-во выходов и задан (не 0)
			OUT->Outputs[IN->Channel.Data.uint32].Data.uint32 = IN->Input.Data.uint32;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00040_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00040_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00040_OUT_type);
    default:
        return 0;
    }
}
