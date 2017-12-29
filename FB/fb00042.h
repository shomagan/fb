/* ФБ "Триггер со сбросом" */

typedef struct {
	Register_type In;     // Вход подачи "1"
} fb00042_IN_type;

typedef struct {
	Register_type Out;    // Выход (импульс)
	Register_type ROut;   // Выход на сброс входа
} fb00042_OUT_type;
