/* �� "�������� (��� ��������� �������)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00071.h"

void fb00071_exec(void) {

	fb00071_IN_type *IN = (fb00071_IN_type *) FBInputs;
	fb00071_OUT_type *OUT = (fb00071_OUT_type *) FBOutputs;
  
	// �������� ���� ����� Channel
	if ((IN->Channel.Type & DataTypeMask) != KodFloat32) {
		if (IN->Channel.Data.uint32 < Channels) // � ������ �� ��������� ���-�� �������
			OUT->Outputs[IN->Channel.Data.uint32].Data.uint32 = IN->Input.Data.uint32;
	}
}
