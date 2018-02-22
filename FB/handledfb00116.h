/* ФБ "Мультиплексор 2.0" */

typedef struct {
	Register_type Input[254];  // uint32
} fb00116_IN_type;

typedef struct {
	Register_type Output[254];  // 1
} fb00116_OUT_type;
u32 fb00116_var_size(u8 type);
