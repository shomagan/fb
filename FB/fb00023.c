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
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00023_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00023_OUT_type);
    default:
        return 0;
    }
}
