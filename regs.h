#ifndef _REGS_H_
#define _REGS_H_
// Размеры окон в регистрах
//==============================================================================
#define Options_RegNum            410
#define ArcR7_WindowRegNum        34
#define ConfigLoad_WindowRegNum   34
#define ProgramLoad_WindowRegNum  34
//==============================================================================

// Адреса int16 регистров
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
// Адреса регистров контроллера где располагаются его системные настройки и переменные
//==============================================================================
#define regMyAdrRTM64           	0   // 1 rw Адрес РТМ64
#define regMyAdrMODBUS          	1   // 1 rw Адрес по ModBUS
#define regMyPortMODBUS         	2   // 1 rw
#define regMyIpAdr              	3   // 4 rw
#define regMySubNetMask         	7   // 4 rw
#define regMyRoutIpAdr          	11  // 4 rw
#define regMyMAC                	15  // 6 rw

#define regSystemTime				21  // 3 rw Системное время
#define regCmdRESET             	24  // 1 -w Команда перезагрузки контроллера
#define regCmdFBUpd					25  // 1 -w Команда окончания загрузки файла конфигурации

#define regCmdFB		        	27  // 1 -w Команда запрещения/разрешения исполнения конфигурации
#define regCmdPrgUpd				26	// 1 -w Команда оканчания загрузки файла прошивки
#define regCmdCRC		 	        28  // 1 -w Команда расчёта CRC файлов в буферах контроллера
#define regFileCRC		            29  // 1 r- CRC файла, рассчитанная после подачи команды рассчёта

#define regBaud_COM0             	30  // 1 rw Параметры COM0
#define regBaud_COM1				31	// 1 rw Параметры COM1
#define regBaud_COMIntBUS			32	// 1 rw Параметры COM2
#define regBaud_COMext				33	// 1 rw Параметры COMext

// 34...61 Reserved	

#define regCntTOut					62	// 2 r- Время отключения
#define regCntDOut					64	// 2 r- Дата отключения

// 66...67 Служебные

#define regFreeStackSize			68 // 1 r- Размер сбодного стека в байтах
#define regRNSets					69 // 1 rw настройки ближнего радио

#define regFreq16					70	// 2 к- Частота на входе 16
#define regFreq17					72	// 2 r- Частота на входе 17
#define regCntDI					74	// по 2 18 раз r- 18 32-х разрядных счетчиков
	// 74...109

#define regSostDO					110	// 1 rw Состояние DO Запись в этот регистр вызывает изменение на выходах DO
#define regADCChan					111 // по 1 4 раза r- 4 канала ADC
	// 111...114

#define regTemperatureSD			115	// 1 r- Температура SD карты со знаком
#define regOldDI					116	// 2 r- Предыдущее состояние DI
#define regSostDI					118	// 2 r- Текущее состояние DI
#define regDIFilter					120 // 1 rw период опроса входов DI - для ликвидации дребезга по счетным входам
// 121..126 Резерв

#define regKernelFlags				127 // 1 r- Флаги исполнения конфигурации
// Статистика цикломашины ФБ
#define regKernelFullTime       	128 // 1
#define regKernelClearTime      	129 // 1
#define regKernelLoadVarsTime   	130 // 1
#define regKernelSaveVarsTime   	131 // 1
// Статистика менеджера пакетов
#define regIdlePaketsNum        	132 // 1
#define regTimeOutsNum          	133 // 1
#define regBrakePaketsNum       	134 // 1
// Ресурсы памяти контроллера
#define regMaxCfgSize           	135 // 1
#define regMaxPrgSize           	136 // 1
#define regMaxFB_RAMsize        	137 // 1
#define regSaveFB_RAMsize       	138 // 1
#define regArcR7_RecNum         	139 // 1
#define regregR7_Index             	140 // 2
// Параметры текущей конфигурации
#define regCfgSize              	142 // 1
#define regCfgTWICommSize       	143 // 1
#define regFBCfgSize            	159 // 1
#define regFBkernelRate         	160 // 1
// Системные переменные
#define regResetCnt             	146 // 1
#define regResetCase            	147 // 1
#define regVersChip             	148 // 1
#define regBootFlags            	149 // 1
// Флаги ошибок
#define regCfgUpdateErrorFlags  	150 // 1 Флаги ошибок при обновлении файла конфигурации
#define regKernelErrorFlags     	151 // 1 Флаги ошибок при исполнении конфигурации
// Прочее
#define regI2CrestartCnt        	152 // 1 Количество перезапусков шины I2C
#define regGMSKFFSKSet				155 // настройки модуляции дальнего радио
#define regArcNum2Rd				410	// 2

