/* ФБ "Побитовое И" (заголовочный файл) */

typedef struct {
	Register_type In1;
	Register_type In2;
} fb00005_IN_type;

typedef struct {
	Register_type Out;
} fb00005_OUT_type;
u32 fb00005_var_size(u8 type);
