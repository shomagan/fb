/*�� "���������"*/
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00086.h"

void fb00086_exec ()
{
	fb00086_IN_type *IN = (fb00086_IN_type *) &FBInputs;
	fb00086_OUT_type *OUT = (fb00086_OUT_type *) &FBOutputs;
	
	Register_type *pMain, *pAuto, *pCmd_ON, *pCmd_OFF;
	u8 tmp, Cmd; //3-���� ���,2-��� ���,1-������ �� ������,0-��� ��������
	u8 i;
	
	Cmd = 1;//��������� ��������� ������� "���"
	i = 4;
	if (IN->enable.Data.bit) {
		if (IN->lo.Data.bit) tmp = 1; else tmp = 0;   //��������� ���
		if (IN->hi.Data.bit) tmp += 2; //��� �������� 
		if (IN->hihi.Data.bit) tmp += 4; //��� ��� 
		switch (tmp) {
		case 0: //��� ��������
			break;
		case 2: //������ ������ �������� ������
			//���� ���� �������� � ��������
			if ((IN->main0.Data.bit && IN->auto0.Data.bit) || (IN->main1.Data.bit && IN->auto1.Data.bit) || (IN->main2.Data.bit && IN->auto2.Data.bit) || (IN->main3.Data.bit && IN->auto3.Data.bit)) {
				Cmd = 0;//��� ��������
			} else {
				Cmd = 2;//��� ��� (����� ����������� ��� �������)
			}
			break;
		case 4: //������ ���������� �������� ������
		case 6: //��� ������� ������� �������
			Cmd = 2; //�������� ���
			break;
		default:
			Cmd = 3; //1,3,5,7 - ���� ������ ������� ������
			//��������� ���
		}
	}
	
	i = 4;
	pMain = &(IN->main0);
	pAuto = &(IN->auto0);
	pCmd_ON = &(OUT->cmd0_ON);
	pCmd_OFF = &(OUT->cmd0_OFF);
	while (i--) {		
		if (pAuto->Data.bit == 0)
			tmp = 1; //�� � ��������, ������ �� ������
		else if (Cmd) //���� ������� �� "��� ��������"
			 tmp = Cmd;
		else if (pMain->Data.bit) //��������, ���� ���� ������� �� ���������
			 tmp = 2;
		else //�� ��������, ������ �� ���� ������
			tmp = 1;

		pCmd_ON->Data.bit=(tmp==0x02) ? 1:0;// ���� ���� ������� �� ��������� ������������� ��� 
		pCmd_OFF->Data.bit=(tmp==0x03) ? 1:0;// ���� ���� ������� �� ���������� ������������� ���� 
		pMain++;
		pAuto++;
		pCmd_ON = pCmd_OFF + 1;//��������� � ���������� ������
		pCmd_OFF = pCmd_ON + 1;
	}
	//���������� ����������� ����������� ��������� ������ � �������� �������
    
	OUT->State.Data.uint8 = (IN->enable.Data.bit ?1:0) | (IN->hihi.Data.bit ?2:0) | (IN->hi.Data.bit ?4:0) | (IN->lo.Data.bit ?8:0)\
		| (Cmd == 0 ? 16:0) | (Cmd == 2 ? 32:0) | (Cmd == 3 ? 64:0);
	 //3-���� ���,2-��� ���,1-������ �� ������,0-��� ��������
}
