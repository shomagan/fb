/* ФБ "Побитовое НЕ" (заголовочный файл) */

typedef struct {
	Register_type In1;
} fb00008_IN_type;

typedef struct {
	Register_type Out;
} fb00008_OUT_type;
u32 fb00008_var_size(u8 type);
