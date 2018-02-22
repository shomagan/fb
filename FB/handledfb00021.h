/* ФБ "Компаратор" */

typedef struct {
	Register_type Input;
	Register_type UpperLimit;
	Register_type LowerLimit;
} fb00021_IN_type;

typedef struct {
	Register_type OutUp;
	Register_type OutLow;
} fb00021_OUT_type;
u32 fb00021_var_size(u8 type);
