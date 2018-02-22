/* ФБ фильтр "DI длинный 0 остальное 1" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

typedef struct {
	Register_type DI;			// bit
	Register_type Bit01;		// bit
	Register_type dT;			// uint8
} fb00094_IN_type;

typedef struct {
	Register_type DIOld;		// bit
	Register_type CntSec;		// uint32
} fb00094_VAR_type;

typedef struct {
	Register_type DO;			// bit
} fb00094_OUT_type;

void fb00094_exec(void){
fb00094_IN_type *IN=(fb00094_IN_type *) FBInputs;
fb00094_VAR_type *VAR=(fb00094_VAR_type *) FBVars;
fb00094_OUT_type *OUT=(fb00094_OUT_type *) FBOutputs;

	if(KernelInfo.EventFlags.Bit.CfgFirstExec){
		VAR->CntSec.Data.uint32 = cntSecFromStart;	
		OUT->DO.Data.bit = VAR->DIOld.Data.bit = IN->DI.Data.bit;	
		  
	} 
	else {
		if(IN->DI.Data.bit == VAR->DIOld.Data.bit){	//Вход не изменился
			if(IN->DI.Data.bit == IN->Bit01.Data.bit){ //тянется то сост, которое тянем
				if((cntSecFromStart - VAR->CntSec.Data.uint32) >= IN->dT.Data.uint32) 
					OUT->DO.Data.bit = IN->Bit01.Data.bit; 	// дотянули!
				//else //OUT->DO.Data.bit = ~IN->Bit01.Data.bit; 	// не дотянули еще
			}
			else  OUT->DO.Data.bit = ~IN->Bit01.Data.bit;
		}
		else{			//изменение по входу
			if(IN->DI.Data.bit == IN->Bit01.Data.bit) 		//на входе появилось то сост, которое тянем
				VAR->CntSec.Data.uint32 = cntSecFromStart; 	// запомним счетч секунд - отсюда тянем			
			OUT->DO.Data.bit = ~IN->Bit01.Data.bit; 	// не дотянули еще	
			VAR->DIOld.Data.bit = IN->DI.Data.bit;
		}
	}
}
