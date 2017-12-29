/* ФБ "Системное время: текущая дата и время в int32" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00023.h"

void fb00023_exec (void){
	fb00023_OUT_type * OUT = (fb00023_OUT_type *) FBOutputs;
	u32 TimeTemp;

	TimeTemp = GetSystemTime_t();
	if (TimeTemp){
		OUT->SystemTime.Data.uint32 = TimeTemp;
	}

	OUT->Need2Sync.Data.bit = GetNeed2SyncState();
}
