/* �� "������ � I2C-������"*/

#define MaxWrBufferSize       256  // ������������ ����� ������ ������ � ������

typedef struct {
	Register_type Cmd_write;        // bit
	Register_type Module_adress;    // int16
	Register_type Internal_adress;  // int16
	Register_type NumBytes;         // int16
	Register_type In[250];
} fb00032_IN_type;
