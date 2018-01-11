// �� "������� ��" 
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00091.h"

void fb00091_exec (void)
{
	fb00091_IN_type * IN = (fb00091_IN_type *) FBInputs;		// �����
	fb00091_VAR_type * VARS = (fb00091_VAR_type *) FBVars;	// ����������
	fb00091_OUT_type * OUT = (fb00091_OUT_type *) FBOutputs;	// ������
	
	u32 CntDiff;
	
	time_t Time;
	struct tm tmx;
	
	u8 flMakeSutArch;
		//bit0 - =1 ������������ ����� �� ��������
		//bit1 - =1 ���������� ������� ����� � ������� � �������� �������
	CntDiff = 0;
	VARS->CntTicksSec.Data.uint8++;	// �������������� ������� ����� ����������� �������
  flMakeSutArch = 0;

	
	if (OUT->ArhInvEna.Data.bit) { // ������ ������� ������������ �������� ������ 1 ���� ����������
		OUT->ArhInvEna.Data.bit = 0;
		OUT->ArhInvPeretok.Data.bit = 0;
	}
	
	if (VARS->EnaOld.Data.bit != 0) { // EnaOld = 1 // ����� �������
		if ((IN->CounterDI.Data.uint32 > VARS->CounterDIOld.Data.uint32) && (VARS->CounterDIOld.Data.uint32)) {
			
			CntDiff = (IN->CounterDI.Data.uint32 - VARS->CounterDIOld.Data.uint32); // ��������� ���������� ��������
		}
			
		VARS->CounterMinOld.Data.uint32 += CntDiff;		// �������� �������

		if (IN->EnaPeretok.Data.bit) { //���� ������� ���������� ��������
			if (IN->PeretokDI.Data.bit) { // ��� ������� ������ ����� ��������� (����� ��������)
				OUT->CNTInvT.Data.uint32 += CntDiff;	// ������������ �������
			} else { // ���� ������� ������ ����� ��������� (����� �� ��������)
				OUT->CNTInvTif.Data.uint32 += CntDiff;	// ������� ��������� �� ������� ��������
			}
		} else { // ���� �������� �� �����
			OUT->CNTInvT.Data.uint32 += CntDiff;	// ������������ �������
		}
		
		OUT->CNTIntegrTS.Data.uint32 += CntDiff;	// ������������ �� ������� ����� �������
			
		if (VARS->CntTicksSec.Data.uint8 == ((u8)(KernelInfo.FBkernelRate & 0xff))) { // ���� ������ �������
			// ���������� �������
			if (VARS->CntSeconds.Data.uint8 >= 60) {
				Time = IN->UNIXTime.Data.uint32;	// ����� � ������� Unix
				struct tm* pTmx;
        pTmx = localtime(&Time);    // �������������� ������� �� UNIX-�������
        tmx = *pTmx;


				OUT->MinCntDiff.Data.uint32 = VARS->CounterMinOld.Data.uint32 - OUT->MinCnt.Data.uint32; // ��������� �������� ���������
				OUT->MinCnt.Data.uint32 = VARS->CounterMinOld.Data.uint32; // �������� ������ �������� ��������� �������
				VARS->CounterMinOld.Data.uint32 = 0;
				VARS->CntSeconds.Data.uint8 = 0;
				VARS->CntMinutes.Data.uint16++;
				
				if (OUT->MinCntDiff.Data.uint32 > IN->AvarRashod.Data.uint32) {
					OUT->flAvarRash.Data.bit = 1;
				} else {
					OUT->flAvarRash.Data.bit = 0;
				}

				if (IN->Ena2Hours.Data.bit) { // ���� ����� ���� ������������ �� ������������
					if ((tmx.tm_min == 0) && ((tmx.tm_hour % 2) == 0)) {	// �������� ��� �������� ������ ���
						flMakeSutArch |= BIT(0); // ���������� ������������ ����� � ������ ����� ���������� (��������)
					}
				} else if (VARS->CntMinutes.Data.uint16 >= IN->IntervalCNT.Data.uint16) { // ���� ���������� ��������
					flMakeSutArch |= BIT(0); // ���������� ������������ ����� � ������ ����� ��������
				}
				
				if (IN->EnaNullNull.Data.bit) { // ���� ���������� ��������� � 00:00
					if ((tmx.tm_min == 0) && (tmx.tm_hour == 0)) { // �������� ��� ��������� ����� �����
						flMakeSutArch |= BIT(0); // ���������� ������������ ����� � ������ ����� ��������
						flMakeSutArch |= BIT(1); // ���������� ���������� � ������� ����� � ������ �����
					}
				}
			}
		}
		
		if (flMakeSutArch & BIT(0)) {
			OUT->ArhInvEna.Data.bit = 1;	// ����� �� �������� �����
			OUT->ArhInvTimeBeg.Data.uint32 = VARS->TimeBeg.Data.uint32; // ����� ������ ������ ��� ������
			OUT->ArhInvDuration.Data.uint16 = VARS->CntMinutes.Data.uint16; // ������������ ������ ��� ������ � �������
			OUT->ArhCNTInvT.Data.uint32 = OUT->CNTInvT.Data.uint32; // ������� �� ������� �������� ��� ������
			
			if (IN->EnaPeretok.Data.bit) { // ���� ��������� ��������
				OUT->ArhInvPeretok.Data.bit = 1;
				OUT->ArhCNTInvTif.Data.uint32 = OUT->CNTInvTif.Data.uint32; // �������� �������
				OUT->CNTInvPif.Data.uint32 = OUT->CNTInvTif.Data.uint32; // �������� ������� � ������� ���������
				OUT->CNTInvTif.Data.uint32 = 0; // ������� ������� �������
			}
			
			OUT->CNTInvP.Data.uint32 = OUT->CNTInvT.Data.uint32; // ������� �� ������� �������� �������� � �������
			OUT->CNTInvT.Data.uint32 = 0; // ������� ������� �� ������� �������
			VARS->TimeBeg.Data.uint32 = IN->UNIXTime.Data.uint32; // �������� ����� ������ �������� ������
			VARS->CntMinutes.Data.uint16 = 0; // ������� ������������ ������
			flMakeSutArch &= ~BIT(0);
		}
		
		if  (flMakeSutArch & BIT(1)) {
			OUT->CNTIntegrPS.Data.uint32 = OUT->CNTIntegrTS.Data.uint32; // �������� ������� �������� ������� � ���������� ������
			OUT->CNTIntegrTS.Data.uint32 = 0; // ������� ������� �������� �������
			flMakeSutArch &= ~BIT(1);
		}
	} else {
		VARS->EnaOld.Data.bit = 0;
		VARS->CntTicksSec.Data.uint8 = 0;
		VARS->CounterMinOld.Data.uint32 = 0;
		VARS->CntMinutes.Data.uint16 = 0;
		VARS->TimeBeg.Data.uint32 = IN->UNIXTime.Data.uint32;
		
		OUT->MinCnt.Data.uint32 = 0;
		OUT->MinCntDiff.Data.uint32 = 0;
		OUT->CNTInvT.Data.uint32 = 0;
		OUT->CNTInvP.Data.uint32 = 0;
		OUT->CNTIntegrTS.Data.uint32 = 0;
		OUT->CNTIntegrPS.Data.uint32 = 0;
		OUT->CNTInvTif.Data.uint32 = 0;
		OUT->CNTInvPif.Data.uint32 = 0;
		OUT->ArhInvEna.Data.bit = 0;
		OUT->ArhInvDuration.Data.uint32 = 0;
		OUT->ArhInvTimeBeg.Data.uint32 = 0;
		OUT->ArhInvPeretok.Data.bit = 0;
		OUT->flAvarRash.Data.bit = 0;
	}
	
	VARS->CounterDIOld.Data.uint32 = IN->CounterDI.Data.uint32;
	VARS->EnaOld.Data.bit = IN->Enable.Data.bit;
	
	if (VARS->CntTicksSec.Data.uint8 == ((u8)(KernelInfo.FBkernelRate & 0xff))) { // ������� ������� ����� ����������� �������
		VARS->CntTicksSec.Data.uint8 = 0;
		VARS->CntSeconds.Data.uint8++;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00091_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00091_IN_type);
    case(1):
        return sizeof(fb00091_VAR_type);
    case(2):
        return sizeof(fb00091_OUT_type);
    default:
        return 0;
    }
}
