/* �� "��������" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00080.h"

void fb00080_exec(void) {
/*	fb00078_IN_type *IN = (fb00078_IN_type *) FBInputs;
	fb00078_VAR_type *VAR = (fb00078_VAR_type *) FBVars;
	fb00078_OUT_type *OUT = (fb00078_OUT_type *) FBOutputs;
*/
	fb00080_IN_type *IN = (fb00080_IN_type *) FBInputs;
	fb00080_VAR_type *VAR = (fb00080_VAR_type *) FBVars;
	fb00080_OUT_type *OUT = (fb00080_OUT_type *) FBOutputs;

//	unsigned char NeedImpuls;
	unsigned int varSost;

	if(KernelInfo.EventFlags.Bit.CfgFirstExec) { //������ ������
		OUT->OutOpen.Data.bit = 0;
		OUT->OutClose.Data.bit = 0;
		OUT->OutStop.Data.bit = 0;
		OUT->Timer.Data.uint16 = 0;
		OUT->Sost.Data.uint16 = 0;
		VAR->SecTimer.Data.uint8 = 0;
		VAR->ImpulsTime.Data.uint8 = 0;
		varSost = 0;
	} else { // �� ������ ������

		VAR->SecTimer.Data.uint8++;

//		NeedImpuls = (VAR->ImpulsTime.Data.uint8 > 0) ? 1 : 0;

		varSost = OUT->Sost.Data.uint16;

		if(IN->Dist.Data.bit == 0) { //���� ������� �����
			varSost = 0;
			OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
			OUT->OutOpen.Data.bit = 0;
			OUT->OutClose.Data.bit = 0;
			OUT->OutStop.Data.bit = 0;
			VAR->ImpulsTime.Data.uint16 = 0;
		} else { //���� ������������� �����
			varSost |= s00080_DIST;
			if(IN->CmdStop.Data.bit || IN->Alarmed.Data.bit) { //���� ������� ���� ��� ������
				OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
				OUT->OutStop.Data.bit = 1;		//������ ������� �� ����� ����
//				NeedImpuls = 1;
				VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // ����� �������� ��������� ������������ ������� � ���.
				OUT->OutClose.Data.bit = 0;		//�������� ����� ���������� �������
				OUT->OutOpen.Data.bit = 0;		//�������� ����� ���������� �������
				varSost &= ~s00080_OPENING;		//�������� ���� �����������
				varSost &= ~s00080_CLOSING;		//�������� ���� �����������

			} else { // ��������� ������ �������� � ��������
				if((IN->CmdOpen.Data.bit) && (!(varSost & s00080_CLOSING))) { // ���� ������� �������, � �� ����������
					if(!IN->Opened.Data.bit&&(!OUT->OutStop.Data.bit)) {	//� �� �������
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // ����� �������� ��������� ������������ ������� � ���.
						OUT->OutOpen.Data.bit = 1;	//������ ����������� ������� �� ����� �������
						varSost |= s00080_OPENING;	//���������� ���� ����������
						varSost &= ~s00080_CLOSING;	//�������� ���� �����������
						varSost &= ~s00080_AVARMUFTA;	//�������� ���� ������ �� �����
						varSost &= ~s00080_AVARVPHOPEN;	//������� ���� ������ �� ��������� ��������
						varSost &= ~s00080_AVARVPHCLOSE;	//�������� ���� ������ �� ��������� ��������
					}
				}
				if((IN->CmdClose.Data.bit) && (!(varSost & s00080_OPENING))) { // ���� ������� �������, � �� �����������
					if(!IN->Closed.Data.bit&&(!OUT->OutStop.Data.bit)) {	//� �� �������
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // ����� �������� ��������� ������������ ������� � ���.
						OUT->OutClose.Data.bit = 1;	//������ ����������� ������� �� ����� �������
						varSost |= s00080_CLOSING;	//��������� ���� �����������
						varSost &= ~s00080_OPENING;	//�������� ���� �����������
						varSost &= ~s00080_AVARMUFTA; //�������� ���� ������ �� �����
						varSost &= ~s00080_AVARVPHOPEN;	//������� ���� ������ �� ��������� ��������
						varSost &= ~s00080_AVARVPHCLOSE; //�������� ���� ������ �� ��������� ��������
					}
				}
			}
		
//			if(NeedImpuls) { // ��������� �������� ��������� ������������ ������� ��������, ��������, ����
 			if(VAR->ImpulsTime.Data.uint8 == 0) { //����� ���������  �������� �����?
 				OUT->OutClose.Data.bit = 0;		// ���� �����, �� �������� ����������� ������ �������� �������� ����
 				OUT->OutOpen.Data.bit = 0;
 				OUT->OutStop.Data.bit = 0;
 			} else {
 				if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
 					VAR->ImpulsTime.Data.uint8--;	//���� �� �����, �� ��������������� ������� ������ ��������� ������������ ��������
 				}
 			}
//			}
			
			if(varSost & s00080_OPENING) {	//���� �������� ����������
				if(OUT->Timer.Data.uint16 == 0) {	//���� ����������� ����� ������� ����
					varSost &= ~s00080_OPENING;	//�������� ���� �����������
					varSost |= s00080_AVARVPHOPEN;	//��������� ���� ������ �� ��������� ��������
					OUT->OutStop.Data.bit = 1;		//������ ������� �� ����� ����
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else { //����� ������� ���� �� �����
					if(IN->Opened.Data.bit) { //���� �������� �������
						varSost &= ~s00080_OPENING;	//�������� ���� �����������
						varSost &= ~s00080_AVARVPHOPEN;	//�������� ���� ������ �� ��������� ��������
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//���� �� ����� ����� ������� ����, �� ���������������� ������� ������ ������� ������� ����
						}	
					}
				}
			}
			
			if(varSost & s00080_CLOSING) {	//���� �������� �����������
				if(OUT->Timer.Data.uint16 == 0) {	//���� ����������� ����� ������� ����
					varSost &= ~s00080_CLOSING;	//������� ���� �����������
					varSost |= s00080_AVARVPHCLOSE;	//��������� ���� ������ �� ��������� ��������
					OUT->OutStop.Data.bit = 1;	//������ ������� �� ����� ����
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else {	//����� ������� ���� �� �����
					if(IN->Closed.Data.bit) {	//���� �������� �������
						varSost &= ~s00080_CLOSING;	//������� ���� �����������
						varSost &= ~s00080_AVARVPHCLOSE;	//�������� ���� ������ �� ��������� ��������
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//���� �� ����� ����� ������� ����, �� ���������������� ������� ������ ������� ������� ����
						}	
					}
				}
			}
		}
	} //�� ������ ������

	if(IN->Alarmed.Data.bit) {		//�������� ��������� ������ �� ����� � ����������� � ������
		varSost |= s00080_AVARMUFTA;
	} else {
		varSost &= ~s00080_AVARMUFTA;
	}

	if(IN->Opened.Data.bit) {		//�������� ��������� ������� � ����������� � ������
		varSost |= s00080_OPENED;
	} else {
		varSost &= ~s00080_OPENED;
	}

	if(IN->Closed.Data.bit) {		//�������� ��������� ������� � ����������� � ������
		varSost |= s00080_CLOSED;
	} else {
		varSost &= ~s00080_CLOSED;
	}

	if(IN->Uon.Data.bit) {			//�������� ��������� ������� ���������� ����������� � ������
		varSost |= s00080_UON;
	} else {
		varSost &= ~s00080_UON;
	}

	OUT->Sost.Data.uint16 = varSost;

	if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
		VAR->SecTimer.Data.uint8 = 0;
	}
}
