/* �� "����������� I2C-������ �� ����" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00039.h"

void fb00039_exec(void) {
/*	fb00039_IN_type *IN = (fb00039_IN_type *) FBInputs;
	fb00039_OUT_type *OUT = (fb00039_OUT_type *) FBOutputs;

	if(IN->ModuleAddr.Data.uint8 > 1) { // �� COM1/COM2
		if (IN->ModuleAddr.Data.uint8 & 0x01) // ����� ������ �������� - ������������
			OUT->Connected.Data.bit = 0;
		else	                                    // ����� ������ - ����������
			OUT->Connected.Data.bit = TWIModulePresented(IN->ModuleAddr.Data.uint8);
	} else // ������ 2 ������ ������ ����������� �������
		OUT->Connected.Data.bit = 1; // ������ ������������ � CPU32
*/
}
