/* ФБ "Системное время: секунд от начала суток" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00026.h"

void fb00026_exec(void) {

	fb00026_OUT_type *OUT = (fb00026_OUT_type *) FBOutputs;

	OUT->SystemTime.Data.uint32 = (FB32blok.vars.Cnt1Chas * 3600) + (FB32blok.vars.Cnt1Min * 60) + FB32blok.vars.Cnt1Sec;

}
