/* ФБ "Побитовое исключающее ИЛИ" (заголовочный файл) */

typedef struct {
	Register_type In1;
	Register_type In2;
} fb00007_IN_type;

typedef struct {
	Register_type Out;
} fb00007_OUT_type;
u32 fb00007_var_size(u8 type);
