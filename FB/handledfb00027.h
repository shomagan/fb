/* ФБ "Таймер: секунд от начала периода" */

typedef struct {
	Register_type Reset;        // bit
} fb00027_IN_type;

typedef struct {
	Register_type StartTime;
} fb00027_VAR_type;

typedef struct {
	Register_type PeriodTime;
} fb00027_OUT_type;
u32 fb00027_var_size(u8 type);
