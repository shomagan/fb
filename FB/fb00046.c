/* ФБ "Конвертер времени в UNIX-формат" */
#include <time.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00046.h"

void fb00046_exec(void) {

	fb00046_IN_type *IN = (fb00046_IN_type *) FBInputs;
	fb00046_OUT_type *OUT = (fb00046_OUT_type *) FBOutputs;

	struct tm tmx;

	tmx.tm_sec  = IN->Sec.Data.uint8;      // seconds after the minute (from 0)
	tmx.tm_min  = IN->Min.Data.uint8;      // minutes after the hour (from 0)
	tmx.tm_hour = IN->Hour.Data.uint8;     // hour of the day (from 0)
	tmx.tm_mday = IN->MDay.Data.uint8;     // day of the month (from 1)
	tmx.tm_mon  = IN->Mon.Data.uint8-1;    // month of the year (from 0)
	tmx.tm_year = IN->Year.Data.uint8+80;  // years since 1900 (from 0)
	tmx.tm_wday = 0;                          // days since Sunday (from 0)
	tmx.tm_yday = 0;                          // day of the year (from 0)
	tmx.tm_isdst = 0;                         // Daylight Saving Time flag
	time_t UnixTime = mktime(&tmx);
  
	OUT->UNIX_time.Data.uint32 = UnixTime;
}
