/* "MODBUS_RTU Master: Чтение - функции 1/2/3/4" */
#include "../kernel.h"
#define MAX_GUID_ADDRESS 16
typedef struct {
	Register_type Enable;           // bit
	Register_type IntervalRequest;  // int16 in ms 
  Register_type TimeOut;          // int16
	Register_type Chanel;           // int16
  Register_type NodeAddress1;     //uin16
  Register_type NodeChanel1;     //uin8
  Register_type NodeAddress2;     //uin16
  Register_type NodeChanel2;     //uin8
  Register_type NodeAddress3;     //uin16
  Register_type NodeChanel3;     //uin8
  Register_type NodeAddress4;     //uin16
  Register_type NodeChanel4;     //uin8
  Register_type NodeAddress5;     //uin16
  Register_type NodeChanel5;     //uin8
  Register_type GuidAddress[MAX_GUID_ADDRESS];          // uint16  
} fb00123_IN_type;


typedef struct {
	Register_type TimeOut;  //bit
	Register_type ER_Exception; //bit
	Register_type OK; //bit
  Register_type Status;           //uint16
	Register_type PackNum;			    // uint8
  Register_type PacketID;			    // uint8
  Register_type TimeOutCounter;   // uint16 in kernel takt
  Register_type IntervalTimer;    //int16
  Register_type RestartCounter;   //int16
  Register_type Out[256 - 3]; // максимум 251 байта
} fb00123_OUT_type;
u32 fb00123_var_size(u8 type);
