/* ФБ "инертная задержка " */
#define MEGA12

#ifdef MEGA12
 #include "../vars.h"
 #include "../regs.h"
#else
 #include "../RegAccess.h"
 #include "../timers.h"
#endif
#include "../kernel.h"
#include <math.h>
#include "fb00100.h"
void fb00100_exec() {

	fb00100_IN_type *IN = (fb00100_IN_type *) FBInputs;
	fb00100_VAR_type *VAR = (fb00100_VAR_type *) FBVars;
	fb00100_OUT_type *OUT = (fb00100_OUT_type *) FBOutputs;
  const float SPEED = 0.1;
  if (KernelInfo.EventFlags.Bit.CfgFirstExec){///1 выполнение
    VAR->InputOld.Data.float32 = IN->Input.Data.float32;
    OUT->Output.Data.float32 = (VAR->InputOld.Data.float32*0.01) * IN->dInput.Data.float32;
  }
  else {
    if ((IN->Input.Data.float32 - VAR->InputOld.Data.float32)>=SPEED)
      VAR->InputOld.Data.float32 = VAR->InputOld.Data.float32 + SPEED;
    else if((IN->Input.Data.float32 - VAR->InputOld.Data.float32)<=-SPEED)
      VAR->InputOld.Data.float32 = VAR->InputOld.Data.float32 - SPEED;
    else
      VAR->InputOld.Data.float32 = VAR->InputOld.Data.float32 + (IN->Input.Data.float32 - VAR->InputOld.Data.float32);      
    if (VAR->InputOld.Data.float32 > 100.0)VAR->InputOld.Data.float32 =100.0;
    if (VAR->InputOld.Data.float32 < 0.0)VAR->InputOld.Data.float32 =0.0;
    OUT->Output.Data.float32 = (VAR->InputOld.Data.float32*0.01) * IN->dInput.Data.float32;
  }
}
