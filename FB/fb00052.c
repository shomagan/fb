/* �� "��������� R7 "�������� ������ �������" (��� 17, ������ 7)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00052.h"
/*������� ����� � ����� �������(����),4 ������� �������� �������
*� ����������� 6 ������� �������� 
*/            
void fb00052_exec(void) {
	fb00052_IN_type *IN = (fb00052_IN_type *) FBInputs;
	fb00052_OUT_type *OUT = (fb00052_OUT_type *) FBOutputs;
  
	u8 R7Buff[R7_BodySize];

	OUT->Ok.Data.bit = 0;

	if (IN->CmdARX.Data.bit) { // ���� ������������� ������ ���������
    // ��������� ��� ��� ����������� ����
		if (((IN->EventID.Type & DataTypeMask)!= KodFloat32) && \
			((IN->DD0.Type & DataTypeMask) == KodInt8) && \
        	((IN->DD1.Type & DataTypeMask) == KodInt8) && \
          	((IN->DD2.Type & DataTypeMask) == KodInt8) && \
            ((IN->DD3.Type & DataTypeMask) == KodInt8) ) {
		
			R7Buff[0] = 0;                                        // ����� ������
			R7Buff[1] = 0;                        // � R5 ����� ���� ������ ��������� ����������
			R7Buff[2] = 0;                        // � ��������� ����������� ������� R5
			R7Buff[3] = 7;                        // ��� ������ (�� R5) = 7 (�������� ������ �������)
			R7Buff[4] = IN->EventID.Data.uint8;   // ��� �������
			R7Buff[5] = IN->DD0.Data.uint8;       // DD0
			R7Buff[6] = IN->DD1.Data.uint8;       // DD1
			R7Buff[7] = IN->DD2.Data.uint8;       // DD2
			R7Buff[8] = IN->DD3.Data.uint8;       // DD3
			R7Buff[9] = FB32blok.vars.Cnt1Sec;      // ����� ������� - ���
			R7Buff[10] = FB32blok.vars.Cnt1Min;     // ����� ������ - ���
			R7Buff[11] = FB32blok.vars.Cnt1Chas;    // ����� ������ - ���
			R7Buff[12] = FB32blok.vars.Cnt1Den;     // ����� ������ - ����
			R7Buff[13] = FB32blok.vars.Cnt1Mes;     // ����� ������ - ���
			R7Buff[14] = FB32blok.vars.Cnt1God;     // ����� ������ - ��� c 1980
			R7Buff[15] = 0;                       // "xxx"
			R7Buff[16] = 0;                       // "xxx"
     
			for (char k=17; k<R7_BodySize; k++)
				R7Buff[k] = 0;
     
			NewQ_Arc_R7(R7Buff, 17);  // ������� ���� ������ ����������
			OUT->Ok.Data.bit = 1;
		}  
	}
}
