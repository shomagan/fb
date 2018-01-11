/* ФБ "Алгебраическое умножение" */

typedef struct {
	Register_type In1;
	Register_type In2;
} fb00016_IN_type;

typedef struct {
	Register_type Output;
	Register_type Overflow;
} fb00016_OUT_type;
u32 fb00016_var_size(u8 type);
