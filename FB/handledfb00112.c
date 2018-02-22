/* ФБ BCD to HEX */
 
 
#include "../vars.h"
 
#include <string.h>
#include "../kernel.h"
#include "../regs.h"
 
 
 
#include "handledfb00112.h"


//------------------------------------------------------------------------------
void fb00112_exec(void)
{
	fb00112_IN_type *IN = (fb00112_IN_type *) FBInputs;
	fb00112_OUT_type *OUT = (fb00112_OUT_type *) FBOutputs;
	vu8 i,j,k;
	vu8 Buf[254]={0};
	j=0;
	vu32 XX, DEC[50];
	
	// забираем
	if ((IN->Input[0].Type & DataTypeMask)==KodInt8) { // На входе u8
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
				if (IN->Format.Data.bit) {
					if (IN->Input[i].Data.uint8 & 0xFF || j) { // Выравниваем байты влево
						Buf[j++]=IN->Input[i].Data.uint8;
					}
				} else {
					Buf[j++]=IN->Input[i].Data.uint8;
				}
			}
	} else if ((IN->Input[0].Type & DataTypeMask)==KodInt16){ //На входе u16
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
				//if (IN->Input[i].Data.uint16 & 0xFF || j) { // Выравниваем байты влево
					*((u16*)(Buf + j))=IN->Input[i].Data.uint16;
					j+=2;
				//}
			}
	} else { //На входе u32
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
				//if (IN->Input[i].Data.uint32 & 0xFF || j) { // Выравниваем байты влево
					*((u32*)(Buf + j))=IN->Input[i].Data.uint32;
					j+=4;
				//}
			}
	}
	
	// Выдаем
	k=0;
	if ((OUT->Output[0].Type & DataTypeMask)==KodInt8) { // На выходе u8
		for (i=0; i<j; i++) 
			OUT->Output[i].Data.uint8 = (Buf[i] & 0xF) + ((Buf[i] & 0xF0) >> 4)*10;
		
	} else if ((OUT->Output[0].Type & DataTypeMask)==KodInt16) { // На выходе u16
				for(i=0;i<j;i+=2){
					OUT->Output[k++].Data.uint16 = ((Buf[i] & 0xF0)>>4)*1000 + ((Buf[i]) & 0x0F)*100 + ((Buf[i+1] & 0xF0)>>4)*10 + ((Buf[i+1]) & 0x0F);
				}
	
	} else { // На выходе u32
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

}/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00112_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00112_IN_type);
    case(1):
        return sizeof(fb00112_VAR_type);
    case(2):
        return sizeof(fb00112_OUT_type);
    default:
        return 0;
    }
}
