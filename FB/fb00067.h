/* �� "������ ����������" */

typedef struct {
	Register_type Din;      // ������� ������
	Register_type Ust;      // ������� ��� ������� ��
} fb00067_IN_type;

typedef struct {
	Register_type Timer;  // �������� �������
} fb00067_VAR_type;

typedef struct {
	Register_type Dout;   // �������� c�����
} fb00067_OUT_type;
u32 fb00067_var_size(u8 type);
