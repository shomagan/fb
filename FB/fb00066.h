/* "��� (��������) v.2" */

typedef struct {
	Register_type Enable;       // bit    // Enable
	Register_type Hold;         // bit    // ��������� ������ �� �� ��������� ��������� ���
	Register_type GP_enabled;   // bit    // ������ �� ���������
	Register_type KodPSM;       // int8   // ��� ���
	Register_type OtvMask;      // int32  // ������ � ������
//------------------------------------------  
	Register_type GZU_OtvNum;   // int8   // ���-�� �������
	Register_type ForwardTime;  // int16  // ����� ������� ���� (���)
	Register_type ReverseTime;  // int16  // ����� ��������� ���� (���)
	Register_type StabTime;     // int16  // ����� ������������ (���)
	Register_type TryNum;       // int8   // ���-�� �������� ���������
	Register_type APV_interval; // int16  // �������� ����� ��������� ���
	Register_type APV_TryNum;   // int8   // ������� ���
//------------------------------------------  
	Register_type EndPeriod;    // bit    // ������ ������ �������
	Register_type CmdSwitchOtv; // bit    // ��� ������� ������
	Register_type CmdStopReset; // bit    // ��� ����� �����
	Register_type ManualOtvNum; // int8   // ����� ��� ������� ������
	Register_type ExtraOtvNum;  // int8   //������������  �����
//  Register_type CmdManual;    // bit    // ��� ������ �����
} fb00066_IN_type;

typedef struct {
	Register_type Timer1;       // int32
	Register_type Timer2;       // int32
	Register_type KodPSMOld;    // int8
	Register_type TryCount;     // int8
	Register_type APV_TryCount; // int8
	Register_type TempExtra;     // int8
} fb00066_VAR_type;

typedef struct {
	Register_type GP_ON;        // bit
	Register_type GP_OFF;       // bit
	Register_type Counting;     // bit
	Register_type EndPeriod;    // bit
	Register_type TekOtvod;     // int8
	Register_type GZUsost;      // int16
	Register_type ManualOtvNum; // int8   // ����� ��� ������� ������
	Register_type TimerOut;     // int16
	Register_type TimerUstOut;  // int16
} fb00066_OUT_type;

// �������� ����� �������� �� ��������� ���� ���
#define KluchDelay  15

// GZUsost
#define Enabled     (1<<0)  // ������ �� ���������
#define Holded      (1<<1)  // �� ����������
#define GP_En       (1<<2)  // ������ �� ���������
#define NeedPerevod (1<<3)  // ��������� ������� ������

#define Forward     (1<<4)  // ��� ������ ���
#define Reverse     (1<<5)  // ��� �������� ���
#define Stab        (1<<6)  // ��� ������������
#define Zamer       (1<<7)  // ��� �����
#define Stop        (1<<8)  // ����
#define FullStop    (1<<9)  // ������ ����

#define PSMbraked   (1<<10) // ������� ����� - ������������� ���
#define GPbraked    (1<<11) // ������� ����� - ������������� ��
#define TryCnt0     (1<<12) // ������� ����� - ��������� ������� "���������" ������������
#define Kluch       (1<<13) // ������ ������� ������ ������

#define Manual      (1<<14)  // ������ �����
#define Manual1Cnt  (1<<15)  // ��������� ������ ����� (1 ���), ����� �����������
