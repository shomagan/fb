/* "����������� I2C-������ �� ����" */

typedef struct {
	Register_type ModuleAddr;   // int8/16/32   // i2c-����� ������
} fb00039_IN_type;

typedef struct {
	Register_type Connected;    // bit          // ������� ����������� ������ �� ����
} fb00039_OUT_type;
u32 fb00039_var_size(u8 type);
