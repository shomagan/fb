/* ФБ "Фильтр дискретный" */

typedef struct {
	Register_type Din;      // Входной сигнал
	Register_type Ust;      // Уставка для таймера ФБ
} fb00067_IN_type;

typedef struct {
	Register_type Timer;  // Значение таймера
} fb00067_VAR_type;

typedef struct {
	Register_type Dout;   // Выходной cигнал
} fb00067_OUT_type;
u32 fb00067_var_size(u8 type);
