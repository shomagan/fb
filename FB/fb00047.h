/* �� "��������� R7 "����� ���" (��� 17, ������ 1)" */

typedef struct {
	Register_type CmdARX;      // bit
	Register_type OtvNum;      // int8  ����� ������ 
	Register_type Counter;     // int32 �������
	Register_type StartTime;   // int32 ����� ������ ������
	Register_type CntTime;     // int16 ������������ ������
} fb00047_IN_type;

typedef struct {
	Register_type Ok;
} fb00047_OUT_type;
