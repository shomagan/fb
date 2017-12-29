/* �� "��������� R7 "��������� DI �� ����" (��� 18)" */

typedef struct {
	Register_type CmdArch;		// bit      // ������� �� ���������
	Register_type NChan;		// uint8	// ����� ������
	Register_type AuthorArch;		// byte     // ��������� �������� ������
	Register_type SostDI;		// uint16   // ������� ��������� DI
	Register_type PrevSostDI;		// uint16   // ���������� ��������� DI
	Register_type DurationSostDI;		// uint32   // ����������������� ����������� ��������� DI
	Register_type EventTime;		// time     // ����� ������������� �������
} fb00083_IN_type;

typedef struct {
	Register_type Ok;		// bit
} fb00083_OUT_type;
