/* ФБ "Системное время: секунд от начала минуты" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00024.h"

void fb00024_exec(void) {

	fb00024_OUT_type *OUT = (fb00024_OUT_type *) FBOutputs;
  
	OUT->SystemTime.Data.uint32 = FB32blok.vars.Cnt1Sec;

}
