/* �� "����������� (�������-���������)" */
                               
typedef struct {
	//Register_type Enable;			//- bit - ���������� �������������
	Register_type CntNum;			//- uint8 - ����� �������� � �����
	Register_type Period;			//- uint16 - ������������� �������������
	Register_type CounterIn;	//- uint32/float - ��������������� ��������
  Register_type CounterHour;	//- uint8/float - ��������������� ��������
} fb00093_IN_type;

typedef struct {
	Register_type OK;						//- bit - �� 1 ���� ����� ������������� (��� ���� CounterOut ������ ��)
	Register_type CounterOut;		//- uint16/32/float - ������� �� ������� �������� (��)
	Register_type OldCounterIn;	//- uint32 - �������� ����� � ������� ����
	Register_type StartTime;		//- time - ����� ������ ������ (UnixTime)
	//������� ��� ��������� ������ � ����������� ������� ������
} fb00093_OUT_type;

void fb00093_exec();
