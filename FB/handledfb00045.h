/* ФБ "Конвертер времени из UNIX-формата" */

typedef struct {
	Register_type UNIX_time;  // Время в формате UNIX
} fb00045_IN_type;

typedef struct {
	Register_type Sec;        // Секунд
	Register_type Min;        // Минут
	Register_type Hour;       // Часов
	Register_type MDay;       // День месяца
	Register_type Mon;        // Месяц
	Register_type Year;       // Год
} fb00045_OUT_type;

u32 fb00045_var_size(u8 type);
