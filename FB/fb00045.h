/* �� "��������� ������� �� UNIX-�������" */

typedef struct {
	Register_type UNIX_time;  // ����� � ������� UNIX
} fb00045_IN_type;

typedef struct {
	Register_type Sec;        // ������
	Register_type Min;        // �����
	Register_type Hour;       // �����
	Register_type MDay;       // ���� ������
	Register_type Mon;        // �����
	Register_type Year;       // ���
} fb00045_OUT_type;