#define regMapTable 					294


#define BootFlags_UserMode            (1<<0)  // Пользовательский режим

//------------------------------------------------------------------------------

// Коды ошибок // Exceptions
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

// Пароли на изменение важных системных настроек
#define pswCmdRESET             5300    // Пароль на команду сброса контроллера
#define pswCmdCfgLoadingFinish  5400    // Пароль на команду окончания загрузки файла конфигурации
#define pswCmdCfgCopy2Buff      5401    // Пароль на команду копирования рабочей конфигурации в буфер
#define pswCmdModeBOOT          5500    // Пароль на команду окончания загрузки файла прошивки и перевод контроллера в BOOT
#define pswCmdModeUSER          5501    // Пароль на команду перевода контроллера в USER
#define pswCmdModeBOOTandUPD    5502    // Пароль на команду перевода контроллера в BOOT с последующим обновлением ПО контроллера
#define pswCmdCfgDisable        5600    // Пароль на команду запрещения исполнения конфигурации
#define pswCmdCfgEnable         5601    // Пароль на команду разрешения исполнения конфигурации
#define pswCmdCfgSaveRAM        5602    // Пароль на команду принудительного сохранения сохраняемой части ОЗУ
#define pswCmdCalcCfgFileCRC    5700    // Пароль на команду расчёта CRC файла конфигурации
#define pswCmdCalcPrgFileCRC    5701    // Пароль на команду расчёта CRC файла прошивки

typedef union __sEventFlags {
  struct {
		u8 Bit00                ; // 0 Флаг разрешения исполнения конфигурации
		u8 Bit01                ; // 1
		u8 Bit02                ; // 2
		u8 Bit03                ; // 3
		u8 Bit04                ; // 4 Необходино проверить CRC конфигурации
		u8 Bit05                ; // 5 Необходимо попытаться обновить файл конфигурации из буфера
		u8 Bit06                ; // 6 
		u8 Need2Go2Boot         ; // 7 Необходимо переключиться в BOOT
		u8 Need2UpdateSoftware  ; // 8 Необходимо произвести обновление ПО
		u8 Bit09                ; // 9 Необходимо рассчитать CRC файла в буфере конфигурации
		u8 Need2CalcPrgCRC      ; // 10 Необходимо рассчитать CRC файла в буфере прошивки
		u8 Bit11                ; // 11
		u8 Bit12                ; // 12
		u8 Bit13		            ; // 13
		u8 Need2SaveFBRAM       ; // 14 Необходимо сохранить во flash сохраняемую часть ОЗУ
		u8 Bit15                ; // 15 Первая секунда исполнения конфигурации
		u8 Bit16                ; // 16 Первое исполнение конфигурации
		u8 DateTimeSync         ; // 17 Время синхронизировано
		u8 Need2ResetAfterCnt   ; // 18 Необходимо перезагрузить контроллер после отправки ответа
		u8 Need2Reset           ; // 19 Необходимо перезагрузить контроллер
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
} sEventFlags; //комплексный тип
extern sEventFlags EventFlags;

typedef union {
   struct {
		unsigned NoCfgFile            ; // Отсутствует файл конфигурации
		unsigned BadCfgFileCRC        ; // Неправильная CRС файла конфигурации
		unsigned SmallCfgFile         ; // Слишком маленький файл конфигурации
		unsigned BigCfgFile           ; // Слишком большой файл конфигурации
		unsigned BadCfgFileLengths    ; // Неправильные длины блоков файла конфигурации
	} Bit;
	vu32 Register;
} sCfgUpdateErrorFlags;


typedef  union {
   struct{
		unsigned NoCfgFile            ; // Отсутствует файл конфигурации
		unsigned BadCfgFileCRC        ; // Неправильная CRС файла конфигурации
		unsigned BadCfgFileLengths    ; // Неправильные длины блоков файла конфигурации
		unsigned BadCodeFB            ; // В файле конфигурации присутствуют неподдерживаемые типы ФБ
		unsigned BadRegAddr           ; // В файле конфигурации присутствует доступ к области за пределами ОЗУ ФБ
	} Bit;
	vu32 Register;
} sKernelErrorFlags;


#endif
