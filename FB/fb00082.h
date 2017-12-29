/* �� "��� � ��������� ������������� ����������� " */
typedef struct {    
	Register_type Enable;				// bit 0 - ������, 1 - ��������������
	Register_type ReverseU;			// bit 1- ����������� ����������
	Register_type Rezet;			// bit 1- ����� ����������� ����������
	Register_type RequireValue; 		// float ������� �������������
  Register_type CurrentValue;			// float ������������ ��������
	Register_type kP;		 		// float ����������� ������������������
	Register_type kI;		  		// float ����������� ������� ��������������
	Register_type kD;				// float ����������� ������� ��������������
	Register_type Position;	    	// float - ����������� ��������� ���������� � ���������
	Register_type GistTube;	 		// float ���� ������������������ � �������� ����������� ���������
	Register_type DelayTime;	 	// uint32 ����� �������� ����������� � ������
} fb00082_IN_type;

typedef struct {
	Register_type prevEi;		// float - ����������� ������ �����������
	Register_type prevEi1;			// float - ���������� �������� ������ �������������
	Register_type prevUo;			// float - ����������� ����������� �� ������������ �����
	Register_type EnableOld;			// bit - ��� ������������ ������� ����� ���������
	Register_type NumberTick;			// uint32 - ���������� ������ ����� ���������,��� ��������� ������
} fb00082_VAR_type;

typedef struct {
	Register_type Error;	     	// bit ��������� ������ ������� ����������
	Register_type Output;	    	// float - ����������� ��������� ���������� � ���������
	Register_type Test;				// float
} fb00082_OUT_type;

void fb00082_exec(void);

