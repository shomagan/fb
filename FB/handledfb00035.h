/* "RTM64var Master" */

//#define LenBlok		       		64				//Длина блока данных в пакете
//#define	LenPak		       		10+2+LenBlok+2  //(78) 5адресов, Команда, пакет, CRC
//#define	FB_RTM_MaxLengthPak    	LenBlok+26		//(90) Длина пакета по AX c   0~...~0

typedef struct {
	Register_type Enable;          // bit
	Register_type CRC16_64;        // bit
	Register_type Module_Addr;     // int16
	Register_type Module_IntAddr;  // int16
  
	Register_type RTM1_Addr;       // int16
	Register_type RTM1_Retran;     // int8
	Register_type RTM2_Addr;       // int16
	Register_type RTM2_Retran;     // int8
	Register_type RTM3_Addr;       // int16
	Register_type RTM3_Retran;     // int8
	Register_type RTM4_Addr;       // int16
	Register_type RTM4_Retran;     // int8
  
	Register_type RTM_Command;     // int16
	Register_type LenBlockOut;      // int8
	Register_type TimeOut;         // int16
	Register_type Out[64];    // максимум 64 байта
} fb00035_IN_type;

typedef struct {
	Register_type PackNum;
} fb00035_VAR_type;

typedef struct {
	Register_type TimeOut;         // bit
	Register_type ER_Exception;    // bit
	Register_type OK;              // bit
	Register_type LenBlockIn;       // int8
	Register_type In[64];     // максимум 64 байта
} fb00035_OUT_type;
u32 fb00035_var_size(u8 type);
