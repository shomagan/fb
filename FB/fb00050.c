/* �� "��������� R7 "��������� DI" (��� 17, ������ 5)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00050.h"
/*������� ����� ��� ��������� ��������� DI(bit)
*��������� ����� ������� ��������� � ����� �������
*/
void fb00050_exec(void) {
	fb00050_IN_type *IN = (fb00050_IN_type *) FBInputs;
	fb00050_OUT_type *OUT = (fb00050_OUT_type *) FBOutputs;
	u8 R7Buff[R7_BodySize];

	OUT->Ok.Data.bit = 0;

  	// ��� ������ ���������� ������������, ���������� ������� �������� ��� ������
	if (KernelInfo.EventFlags.Bit.CfgFirstExec)
		OUT->DI_Old.Data.bit = IN->DI.Data.bit;

	if (IN->Enable.Data.bit) { // ���� ������������� ������ ���������
   		// ��������� ��� ��� ����� �������������
    	if (((IN->DINum.Type & DataTypeMask)!= KodFloat32) && \
      		((IN->DI.Type & DataTypeMask) == KodBit) && \
        	((OUT->DI_Old.Type & DataTypeMask) == KodBit)) {
			
			// ����������, ���� �� ���������
      		if (IN->DI.Data.bit != OUT->DI_Old.Data.bit) {
				R7Buff[0] = 0;                    		// ����� ������
				R7Buff[1] = 0;                    		// � R5 ����� ���� ������ ��������� ����������
				R7Buff[2] = 0;                    		// � ��������� ����������� ������� R5
				R7Buff[3] = 5;                    		// ��� ������ (�� R5) = 5 (��������� DI)
				R7Buff[4] = IN->DINum.Data.uint8; 		// ����� DI
				R7Buff[5] = IN->DI.Data.bit;      		// ��������� DI �����
				R7Buff[6] = 0;                    		// "xxx"
				R7Buff[7] = 0;                    		// "xxx"
				R7Buff[8] = 0;                    		// "xxx"
				R7Buff[9] = FB32blok.vars.Cnt1Sec;      // ����� ������� - ���
				R7Buff[10] = FB32blok.vars.Cnt1Min;     // ����� ������ - ���
				R7Buff[11] = FB32blok.vars.Cnt1Chas;    // ����� ������ - ���
				R7Buff[12] = FB32blok.vars.Cnt1Den;     // ����� ������ - ����
				R7Buff[13] = FB32blok.vars.Cnt1Mes;     // ����� ������ - ���
				R7Buff[14] = FB32blok.vars.Cnt1God;     // ����� ������ - ��� c 1980
				R7Buff[15] = 0;			                // "xxx"
				R7Buff[16] = 0;         		        // "xxx"
        
				for (char k=17; k<R7_BodySize; k++)
					R7Buff[k] = 0;
        
				NewQ_Arc_R7(R7Buff, 17);  // ������� ���� ������ ����������
        
				OUT->DI_Old.Data.bit = IN->DI.Data.bit;
				OUT->Ok.Data.bit = 1;
			}
		}  
	} else
		OUT->DI_Old.Data.bit = IN->DI.Data.bit;
}
