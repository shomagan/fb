/* ФБ "Системное время: секунд от начала часа" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00025.h"

void fb00025_exec(void) {

	fb00025_OUT_type *OUT = (fb00025_OUT_type *) FBOutputs;

	OUT->SystemTime.Data.uint32 = (FB32blok.vars.Cnt1Min * 60) + FB32blok.vars.Cnt1Sec;
}
