/* �� BCD to HEX */
#include "../vars.h"
#include <string.h>
#include "../kernel.h"
#include "../regs.h"
#include "fb00112.h"


//------------------------------------------------------------------------------
void fb00112_exec(void)
{
	fb00112_IN_type *IN = (fb00112_IN_type *) FBInputs;
	fb00112_OUT_type *OUT = (fb00112_OUT_type *) FBOutputs;
	vu8 i,j,k;
	vu8 Buf[254]={0};
	j=0;
	vu32 XX, DEC[50];
	
	// ��������
	if ((IN->Input[0].Type & DataTypeMask)==KodInt8) { // �� ����� u8
			for (i=0;i<IN->N.Data.uint8; i++) {// �������� 
				if (IN->Format.Data.bit) {
					if (IN->Input[i].Data.uint8 & 0xFF || j) { // ����������� ����� �����
						Buf[j++]=IN->Input[i].Data.uint8;
					}
				} else {
					Buf[j++]=IN->Input[i].Data.uint8;
				}
			}
	} else if ((IN->Input[0].Type & DataTypeMask)==KodInt16){ //�� ����� u16
			for (i=0;i<IN->N.Data.uint8; i++) {// �������� 
				//if (IN->Input[i].Data.uint16 & 0xFF || j) { // ����������� ����� �����
					*((u16*)(Buf + j))=IN->Input[i].Data.uint16;
					j+=2;
				//}
			}
	} else { //�� ����� u32
			for (i=0;i<IN->N.Data.uint8; i++) {// �������� 
				//if (IN->Input[i].Data.uint32 & 0xFF || j) { // ����������� ����� �����
					*((u32*)(Buf + j))=IN->Input[i].Data.uint32;
					j+=4;
				//}
			}
	}
	
	// ������
	k=0;
	if ((OUT->Output[0].Type & DataTypeMask)==KodInt8) { // �� ������ u8
		for (i=0; i<j; i++) 
			OUT->Output[i].Data.uint8 = (Buf[i] & 0xF) + ((Buf[i] & 0xF0) >> 4)*10;
		
	} else if ((OUT->Output[0].Type & DataTypeMask)==KodInt16) { // �� ������ u16
				for(i=0;i<j;i+=2){
					OUT->Output[k++].Data.uint16 = ((Buf[i] & 0xF0)>>4)*1000 + ((Buf[i]) & 0x0F)*100 + ((Buf[i+1] & 0xF0)>>4)*10 + ((Buf[i+1]) & 0x0F);
				}
	
	} else { // �� ������ u32
				for(i=0;i<j;i+=4){
					OUT->Output[k++].Data.uint32 = 	((Buf[i] & 0xF0)>>4)*10000000 + 
																					((Buf[i]) & 0x0F)*1000000 + 
																					((Buf[i+1] & 0xF0)>>4)*100000 + 
																					((Buf[i+1]) & 0x0F)*10000 +
																					((Buf[i+2] & 0xF0)>>4)*1000 + 
																					((Buf[i+2]) & 0x0F)*100 + 
																					((Buf[i+3] & 0xF0)>>4)*10 + 
																					((Buf[i+3]) & 0x0F);

				}
				
	}

}