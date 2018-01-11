/* ФБ "Чтение из батарейного домена" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00085.h"

void fb00085_exec(void) {
	fb00085_IN_type *IN = (fb00085_IN_type *) FBInputs;
	fb00085_OUT_type *OUT = (fb00085_OUT_type *) FBOutputs;


	if (IN->Address.Data.uint16 < MAX_BAT_MEM_SIZE) {
		OUT->Value.Data.uint32 = BateryMemFB32[IN->Address.Data.uint16];
	}

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00085_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00085_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00085_OUT_type);
    default:
        return 0;
    }
}
