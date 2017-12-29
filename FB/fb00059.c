/* �� "������ � ������ ���������� ������������" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00059.h"

void fb00059_exec(void) {
	fb00059_OUT_type *OUT = (fb00059_OUT_type *) FBOutputs;
  
	if (CfgStartTime) // �������� �� �� ��� ����� ������ ���� ���������
		OUT->CfgTime.Data.uint32 = GetSystemTime_t() - CfgStartTime;
	else
		CfgStartTime = GetSystemTime_t(); // �� ������, ���� �� ������ ������ ���������� ������������ ����� ��� �� ���� �� ���� ��������� �� RTC

}
