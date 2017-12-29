/*�� "��������� ���������� R7" (������������ ����)*/
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00088.h"

#define flEnable (1<<0)     //���� ��������� ��������� ������ ��� � �������� ������ 
#define flSaveDNM (1<<1)    //���� ��������� ��������� ������������� 
#define flKnapPASS (1<<3)    //���� ���� ��������� ������� � ������  ���� 

// BodySize 55 ���� 

#define k1   4	//k - ���������� ��������  

void fb00088_exec ()
{
	fb00088_IN_type *IN = (fb00088_IN_type *) &FBInputs;
	fb00088_OUT_type *OUT = (fb00088_OUT_type *) &FBOutputs;
	u8 Hvost [7];
	u16 k;
	u8 i, n;

	if (IN->Enable.Data.bit && ((OUT->State.Data.uint8 & flEnable )==0)) {//����� �������� ��������� ������� �� ���� "��� �����"
		OUT->State.Data.uint8 |= 1;	//��������� ������� ������ �� ��������� ������� Enable
		u32 TimeUNIX = GetSystemTime_t();	// �������� ��������� ����� (�� ������� ������) � UNIX	
		u8* Time;
		OUT->OutDNMNumber.Data.uint8 = IN->InDNMNumber.Data.uint8+1;//���� �������� ����� �������������� ������� ��������� �������(�� ��������� ������ ��� ������� ����� "��������� ���������� R7" ) 
		
		k = 0; 
		
		for (; k < 63; k++)
			OUT->OutArray[k].Data.uint8 = IN->InArray[k].Data.uint8;//�������� ������ 0 -  62 ���� �������� ������� 
		
		OUT->OutArray[k].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//����� ���
		for (; k < 126; k++ )
			OUT->OutArray[k+1].Data.uint8 = IN->InArray[k].Data.uint8;//��������  63 -  125 ���� �������� �������
		
		OUT->OutArray[k + 1].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//����� ���					
		for (; k < 185; k++ )
			OUT->OutArray[k + 2].Data.uint8 = IN->InArray[k].Data.uint8;//�������� ������ 126 -  184(186 ���������) ���� �������� ������� (�������� ������ 7 ���� ������� ������ ������ ��� ����� ����� � ������ ���)

		Time = (u8*)(&TimeUNIX);
		OUT->OutArray[k + 2].Data.uint8 = *Time ;	//����� Low 187					
		TimeUNIX >>= 8;
		OUT->OutArray[k + 3].Data.uint8 = *Time;	//����� MLow 188					
		TimeUNIX >>= 8;
		OUT->OutArray[k + 4].Data.uint8 = *Time;	//����� MHi 189				
		TimeUNIX >>= 8;
		OUT->OutArray[k + 5].Data.uint8 = *Time;	//����� Hi 190					

		OUT->OutArray[k + 6].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//����� ��� ���� 191					
        for (; k < 192; k++)
			Hvost[k - 185] = IN->InArray[k].Data.uint8;  // �������� ����� ��� ������� � ������ � �����
        
        OUT->State.Data.uint8&=~flKnapPASS; //������ ����� ������ ��� �������� ���� ������������ �������� ����
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////**/
    if (IN->Enable.Data.bit && IN->KnapReady.Data.bit && ((OUT->State.Data.uint8 & flKnapPASS) == 0)) {//���� ���������� ��� ���� ��� (���� ������������ ��������� ��������� ���)
        OUT->State.Data.uint8 |= flKnapPASS;      //������������� ���� ������� ������
        OUT->KnapValue.Data.uint8 = IN->KnapValue.Data.uint8;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***/
	if (IN->SaveDNM.Data.bit && ((OUT->State.Data.uint8 & flSaveDNM) == 0)) {//����� �������� 4-x ������� R7 ��� ������ ������������ �� �����		
		OUT->State.Data.uint8 |= (1 << 1); 	//��������� ������� ������ �� ��������� ������� SaveBuff	
   		u8 R7Buff[k1][R7_BodySize - 1];
		for (i = 0 ; i < k1 ; i++ ) {
			R7Buff[i][0] = 1;              
			R7Buff[i][1] = OUT->OutArray[63].Data.uint8;
			R7Buff[i][2] = k1;
			R7Buff[i][3] = i;
		}
		
		R7Buff[0][4] = OUT->OutArray[187].Data.uint8;	
		R7Buff[0][5] = OUT->OutArray[188].Data.uint8;
		R7Buff[0][6] = OUT->OutArray[189].Data.uint8;
		R7Buff[0][7] = OUT->OutArray[190].Data.uint8;
		R7Buff[0][8] = OUT->OutArray[0].Data.uint8;
		R7Buff[0][9] = OUT->OutArray[1].Data.uint8;
		R7Buff[0][10] = 0;	
        n = 3;
		for (; n < 45; n++)
			R7Buff[0][n + 9] = OUT->OutArray[n].Data.uint8;	    //��������� ������ ������ �7	
			
		for ( ; n < 62; n++)
			R7Buff[1][n - 41] = OUT->OutArray[n].Data.uint8;	//��������� ������ ����� ������� �������			
		
		n++;
		
		for ( ; n < 96; n++)
			R7Buff[1][n - 42] = OUT->OutArray[n].Data.uint8;	//��������� ������� ����� �������� �������			

		for ( ; n < 126; n++)
			R7Buff[2][n - 92] = OUT->OutArray[n].Data.uint8;	//��������� ������ ����� �������� �������							
		
		n++;	
		
		for ( ; n < 147; n++)
			R7Buff[2][n - 93] = OUT->OutArray[n].Data.uint8;	//��������� ������ ����� �������� �������							
		
		for ( ; n < 187; n++)
			R7Buff[3][n-143] = OUT->OutArray[n].Data.uint8;	//��������� 4 ������							
		
		n = 44;
		
		for ( ; n < R7_BodySize-4; n++)
			R7Buff[3][n] = Hvost[n - 44] ;	//��������� ����� �������� 3 ����� ��� ���� ��� 							

        if (OUT->State.Data.uint8 & flKnapPASS)
            R7Buff[3][n] = 0xFF;
        else
            R7Buff[3][n] = 0x00;
        
		n++;
        
		R7Buff[3][n] = OUT->KnapValue.Data.uint8;
        
		n++;
        
		R7Buff[3][n] = 0;
		NewQ_Arc_R7(R7Buff[0], 19);  // ������� ���� ������ ����������
		NewQ_Arc_R7(R7Buff[1], 19);  // ������� ���� ������ ����������
		NewQ_Arc_R7(R7Buff[2], 19);  // ������� ���� ������ ����������
		NewQ_Arc_R7(R7Buff[3], 19);  // ������� ���� ������ ����������

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////****/    

        
	if (!IN->Enable.Data.bit ) {
		OUT->State.Data.uint8 &= ~flEnable;
	}

	if (!IN->SaveDNM.Data.bit ) {
		(OUT->State.Data.uint8 &= ~flSaveDNM);
	}
}
