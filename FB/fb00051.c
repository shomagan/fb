/* �� "��������� R7 "��������� AI" (��� 17, ������ 6)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00051.h"
/*������� ����� ��� ��������� �������� �������� ������ ��������� �����������
*��������� ������ � ����� �������� AI(������ �� 2 �����) � �����
*/
void fb00051_exec (void)
{
	fb00051_IN_type *IN = (fb00051_IN_type *) FBInputs;
	fb00051_OUT_type *OUT = (fb00051_OUT_type *) FBOutputs;
  
	u16 Delta = 0;
	u8 R7Buff[R7_BodySize];
	u8 k;
	
	OUT->Ok.Data.bit = 0;
  
	// ��� ������ ���������� ������������, ���������� ������� �������� ��� ������
	if (KernelInfo.EventFlags.Bit.CfgFirstExec)
		OUT->AI_Old.Data.uint16 = IN->AI.Data.uint16;

	if (IN->Enable.Data.bit) {// ���� ������������� ������ ���������
		// ��������� ��� ��� ����� �������������
		if (((IN->AINum.Type&DataTypeMask) != KodFloat32) && \
			((IN->AI.Type&DataTypeMask) != KodFloat32) && \
			((OUT->AI_Old.Type&DataTypeMask) != KodFloat32)) {
			
			// ����������, ���� �� ��������� ������ �����������
			if (IN->AI.Data.uint16 >= OUT->AI_Old.Data.uint16)
				Delta = IN->AI.Data.uint16 - OUT->AI_Old.Data.uint16;
			else
				Delta = OUT->AI_Old.Data.uint16 - IN->AI.Data.uint16;
      
			if (Delta > IN->AI_Gist.Data.uint16) {
				R7Buff[0] = 0;                                        // ����� ������
				R7Buff[1] = 0;                                        // � R5 ����� ���� ������ ��������� ����������
				R7Buff[2] = 0;                                        // � ��������� ����������� ������� R5
				R7Buff[3] = 6;                                        // ��� ������ (�� R5) = 6 (��������� AI)
				R7Buff[4] = IN->AINum.Data.uint8;                     // ����� AI
				R7Buff[5] = (u8) (IN->AI.Data.uint16 & 0xFF);       // ��������� AI ����� ��.
				R7Buff[6] = (u8) (IN->AI.Data.uint16 >> 8);         // ��������� AI ����� ��.
				R7Buff[7] = (u8) (OUT->AI_Old.Data.uint16 & 0xFF);  // ��������� AI ������ ��.
				R7Buff[8] = (u8) (OUT->AI_Old.Data.uint16 >> 8);    // ��������� AI ������ ��.
				R7Buff[9] = FB32blok.vars.Cnt1Sec;      // ����� ������� - ���
				R7Buff[10] = FB32blok.vars.Cnt1Min;     // ����� ������ - ���
				R7Buff[11] = FB32blok.vars.Cnt1Chas;    // ����� ������ - ���
				R7Buff[12] = FB32blok.vars.Cnt1Den;     // ����� ������ - ����
				R7Buff[13] = FB32blok.vars.Cnt1Mes;     // ����� ������ - ���
				R7Buff[14] = FB32blok.vars.Cnt1God;     // ����� ������ - ��� c 1980
				R7Buff[15] = 0;                                       // "xxx"
				R7Buff[16] = 0;                                       // "xxx"
        
				for (k = 17; k < R7_BodySize; k++)
					R7Buff[k] = 0;
        
				NewQ_Arc_R7(R7Buff, 17);  // ������� ���� ������ ����������
        
				OUT->AI_Old.Data.uint16 = IN->AI.Data.uint16;
				OUT->Ok.Data.bit = 1;
			}
		}  
	} else {
		OUT->AI_Old.Data.uint16 = IN->AI.Data.uint16;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00051_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00051_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00051_OUT_type);
    default:
        return 0;
    }
}
