/* �� "������ ��������� ���������" */

typedef struct {
	Register_type ToWrite;  // bit ������� �� ������
	Register_type Address;  // ����� ���������� ���������
	Register_type Value;    // �������� ��������� ��������� ��� ������
} fb00057_IN_type;

typedef struct {
	Register_type ErrorCode;  // ��� ������ ��� ������
} fb00057_OUT_type;
