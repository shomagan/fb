/*�� ������������� ������� ����������*/

typedef struct {    
	Register_type Enable;	 		//bit ������� �� �����������(����������)
	Register_type GUID;	 		  //uint16 ������� ���������� � ���� GUID ����� ������������
} fb00104_IN_type;
typedef struct {
	Register_type OK;	    	// bit ����������� ���� ����� �� � �� ����� �� ����� ������������ 
} fb00104_OUT_type;

void fb00104_exec();
u32 fb00104_var_size(u8 type);
