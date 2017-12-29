/* ФБ "Первое исполнение ФБ логики" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00061.h"

void fb00061_exec(void) {
	fb00061_OUT_type *OUT = (fb00061_OUT_type *) FBOutputs;
  
	OUT->Output.Data.bit = (KernelInfo.EventFlags.Bit.CfgFirstExec) ? 1 : 0;

}
