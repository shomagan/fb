typedef struct {
	Register_type Dist;				// bit 1 - �������������, 0 - �������
	Register_type CmdOpen;			// bit ������� � 0 �� 1 - �������
	Register_type CmdClose;			// bit ������� � 0 �� 1 - �������
	Register_type CmdStop;			// bit ������� � 0 �� 1 - ����������
	Register_type Opened;			// bit �������
	Register_type Closed;			// bit �������
	Register_type Alarmed;			// bit ������ - �����
	Register_type Uon;				// bit ������� ����������
	Register_type VPH; 				// uint16 -����� ������� ����
} fb00080_IN_type;

typedef struct {
	Register_type SecTimer;     	// uint8 ������ ������� ������
	Register_type ImpulsTime;		// uint8 ������ ��������� ����������� �������
} fb00080_VAR_type;

typedef struct {
	Register_type OutOpen;			// bit ����� ���������� �������
	Register_type OutClose;			// bit ����� ���������� �������
	Register_type OutStop;			// bit ����� ���������� ����
	Register_type Position; 		// uint16 �������������� �������
	Register_type Sost; 			// uint16 ���������
	Register_type Timer; 			// uint16 �������� ������ ������� ���� ��������
} fb00080_OUT_type;

#define	s00080_DIST					(1<<0)		//������������� �����
#define	s00080_OPENED				(1<<1)		//�������
#define	s00080_CLOSED				(1<<2)		//�������
#define	s00080_AVARMUFTA			(1<<3)		//������ - �����
#define	s00080_AVARVPHOPEN			(1<<4)		//������ �� ��������� ��������
#define s00080_AVARVPHCLOSE			(1<<5)		//������ �� ��������� ��������
#define	s00080_OPENING				(1<<6)		//������������
#define	s00080_CLOSING				(1<<7)		//�����������
#define	s00080_UON					(1<<8)		//������� ����������
#define	s00080_RES1					(1<<9)		//������
#define	s00080_RES2					(1<<10)		//������
#define	s00080_RES3					(1<<11)		//������
#define	s00080_RES4					(1<<12)		//������
#define	s00080_RES5					(1<<13)		//������
#define	s00080_RES6					(1<<14)		//������
#define	s00080_RES7					(1<<15)		//������


#define s00080_IMPULSTIME			3			//����� ��������� ������������ ������� � ��������

void fb00080_exec(void);
