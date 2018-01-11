/*������ ������� ����������*/

typedef struct {
	Register_type Enable;   // bit  ���������� �� ���������� ���� ��
	Register_type Run;   		// bit  ������ �������� �������
	Register_type NSlave;     // int16 ����� ���������� � ���� ����������� �� � ������� �������
	Register_type Nsp;      // int8 ������ ������ �� ������. ���������� �������� �� ������ 
	Register_type IDsp; // int16 ������� ���������� ID
	Register_type SP[256 - 6]; // ������ �� ������. �������� 249 ���� // u8, u16, u32
} fb00105_IN_type;

typedef struct {
	Register_type PackNum;			// uint8 ����� � ������ ������� ���������� � ������� ���� � ������� �������
	Register_type Trig;					// bit   ���������� ���������
	Register_type Go;						// bit	 ���������� �����
} fb00105_VAR_type;

typedef struct {
	Register_type Exit; // bit �����. 1-��������� ����. ��(����� ����� ��� ����� �� ��������), 0-�� ���������, ���� ����� � �������
	Register_type Exception; // bit �����. 1-��������� ����. ��(����� ����� ��� ����� �� ��������), 0-�� ���������, ���� ����� � �������
	Register_type Ok;
} fb00105_OUT_type;

void fb00105_exec (void);		// - ������ ������� ����������

u32 fb00105_var_size(u8 type);
