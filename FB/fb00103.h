/* �� "Master ������": ������ ������� ����������, ������������� ������� � �������� */

typedef struct {
	Register_type Enable;   // bit  ���������� �� ���������� ���� ��
	Register_type Run;   		// bit  ������ �������� �������
	Register_type Chanel;   // int8 ���� ��������� ����� ������ 10-�� (��������������) �� ���������� ����� ���� ������������������ �������, ������ 10-�� �� ���� ���� ������� � �� ��� ����������� ������ �� ����� ������
	Register_type Direct;   // bit  NSlv ��� ����� �������� - 1. 0 - NSlv ��� ����� ������� ��� ���� ����������� � �������� �������
	Register_type NSlv;     // int16 ����� ���������� � ���� ����������� �� � ������� �������
	Register_type NSP;      // int8 ���������� ��
	Register_type InSP[256]; // int16 ������� ���������� N
} fb00103_IN_type;

typedef struct {
	Register_type PackNum;			// uint8 ����� � ������ ������� ���������� � ������� ���� � ������� �������
	Register_type Trig;					// bit   ���������� ���������
	Register_type SR;						// bit	 ���������� �������� ��� Run - Exit ����� Enable = 0
	Register_type SyncTimeFB; 	//bit		 ���� �������� ������� � ����� ������, ������ ��� � ������
} fb00103_VAR_type;

typedef struct {
	Register_type Exit; // bit �����. 1-��������� ����. ��(����� ����� ��� ����� �� ��������), 0-�� ���������, ���� ����� � �������
	Register_type Exception;               // ������, ����� �� �����
	Register_type Ok; // ��� ������
	Register_type SP[256 - 3]; // �������� 251 ����� ������ ������� ����������
} fb00103_OUT_type;

void fb00103_exec (void);		// - ������ ������� ����������
