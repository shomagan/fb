/* �� "��������� ������� � UNIX-������" */

typedef struct {
	Register_type Sec;  // ������
	Register_type Min;  // �����
	Register_type Hour; // �����
	Register_type MDay; // ���� ������
	Register_type Mon;  // �����
	Register_type Year; // ���
} fb00046_IN_type;

typedef struct {
	Register_type UNIX_time;       // ����� � ������� UNIX
} fb00046_OUT_type;
