/* ФБ "Логическое НЕ" (заголовочный файл)*/

typedef struct {
    Register_type In1;
    Register_type In2;
} fb00004_IN_type;

typedef struct {
    Register_type Out;
} fb00004_OUT_type;
u32 fb00004_var_size(u8 type);
