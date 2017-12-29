/*������������� DI*/

typedef struct {
	Register_type Nbit;   // int8  ����� ���� �� ����� � ������
	Register_type Kanal[256-1]; // int16 ����� (1-16) ���
} fb00106_IN_type;

typedef struct {
	Register_type OUT;			// bit ��������
	Register_type Error;			// bit ������
} fb00106_OUT_type;


void fb00106_exec (void);		// - ������ ������� ����������

