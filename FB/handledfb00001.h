/* ФБ "Логическое И" (заголовочный файл) */

#define MaxInputs 32

typedef struct {
	Register_type Inputs[MaxInputs];
} fb00001_IN_type;

typedef struct {
	Register_type Out;
} fb00001_OUT_type;

u32 fb00001_var_size(u8 type);
