/* ФБ "Алгебраическое деление" */

typedef struct {
	Register_type Value;
	Register_type Divider;
} fb00017_IN_type;

typedef struct {
	Register_type Output;
	Register_type Error;
} fb00017_OUT_type;
u32 fb00017_var_size(u8 type);
