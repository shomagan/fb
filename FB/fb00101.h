/* �� "������� ���������� ��������" */
typedef struct {
  Register_type Enable;        // bit //enable
  Register_type Avtomat;       //bit  1 - avtomat
  //Register_type Reverse;       //bit  //1 - ����������� ����������
  Register_type Revers;       //bit  //1 - ����������� ����������
  Register_type DisbalanceEnable;//bit  //1 - ��������� ��������� ���������� ������������� ��������� �������� � ��������� 
                                                  // ��������� ��������� ��������
  Register_type GistMore;      //float // �� ������� ������ ���� ������ � ���������
  Register_type GistLess;      //float // �� ������� ������ ���� ������ � ���������
  Register_type PositionInc;     //uint16// �� ������� �������� ������� ���� NeceseryParam(����������� ��������) ������ CurrParam(��������)
  Register_type PositionDec;     //uint16// �� ������� �������� ������� ���� NeceseryParam(����������� ��������) ������ CurrParam(��������)
  Register_type DisregardTime; //uint16// �������� ������� � ��� NeceseryParam CurrParam
  Register_type NeceseryPosition; // uint16 // 
  Register_type CurrPosition;     // uint16 // 
  Register_type MaxPosition;      // uint16 // 
  Register_type MinPosition;      // uint16 // 
  Register_type NeceseryParam;   // uint16/float // !!!��� � CurrParam ������ ���������
  Register_type CurrParam;        // uint16/float //!!!��� � NeceseryParam ������ ��������� 
} fb00101_IN_type;

typedef struct {
  Register_type KernelClk;
} fb00101_VAR_type;

typedef struct {
	Register_type WritePosition; // bit // !!!���������� ������ ������� ��������
                                      // 0 - ����������� � ����� ��� � MaxPosition MinPosition
	Register_type BigParam;      // bit //
	Register_type LowParam;      //  bit // 
	Register_type State;         //  uint32// 
  Register_type ReverseTime;   // uint16//�������� ������ �����������
	Register_type OutPosition;         // uint16 // 
} fb00101_OUT_type;
void fb00101_exec(void);
