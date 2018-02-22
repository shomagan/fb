/* "modem - add string to table for modbus" */
#include "../kernel.h"
#define WAS_ADDED BIT(0)
#define MAX_MODBUS_ADDRESS 100
#define INPUT_NUMBER_WITHOUT_MODBUS 13    //from enable to nodechanel5

typedef struct {
	Register_type Enable;          // bit
  Register_type ChanelFrom;       //uint8
  Register_type Chanelto;       //uint8
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
  Register_type ModbusAddress[MAX_MODBUS_ADDRESS];          // uint8
} fb00118_IN_type;

typedef struct {
	Register_type Table_Note[298];			// uint8
} fb00118_VAR_type;

typedef struct {
	Register_type Status;			        // uint16
  Register_type TableNoteNumm;			// uint16
} fb00118_OUT_type;
u32 fb00118_var_size(u8 type);
