/* �� "������ ��������� ���������" */

typedef struct {
	Register_type Address;    // � (�����) ��������� ���������
} fb00056_IN_type;

typedef struct {
	Register_type Value;      // �������� ��������� ���������
	Register_type ErrorCode;  // ��� ������ ��� ������
} fb00056_OUT_type;
u32 fb00056_var_size(u8 type);
