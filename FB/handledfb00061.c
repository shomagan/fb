/* ФБ "Первое исполнение ФБ логики" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00061.h"

void fb00061_exec(void) {
	fb00061_OUT_type *OUT = (fb00061_OUT_type *) FBOutputs;
  
	OUT->Output.Data.bit = (KernelInfo.EventFlags.Bit.CfgFirstExec) ? 1 : 0;

}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00061_var_size(unsigned char type) {
    switch(type){
    case(0):
        return 0;
    case(1):
        return 0;
    case(2):
        return sizeof(fb00061_OUT_type);
    default:
        return 0;
    }
}
