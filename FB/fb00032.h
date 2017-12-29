/* ФБ "Запись в I2C-модуль"*/

#define MaxWrBufferSize       256  // Максимальный объём буфера записи в байтах

typedef struct {
	Register_type Cmd_write;        // bit
	Register_type Module_adress;    // int16
	Register_type Internal_adress;  // int16
	Register_type NumBytes;         // int16
	Register_type In[250];
} fb00032_IN_type;
