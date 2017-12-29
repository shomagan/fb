/* ФБ преобразовать 2хuint16 -> uint32 */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00092.h"

void fb00092_exec(void)
{

	fb00092_IN_type *IN = (fb00092_IN_type *) FBInputs;
	fb00092_OUT_type *OUT = (fb00092_OUT_type *) FBOutputs;
  
	OUT->OutNum.Data.uint32 = (u32)(((IN->BigIn16.Data.uint16 << 16) & 0xffff0000) | IN->LitIn16.Data.uint16);
 }
