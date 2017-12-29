/* �� "������� ��������" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00076.h"

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
