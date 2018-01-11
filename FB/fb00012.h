/* ФБ "Беззнаковое целое -> Float32 (с множителем и делителем)" */

typedef struct {
	Register_type Value;
	Register_type Multiplier;
	Register_type Divider;
} fb00012_IN_type;

typedef struct {
	Register_type Output;
} fb00012_OUT_type;
u32 fb00012_var_size(u8 type);
