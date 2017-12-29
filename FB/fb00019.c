/* �� "������� �� N ������" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00019.h"

void fb00019_exec(void) {

	fb00019_IN_type *IN = (fb00019_IN_type *) FBInputs;
	fb00019_VAR_type *VAR = (fb00019_VAR_type *) FBVars;
	fb00019_OUT_type *OUT = (fb00019_OUT_type *) FBOutputs;

	if ((IN->N.Type & DataTypeMask) != KodFloat32) {
		if (VAR->I.Data.uint32 >= IN->N.Data.uint32) {
			if ((OUT->Output.Type & DataTypeMask) == KodFloat32)
				OUT->Output.Data.float32 = VAR->Summ.Data.float32 / VAR->I.Data.uint32;
			else
				OUT->Output.Data.uint32 = VAR->Summ.Data.uint32 / VAR->I.Data.uint32;
      
			VAR->I.Data.uint32 = 0;
			VAR->Summ.Data.uint32 = 0;
		} else {
			if ((OUT->Output.Type & DataTypeMask) != KodFloat32)
				VAR->Summ.Data.float32 += IN->Value.Data.float32;
			else
				VAR->Summ.Data.uint32 += IN->Value.Data.uint32;
      
			VAR->I.Data.uint32++;
		}
	} else
		OUT->Output.Data.uint32 = 0;
}
