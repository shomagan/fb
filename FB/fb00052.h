/* �� "��������� R7 "�������� ������ �������" (��� 17, ������ 7)" */

typedef struct {
  Register_type CmdARX;     // bit
  Register_type EventID;    // int8   ��� �������
  Register_type DD0;        // int8   ���� 0 �������� �������
  Register_type DD1;        // int8   ���� 1 �������� �������
  Register_type DD2;        // int8   ���� 2 �������� �������
  Register_type DD3;        // int8   ���� 3 �������� �������
} fb00052_IN_type;

typedef struct {
  Register_type Ok;         // bit  
} fb00052_OUT_type;
