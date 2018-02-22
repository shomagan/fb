/* ФБ "Масштаб величины" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00076.h"

void fb00076_exec(void) {

	fb00076_IN_type *IN = (fb00076_IN_type *) FBInputs;
	fb00076_OUT_type *OUT = (fb00076_OUT_type *) FBOutputs;
  
	Flo32 y1,y2,x1,x2,x;
	y1 = Void2Float32 (&IN->Y_1);
	y2 = Void2Float32 (&IN->Y_2);
	x1 = Void2Float32 (&IN->X_1);
	x2 = Void2Float32 (&IN->X_2);
	x = Void2Float32 (&IN->X);
	if ((OUT->Y.Type & DataTypeMask) == KodFloat32){
		OUT->Y.Data.float32 = y1+ (((y2 - y1) * (x - x1)) / (x2 - x1)); 
	}
	else{
		OUT->Y.Data.uint32 = (u32) (y1+ (((y2 - y1) * (x - x1)) / (x2 - x1))); 
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00076_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00076_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00076_OUT_type);
    default:
        return 0;
    }
}
