/* ФБ "Синхронизатор времени" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00044.h"

void fb00044_exec(void) {

	fb00044_IN_type *IN = (fb00044_IN_type *) FBInputs;

	if (IN->Enable.Data.bit)
		SysTimeWriteUNIX (IN->Time.Data.uint32);
}
