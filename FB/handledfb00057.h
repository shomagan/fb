/* ФБ "Запись системной настройки" */

typedef struct {
	Register_type ToWrite;  // bit Команда на запись
	Register_type Address;  // Адрес системного параметра
	Register_type Value;    // Значение системной настройки для записи
} fb00057_IN_type;

typedef struct {
	Register_type ErrorCode;  // Код ошибки при записи
} fb00057_OUT_type;
u32 fb00057_var_size(u8 type);
