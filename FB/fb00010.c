/* ФБ "Набор битов -> Беззнаковое целое" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00010.h"

void fb00010_exec(void) {
	
	fb00010_IN_type *IN = (fb00010_IN_type *) FBInputs;
	fb00010_OUT_type *OUT = (fb00010_OUT_type *) FBOutputs;
	u8 i;

	OUT->Output.Data.uint32 = 0;
  
	switch (OUT->Output.Type & DataTypeMask) {   // Тип входа
		case KodBit:
			OUT->Output.Data.bit = (IN->Bits[0].Data.bit) ? 1 : 0;
			break;
		case KodInt8:
			for(i = 0; i < 8; i++) {
        if (i < FB_N_In){
  				if(IN->Bits[i].Data.bit){
  					OUT->Output.Data.uint8 |= (1<<i);
  				}
        }else{
          break;  //for
        }
			}
			break;
		case KodInt16:
			for(i = 0; i<16; i++) {
        if (i < FB_N_In){
  				if(IN->Bits[i].Data.bit) {
  					OUT->Output.Data.uint16 |= (1<<i);
  				}
        }else{
          break;  //for
        }
			}
			break;
		case KodInt32:
		case KodTime32:
			for(i = 0; i < 32; i++) {
        if (i < FB_N_In){
  				if (IN->Bits[i].Data.bit) {
  					OUT->Output.Data.uint32 |= (1<<i);
  				}
        }else{
          break;  //for
        }
			}
			break;
 		default:
 			break;
	}
}
