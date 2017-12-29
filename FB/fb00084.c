/* ФБ "Запись в батарейный домен" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00084.h"

void fb00084_exec(void) {
	fb00084_IN_type *IN = (fb00084_IN_type *) FBInputs;
	fb00084_OUT_type *OUT = (fb00084_OUT_type *) FBOutputs;
  
	OUT->Ok.Data.bit = 0;

	if (IN->EnWrite.Data.bit) {
		if ((IN->Address.Type & DataTypeMask) != KodFloat32) {
			if (IN->Address.Data.uint16 < MAX_BAT_MEM_SIZE) {
				BateryMemFB32[IN->Address.Data.uint16] = IN->Value.Data.uint32;
				OUT->Ok.Data.bit = 1;
			}
		}
	}
}
