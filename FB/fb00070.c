/* "Преобразователь маршруса RTM64var -> RTM64" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00070.h"

void fb00070_exec(void)
{

	fb00070_IN_type *IN = (fb00070_IN_type *) FBInputs;
	fb00070_OUT_type *OUT = (fb00070_OUT_type *) FBOutputs;

	u8 i, RetranNum = 0;
    
	OUT->Module_Addr.Data.uint16 = IN->Module_Addr.Data.uint16;
	OUT->Module_IntAddr.Data.uint16 = IN->Module_IntAddr.Data.uint16;
  
	for (i=0; i<4; i++) {
    // Считаем кол-во контроллеров в маршруте
		if ((IN->RTM_Rout[i<<1].Data.uint16 > 0) && 
        	(IN->RTM_Rout[i<<1].Data.uint16 != 0xFFFF) && 
	        (IN->RTM_Rout[(i<<1)+1].Data.uint8 != 0xFF) )
    		
			RetranNum++;
    
		OUT->RTM_Rout[i<<1].Data.uint16 = 0;
		OUT->RTM_Rout[(i<<1)+1].Data.uint8 = 0;
	}
  
	// Заполняем выходной маршрут
	if (RetranNum > 0) {
		OUT->RTM_Rout[6].Data.uint16 = IN->RTM_Rout[RetranNum-1].Data.uint16;
		OUT->RTM_Rout[7].Data.uint8 = IN->RTM_Rout[RetranNum-1].Data.uint8;
    
		for (i=0; i<(RetranNum-1); i++) {
			OUT->RTM_Rout[i<<1].Data.uint16 = IN->RTM_Rout[i<<1].Data.uint16;
			OUT->RTM_Rout[(i<<1)+1].Data.uint8 = IN->RTM_Rout[(i<<1)+1].Data.uint8;
		}
	}
}
