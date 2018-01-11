
#ifndef _KERNEL_H
#define _KERNEL_H
typedef signed long s64;
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;
typedef volatile signed int vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;
typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef const unsigned int uc32;
typedef const unsigned short uc16;
typedef const unsigned char uc8;
typedef volatile unsigned int vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;
typedef volatile unsigned int const vuc32;
typedef volatile unsigned short const vuc16;
typedef volatile unsigned char const vuc8;
typedef double	Flo64;    // Double precision floating point
typedef double	* pFlo64;
typedef float	Flo32;    // Single precision floating point
typedef float	* pFlo32;
typedef signed long long Int64S;   // Signed 64 bit quantity
typedef signed long long  * pInt64S;
typedef unsigned long long Int64U;   // Unsigned 64 bit quantity
typedef unsigned long long  * pInt64U;
typedef signed int Int32S;   // Signed 32 bit quantity
typedef signed int * pInt32S;
typedef unsigned int Int32U;   // Unsigned 32 bit quantity
typedef unsigned int * pInt32U;
typedef signed short Int16S;   // Signed 16 bit quantity
typedef signed short * pInt16S;
typedef unsigned short Int16U;   // Unsigned 16 bit quantity
typedef unsigned short * pInt16U;
typedef signed char Int8S;    // Signed 8 bit quantity
typedef signed char * pInt8S;
typedef unsigned char Int8U;    // Unsigned 8 bit quantity
typedef unsigned char * pInt8U;
typedef unsigned char Boolean;  // Boolean
typedef unsigned char * pBoolean;
#define BIT(x) (1<<x)
#define R7_BodySize 64
#define MasLenRTM64Block 64
#define Channels 9
#define MaxPacketLen 256

#define MEGA12
#define cstMaxCfgSize	65024u		// ������������ ������ ����� ������������.(������ ���� ������ 256)
#define cstMaxFB_RAMsize		(1512 + 32768ul)		// ������ ������� ������ ���������� ��.(������ ���� ������ 256)
#define cstKERNEL_RAM_SIZE		32768ul		// ������ ������� ������ ���������� ��.(������ ���� ������ 256)
#define cstSavedFB_RAMSize		8192ul		// ����������� ����� �� cstMaxFB_RAMsize(������ ���� ������ 256)
#define RAM_SavedRAM_StartAddr	(cstMaxFB_RAMsize - cstSavedFB_RAMSize)		// ��������� ����� ����������� ���������� FB
#define CONFIG_START_ADRES 0x08010000   //����� ������ ������������ �� ����� ����������� ������ ��� ������
		//� ��������� ����� (�� 8�) - ��������, ��������������� ����� �������
#define cstFBInputsNum	256u		// ������������ ���-�� ������ ��� 1 ��.
#define cstFBVarsNum		512u		// ������������ ���-�� ���������� ���������� ��� 1 ��.
#define cstFBOutputsNum		256u		// ������������ ���-�� ������� ��� 1 ��.
// ����� ��� ����������� ���� Type:
#define RegTypeMask	0x03
#define IsArrayMask	0x04
#define DataTypeMask	0xE0
// ��� �������� (�� ����� RegType)
#define KodConst	0x00
#define KodInput	0x01
#define KodOutput	0x02
#define KodVariable	0x03
// ���� ����� ������ (�� ����� TypeMask)
#define KodBit	0x00
#define KodInt8	0x20
#define KodInt16	0x40
#define KodInt32	0x60
#define KodFloat32	0x80
#define KodTime32	0xA0
#ifndef _MSC_VER
  #define _MSC_VER 1
#endif
#ifdef _MSC_VER
    #define PACKED_STRUCT(name) \
    __pragma(pack(push, 1)) struct name __pragma(pack(pop))
#elif defined(__GNUC__)
    #define PACKED_STRUCT(name) struct __attribute__((packed)) name
