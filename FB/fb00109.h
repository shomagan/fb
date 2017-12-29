/* "mdbtcp write function(5,6,15,16)" */
#include "../kernel.h"
#define MAX_PASS_PERFOMANCE 25

typedef struct {
	Register_type Enable;          // bit
  Register_type IP4;             // uint8
  Register_type IP3;             // uint8
  Register_type IP2;             // uint8
  Register_type IP1;             // uint8
  Register_type Port;             // uint16
  Register_type ConectionTimeOut; // uint16 in ms
  Register_type IntervalTime;     // uint16 in ms
	Register_type MODBUS_Addr;     // int8
	Register_type MODBUS_Func;     // int8
	Register_type RegAddr;         // int16
	Register_type RegNum;          // int16
  Register_type In[256 - 13]; // максимум 248 байта
} fb00109_IN_type;


typedef struct {
	Register_type Status;			// uint8
#define WORKING 0						//if this fb in work
#define CONNECTION_STATE 1	//if TCP connection was started
#define PASSED 2	          //if fb passed perfomance
#define TIMER_BLOCK 3	          //if fb passed perfomance
	Register_type ErrCount;   // uint16
  Register_type OkCount;    // uint16
  Register_type TimeOutCounter;    // uint16 in kernel takt
  Register_type IntervalTimer;     // uint16 in ms
  Register_type PassPerfomance;    // uint8
  Register_type PassPerfomanceCounter;    // uint8 
	Register_type OK;
} fb00109_OUT_type;
