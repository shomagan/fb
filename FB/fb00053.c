/* ФБ "Часть массива" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00053.h"

void fb00053_exec(void) {

	fb00053_IN_type *IN = (fb00053_IN_type *) FBInputs;
	fb00053_OUT_type *OUT = (fb00053_OUT_type *) FBOutputs;
  Dataunion Data;
	u8 i;
	
// заполним 
	if ((IN->InArray[0].Type & DataTypeMask)==KodInt8) {
		if ((IN->NumBytes.Data.uint8 + IN->StartByte.Data.uint8)<250){
			for (i=0;i<IN->NumBytes.Data.uint8;i++)
			Data.uint8[i]=IN->InArray[IN->StartByte.Data.uint8 + i].Data.uint8;
		}
	}
	  else if((IN->InArray[0].Type & DataTypeMask)==KodInt16) {
			if ((IN->NumBytes.Data.uint8 + IN->StartByte.Data.uint8)<125){
				for (i=0;i<IN->NumBytes.Data.uint8;i++)
				Data.uint16[i]=IN->InArray[IN->StartByte.Data.uint8 + i].Data.uint16;
			}
		}
			else {
				if ((IN->NumBytes.Data.uint8 + IN->StartByte.Data.uint8)<62){
					for (i=0;i<IN->NumBytes.Data.uint8;i++)
					Data.uint32[i]=IN->InArray[IN->StartByte.Data.uint8 + i].Data.uint32;
				}
			}

// Выдадим
	if ((OUT->OutArray[0].Type & DataTypeMask)==KodInt8) {
		for (i=0;i<FB_N_Out;i++)
				OUT->OutArray[i].Data.uint8 = Data.uint8[i];
	} else if ((OUT->OutArray[0].Type & DataTypeMask)==KodInt16) {
			for (i=0;i<FB_N_Out;i++)
					OUT->OutArray[i].Data.uint16 = Data.uint16[i];
		} else {
			for (i=0;i<FB_N_Out;i++)
					OUT->OutArray[i].Data.uint32 = Data.uint32[i];
		}
		
	/* До этого было так...
	if ((IN->StartByte.Data.uint32 < FB53_InArrayMaxSize) && (IN->NumBytes.Data.uint32 < FB53_OutArrayMaxSize) && \
  	u8 InIdx, OutIdx;
    	((IN->StartByte.Data.uint32 + IN->NumBytes.Data.uint32) < FB53_InArrayMaxSize)) {
		InIdx = IN->StartByte.Data.uint32;
		OutIdx = 0;
    
		for (i = 0; i < IN->NumBytes.Data.uint32; i++){
			OUT->OutArray[OutIdx+i].Data.uint32 = IN->InArray[InIdx+i].Data.uint32;
		}
	}*/
}
