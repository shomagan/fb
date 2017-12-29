/* ФБ "MODBUS Master: Запись - функции 5/6/15/16" */

typedef struct {
	Register_type Enable;          // bit
	Register_type IntervalRequest;     // int16
	Register_type Chanel;  // int16
	Register_type MODBUS_Addr;     // int8
	Register_type MODBUS_Func;     // int8
	Register_type RegAddr;         // int16
	Register_type RegNum;          // int16
	Register_type TimeOut;         // int16
	Register_type In[256 - 9]; // максимум 248 байта
} fb00034_IN_type;

typedef struct {
	Register_type PackNum;
} fb00034_VAR_type;

typedef struct {
	Register_type TimeOut;
	Register_type ER_Exception;
	Register_type OK;
} fb00034_OUT_type;
