/* ФБ "Весовой импульс с счетчика" */

typedef struct {
	Register_type Enable;       // bit
	Register_type Reset;        // bit
	Register_type Value;        // int8/16/32/float32
	Register_type MaxIncrement; // int8/16/32/float32 Уставка максимального изменения счётчика за такт (если 0 - отключен)
} fb00081_IN_type;

typedef struct {
	Register_type Enable_Old;   // bit
	Register_type Value_Old;    // int8/16/32
} fb00081_VAR_type;

typedef struct {
	Register_type Counter;        // int8/16/32
} fb00081_OUT_type;
