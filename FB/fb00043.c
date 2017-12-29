/* �� "������������ �� ������" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00043.h"

void fb00043_exec(void) {

	fb00043_IN_type *IN = (fb00043_IN_type *) FBInputs;
	fb00043_VAR_type *VAR = (fb00043_VAR_type *) FBVars;
	fb00043_OUT_type *OUT = (fb00043_OUT_type *) FBOutputs;
  
	if (OUT->Out.Data.bit) { // OUT="1"
		if (OUT->Timer.Data.uint32)   // ����������� �������
			OUT->Timer.Data.uint32--; 
    
		if (!OUT->Timer.Data.uint32)  // ����� ��������� �����������
			OUT->Out.Data.bit = 0;      // ������� �������� - �������� �����
	}

	if ((IN->In.Data.bit) && (VAR->In_Old.Data.bit == 0)) {    // IN="1", IN_Old="0" // �����
		OUT->Out.Data.bit = 1;
		OUT->Timer.Data.uint32 = IN->Tics.Data.uint32;
	}
  
	VAR->In_Old.Data.bit = IN->In.Data.bit;   // ��������� ��������� In_Old
}

