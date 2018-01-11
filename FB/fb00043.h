/* ФБ "Одновибратор по фронту" */

typedef struct {
	Register_type In;     // Вход               bit
	Register_type Tics;   // Тактов импульса    int8/16/32
} fb00043_IN_type;

typedef struct {
	Register_type In_Old; // Предыдущее состояние входа
} fb00043_VAR_type;

typedef struct {
	Register_type Timer;  // Таймер
	Register_type Out;    // Выход (импульс)
} fb00043_OUT_type;
u32 fb00043_var_size(u8 type);
