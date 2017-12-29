/* ФБ "Алгебраическое сложение" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00014.h"

void fb00014_exec(void) {

  fb00014_IN_type *IN = (fb00014_IN_type *) FBInputs;
  fb00014_OUT_type *OUT = (fb00014_OUT_type *) FBOutputs;

  u8 i, HasFloats; 
  Flo32 TempFloat;
  HasFloats = 0;
  TempFloat = 0.0;
  
  OUT->Output.Data.uint32 = 0;
  OUT->Overflow.Data.bit = 0;

  if (FB_N_In <= MaxInputs) {
    switch (OUT->Output.Type & DataTypeMask) {
    case KodInt8:
    case KodInt16:
    case KodInt32:
    case KodTime32: // Выход не вещественного типа
      for (i = 0; i < FB_N_In; i++) {
        if ((IN->Inputs[i].Type & DataTypeMask) == KodFloat32)  // Очередной вход типа Float
          HasFloats = 1;
      }
      
      for (i = 0; i < FB_N_In; i++) {
        if (HasFloats)
          TempFloat += Void2Float32 (&(IN->Inputs[i]));
        else {
          if ((IN->Inputs[i].Type & DataTypeMask) == KodFloat32)
            OUT->Output.Data.uint32 += IN->Inputs[i].Data.float32; 
          else
            OUT->Output.Data.uint32 += IN->Inputs[i].Data.uint32;
         
          if (WasAddOverflow ())
            OUT->Overflow.Data.bit = 1;
          else
            OUT->Overflow.Data.bit = 0;
        }
      }

      if (HasFloats) {
        OUT->Overflow.Data.bit = (IsCorrectFloat (TempFloat)) ? 0 : 1;
        OUT->Output.Data.uint32 = (u32) TempFloat; 
      }
      break;
    case KodFloat32:    // Выход вещественного типа
      for (i=0; i<FB_N_In; i++)
        OUT->Output.Data.float32 += Void2Float32 (&(IN->Inputs[i]));
      
      OUT->Overflow.Data.bit = (IsCorrectFloat (OUT->Output.Data.float32)) ? 0 : 1;
      break;
    default:
      OUT->Output.Data.uint32 = 0;
      break;    
    }
  } else {
    OUT->Output.Data.uint32 = 0;
  }
}
