/* ФБ " Беззнаковое целое -> Набор битов" */

typedef struct {
	Register_type Input;
} fb00009_IN_type;

typedef struct {
	Register_type Bits[32];
} fb00009_OUT_type;
u32 fb00009_var_size(u8 type);
