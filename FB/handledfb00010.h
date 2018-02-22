/* ФБ "Набор битов -> Беззнаковое целое" */

typedef struct {
	Register_type Bits[32];
} fb00010_IN_type;

typedef struct {
	Register_type Output;
} fb00010_OUT_type;
u32 fb00010_var_size(u8 type);
