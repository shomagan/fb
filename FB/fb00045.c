/* ФБ "Конвертер времени из UNIX-формата" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include <time.h>
#include "fb00045.h"

void fb00045_exec(void) {
	fb00045_IN_type *IN = (fb00045_IN_type *) FBInputs;
	fb00045_OUT_type *OUT = (fb00045_OUT_type *) FBOutputs;

	time_t Time = IN->UNIX_time.Data.uint32;
	struct tm *ptmx = localtime(&Time);    // Преобразование времени из UNIX-формата

	// Пишем в выходы
	OUT->Sec.Data.uint8 = ptmx->tm_sec;
	OUT->Min.Data.uint8 = ptmx->tm_min;
	OUT->Hour.Data.uint8 = ptmx->tm_hour;
	OUT->MDay.Data.uint8 = ptmx->tm_mday;
	OUT->Mon.Data.uint8 = ptmx->tm_mon+1;
	OUT->Year.Data.uint8 = ptmx->tm_year-80;

}
