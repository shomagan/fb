/*������ DO*/

typedef struct {
	Register_type Nbit;   // int8  ����� ���� �� ����� � ������
	Register_type Bit; // int16 ����� (1-16) ���
	Register_type IN[256-2];			// bit ��������
} fb00107_IN_type;

typedef struct {
	Register_type Error;			// bit ������
	Register_type OUT[256-1];			// bit ��������
} fb00107_OUT_type;


void fb00107_exec (void);		// - ������ ������� ����������

u32 fb00107_var_size(u8 type);