#endif
#pragma pack(push)
#pragma pack(1)
typedef union DataTypes_union{
    u8 bit:1;
    u8 uint8;
    u16 uint16;
    u32 uint32;
    Flo32 float32;
    u8 arbytes[4];
} _DataTypes;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct{
    u8 Type;
    _DataTypes Data;
} Register_type;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef  union __sKernelEventFlags {
    struct {
        u8 EnableFB             ; // 0 ���� ���������� ���������� ������������
        u8 TimePermission       ; // 1 ������ ����� ��������� ������������,���������� �� ��������� �� �������,�� ������� ���������������� �������
        u8 Perfoming            ; // 2 ������������ ��� ���������,������������ � ������ ����� � �� �����
        u8 Bit03                ; // 3
        u8 Need2CheckConfCRC    ; // 4 ���������� ��������� CRC ������������
        u8 Need2UpdateCfg       ; // 5 ���������� ���������� �������� ���� ������������ �� ������
        u8 Bit06                ; // 6
        u8 Bit07                ; // 7 ���������� ������������� � BOOT
        u8 Need2UpdateSoftware  ; // 8 ���������� ���������� ���������� ��
        u8 Need2CalcCfgCRC      ; // 9 ���������� ���������� CRC ����� � ������ ������������
        u8 Need2CalcPrgCRC      ; // 10 ���������� ���������� CRC ����� � ������ ��������
        u8 Bit11                ; // 11
        u8 Bit12                ; // 12
        u8 Bit13                ; // 13
        u8 Bit14                ; // 14 ���������� ��������� �� flash ����������� ����� ���
        u8 CfgFirstSec          ; // 15 ������ ������� ���������� ������������
        u8 CfgFirstExec         ; // 16 ������ ���������� ������������
        u8 ErrorCRC             ; // 17 ����� ����������������
        u8 CheckPassed          ; // 18 ���������� ������������� ���������� ����� �������� ������
        u8 Bit19                ; // 19 ���������� ������������� ����������
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
} sKernelEventFlags; //����������� ���
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct {
  u16 CfgSize;          //
  u16 CfgTWICommSize;   //
  u16 FBCfgSize;        //
  u16 FBkernelRate;     //������ � �������
  Int64U StartTick; //����� ������ ���������� ������������(���� �� 100 ���)
  Int64U StopTick;//����� ����� ���������� ������������(���� �� 100 ���)
  u32 WorkingTime;
  u32 CfgStartTime;
  u8* pCFG;     //��������� �� ������� ����� ���������� ������������
  u8* pStartCFG;//��������� �� ������ ������������
  u8* pNextStartCFG;//pointer to next config
  sKernelEventFlags EventFlags;
}KernelInfo_t;
#pragma pack(pop)
#define MAX_KERNEL_NUMBER 10
#define KERNEL_ITTERAPT_FREQ 1000
/*format heada for config
 *
 */
#pragma pack(push)
#pragma pack(1)
typedef struct ConfigHead{
    u32 Size;
  	u32 Version;
  	u32 TimeLastUpdate;
  	u8  Avtor[16];
  	u8 SectionNumber;
}ConfigHead_t;
#pragma pack(pop)


/*format heada for section
 *
 */
#pragma pack(push)
#pragma pack(1)
typedef struct SectionHead{
	u32 Pozition;
	u8  Type;
	u32 LengthSection;
	u8  ServiceFlag[3];
	u32 Rezerv;
}SectionHead_t;
#pragma pack(pop)
typedef void (*FB_Func)(void);
extern u8 *pCFG;
extern u8 *pCFG_temp;
extern vu16 FB_N_In, FB_N_Vars, FB_N_Out;
extern vu32 CfgStartTime;
extern u8 *pStartCfg;
extern vu8 CntCfg1SecExec;
extern vu8 CntSaveFBRam;

#define BINAR_CONFIG_TYPE 0
#define SP_CONFIG_TYPE 1
#define VISUAL_CONFIG_TYPE 2
extern KernelInfo_t KernelInfo;
extern Register_type FBInputs[];
extern Register_type FBVars[];
extern Register_type FBOutputs[];
extern vu8 CntSaveFBRam;
extern u32 BateryMemFB32[512];
u8 GetNeed2SyncState(void);
u8 SetSystemOption(u16 address,u16 value);
u8 GetSystemOption (u16 address, u16* TempValue);
void SysTimeWriteUNIX (u32 time_to_write);
u32 GetSystemTime_t(void);
u8 OverflowInInt(vu8, vu32);
u8 VarSize(vu8);
u8 WasAddOverflow(void);
u8 IsCorrectFloat(Flo32);
Flo32 Void2Float32(Register_type *);
void ClearFBregs (vu16 FBInputsNum,vu16 FBVarsNum,vu16 FBOutputsNum);
u8 ReadInt8Cfg(void);
u16 ReadInt16Cfg(void);
u32 ReadInt32Cfg(void);
Flo32 ReadFloat32Cfg(void);
void LoadConst(vu8 type, vu16 ArraySize);
void LoadVar(vu8 type, vu16 pAdress, vu16 ArraySize);
void SaveVar(vu8 type, vu16 pAdress, vu16 ArraySize);
u8 LoadFBRegister(void);
u8 SaveFBRegister(void);
void* get_pointer_to_value(vu8* current_variable);
u16 check_file_crc(vu32 addr, vu32 length);
//u8 SaveOutputs(void);
//void SaveOutputs2General_RAM(void);
u8 KernelInit(void);
void KernelCycle(void);		// ���� ���������� ������������ ��.

void fb00000_exec(void);		// 
void fb00001_exec(void);		// + ���������� �
void fb00002_exec(void);		// + ���������� ���
void fb00003_exec(void);		// + ���������� ����������� ���
void FB00004_exec(void);		// + ���������� ��
void fb00005_exec(void);		// + ��������� �
void fb00006_exec(void);		// + ��������� ���
void fb00007_exec(void);		// + ��������� ����������� ���
void fb00008_exec(void);		// + ��������� ��
void fb00009_exec(void);		// + ��������������� ����������� ����� -> ����� �����
void fb00010_exec(void);		// + ��������������� ����� ����� -> ����������� �����
void fb00011_exec(void);		// + ��������������� ����������� ����� -> FLOAT32
void fb00012_exec(void);		// + ��������������� ����������� ����� -> FLOAT32 (� ���������� � ���������)
void fb00013_exec(void);		// + Float32 -> ����� (������ ������� �����)
void fb00014_exec(void);		// + �������������� ��������
void fb00015_exec(void);		// + �������������� ��������
void fb00016_exec(void);		// + �������������� ���������
void fb00017_exec(void);		// + �������������� �������
void fb00018_exec(void);		// + �������������� ���������� � �������
void fb00019_exec(void);		// + ������� �� N ������
void fb00020_exec(void);		// + ������� �� N ������
void fb00021_exec(void);		// + ����������
void fb00022_exec(void);		// + ������������� (�� 32 ������)
void fb00023_exec(void);		// + ��������� �����: ������� ���� � ����� � int32
void fb00024_exec(void);		// + ��������� �����: ������ �� ������ ������
void fb00025_exec(void);		// + ��������� �����: ������ �� ������ ����
void fb00026_exec(void);		// + ��������� �����: ������ �� ������ �����
void fb00027_exec(void);		// + ������: ������ �� ������ �������
void fb00028_exec(void);		// + ������������ �������� (� ������)
void fb00029_exec(void);		// + ������� �� ������� ����� N ������
void fb00030_exec(void);		// + ��������� R7 ������������� (��� 18)
void fb00031_exec(void);		// - ������ �� I2C-������
void fb00032_exec(void);		// - ������ � I2C-������
void fb00033_exec(void);		// - MODBUS Master: ������ - ������� 1/2/3/4
void fb00034_exec(void);		// - MODBUS Master: ������ - ������� 5/6/15/16
void fb00035_exec(void);		// - RTM64var Master
void fb00036_exec(void);		// - RTM64 Master
void fb00037_exec(void);		// + �������
void fb00038_exec(void);		// + ��� (��������) v.1
void fb00039_exec(void);		// - ����������� I2C-������ �� ����
void fb00040_exec(void);		// + �������� (� ���������� �������)
void fb00041_exec(void);		// + RS-������� � ������������ 0
void fb00042_exec(void);		// + ������� �� �������
void fb00043_exec(void);		// + ������������ �� ������
void fb00044_exec(void);		// + ������������� �������
void fb00045_exec(void);		// + ��������� ������� �� UNIX-�������
void fb00046_exec(void);		// + ��������� ������� � UNIX-������
void fb00047_exec(void);		// + ��������� R7 "����� ���" (��� 17, ������ 1)
void fb00048_exec(void);		// + ��������� R7 "����� ��" (��� 17, ������ 2)
void fb00049_exec(void);		// + ��������� R7 "��������� ��������� �������" (��� 17, ������ 4)
void fb00050_exec(void);		// + ��������� R7 "��������� DI" (��� 17, ������ 5)
void fb00051_exec(void);		// + ��������� R7 "��������� AI" (��� 17, ������ 6)
void fb00052_exec(void);		// + ��������� R7 "�������� ������ �������" (��� 17, ������ 7)
void fb00053_exec(void);		// + ����� �������
void fb00054_exec(void);		// + ����������� ������ � �����
void fb00055_exec(void);		// + ������ int8/16 -> 1 bit/int/float
void fb00056_exec(void);		// + ������ ��������� ���������
void fb00057_exec(void);		// + ������ ��������� ���������
void fb00058_exec(void);		// + ������ ������� ���������� ������������
void fb00059_exec(void);		// + ������ � ������ ���������� ������������
void fb00060_exec(void);		// + ��������������� � ������
void fb00061_exec(void);		// + ������ ���������� �� ������
void fb00062_exec(void);		// + �������� ���������� (���)
void fb00063_exec(void);		// + ��������������� UInt16 -> 2x UInt8
void fb00064_exec(void);		// - ����������� ����
void fb00065_exec(void);		// + ��������������� ������� uint16_BE->������ uint8
void fb00066_exec(void);		// - ��� (��������) v.2
void fb00067_exec(void);		// + ������ ����������
#define KNAP_CONTROL 0
void fb00068_exec(void);		// - ������� ���������� �������� �� ����
void fb00069_exec(void);		// + �������� ���������
void fb00070_exec(void);		// + ��������������� �������� RTM64var -> RTM64
void fb00071_exec(void);		// + �������� (��� ��������� �������)
void fb00072_exec(void);		// - ������� ��������
void fb00073_exec(void);		// + ��������������� UInt32/Float -> 2x UInt16
void fb00074_exec(void);		// + ��������������� Int->Float32
void fb00075_exec(void);		// + ��������������� 2x UInt16 -> UInt32/Float
void fb00076_exec(void);		// + ������� ��������
void fb00077_exec(void);		// - ��������� R7 "����� ���-��������" (��� 16)
void fb00078_exec(void);		// + ������� c ������������ �� ����. ���������� �����
void fb00079_exec(void);		// - ����� ��� ���
void fb00080_exec(void);		// - ��������
void fb00081_exec(void);		// - ������� ������� � ��������
void fb00082_exec(void);		// - ���
void fb00083_exec(void);		// + ��������� R7 "��������� DI �� ����" (��� 18)
void fb00084_exec(void);		// + ������ � ���������� �����
void fb00085_exec(void);		// + ������ �� ����������� ������
void fb00086_exec(void);		// - ���������
void fb00087_exec(void);		// - ������� �������� ���������� ���
void fb00088_exec(void);		// - ��������� R7 ��� ����������
void fb00089_exec(void);		// - "������� ������� ���������"
void fb00090_exec (void);		// - ����� � ���
void fb00091_exec (void);		// - ������� ��
void fb00092_exec (void);		// - ������������� 2�uint16 -> uint32
void fb00093_exec (void);		// + �� ����������� (�������-���������)
void fb00094_exec (void);		// ������ "DI ������� 0 ��������� 1 ��� ��-2 �� ����
void fb00099_exec (void);		// - ���
void fb00100_exec (void);		// - ��������
void fb00101_exec (void);		// - ��������
void fb00102_exec (void);		// - �� �������
void fb00103_exec (void);		// - �� ������ ������� ����������
void fb00104_exec (void);		// - SP ARC
void fb00105_exec (void);		// - ������ ������� ����������
void fb00106_exec (void);		// - ������������� DI
void fb00107_exec (void);		// - ������ DO
void fb00108_exec (void);		// - mdbtcp read function(0,1,2,3,4) 
void fb00109_exec (void);		// - mdbtcp write function(5,6,15,16)
void fb00110_exec (void);		// - modem
void fb00111_exec (void);		// - �� ����� ���������
void fb00112_exec (void);		// - BCD to HEX
void fb00113_exec (void);		// - HEX to BCD
void fb00114_exec (void);		// - ��������������� UInt32 -> 4x UInt8
void fb00115_exec (void);		// - ������
void fb00116_exec (void);		// - ������������� 2.0
void fb00117_exec (void);		// - ���� - ����� ��������
void fb00118_exec (void);		// - modem
void fb00119_exec (void);		// - modbus udp read
void fb00120_exec (void);		// - modem udp write
void fb00121_exec (void);		// - modbus read new 
void fb00122_exec (void);		// - modem write new
extern const FB_Func fb_exec[123];

void NewQ_Arc_R7(vu8 *pR7buffer, vu8 SubType);  // ������� ���� ������ ����������
//=== ������ ��������� ������ Paket �� Tiks1ms mS ===//
void LedPaketOn(vs16 Tiks1ms);
//=== ������ ��������� LEDOTVET ===//
void LedOtvetOn(vs16 Tiks1ms);
//=== ������ ��������� LEDERROR ===//
void LedErrorOn(vs16 Tiks1ms);
//=== ������ ��������� LEDTEST ===//
void LedTestOn(vs16 Tiks1ms);

#endif
