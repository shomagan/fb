/* �� "��������� R7 "����� ���" (��� 17, ������ 1)" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00047.h"

/*������ ������ ������(����),�������� ��������(4 �����)
 *����� ������ ������(6 ����)������������� ���(2 ����)
 *37 ���� �� ������������ 
*/
void fb00047_exec (void)
{
	fb00047_IN_type *IN = (fb00047_IN_type *) FBInputs;
	fb00047_OUT_type *OUT = (fb00047_OUT_type *) FBOutputs;

	time_t TimeStart,TimeCurrent;
	struct tm tmx;
	struct tm* pTmx;
	u8 R7Buff[R7_BodySize];
	u8 k;
	
	OUT->Ok.Data.bit = 0;
  
	if (IN->CmdARX.Data.bit) {// ���� ������������� ������ ���������
		// ��������� ��� ��� ����� �������������
		if (((IN->OtvNum.Type & DataTypeMask)!= KodFloat32) && ((IN->Counter.Type & DataTypeMask)!= KodFloat32) && \
			((IN->StartTime.Type & DataTypeMask)!= KodFloat32) && ((IN->CntTime.Type & DataTypeMask)!= KodFloat32)) {
				TimeStart = IN->StartTime.Data.uint32;
				pTmx = localtime(&TimeStart);    // �������������� ������� �� UNIX-�������
				tmx = *pTmx;
      
				R7Buff[0] = 0;                                        // ����� ������
				R7Buff[1] = 0;                                        // � R5 ����� ���� ������ ��������� ����������
				R7Buff[2] = 0;                                        // � ��������� ����������� ������� R5
				R7Buff[3] = 1;                                        // ��� ������ (�� R5) = 1 (���)
				R7Buff[4] = IN->OtvNum.Data.uint8;                    // ����� ������
				R7Buff[5] = (char) (IN->Counter.Data.uint32 & 0xFF);  // ������� ��.
				R7Buff[6] = (char) (IN->Counter.Data.uint32 >> 8);    // �������
				R7Buff[7] = (char) (IN->Counter.Data.uint32 >> 16);   // �������
				R7Buff[8] = (char) (IN->Counter.Data.uint32 >> 24);   // ������� ��.
				R7Buff[9] = tmx.tm_sec;                             // ����� ������ - ���
				R7Buff[10] = tmx.tm_min;                            // ����� ������ - ���
				R7Buff[11] = tmx.tm_hour;                           // ����� ������ - ���
				R7Buff[12] = tmx.tm_mday;                           // ����� ������ - ����
				R7Buff[13] = tmx.tm_mon+1;                          // ����� ������ - ���
				R7Buff[14] = tmx.tm_year-80;                        // ����� ������ - ��� c 1980
        TimeCurrent = GetSystemTime_t();
        IN->CntTime.Data.uint16 = (TimeCurrent - TimeStart)/60;
        if(IN->CntTime.Data.uint16 > 1440){
          IN->CntTime.Data.uint16 = 1440;
        }else if((IN->CntTime.Data.uint16 < 3)){
          IN->CntTime.Data.uint16 = 3;
        }

				R7Buff[15] = (char) (IN->CntTime.Data.uint16 & 0xFF); // ������������ � ������� ��.
				R7Buff[16] = (char) (IN->CntTime.Data.uint16 >> 8);   // ������������ � ������� ��.

				for (k = 17; k < R7_BodySize; k++)
					R7Buff[k] = 0;

				NewQ_Arc_R7(R7Buff, 17);  // ������� ���� ������ ����������
				OUT->Ok.Data.bit = 1;
		}  
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00047_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00047_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00047_OUT_type);
    default:
        return 0;
    }
}
