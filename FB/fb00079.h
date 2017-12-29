/* �� "����� ��� ���" */

typedef struct {
	Register_type Dist_mode;			//bit			1 - ������������� ����� 0 - ������� �����
	Register_type Cmd_ON;				//bit			������� �������� (���������� ���� ���������� 1 ���� ���������� ������������)
	Register_type Cmd_OFF;				//bit			������� ��������� (���������� ���� ���������� 1 ���� ���������� ������������)
	Register_type Actuator;				//bit			��������� ��������� 1 - ������� 0 - ���������
	Register_type Alarm;				//bit			������
	Register_type Block;				//bit			����������
	Register_type ResetAlarm;			//bit			����� ������(���������� ���� ���������� 1 ���� ���������� ������������)
	Register_type ImpulsONOFFTime;		//uint8			����� � ��� � ������� �������� ��������� ����� ���������� �� ��������� ��
	Register_type ActuatorTime;			//uint32		����� � ��� �������� ��������� ��������� ���������
	Register_type ActuatorRestart;		//uint16		���������� ������� �������� ��������� ��������� ���������
	Register_type TimeNonStop;			//uint32		����� ����� �� � ��� (� ������� �������� �� ����������� �� ���������� �� ����� �����)
	Register_type APV_TryNum;			//uint16		���������� ������� ���
	Register_type APV_Interval;			//uint32		����� ����� ��������� ���
} fb00079_IN_type;

typedef struct {
	Register_type SecTimer;				//uint8			���������� ������� ��� ������� ������
	Register_type CntReinitAPV;			//uint32		���������� ������� ����������������� ���
} fb00079_VAR_type;

typedef struct {
	Register_type Control_ON;			//bit			����� �� ��������� ��������� ��
	Register_type Control_OFF;			//bit			����� �� ���������� ��������� ��
	Register_type stUprav;				//bit			�������, ��� �� ������������ ����������� �������
	Register_type CntActTime;			//uint32		������� ������� � ��� �������� ��������� ���������
	Register_type CntActRestart;		//uint16		������� ���������� ������� �������� ��������� ���������
	Register_type CntNonStop;			//uint32		������� ������ � ��� ������� ����� �� (�������� �������� ����� �������� ��������� ���������)
	Register_type APV_TryCnt;			//uint16		������� ������� ���
	Register_type APV_Timer;			//uint32		������� ������� � ��� ����� ��������� ���
	Register_type CntImpONOFF;			//uint8			������� ������� � ��� ������������ ����������� �� ���������
	Register_type State;				//uint32		������� ��������� ��������� ������ ����� � ��� (����������� ����)
} fb00079_OUT_type;

//--------------- ��������� ��������� ������ ����� � ��� ------------------
#define s00079_Dist				(1<<0)		//���� �������������� ������
#define s00079_Actuator			(1<<1)		//���� ���������� ���������
#define s00079_Block			(1<<2)		//������� ������� ����������
#define s00079_Alarm			(1<<3)		//������� ������� ������

#define s00079_APVon			(1<<4)		//���� ����������� ��� �� ������� �� ���
#define s00079_flAlarm			(1<<5)		//���� ������� ������, ������������ �� ����� ����� ������
#define s00079_flBlock			(1<<6)		//���� ������� ����������
#define s00079_WaitActuator		(1<<7)		//����� ��������� �������� ���������

#define s00079_ExpectActuator	(1<<8)		//��� ������ ��������� �������� ��������� ���������� �������� ��������� ��������� 1-������� 0-���������
#define s00079_WaitBlock		(1<<9)		//�������� ������������� ���������� �� ����� �����
#define s00079_WaitAPV			(1<<10)		//�������� ��������� ����� ��������� ���
#define s00079_APV_TryCnt_Null	(1<<11)		//���� ��� ��������� ������� ���

#define s00079_Need_ON			(1<<12)		//���������� ��������
#define s00079_Need_OFF			(1<<13)		//���������� ���������
#define s00079_ActuatorFail_OFF	(1<<14)		//�� ��������� ��������� ��� ����������
#define s00079_ActuatorFail_ON	(1<<15)		//�� ��������� ��������� ��� ���������

#define s00079_ReinitAPV		(1<<16)		//�������� ������������� ��� ����� ���������� ��������������� ������� ����� ������
											//�.�. ���� �� ���������� �� ������� ���, �� ���� ����� ������� ��� ������� � ��������� ��������
#define s00079_WaitImpONOFF		(1<<17)		//���� �������� �������� ��������� ��� ����������
#define s00079_WaitImpSTOP		(1<<18)		//���� ��������������� �������� ���������� ����� ���������� ��������� (�� ��������� ��������� �� ���������)

//------------------ ����� ������� ---------------------------
#define s00079_StartMask1		(s00079_Dist | s00079_Need_ON)	//1-�� ����� ������� ��� ������� ����� ��������� �����
#define s00079_StartMask2		(s00079_Dist | s00079_Block | s00079_Need_ON)	//2-�� ����� ������� ��� ������� ����� ��������� �����
#define s00079_BlockMask		(s00079_Block | s00079_Actuator | s00079_Dist)	//����� ������� ��� ������� ����������� ����������
#define s00079_UpravMask		(s00079_APVon | s00079_Alarm | s00079_Block | s00079_Actuator | s00079_Dist)	//����� ������� ��� ������� ����� ������������ ������� ��������� � ����������
#define s00079_APVMask1ON		(s00079_flAlarm | s00079_APVon | s00079_Dist)
#define s00079_APVMask2ON		(s00079_ReinitAPV | s00079_flAlarm | s00079_APVon | s00079_Dist)
#define s00079_APVMask1OFF		~(s00079_APVMask1ON)
#define s00079_APVMask2OFF		~(s00079_APVMask2ON)

void fb00079_exec(void);
