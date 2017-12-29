/* ФБ "Первая секунда исполнения конфигурации" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00058.h"

void fb00058_exec(void) {
	fb00058_OUT_type *OUT = (fb00058_OUT_type *) FBOutputs;

	OUT->FirstSec.Data.bit = (KernelInfo.EventFlags.Bit.CfgFirstSec) ? 1 : 0;

}
