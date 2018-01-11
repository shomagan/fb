/* ФБ "Преобразователь 2x UInt16 -> UInt32/Float" */

typedef struct {
	Register_type LoWord;  // uint16
	Register_type HiWord;  // uint16
} fb00075_IN_type;

typedef struct {
	Register_type Output;  // Выход 32бит
} fb00075_OUT_type;
u32 fb00075_var_size(u8 type);
