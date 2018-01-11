/* ФБ "MODBUS Master: Запись - функции 5/6/15/16" */
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
	Register_type In[256 - 9]; // максимум 248 байта
} fb00122_IN_type;


typedef struct {
	Register_type TimeOut;  //bit
	Register_type ER_Exception; //bit
	Register_type OK; //bit
  Register_type Status; //uint16
 	Register_type PackNum;			// uint8
  Register_type TimeOutCounter;    // uint16 in kernel takt
  Register_type IntervalTimer;  //int16
  Register_type RestartCounter;   //int16
} fb00122_OUT_type;
u32 fb00122_var_size(u8 type);
