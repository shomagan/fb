/* �� "��������������� � ������" */

typedef struct {
	Register_type Input[256];    // ������� ��������
} fb00060_IN_type;


typedef struct {
	Register_type Output[256];  // �������� ������
} fb00060_OUT_type;
u32 fb00060_var_size(u8 type);
