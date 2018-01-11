/* �� "������� ��" (������������ ����) */
                               
typedef struct {
	Register_type Enable;		//-1 bit 		- ���������� ������
	Register_type CounterDI;	//-2 uint32		- ������� ����
	Register_type UNIXTime;		//-3 time		- ��������� ����� � ������� UNIX
	Register_type IntervalCNT;	//-4 uint16		- �������� � ��� ������������ ������������ ���������
	Register_type AvarRashod;	//-5 uint32		- ������� ���������� �������
	Register_type EnaPeretok;	//-6 bit			- ��������� ��������
	Register_type PeretokDI;	//-7 bit			- ��� ����������� ������������� ��������� (��������� ������, � ���� ����)
	Register_type EnaNullNull;	//-8 bit			- ��� ������������ � 00:00
	Register_type Ena2Hours;	//-9 bit			- �����������
} fb00091_IN_type;

typedef struct {
	Register_type EnaOld;			//-1 bit		- ���������� ������, ���������� ��������
	Register_type CounterDIOld;		//-2 uint32	- ������� ����, ���������� ��������
	Register_type CounterMinOld;	//-3 uint32	- ������ �������� ��������� ��������
	Register_type CntTicksSec;		//-4 uint8	- ������� �������� ������������ ��� ����������� ������
	Register_type CntSeconds;		//-5 uint8	- ������� ������
	Register_type CntMinutes;		//-6 uint16	- ������� ��������� ����� ��� ������������
	Register_type TimeBeg;			//-7 time	- ����� ������ �������� ������
} fb00091_VAR_type;

typedef struct {
	Register_type MinCnt;			//-1 uint32	- �������� �������
	Register_type MinCntDiff;		//-2 uint32	- ��������� ��������� ��������
	Register_type CNTInvT;			//-3 uint32	- ������� �� ������� ��������
	Register_type CNTInvP;			//-4 uint32	- ������� �� ������� ��������
	Register_type CNTIntegrTS;		//-5 uint32	- ������� ������������ �� ������� �����
	Register_type CNTIntegrPS;		//-6 uint32	- ������� ������������ �� ������� �����
	Register_type CNTInvTif;		//-7 uint32	- ������� �� ������� �������� �������
	Register_type CNTInvPif;		//-8 uint32	- ������� �� ������� �������� �� �������
	Register_type flAvarRash;		//-9 bit	- ���� ���������� �������
	Register_type ArhInvEna;		//-10 bit		- ����, ��� ������� ������������ �������� ���� ������������
	Register_type ArhInvDuration;	//-11 uint16	- ��� ������, ������������ ������
	Register_type ArhInvTimeBeg;	//-12 time		- ��� ������, ����� ������ ������
	Register_type ArhCNTInvT;		//-13 uint32	- ��� ������, ������� �� ������� ��������
	Register_type ArhInvPeretok;	//-14 bit		- ����, ��� ������� �������� �� ������������ ��������� ���� ������������
	Register_type ArhCNTInvTif;		//-15 uint32	- ��� ������, ������� ��������� �� ������� ��������
} fb00091_OUT_type;
u32 fb00091_var_size(u8 type);
