/* ФБ "MODBUS Master: Запись - функции 5/6/15/16" */
#include "../kernel.h"

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
  Register_type GuidAddress1;          // uint16  
  Register_type GuidSize1;          // uint8  
  Register_type GuidAddress2;          // uint16  
  Register_type GuidSize2;          // uint8  
  Register_type GuidAddress3;          // uint16  
  Register_type GuidSize3;          // uint8  
  Register_type GuidAddress4;          // uint16  
  Register_type GuidSize4;          // uint8  
  Register_type GuidAddress5;          // uint16  
  Register_type GuidSize5;          // uint8  
  Register_type In[256 - 24];
} fb00124_IN_type;


typedef struct {
	Register_type TimeOut;  //bit
	Register_type ER_Exception; //bit
	Register_type OK; //bit
  Register_type Status; //uint16
 	Register_type PackNum;			// uint8
  Register_type PacketID;			    // uint8
  Register_type TimeOutCounter;    // uint16 in kernel takt
  Register_type IntervalTimer;  //int16
  Register_type RestartCounter;   //int16
} fb00124_OUT_type;
u32 fb00124_var_size(u8 type);
