/* �� "��������������� UInt32/Float -> 2x UInt16" */

typedef struct {
	Register_type Input;  // uint16
} fb00073_IN_type;

typedef struct {
	Register_type LoWord;  // ������� �����
	Register_type HiWord;  // ������� �����
} fb00073_OUT_type;
u32 fb00073_var_size(u8 type);
