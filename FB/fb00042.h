/* �� "������� �� �������" */

typedef struct {
	Register_type In;     // ���� ������ "1"
} fb00042_IN_type;

typedef struct {
	Register_type Out;    // ����� (�������)
	Register_type ROut;   // ����� �� ����� �����
} fb00042_OUT_type;
u32 fb00042_var_size(u8 type);
