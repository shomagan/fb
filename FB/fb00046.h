/* ФБ "Конвертер времени в UNIX-формат" */

typedef struct {
	Register_type Sec;  // Секунд
	Register_type Min;  // Минут
	Register_type Hour; // Часов
	Register_type MDay; // День месяца
	Register_type Mon;  // Месяц
	Register_type Year; // Год
} fb00046_IN_type;

typedef struct {
	Register_type UNIX_time;       // Время в формате UNIX
} fb00046_OUT_type;
