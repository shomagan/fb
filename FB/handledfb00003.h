/* ФБ "Логическое исключающее ИЛИ" (заголовочный файл) */

#define MaxInputs 32

typedef struct {
	Register_type Inputs[MaxInputs];
} fb00003_IN_type;

typedef struct {
	Register_type Out;
} fb00003_OUT_type;
u32 fb00003_var_size(u8 type);
