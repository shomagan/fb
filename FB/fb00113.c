/* ФБ HEX to BCD */
#include "../vars.h"
#include <string.h>
#include "../kernel.h"
#include "../regs.h"
#include "fb00113.h"

vu32 dec2bcd(vu32 dec) 
{
    vu32 result = 0;
    int shift = 0;

    while (dec)
    {
        result +=  (dec % 10) << shift;
        dec = dec / 10;
        shift += 4;
    }
    return result;
}

//------------------------------------------------------------------------------
void fb00113_exec(void)
{
	fb00113_IN_type *IN = (fb00113_IN_type *) FBInputs;
	fb00113_OUT_type *OUT = (fb00113_OUT_type *) FBOutputs;
	vu8 i,j,k,Buf[254];
	j=0;
	memset((void*)Buf, 0 , sizeof(Buf));
		// забираем
	if ((IN->Input[0].Type & DataTypeMask)==KodInt8) { // На входе u8
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
					Buf[j++]=IN->Input[i].Data.uint8;
			}
	} else if ((IN->Input[0].Type & DataTypeMask)==KodInt16){ //На входе u16
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
					*((u16*)(Buf + j))=IN->Input[i].Data.uint16;
					j+=2;
			}
	} else { //На входе u32
			for (i=0;i<IN->N.Data.uint8; i++) {// заполним 
					*((u32*)(Buf + j))=IN->Input[i].Data.uint32;
					j+=4;
			}
	}
	
		// Выдаем
	k=0;
	if ((OUT->Output[0].Type & DataTypeMask)==KodInt8) { // На выходе u8
		for (i=0; i<j; i++)
			OUT->Output[i].Data.uint8 = ((Buf[i]/10)<<4)|(Buf[i]%10);
		
	} else if ((OUT->Output[0].Type & DataTypeMask)==KodInt16) { // На выходе u16
				for(i=0;i<j;i+=2){
					OUT->Output[k++].Data.uint16 = dec2bcd(*((u16*)(Buf + i)));
				}
	
	} else { // На выходе u32
				for(i=0;i<j;i+=4){
					OUT->Output[k++].Data.uint32 = 	dec2bcd(*((u32*)(Buf + i)));
				}
	}
}

