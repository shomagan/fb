/* ФБ "Секунд с начала исполнения конфигурации" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00059.h"

void fb00059_exec(void) {
	fb00059_OUT_type *OUT = (fb00059_OUT_type *) FBOutputs;
  
	if (CfgStartTime) // Проверка на то что время старта было запомнено
		OUT->CfgTime.Data.uint32 = GetSystemTime_t() - CfgStartTime;
	else
		CfgStartTime = GetSystemTime_t(); // На случай, если на момент начала исполнения конфигурации время ещё не было ни разу прочитано из RTC

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00059_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00059_OUT_type);
    default:
        return 0;
    }
}
