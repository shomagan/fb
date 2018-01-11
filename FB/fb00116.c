/* ФБ "Мультиплексор 2.0" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"
#include "fb00116.h"

void fb00116_exec(void) {

	fb00116_IN_type *IN = (fb00116_IN_type *) FBInputs;
	fb00116_OUT_type *OUT = (fb00116_OUT_type *) FBOutputs;
 	vu8 i,j;   
	
	 // № канала не превышает кол-во входов
	
	for (i=0,j=0; (i<(FB_N_In/2))&&(i<FB_N_Out); i++,j+=2) {
		if ((IN->Input[j+1].Data.uint32<=FB_N_In/2)&&IN->Input[j+1].Data.uint32>0){
			switch (OUT->Output[i].Type & DataTypeMask) {
			case KodBit:
				OUT->Output[i].Data.bit = (IN->Input[((IN->Input[j+1].Data.uint32)-1)*2].Data.bit) ? 1 : 0;
				break;
			case KodInt8:
			case KodInt16:
			case KodInt32:
			case KodTime32:
				OUT->Output[i].Data.uint32 = IN->Input[((IN->Input[j+1].Data.uint32)-1)*2].Data.uint32;
				break;
			case KodFloat32:
				OUT->Output[i].Data.float32 = IN->Input[((IN->Input[j+1].Data.uint32)-1)*2].Data.float32;
				break;
			}
		} else {OUT->Output[i].Data.uint32=0; LedErrorOn(100);}
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00116_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00116_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00116_OUT_type);
    default:
        return 0;
    }
}
