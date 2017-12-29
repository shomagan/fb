/* "Чтение из I2C-модуля" */

typedef struct {
	Register_type Enable;           // bit
	Register_type Module_adress;    // int16
	Register_type Internal_adress;  // int16
	Register_type NumBytes;         // int16
} fb00031_IN_type;

typedef struct {
	Register_type ReadedOK;
	Register_type Out[250];
} fb00031_OUT_type;
