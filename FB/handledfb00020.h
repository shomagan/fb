/* ФБ "Среднее за N секунд" */

typedef struct {
	Register_type Value;
	Register_type N;
} fb00020_IN_type;

typedef struct {
	Register_type Summ;
	Register_type I;
	Register_type StartTime;
} fb00020_VAR_type;

typedef struct {
	Register_type Output;
} fb00020_OUT_type;
u32 fb00020_var_size(u8 type);
