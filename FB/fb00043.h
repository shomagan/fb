/* �� "������������ �� ������" */

typedef struct {
	Register_type In;     // ����               bit
	Register_type Tics;   // ������ ��������    int8/16/32
} fb00043_IN_type;

typedef struct {
	Register_type In_Old; // ���������� ��������� �����
} fb00043_VAR_type;

typedef struct {
	Register_type Timer;  // ������
	Register_type Out;    // ����� (�������)
} fb00043_OUT_type;
u32 fb00043_var_size(u8 type);
