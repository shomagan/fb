/* �� "��������������� ������� uint16_BE->������ uint8" */

typedef struct {
	Register_type BigEndian;    // ������� ��������
	Register_type Input[256-1];  // ������� ��������
} fb00065_IN_type;

typedef struct {
	Register_type Output[256];  // �������� ������
} fb00065_OUT_type;
u32 fb00065_var_size(u8 type);
