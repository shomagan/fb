/* ФБ "Алгебраическая разность" */

typedef struct {
	Register_type In1;
	Register_type In2;
} fb00015_IN_type;

typedef struct {
	Register_type Output;
	Register_type Negative;
} fb00015_OUT_type;
u32 fb00015_var_size(u8 type);
