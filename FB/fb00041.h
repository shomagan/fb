/* ФБ "RS-триггер с приоритетным 0" */

typedef struct {
	Register_type R;    // Вход сброса выхода
	Register_type S;    // Вход установки выхода
} fb00041_IN_type;

typedef struct {
	Register_type T;    // Выход T
	Register_type nT;   // Инвертированный выход T
} fb00041_OUT_type;
