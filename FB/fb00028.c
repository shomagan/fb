/* �� "������������ �������� (� ������)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00028.h"

void fb00028_exec (void)
{

	fb00028_IN_type *IN = (fb00028_IN_type *) FBInputs;
	fb00028_VAR_type *VAR = (fb00028_VAR_type *) FBVars;
	fb00028_OUT_type *OUT = (fb00028_OUT_type *) FBOutputs;

	if ((IN->Input.Type & DataTypeMask) == KodBit) { // ������� �������� ������ ���� ����������!
		OUT->Output.Data.uint32 = VAR->Counter.Data.uint32;   // ������� �������

		if (IN->Input.Data.bit)           // �� ����� "1"
			VAR->Counter.Data.uint32++;     // ������� ������������
		else                              // �� ����� "0"
			VAR->Counter.Data.uint32 = 0;   // �������� �������
	} else
		OUT->Output.Data.uint32 = 0;
}
