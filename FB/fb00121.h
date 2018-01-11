/* "MODBUS_RTU Master: Чтение - функции 1/2/3/4" */
#include "../kernel.h"

typedef struct {
	Register_type Enable;           // bit
	Register_type IntervalRequest;  // int16 in ms 
	Register_type Chanel;           // int16
	Register_type MODBUS_Addr;      // int8
	Register_type MODBUS_Func;      // int8
	Register_type RegAddr;          // int16
	Register_type RegNum;           // int16
	Register_type TimeOut;          // int16
} fb00121_IN_type;


typedef struct {
	Register_type TimeOut;  //bit
	Register_type ER_Exception; //bit
	Register_type OK; //bit
  Register_type Status;           //uint16
	Register_type PackNum;			    // uint8
  Register_type TimeOutCounter;   // uint16 in kernel takt
  Register_type IntervalTimer;    //int16
  Register_type RestartCounter;   //int16
  Register_type Out[256 - 3]; // максимум 251 байта
} fb00121_OUT_type;
u32 fb00121_var_size(u8 type);
