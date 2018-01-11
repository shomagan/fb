/* ФБ "Детектор изменений" */

typedef struct {
	Register_type Input[256-1];      // Вход
} fb00069_IN_type;

typedef struct {
	Register_type Detected;                   // Детектор изменений
	Register_type Output[256-1];   // Выход
} fb00069_OUT_type;
u32 fb00069_var_size(u8 type);
