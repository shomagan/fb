/* ФБ "Первая секунда исполнения конфигурации" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00058.h"

void fb00058_exec(void) {
	fb00058_OUT_type *OUT = (fb00058_OUT_type *) FBOutputs;

	OUT->FirstSec.Data.bit = (KernelInfo.EventFlags.Bit.CfgFirstSec) ? 1 : 0;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00058_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00058_OUT_type);
    default:
        return 0;
    }
}
