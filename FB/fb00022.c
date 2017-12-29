/* �� "������������� (�� 32 ������)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00022.h"

void fb00022_exec (void)
{

	fb00022_IN_type *IN = (fb00022_IN_type *) FBInputs;
	fb00022_OUT_type *OUT = (fb00022_OUT_type *) FBOutputs;

	// �������� ���� ����� Channel
	if ((IN->Channel.Type & DataTypeMask) != KodFloat32) {
		if (IN->Channel.Data.uint32 < (FB_N_In-1)) { // � ������ �� ��������� ���-�� ������
			switch (OUT->Output.Type & DataTypeMask) {
			case KodBit:
				OUT->Output.Data.bit = (IN->Inputs[IN->Channel.Data.uint32].Data.bit) ? 1 : 0;
				break;
			case KodInt8:
			case KodInt16:
			case KodInt32:
			case KodTime32:
				OUT->Output.Data.uint32 = IN->Inputs[IN->Channel.Data.uint32].Data.uint32;
				break;
			case KodFloat32:
				OUT->Output.Data.float32 = IN->Inputs[IN->Channel.Data.uint32].Data.float32;
				break;
			}
		} else
			OUT->Output.Data.uint32 = 0;
	} else
		OUT->Output.Data.uint32 = 0;
}
