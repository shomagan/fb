/* ФБ "Запись в батарейный домен" */
 
 
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00084.h"

void fb00084_exec(void) {
	fb00084_IN_type *IN = (fb00084_IN_type *) FBInputs;
	fb00084_OUT_type *OUT = (fb00084_OUT_type *) FBOutputs;
  
	OUT->Ok.Data.bit = 0;

	if (IN->EnWrite.Data.bit) {
		if ((IN->Address.Type & DataTypeMask) != KodFloat32) {
			if (IN->Address.Data.uint16 < MAX_BAT_MEM_SIZE) {
				BateryMemFB32[IN->Address.Data.uint16] = IN->Value.Data.uint32;
				OUT->Ok.Data.bit = 1;
			}
		}
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00084_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00084_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00084_OUT_type);
    default:
        return 0;
    }
}
