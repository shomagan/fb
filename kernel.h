
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
#define cstMaxCfgSize	65024u		// Максимальный размер файла конфигурации.(должно быть кратно 256)
#define cstMaxFB_RAMsize		(1512 + 32768ul)		// Размер массива общего назначения ФБ.(должно быть кратно 256)
#define cstKERNEL_RAM_SIZE		32768ul		// Размер массива общего назначения ФБ.(должно быть кратно 256)
#define cstSavedFB_RAMSize		8192ul		// сохраняемая часть из cstMaxFB_RAMsize(должно быть кратно 256)
#define RAM_SavedRAM_StartAddr	(cstMaxFB_RAMsize - cstSavedFB_RAMSize)		// начальный адрес сохраняемых переменных FB
#define CONFIG_START_ADRES 0x08010000   //адрес начали конфигурации во флешь контроллера размер вся секция
		//в последнем байте (из 8к) - значение, увеличивающееся перед записью
#define cstFBInputsNum	256u		// Максимальное кол-во входов для 1 ФБ.
#define cstFBVarsNum		512u		// Максимальное кол-во внутренних переменных для 1 ФБ.
#define cstFBOutputsNum		256u		// Максимальное кол-во выходов для 1 ФБ.
// Маски для расшифровки поля Type:
#define RegTypeMask	0x03
#define IsArrayMask	0x04
#define DataTypeMask	0xE0
// Тип значения (по маске RegType)
#define KodConst	0x00
#define KodInput	0x01
#define KodOutput	0x02
#define KodVariable	0x03
// Коды типов данных (по маске TypeMask)
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
        u8 EnableFB             ; // 0 Флаг разрешения исполнения конфигурации
        u8 TimePermission       ; // 1 пришло время выполнять конфигурацию,выставится по прерывани по времени,до запуска соответствующего кернела
        u8 Perfoming            ; // 2 конфигурация еще выполняет,выставляется в начале цикла и до конца
        u8 Bit03                ; // 3
        u8 Need2CheckConfCRC    ; // 4 Необходино проверить CRC конфигурации
        u8 Need2UpdateCfg       ; // 5 Необходимо попытаться обновить файл конфигурации из буфера
        u8 Bit06                ; // 6
        u8 Bit07                ; // 7 Необходимо переключиться в BOOT
        u8 Need2UpdateSoftware  ; // 8 Необходимо произвести обновление ПО
        u8 Need2CalcCfgCRC      ; // 9 Необходимо рассчитать CRC файла в буфере конфигурации
        u8 Need2CalcPrgCRC      ; // 10 Необходимо рассчитать CRC файла в буфере прошивки
        u8 Bit11                ; // 11
        u8 Bit12                ; // 12
        u8 Bit13                ; // 13
        u8 Bit14                ; // 14 Необходимо сохранить во flash сохраняемую часть ОЗУ
        u8 CfgFirstSec          ; // 15 Первая секунда исполнения конфигурации
        u8 CfgFirstExec         ; // 16 Первое исполнение конфигурации
        u8 ErrorCRC             ; // 17 Время синхронизировано
        u8 CheckPassed          ; // 18 Необходимо перезагрузить контроллер после отправки ответа
        u8 Bit19                ; // 19 Необходимо перезагрузить контроллер
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
} sKernelEventFlags; //комплексный тип
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct {
  u16 CfgSize;          //
  u16 CfgTWICommSize;   //
  u16 FBCfgSize;        //
  u16 FBkernelRate;     //тактов в секунду
  Int64U StartTick; //время начала исполнения конфигурации(тики по 100 мкс)
  Int64U StopTick;//время конца исполнения конфигурации(тики по 100 мкс)
  u32 WorkingTime;
  u32 CfgStartTime;
  u8* pCFG;     //указатель на текущее место исполнения конфигурации
  u8* pStartCFG;//указатель на начало конфигурации
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
void KernelCycle(void);		// Цикл исполнения конфигурации ФБ.

void fb00000_exec(void);		// 
void fb00001_exec(void);		// + Логическое И
void fb00002_exec(void);		// + Логическое ИЛИ
void fb00003_exec(void);		// + Логическое исключающее ИЛИ
void FB00004_exec(void);		// + Логическое НЕ
void fb00005_exec(void);		// + Побитовое И
void fb00006_exec(void);		// + Побитовое ИЛИ
void fb00007_exec(void);		// + Побитовое исключающие ИЛИ
void fb00008_exec(void);		// + Побитовое НЕ
void fb00009_exec(void);		// + Преобразователь БЕЗЗНАКОВОЕ ЦЕЛОЕ -> НАБОР БИТОВ
void fb00010_exec(void);		// + Преобразователь НАБОР БИТОВ -> БЕЗЗНАКОВОЕ ЦЕЛОЕ
void fb00011_exec(void);		// + Преобразователь БЕЗЗНАКОВОЕ ЦЕЛОЕ -> FLOAT32
void fb00012_exec(void);		// + Преобразователь БЕЗЗНАКОВОЕ ЦЕЛОЕ -> FLOAT32 (с множителем и делителем)
void fb00013_exec(void);		// + Float32 -> целое (отброс дробной части)
void fb00014_exec(void);		// + Алгебраическое сложение
void fb00015_exec(void);		// + Алгебраическая разность
void fb00016_exec(void);		// + Алгебраическое умножение
void fb00017_exec(void);		// + Алгебраическое деление
void fb00018_exec(void);		// + Алгебраическое возведение в степень
void fb00019_exec(void);		// + Среднее за N тактов
void fb00020_exec(void);		// + Среднее за N секунд
void fb00021_exec(void);		// + Компаратор
void fb00022_exec(void);		// + Мультиплексор (до 32 входов)
void fb00023_exec(void);		// + Системное время: текущая дата и время в int32
void fb00024_exec(void);		// + Системное время: секунд от начала минуты
void fb00025_exec(void);		// + Системное время: секунд от начала часа
void fb00026_exec(void);		// + Системное время: секунд от начала суток
void fb00027_exec(void);		// + Таймер: секунд от начала периода
void fb00028_exec(void);		// + Длительность импульса (в тактах)
void fb00029_exec(void);		// + Триггер со сбросом через N тактов
void fb00030_exec(void);		// + Архиватор R7 универсальный (тип 18)
void fb00031_exec(void);		// - Чтение из I2C-модуля
void fb00032_exec(void);		// - Запись в I2C-модуль
void fb00033_exec(void);		// - MODBUS Master: Чтение - функции 1/2/3/4
void fb00034_exec(void);		// - MODBUS Master: Запись - функции 5/6/15/16
void fb00035_exec(void);		// - RTM64var Master
void fb00036_exec(void);		// - RTM64 Master
void fb00037_exec(void);		// + Счётчик
void fb00038_exec(void);		// + ГЗУ (Башнефть) v.1
void fb00039_exec(void);		// - Присутствие I2C-модуля на шине
void fb00040_exec(void);		// + Селектор (с обнулением выходов)
void fb00041_exec(void);		// + RS-триггер с приоритетным 0
void fb00042_exec(void);		// + Триггер со сбросом
void fb00043_exec(void);		// + Одновибратор по фронту
void fb00044_exec(void);		// + Синхронизатор времени
void fb00045_exec(void);		// + Конвертер времени из UNIX-формата
void fb00046_exec(void);		// + Конвертер времени в UNIX-формат
void fb00047_exec(void);		// + Архиватор R7 "Замер ГЗУ" (тип 17, подтип 1)
void fb00048_exec(void);		// + Архиватор R7 "Замер БГ" (тип 17, подтип 2)
void fb00049_exec(void);		// + Архиватор R7 "Изменение состояния объекта" (тип 17, подтип 4)
void fb00050_exec(void);		// + Архиватор R7 "Изменение DI" (тип 17, подтип 5)
void fb00051_exec(void);		// + Архиватор R7 "Изменение AI" (тип 17, подтип 6)
void fb00052_exec(void);		// + Архиватор R7 "Протокол работы объекта" (тип 17, подтип 7)
void fb00053_exec(void);		// + Часть массива
void fb00054_exec(void);		// + Компоновщик данных в блоки
void fb00055_exec(void);		// + Массив int8/16 -> 1 bit/int/float
void fb00056_exec(void);		// + Чтение системной настройки
void fb00057_exec(void);		// + Запись системной настройки
void fb00058_exec(void);		// + Первая секунда исполнения конфигурации
void fb00059_exec(void);		// + Секунд с начала исполнения конфигурации
void fb00060_exec(void);		// + Преобразователь в массив
void fb00061_exec(void);		// + Первое исполнение ФБ логики
void fb00062_exec(void);		// + Фиксатор переменной (ОЗУ)
void fb00063_exec(void);		// + Преобразователь UInt16 -> 2x UInt8
void fb00064_exec(void);		// - Вычислитель Кнап
void fb00065_exec(void);		// + Преобразователь массива uint16_BE->массив uint8
void fb00066_exec(void);		// - ГЗУ (Башнефть) v.2
void fb00067_exec(void);		// + Фильтр дискретный
#define KNAP_CONTROL 0
void fb00068_exec(void);		// - Автомат управления приводом по Кнап
void fb00069_exec(void);		// + Детектор изменений
void fb00070_exec(void);		// + Преобразователь маршрута RTM64var -> RTM64
void fb00071_exec(void);		// + Селектор (без обнуления выходов)
void fb00072_exec(void);		// - Счётчик массомер
void fb00073_exec(void);		// + Преобразователь UInt32/Float -> 2x UInt16
void fb00074_exec(void);		// + Преобразователь Int->Float32
void fb00075_exec(void);		// + Преобразователь 2x UInt16 -> UInt32/Float
void fb00076_exec(void);		// + Масштаб величины
void fb00077_exec(void);		// - Архиватор R7 "Замер ГЗУ-Массомер" (тип 16)
void fb00078_exec(void);		// + Счётчик c ограничением по макс. приращению входа
void fb00079_exec(void);		// - Насос без АПВ
void fb00080_exec(void);		// - Задвижка
void fb00081_exec(void);		// - Весовой импульс с счетчика
void fb00082_exec(void);		// - ПИД
void fb00083_exec(void);		// + Архиватор R7 "Состояние DI КП КТПН" (тип 18)
void fb00084_exec(void);		// + Запись в батарейный домен
void fb00085_exec(void);		// + Чтение из батарейного домена
void fb00086_exec(void);		// - Резервуар
void fb00087_exec(void);		// - Счетчик массомер измененный газ
void fb00088_exec(void);		// - Архиватор R7 для динамограм
void fb00089_exec(void);		// - "Счетчик входных импульсов"
void fb00090_exec (void);		// - Насос с АПВ
void fb00091_exec (void);		// - Счетчик БГ
void fb00092_exec (void);		// - преобразовать 2хuint16 -> uint32
void fb00093_exec (void);		// + ФБ двухчасовка (счётчик-архиватор)
void fb00094_exec (void);		// фильтр "DI длинный 0 остальное 1 для ИТ-2 на КТПН
void fb00099_exec (void);		// - ПИД
void fb00100_exec (void);		// - Тестовая
void fb00101_exec (void);		// - Задвижка
void fb00102_exec (void);		// - ФБ Уставка
void fb00103_exec (void);		// - ФБ Чтение сетевых переменных
void fb00104_exec (void);		// - SP ARC
void fb00105_exec (void);		// - Запись сетевых переменных
void fb00106_exec (void);		// - Мультиплексор DI
void fb00107_exec (void);		// - Запись DO
void fb00108_exec (void);		// - mdbtcp read function(0,1,2,3,4) 
void fb00109_exec (void);		// - mdbtcp write function(5,6,15,16)
void fb00110_exec (void);		// - modem
void fb00111_exec (void);		// - ФБ Опрос счетчиков
void fb00112_exec (void);		// - BCD to HEX
void fb00113_exec (void);		// - HEX to BCD
void fb00114_exec (void);		// - Преобразователь UInt32 -> 4x UInt8
void fb00115_exec (void);		// - фильтр
void fb00116_exec (void);		// - Мультиплексор 2.0
void fb00117_exec (void);		// - Вход - выход сквозной
void fb00118_exec (void);		// - modem
void fb00119_exec (void);		// - modbus udp read
void fb00120_exec (void);		// - modem udp write
void fb00121_exec (void);		// - modbus read new 
void fb00122_exec (void);		// - modem write new
extern const FB_Func fb_exec[123];

void NewQ_Arc_R7(vu8 *pR7buffer, vu8 SubType);  // Передаём тело архива архиватору
//=== Зажечь светодиод приема Paket на Tiks1ms mS ===//
void LedPaketOn(vs16 Tiks1ms);
//=== Зажечь светодиод LEDOTVET ===//
void LedOtvetOn(vs16 Tiks1ms);
//=== Зажечь светодиод LEDERROR ===//
void LedErrorOn(vs16 Tiks1ms);
//=== Зажечь светодиод LEDTEST ===//
void LedTestOn(vs16 Tiks1ms);

#endif
