/* �� "��������� R7 "����� ��" (��� 17, ������ 2)" */

typedef struct {
	Register_type CmdARX;      // bit
	Register_type CntNum;      // int8  ����� ��������
	Register_type Counter;     // int32 �������
	Register_type StartTime;   // int32 ����� ������ ������
	Register_type CntTime;     // int16 ������������ ������
} fb00048_IN_type;

typedef struct {
	Register_type Ok;
} fb00048_OUT_type;
