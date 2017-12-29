/*�� "���������" (������������ ����)*/

typedef struct {
	Register_type enable;	//bit 0- ��������� ������ ������ ������
	Register_type hihi;     //bit ������� ��� ��� 
	Register_type hi;       //bit ������� ��� �������� 
	Register_type lo;       //bit ������� ����
	Register_type main0;	//bit==1����� � - �������� bit0=����� � - ���������
	Register_type main1;	//bit==1����� � - �������� bit0=����� � - ���������
	Register_type main2;    //bit==1����� � - �������� bit0=����� � - ���������
	Register_type main3;    //bit==1����� � - �������� bit0=����� � - ���������
	Register_type auto0;	//bit1=����� � �������� � ������ ��� bit0=����� �� � �������� ��� ���� ������
	Register_type auto1;	//bit1=����� � �������� � ������ ��� bit0=����� �� � �������� ��� ���� ������
	Register_type auto2;    //bit1=����� � �������� � ������ ��� bit0=����� �� � �������� ��� ���� ������
	Register_type auto3;    //bit1=����� � �������� � ������ ��� bit0=����� �� � �������� ��� ���� ������
} fb00086_IN_type;

typedef struct {
	Register_type cmd0_ON;	//bit ���/���� ����� � (����������� ���������� �����, ��.����)
	Register_type cmd0_OFF;
	Register_type cmd1_ON;
	Register_type cmd1_OFF;
	Register_type cmd2_ON;
	Register_type cmd2_OFF;
	Register_type cmd3_ON;
	Register_type cmd3_OFF;
	Register_type State;
} fb00086_OUT_type;


