/* ФБ "Чтение системной настройки" */

typedef struct {
	Register_type Address;    // № (адрес) системной настройки
} fb00056_IN_type;

typedef struct {
	Register_type Value;      // Значение системной найтройки
	Register_type ErrorCode;  // Код ошибки при чтении
} fb00056_OUT_type;
