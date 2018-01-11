/* "Присутствие I2C-модуля на шине" */

typedef struct {
	Register_type ModuleAddr;   // int8/16/32   // i2c-адрес модуля
} fb00039_IN_type;

typedef struct {
	Register_type Connected;    // bit          // признак присутствия модуля на шине
} fb00039_OUT_type;
u32 fb00039_var_size(u8 type);
