/* ФБ "уставка" */
#define MEGA12
#ifdef MEGA12
 
 
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "../kernel.h"
#include "handledfb00102.h"
void fb00102_exec(void)
{
  fb00102_IN_type *IN = (fb00102_IN_type *) FBInputs;
  fb00102_OUT_type *OUT = (fb00102_OUT_type *) FBOutputs;
  for (u16 i=0;i<FB_N_Out;i++){
    switch (IN->Default.Type & DataTypeMask)    // Тип входа
    {
    case KodBit:
    case KodInt8:
    case KodInt16:
    case KodInt32:
    case KodTime32:
      if (KernelInfo.EventFlags.Bit.CfgFirstExec){ //первое исполнение ФБ
        if (OUT->Variable[i].Data.uint32 > IN->Max.Data.uint32 || OUT->Variable[i].Data.uint32 <IN->Min.Data.uint32){
          OUT->Variable[i].Data.uint32 = IN->Default.Data.uint32;}
      }
      else if (IN->SetDefault.Data.bit) {OUT->Variable[i].Data.uint32 = IN->Default.Data.uint32;} 
      else if (OUT->Variable[i].Data.uint32 >IN->Max.Data.uint32){OUT->Variable[i].Data.uint32 = IN->Max.Data.uint32;}
      else if (OUT->Variable[i].Data.uint32 <IN->Min.Data.uint32){OUT->Variable[i].Data.uint32 = IN->Min.Data.uint32;}
      break;
    case KodFloat32:
      if (KernelInfo.EventFlags.Bit.CfgFirstExec){//первое исполнение ФБ
        if (OUT->Variable[i].Data.float32 > IN->Max.Data.float32 || OUT->Variable[i].Data.float32 <IN->Min.Data.float32){
          OUT->Variable[i].Data.float32 = IN->Default.Data.float32;}
      }
      else if (IN->SetDefault.Data.bit){
        OUT->Variable[i].Data.float32 = IN->Default.Data.float32;} 
      else if(OUT->Variable[i].Data.float32 >IN->Max.Data.float32){
        OUT->Variable[i].Data.float32 = IN->Max.Data.float32;}
      else if(OUT->Variable[i].Data.float32 < IN->Min.Data.float32){ 
        OUT->Variable[i].Data.float32 = IN->Min.Data.float32;}
    }
  }
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00102_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00102_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00102_OUT_type);
    default:
        return 0;
    }
}
