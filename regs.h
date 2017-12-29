#ifndef _REGS_H_
#define _REGS_H_
// ������� ���� � ���������
//==============================================================================
#define Options_RegNum            410
#define ArcR7_WindowRegNum        34
#define ConfigLoad_WindowRegNum   34
#define ProgramLoad_WindowRegNum  34
//==============================================================================

// ������ int16 ���������
//==============================================================================
#define OptionsStartRegAddr     0
#define OptionsEndRegAddr       Options_RegNum									// 410
#define ArcR7StartRegAddr       OptionsEndRegAddr                               // 410
#define ArcR7EndRegAddr         (ArcR7StartRegAddr + ArcR7_WindowRegNum)        // 444
#define ConfigStartRegAddr      ArcR7EndRegAddr									// 444
#define ConfigEndRegAddr        (ConfigStartRegAddr + ConfigLoad_WindowRegNum)	// 478
#define ProgramStartRegAddr     ConfigEndRegAddr								// 478
#define ProgramEndRegAddr       (ProgramStartRegAddr + ProgramLoad_WindowRegNum)	// 512
#define RAMStartRegAddr         (OWN_VARIABLE_BLOK_SIZE>>1)								// 756
#define RAMEndRegAddr           (RAMStartRegAddr + (cstMaxFB_RAMsize>>1))		// 16896 
#define FreeStartRegAddr        RAMEndRegAddr									// 16896
//==============================================================================


//==============================================================================
// ������ ��������� ����������� ��� ������������� ��� ��������� ��������� � ����������
//==============================================================================
#define regMyAdrRTM64           	0   // 1 rw ����� ���64
#define regMyAdrMODBUS          	1   // 1 rw ����� �� ModBUS
#define regMyPortMODBUS         	2   // 1 rw
#define regMyIpAdr              	3   // 4 rw
#define regMySubNetMask         	7   // 4 rw
#define regMyRoutIpAdr          	11  // 4 rw
#define regMyMAC                	15  // 6 rw

#define regSystemTime				21  // 3 rw ��������� �����
#define regCmdRESET             	24  // 1 -w ������� ������������ �����������
#define regCmdFBUpd					25  // 1 -w ������� ��������� �������� ����� ������������

#define regCmdFB		        	27  // 1 -w ������� ����������/���������� ���������� ������������
#define regCmdPrgUpd				26	// 1 -w ������� ��������� �������� ����� ��������
#define regCmdCRC		 	        28  // 1 -w ������� ������� CRC ������ � ������� �����������
#define regFileCRC		            29  // 1 r- CRC �����, ������������ ����� ������ ������� ��������

#define regBaud_COM0             	30  // 1 rw ��������� COM0
#define regBaud_COM1				31	// 1 rw ��������� COM1
#define regBaud_COMIntBUS			32	// 1 rw ��������� COM2
#define regBaud_COMext				33	// 1 rw ��������� COMext

// 34...61 Reserved	

#define regCntTOut					62	// 2 r- ����� ����������
#define regCntDOut					64	// 2 r- ���� ����������

// 66...67 ���������

#define regFreeStackSize			68 // 1 r- ������ �������� ����� � ������
#define regRNSets					69 // 1 rw ��������� �������� �����

#define regFreq16					70	// 2 �- ������� �� ����� 16
#define regFreq17					72	// 2 r- ������� �� ����� 17
#define regCntDI					74	// �� 2 18 ��� r- 18 32-� ��������� ���������
	// 74...109

#define regSostDO					110	// 1 rw ��������� DO ������ � ���� ������� �������� ��������� �� ������� DO
#define regADCChan					111 // �� 1 4 ���� r- 4 ������ ADC
	// 111...114

#define regTemperatureSD			115	// 1 r- ����������� SD ����� �� ������
#define regOldDI					116	// 2 r- ���������� ��������� DI
#define regSostDI					118	// 2 r- ������� ��������� DI
#define regDIFilter					120 // 1 rw ������ ������ ������ DI - ��� ���������� �������� �� ������� ������
// 121..126 ������

#define regKernelFlags				127 // 1 r- ����� ���������� ������������
// ���������� ����������� ��
#define regKernelFullTime       	128 // 1
#define regKernelClearTime      	129 // 1
#define regKernelLoadVarsTime   	130 // 1
#define regKernelSaveVarsTime   	131 // 1
// ���������� ��������� �������
#define regIdlePaketsNum        	132 // 1
#define regTimeOutsNum          	133 // 1
#define regBrakePaketsNum       	134 // 1
// ������� ������ �����������
#define regMaxCfgSize           	135 // 1
#define regMaxPrgSize           	136 // 1
#define regMaxFB_RAMsize        	137 // 1
#define regSaveFB_RAMsize       	138 // 1
#define regArcR7_RecNum         	139 // 1
#define regregR7_Index             	140 // 2
// ��������� ������� ������������
#define regCfgSize              	142 // 1
#define regCfgTWICommSize       	143 // 1
#define regFBCfgSize            	159 // 1
#define regFBkernelRate         	160 // 1
// ��������� ����������
#define regResetCnt             	146 // 1
#define regResetCase            	147 // 1
#define regVersChip             	148 // 1
#define regBootFlags            	149 // 1
// ����� ������
#define regCfgUpdateErrorFlags  	150 // 1 ����� ������ ��� ���������� ����� ������������
#define regKernelErrorFlags     	151 // 1 ����� ������ ��� ���������� ������������
// ������
#define regI2CrestartCnt        	152 // 1 ���������� ������������ ���� I2C
#define regGMSKFFSKSet				155 // ��������� ��������� �������� �����
#define regArcNum2Rd				410	// 2

