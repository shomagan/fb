/* ФБ "Логическое ИЛИ" (заголовочный файл) */

#define MaxInputs 32

typedef struct {
	Register_type Inputs[MaxInputs];
} fb00002_IN_type;

typedef struct {
	Register_type Out;
} fb00002_OUT_type;

u32 fb00002_var_size(u8 type);
