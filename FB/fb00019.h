/* ФБ "Среднее за N тактов" */

typedef struct {
	Register_type Value;
	Register_type N;
} fb00019_IN_type;

typedef struct {
	Register_type Summ;
	Register_type I;
} fb00019_VAR_type;

typedef struct {
	Register_type Output;
} fb00019_OUT_type;
u32 fb00019_var_size(u8 type);
