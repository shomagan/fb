/* ФБ "управления задвижкой" */
#define MEGA12

#ifdef MEGA12
 
 
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "../kernel.h"
#include "handledfb00101.h"
//State
#define NONCONFORMANCE 0
#define MINMAXERROR 1
#define TYPEERROR 2
void fb00101_exec(void)
{
  fb00101_IN_type *IN = (fb00101_IN_type *) FBInputs;
  fb00101_VAR_type *VAR = (fb00101_VAR_type *) FBVars;
  fb00101_OUT_type *OUT = (fb00101_OUT_type *) FBOutputs;
  float deviation_prcnt;
  signed short int disbalance;
#ifdef MEGA12
  if (KernelInfo.EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#else 
  if (EventFlags.Bit.CfgFirstExec) //первое исполнение ФБ
#endif
  {
  	OUT->BigParam.Data.bit = 0;
  	OUT->LowParam.Data.bit = 0;
  	OUT->WritePosition.Data.bit = 0;
  	OUT->State.Data.uint32 = 0;   
  	OUT->OutPosition.Data.uint16 = IN->CurrPosition.Data.uint16;         
    OUT->ReverseTime.Data.uint16 = IN->DisregardTime.Data.uint16;

  }else if (IN->Enable.Data.bit){
#ifdef MEGA12
    if((VAR->KernelClk.Data.uint32%KernelInfo.FBkernelRate)==0)
#else
    if((VAR->KernelClk.Data.uint32%FBkernelRate)==0)
#endif
    {
      if(OUT->ReverseTime.Data.uint16 > 0) OUT->ReverseTime.Data.uint16--;
    }
    OUT->WritePosition.Data.bit = 1;  //разрешаем запись
    IN->GistLess.Data.float32 = 0 - IN->GistLess.Data.float32;
    if(IN->MaxPosition.Data.uint16 > 1024)
      IN->MaxPosition.Data.uint16 = 1024;
    else if(IN->MaxPosition.Data.uint16 < 200){
      IN->MaxPosition.Data.uint16 = 200;
    	OUT->WritePosition.Data.bit = 0;    //вырубаем разрешение записи
      OUT->State.Data.uint32 |=BIT(MINMAXERROR);
    }
    if(IN->MinPosition.Data.uint16 < 200)
      IN->MinPosition.Data.uint16 = 200;
    else if(IN->MinPosition.Data.uint16 > 1024){
      IN->MinPosition.Data.uint16 = 1024;
    	OUT->WritePosition.Data.bit = 0;    //вырубаем разрешение записи
      OUT->State.Data.uint32 |=BIT(MINMAXERROR);
    }
    if(IN->Avtomat.Data.bit){
      if((IN->NeceseryParam.Type & DataTypeMask)==(IN->CurrParam.Type & DataTypeMask)){
        if((IN->NeceseryParam.Type & DataTypeMask) == KodFloat32){
          deviation_prcnt = ((IN->NeceseryParam.Data.float32 - IN->CurrParam.Data.float32)*100)/IN->NeceseryParam.Data.float32;
        }else if((IN->NeceseryParam.Type & DataTypeMask) == KodInt16){
          deviation_prcnt = ((signed int)(IN->NeceseryParam.Data.uint16 - IN->CurrParam.Data.uint16)*100)/(signed int)(IN->NeceseryParam.Data.uint16);
        }else{
          deviation_prcnt = 0;
          OUT->WritePosition.Data.bit = 0;    //вырубаем разрешение записи
          OUT->State.Data.uint32 |=BIT(TYPEERROR);
        }
        if(deviation_prcnt > IN->GistMore.Data.float32){
        	OUT->BigParam.Data.bit = 1;
        	OUT->LowParam.Data.bit = 0;
        }
        else if (deviation_prcnt < IN->GistLess.Data.float32){
        	OUT->BigParam.Data.bit = 0;
        	OUT->LowParam.Data.bit = 1;
        }
        else{
        	OUT->BigParam.Data.bit = 0;
        	OUT->LowParam.Data.bit = 0;
        }
        if (OUT->ReverseTime.Data.uint16 == 0){//можно действовать
          disbalance = OUT->OutPosition.Data.uint16 - IN->CurrPosition.Data.uint16;
        	if (OUT->BigParam.Data.bit){ 
            if (IN->Revers.Data.bit)
          	  OUT->OutPosition.Data.uint16 = IN->CurrPosition.Data.uint16 - IN->PositionInc.Data.uint16;
            else 
          	  OUT->OutPosition.Data.uint16 = IN->CurrPosition.Data.uint16 + IN->PositionInc.Data.uint16;
            if (IN->DisbalanceEnable.Data.bit) OUT->OutPosition.Data.uint16 = OUT->OutPosition.Data.uint16 + disbalance;
            OUT->ReverseTime.Data.uint16 = IN->DisregardTime.Data.uint16;
          }
        	if (OUT->LowParam.Data.bit){
            if (IN->Revers.Data.bit)
          	  OUT->OutPosition.Data.uint16 = IN->CurrPosition.Data.uint16 - IN->PositionDec.Data.uint16;
            else 
          	  OUT->OutPosition.Data.uint16 = IN->CurrPosition.Data.uint16 + IN->PositionDec.Data.uint16;
            if (IN->DisbalanceEnable.Data.bit) OUT->OutPosition.Data.uint16 = OUT->OutPosition.Data.uint16 + disbalance;
            OUT->ReverseTime.Data.uint16 = IN->DisregardTime.Data.uint16;
          }
        }

      }else{
        OUT->State.Data.uint32 |=BIT(TYPEERROR);
      	OUT->WritePosition.Data.bit = 0;    //вырубаем разрешение записи
      }
    }else{
      OUT->OutPosition.Data.uint16 = IN->NeceseryPosition.Data.uint16;
    }
    OUT->OutPosition.Data.uint16 = (OUT->OutPosition.Data.uint16 > IN->MaxPosition.Data.uint16)?IN->MaxPosition.Data.uint16 : OUT->OutPosition.Data.uint16;
    OUT->OutPosition.Data.uint16 = (OUT->OutPosition.Data.uint16 < IN->MinPosition.Data.uint16)?IN->MinPosition.Data.uint16 : OUT->OutPosition.Data.uint16;
  }else{
  	OUT->BigParam.Data.bit = 0;
  	OUT->LowParam.Data.bit = 0;
  	OUT->State.Data.uint32 = 0;
  	OUT->OutPosition.Data.uint16 = 0;
  }
  VAR->KernelClk.Data.uint32++;
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00101_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00101_IN_type);
    case(1):
        return sizeof(fb00101_VAR_type);
    case(2):
        return sizeof(fb00101_OUT_type);
    default:
        return 0;
    }
}
