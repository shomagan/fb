/* �� "�������� ���������" */

typedef struct {
	Register_type Input[256-1];      // ����
} fb00069_IN_type;

typedef struct {
	Register_type Detected;                   // �������� ���������
	Register_type Output[256-1];   // �����
} fb00069_OUT_type;
u32 fb00069_var_size(u8 type);
