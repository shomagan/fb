/* �� "���" */

typedef struct {    
	Register_type Input;	 		// float ��������� ��������
	Register_type dInput;	 		// float �������� � �������
} fb00100_IN_type;
typedef struct {
	Register_type prevTn0;			// float 
	Register_type InputOld;	 		// float 
} fb00100_VAR_type;
typedef struct {
	Register_type Output;	    	// float 
} fb00100_OUT_type;

void fb00100_exec();
u32 fb00100_var_size(u8 type);