#define regMapTable 					294


#define BootFlags_UserMode            (1<<0)  // ���������������� �����

//------------------------------------------------------------------------------

// ���� ������ // Exceptions
//------------------------------------------------------------------------------
#define ILLEGAL_FUNCTION        0x01
#define ILLEGAL_DATA_ADDRESS    0x02
#define ILLEGAL_DATA_VALUE      0x03
#define SLAVE_DEVICE_FAILURE    0x04
#define ACKNOWLEDGE             0x05
#define SLAVE_DEVICE_BUSY       0x06
#define NEGATIVE_ACKNOWLEDGE    0x07
#define MEMORY_PARITY_ERROR     0x08
//==============================================================================

// ������ �� ��������� ������ ��������� ��������
#define pswCmdRESET             5300    // ������ �� ������� ������ �����������
#define pswCmdCfgLoadingFinish  5400    // ������ �� ������� ��������� �������� ����� ������������
#define pswCmdCfgCopy2Buff      5401    // ������ �� ������� ����������� ������� ������������ � �����
#define pswCmdModeBOOT          5500    // ������ �� ������� ��������� �������� ����� �������� � ������� ����������� � BOOT
#define pswCmdModeUSER          5501    // ������ �� ������� �������� ����������� � USER
#define pswCmdModeBOOTandUPD    5502    // ������ �� ������� �������� ����������� � BOOT � ����������� ����������� �� �����������
#define pswCmdCfgDisable        5600    // ������ �� ������� ���������� ���������� ������������
#define pswCmdCfgEnable         5601    // ������ �� ������� ���������� ���������� ������������
#define pswCmdCfgSaveRAM        5602    // ������ �� ������� ��������������� ���������� ����������� ����� ���
#define pswCmdCalcCfgFileCRC    5700    // ������ �� ������� ������� CRC ����� ������������
#define pswCmdCalcPrgFileCRC    5701    // ������ �� ������� ������� CRC ����� ��������

typedef union __sEventFlags {
  struct {
		u8 Bit00                ; // 0 ���� ���������� ���������� ������������
		u8 Bit01                ; // 1
		u8 Bit02                ; // 2
		u8 Bit03                ; // 3
		u8 Bit04                ; // 4 ���������� ��������� CRC ������������
		u8 Bit05                ; // 5 ���������� ���������� �������� ���� ������������ �� ������
		u8 Bit06                ; // 6 
		u8 Need2Go2Boot         ; // 7 ���������� ������������� � BOOT
		u8 Need2UpdateSoftware  ; // 8 ���������� ���������� ���������� ��
		u8 Bit09                ; // 9 ���������� ���������� CRC ����� � ������ ������������
		u8 Need2CalcPrgCRC      ; // 10 ���������� ���������� CRC ����� � ������ ��������
		u8 Bit11                ; // 11
		u8 Bit12                ; // 12
		u8 Bit13		            ; // 13
		u8 Need2SaveFBRAM       ; // 14 ���������� ��������� �� flash ����������� ����� ���
		u8 Bit15                ; // 15 ������ ������� ���������� ������������
		u8 Bit16                ; // 16 ������ ���������� ������������
		u8 DateTimeSync         ; // 17 ����� ����������������
		u8 Need2ResetAfterCnt   ; // 18 ���������� ������������� ���������� ����� �������� ������
		u8 Need2Reset           ; // 19 ���������� ������������� ����������
		u8 Bit20                ; // 20
		u8 Bit21                ; // 21
		u8 Bit22                ; // 22
		u8 Bit23                ; // 23
		u8 Bit24                ; // 24
		u8 Bit25                ; // 25
		u8 Bit26                ; // 26
		u8 Bit37                ; // 27
		u8 Bit28                ; // 28
		u8 Bit29                ; // 29
		u8 Bit30                ; // 30
		u8 Bit31                ; // 31
	}  Bit;
	vu32 Register;
} sEventFlags; //����������� ���
extern sEventFlags EventFlags;

typedef union {
   struct {
		unsigned NoCfgFile            ; // ����������� ���� ������������
		unsigned BadCfgFileCRC        ; // ������������ CR� ����� ������������
		unsigned SmallCfgFile         ; // ������� ��������� ���� ������������
		unsigned BigCfgFile           ; // ������� ������� ���� ������������
		unsigned BadCfgFileLengths    ; // ������������ ����� ������ ����� ������������
	} Bit;
	vu32 Register;
} sCfgUpdateErrorFlags;


typedef  union {
   struct{
		unsigned NoCfgFile            ; // ����������� ���� ������������
		unsigned BadCfgFileCRC        ; // ������������ CR� ����� ������������
		unsigned BadCfgFileLengths    ; // ������������ ����� ������ ����� ������������
		unsigned BadCodeFB            ; // � ����� ������������ ������������ ���������������� ���� ��
		unsigned BadRegAddr           ; // � ����� ������������ ������������ ������ � ������� �� ��������� ��� ��
	} Bit;
	vu32 Register;
} sKernelErrorFlags;


#endif
