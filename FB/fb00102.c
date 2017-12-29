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
#include "fb00102.h"
void fb00102_exec(void)
{
  fb00102_IN_type *IN = (fb00102_IN_type *) FBInputs;
  fb00102_OUT_type *OUT = (fb00102_OUT_type *) FBOutputs;
  for (u16 i=0;i<FB_N_Out;i++){
    switch (IN->Default.Type & DataTypeMask)    // Тип входа
    {
    case KodBit:
    case KodInt8:
      if (KernelInfo.EventFlags.Bit.CfgFirstExec){ //первое исполнение ФБ
        if (OUT->Variable[i].Data.uint8 > IN->Max.Data.uint8 || OUT->Variable[i].Data.uint8 <IN->Min.Data.uint8){
          OUT->Variable[i].Data.uint8 = IN->Default.Data.uint8;}
      }
      else if (IN->SetDefault.Data.bit) {OUT->Variable[i].Data.uint8 = IN->Default.Data.uint8;} 
      else if (OUT->Variable[i].Data.uint8 >IN->Max.Data.uint8){OUT->Variable[i].Data.uint8 = IN->Max.Data.uint8;}
      else if (OUT->Variable[i].Data.uint8 <IN->Min.Data.uint8){OUT->Variable[i].Data.uint8 = IN->Min.Data.uint8;}
      break;
    case KodInt16:
      if (KernelInfo.EventFlags.Bit.CfgFirstExec){ //первое исполнение ФБ
        if (OUT->Variable[i].Data.uint16 > IN->Max.Data.uint16 || OUT->Variable[i].Data.uint16 <IN->Min.Data.uint16){
          OUT->Variable[i].Data.uint16 = IN->Default.Data.uint16;}
      }
      else if (IN->SetDefault.Data.bit) {OUT->Variable[i].Data.uint16 = IN->Default.Data.uint16;} 
      else if (OUT->Variable[i].Data.uint16 >IN->Max.Data.uint16){OUT->Variable[i].Data.uint16 = IN->Max.Data.uint16;}
      else if (OUT->Variable[i].Data.uint16 <IN->Min.Data.uint16){OUT->Variable[i].Data.uint16 = IN->Min.Data.uint16; }
      break;
    case KodInt32:
      if (KernelInfo.EventFlags.Bit.CfgFirstExec){ //первое исполнение ФБ
        if (OUT->Variable[i].Data.uint32 > IN->Max.Data.uint32 || OUT->Variable[i].Data.uint32 <IN->Min.Data.uint32){
          OUT->Variable[i].Data.uint32 = IN->Default.Data.uint32;}
      }
      else if (IN->SetDefault.Data.bit) {OUT->Variable[i].Data.uint32 = IN->Default.Data.uint32;} 
      else if (OUT->Variable[i].Data.uint32 >IN->Max.Data.uint32){OUT->Variable[i].Data.uint32 = IN->Max.Data.uint32;}
      else if (OUT->Variable[i].Data.uint32 <IN->Min.Data.uint32){OUT->Variable[i].Data.uint32 = IN->Min.Data.uint32;}
      break;
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
