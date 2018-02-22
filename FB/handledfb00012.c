/* ФБ "Беззнаковое целое -> Float32 (с множителем и делителем)" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00012.h"

void fb00012_exec(void) {

	fb00012_IN_type *IN = (fb00012_IN_type *) FBInputs;
	fb00012_OUT_type *OUT = (fb00012_OUT_type *) FBOutputs;
  
	Flo32 FloatVal, FloatMult, FloatDiv;
  
	FloatVal = Void2Float32 (&IN->Value);
	FloatMult = Void2Float32 (&IN->Multiplier);
	FloatDiv = Void2Float32 (&IN->Divider);

	if (FloatMult != 1.0f)                         // 1 в множителе недопустима
		FloatVal *= FloatMult;

	if ((FloatDiv != 1.0f) && (FloatDiv != 0.0f))   // 0 и 1 в делителе недопустимы
		FloatVal /= FloatDiv;

	OUT->Output.Data.float32 = FloatVal;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00012_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00012_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00012_OUT_type);
    default:
        return 0;
    }
}
