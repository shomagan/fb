/* ФБ "Счётчик c ограничением по макс. приращению входа" */

typedef struct {
	Register_type Enable;       // bit
	Register_type Reset;        // bit
	Register_type Value;        // int8/16/32/float32
	Register_type MaxIncrement; // int8/16/32/float32 Уставка максимального изменения счётчика за такт (если 0 - отключен)
} fb00078_IN_type;

typedef struct {
	Register_type Enable_Old;   // bit
	Register_type Value_Old;    // int8/16/32
} fb00078_VAR_type;

typedef struct {
	Register_type Counter;        // int8/16/32
} fb00078_OUT_type;
u32 fb00078_var_size(u8 type);
