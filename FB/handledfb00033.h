/* "MODBUS_RTU Master: Чтение - функции 1/2/3/4" */
#include "../kernel.h"

typedef struct {
	Register_type Enable;          // bit
	Register_type IntervalRequest;     // int16
	Register_type Chanel;  // int16
	Register_type MODBUS_Addr;     // int8
	Register_type MODBUS_Func;     // int8
	Register_type RegAddr;         // int16
	Register_type RegNum;          // int16
	Register_type TimeOut;         // int16
} fb00033_IN_type;

typedef struct {
	Register_type PackNum;			// uint8
} fb00033_VAR_type;

typedef struct {
	Register_type TimeOut;
	Register_type ER_Exception;
	Register_type OK;
	Register_type Out[256 - 3]; // максимум 251 байта
} fb00033_OUT_type;
u32 fb00033_var_size(u8 type);
