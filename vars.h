#define CHANNEL_NUMBER 9
#ifndef _vars_h
#define _vars_h

#include "kernel.h"

//---DEFINE
#define RAM_START	0x20000000		// Начало области ОЗУ.
#define RAM_END		0x2001B3D4
#define STACK_TOP	0x2001C000		// Верх стека в 0x2001C000 - 112 KB.
#define cstPrgSize		((USER_END>>10)-(USER_START>>10))		//(0x08060000-0x08010000)>>10;256К // максимальный размер файла прошивки
#define BOOT_START	0x08000000		// Начало области Boot. Размер 96К.
#if debug_mega
  #define USER_START		0x08000000		// Начало области User. Размер 416К.
#else
  #define USER_START    0x08020000    // Начало области User. Размер 256К.
#endif
#define USER_END      0x08060000    // Конец области User. Размер 256К.
#define SP_START      0x08060000    // Начало области описания сетевых переменных. Размер 128К.
#define SP_END      0x08080000    // Конец области описания сетевых переменных. Размер 128К.
#define OPT_START	0x1FFFC000		// Начало области опциональных байтов.
#define UNIQUEID	0x1FFF7A10		// Уникальный 96 битный ID.
#define KEY1	0x45670123		// Ключ KEY1.
#define KEY2	0xCDEF89AB		// Ключ KEY2.
#define OPTKEY1	0x08192A3B		// Ключ OPTKEY1.
#define OPTKEY2	0x4C5D6E7F		// Ключ OPTKEY2.
#define MCLK		120000000		// Частота системная.
//=== Константы
#define	cstVer		1		// Версия прошивки (байт).
#define	cstMyAdr	3		// Адрес (0...4095).
#define cstMyAdrMB	3
#define	cstIsSvjaznoj		0
#define	cstLINX_ON	1		//D0=1-COM1, D0=0-COM0; D1=1- по Ближ.р/св, D2=1-по Дальн.р/св.
#define	ChipTipe	4		// =1 - 8 кБайт, =2 - 32 кБайта, =3 - 128 кБайт, =4 - 512 кБайт, =5 - 256 кБайт.
#define LenNumDI 18
#define SIZE_CRC16 2
#define SIZE_CRC32 4
//=== Выводы ===//
//=== Port PA ===//
//вход канала преобразования АЦП копируется в итоге в FB32blok.vars.ADCchan[]
#define CS_FLASH_2  0		// Flash 2 w25q64hv
#define ETH_REFCLK	1		// Вход тактирования Ethernet
#define ETH_MDIO		2		// Вывод связи MDIO Ethernet
#define AINRADIO	  3		// Вход ADC1 (ADC123_IN3) для дальнего Радио AIN4.
#define DACOUT1		  4		// Выход DAC1 для дальнего Радио.
#define SCK_FLASH		5		// Тактовая для обмена с микросхемой памяти SPI1
#define MISO_FLASH	6		// Data input from flash M25PE16 SPI1
#define ETH_CRS   	7		// 
#define LEDOTVET  	8		// Выход LEDOTVET.
#define TXD1	      9		// Выход USART2_Tx - COM1.
#define RXD1	      10		// Вход  USART2_Rx - COM1.
#define DI9     		11		// Digital input 9, init requare
#define DI10    		12		// Digital input 10, init requare
//#define SWD    		13		// Digital input 11, init requare
//#define SWCLK    		14		// Digital input 12, init requare
#define WR485_0		  15		// Выход управления передачей СОМ1.
//=== Port PB ===//
#define AIN3  		0		// Вход канала ADC3 (ADC123_IN0).
#define DI8		    1		// Digital input 8, init requare
#define SCK_RN		3		// Выход SPI3_SCK ближней радиосвязи.
#define MISO_RN		4		// Вход SPI3_MISO ближней радиосвязи.
#define MOSI_FLASH 5		//Data output to flash M25PE16  SPI1
#define GPRS_SCL 	6		// NSEL RFM23BP
#define GPRS_SDA_ 	7		// IRQ RFM23BP
#define DI17    	8		// Digital input 17, init requare
#define DI18    	9		// Digital input 18, init requare
#define ETHRXER		10		// Вход RxER Ethernet
#define ETHTXEN		11		// Выход TxEN Ethernet.
#define ETHTXD0		12		// Выход TxD0 Ethernet.
#define ETHTXD1		13		// Выход TxD1 Ethernet.
#define DI11      14   // Digital input 17, init requare
#define DI12      15   // Digital input 18, init requare
//=== Port PC ===//
#define AIN0		0		// Вход канала ADC0 (ADC123_IN10).
#define ETHMDC		1		// Вывод связи MDC Ethernet.
#define AIN1		2		// Вход канала ADC1 (ADC123_IN12).
#define AIN2		3		// Вход канала ADC2 (ADC123_IN13).
#define ETH_RX0 4		// 
#define ETH_RX1 5		// 
#define TXD2		6		// Выход USART6_Tx - межмодуль.
#define RXD2		7		// Вход USART6_Rx - межмодуль.
#define CS_FLASH	8		// Cheep select M25PE16.
#define ETH_INTRP 9		// intrp  Ethernet.
#define TXD0		10		// Выход UART4_Tx - COM0.
#define RXD0		11		// Вход UART4_Rx - COM0.
#define MOSI_RN		12		// Выход SPI3_MOSI ближней радиосвязи.
#define GPIO0_RN		13		// Вход GPIO0_RN ближнего радио.
#define OSC32in		14		// Вход OSC32.
#define OSC32out	15		// Выход OSC32.
//=== Port PD ===//
#define GPRS_IO1  0   //
#define GPRS_IO2  1   //
#define GPRS_IO3  2   //
#define DI13      3   //
#define DI14      4   //
#define USART_TXD_X19      5   //
#define USART_RXD_X19      6   //
#define USART_CLK_X19      7   //
#define LEDTEST		8		// Выход LEDTEST.
#define LedPaket	9		// Выход LedPaket.
#define PTT			10		// Выход управления передачей дальнего радио.
#define WR485_2		11		// Выход управления передачей СОМ2.
#define OUTDO2		12		// Выход DO2.	AF2 TIM4_CH1
#define OUTDO1		13		// Выход DO1.	AF2 TIM4_CH2
#define OUTDO0		14		// Выход DO0.	AF2 TIM4_CH3
#define OUTDO3		15		// Выход DO3.
//=== Port PE ===//
#define DI6   	0		// Выход включения питания СОМ-портов 0 и 1.
#define DI7 		1		// Вход выбора JMP2.
#define IE_DI		2		// Выход разрешения DI1...16.
#define CS_RN		3		// Выход выбора CS ближней радиосвязи.
#define IRQ_RN		4		// Вход IRQ ближней радиосвязи.
#define DI1   	5		// Digital input 1, init requare
#define DI2   	6		// Digital input 2, init requare
#define TxAnt_RN		7		// Выход TxAnt ближней радиосвязи.
#define RxAnt_RN		8		// Выход RxAnt ближней радиосвязи.
#define DI3   	9		// Digital input 3, init requare
#define DI4   	10		// Digital input 4, init requare
#define DI5   	11		// Digital input 5, init requare
#define LEDERROR	12		// Выход LEDERROR.
#define DI16_FAST 		13		//
#define DI15_FAST 		14		//
#define JMP1		15		// Вход выбора JMP1.
//GPRS
#define OnPWRK() (GPIOE->BSRR=(BIT(LEDERROR) << 16))
#define OffPWRK() (GPIOE->BSRR=(BIT(LEDERROR) << 16))

/// Ближнее Радио.
#define SetCS_RN()		(GPIOE->BSRR=(BIT(CS_RN) << 16))		// Выбрать NSS->L.
#define ResetCS_RN()	(GPIOE->BSRR=BIT(CS_RN))		// Отключить NSS->H.

/// Радио RFM23.
#define SetCS_RFM23()		(GPIOB->BSRR=(BIT(GPRS_SCL) << 16))		// Выбрать NSS->L.
#define ResetCS_RFM23()	(GPIOB->BSRR=BIT(GPRS_SCL))		// Отключить NSS->H.

//#define SetSCK_RN()	(GPIOB->BSRR=BIT(SCK_RN))		// Выставить SCK_RN.
#define SetAntTx()	(GPIOE->BSRR=(BIT(RxAnt_RN)<<16)+BIT(TxAnt_RN))		// Снять RXANT и установить TXANT.
#define SetAntRx()	(GPIOE->BSRR=(BIT(TxAnt_RN)<<16)+BIT(RxAnt_RN))		// Снять TXANT и установить RXANT.

/// Ближнее Радио. RFM23BP
//#define SetCS_RN()		(GPIOB->BSRR=(BIT(GPRS_SCL) << 16))		// Выбрать NSS->L.
//#define ResetCS_RN()	(GPIOB->BSRR=BIT(GPRS_SCL))		// Отключить NSS->H.

// FLASH.
#define SetCS_FLASH()		(GPIOC->BSRR=(BIT(CS_FLASH) << 16))		// Выбрать SD->L.
#define ResetCS_FLASH()	(GPIOC->BSRR=BIT(CS_FLASH))		// Отключить SD->H.
// FLASH2.
#define SetCS_FLASH_2()		(GPIOA->BSRR=(BIT(CS_FLASH_2) << 16))		// Выбрать SD->L.
#define ResetCS_FLASH_2()	(GPIOA->BSRR=BIT(CS_FLASH_2))		// Отключить SD->H.

// Дальнее Радио.
#define SetPTT()		(GPIOD->BSRR = BIT(PTT))					// Выставить PTT.
#define ResetPTT()		(GPIOD->BSRR = (BIT(PTT) << 16))			// Снять PTT.

#define RS485On()		(GPIOA->BSRR=BIT(WR485_0))		// Выставить передачу RS485_0.
#define RS485Off()		(GPIOA->BSRR=(BIT(WR485_0)<<16))		// Снять передачу RS485_0.
#define RS485_2On()	(GPIOD->BSRR=BIT(WR485_2))		// Выставить передачу RS485_2.
#define RS485_2Off()	(GPIOD->BSRR=(BIT(WR485_2) << 16))		// Снять передачу RS485_2.
#define RS485_ExtOn()	(GPIOD->BSRR=BIT(USART_CLK_X19))		// Выставить передачу RS485_2.
#define RS485_ExtOff()	(GPIOD->BSRR=(BIT(USART_CLK_X19) << 16))		// Снять передачу RS485_2.

#define LedPaketOff()	(GPIOD->BSRR = (BIT(LedPaket) << 16))	 	// Выключение LedPaket.
#define LedOtvetOff()	(GPIOA->BSRR = (BIT(LEDOTVET) << 16))	 	// Выключение LEDOTVET.
#define LedErrorOff()	(GPIOE->BSRR = (BIT(LEDERROR) << 16))	 	// Выключение LEDERROR.
#define LedTestOff()	(GPIOD->BSRR = (BIT(LEDTEST) << 16))	 	// Выключение LEDTEST.
// Тестовый вывод.
#define SetTest6()		(GPIOE->BSRR = BIT(PINTEST6))		// Выставить PINTEST6.
#define ResetTest6()	(GPIOE->BSRR = (BIT(PINTEST6) << 16))		// Снять PINTEST6.
#define _PORTE(i) (*((__O unsigned long *) (PERIPH_BB_BASE + ((GPIOE_BASE+0x0C-PERIPH_BASE) * 0x20) + (i*4)))) // Bit Bang доступ

//=== Архивы и BKPSRAM ===//
// Уставки из RTC_BKP - четырехбайтными словами, 20 слов.
//!!!перепроверить получение, хранение, восстановление и предоставление данных
	// RTC->BK0R	- пользовательские биты.
		//D0...D7 - ResetSource, причина перезагрузки - bit0-OBL,bit1-pinRST,bit2-POR,bit3-SWR,bit4-IWDG,bit5-WWDG,bit6-LPRST.
		//D9...8 - резерв.
		//D10 = 1 - переписать ПО из SDcard в User_Flash.
		//D11 = 0 - User-программа еще не запускалась.
		//D12 = 1 - User-программа исправна.
		//D13 - служебная функция.
		//D14 = 1 - IsSvjaznoj.
		//D15 - Boot=1 - работать из User-программы, =0 - из Boot-программы.
		//D16...D23 - ModbusRTU адрес
		//D24..D31 - Зарезервировано
	// RTC->BK1R	- (D0...D11) MyAdr, (D12-15 должны быть 0) (D16...D31) Количество перезагрузок.
	// RTC->BK2R	- (D0...D15) RFDelay, Задержка для Дальнего Радио, (D16...D31) RNDelay, Задержка для Ближнего Радио.
	// RTC->BK3R	- BKP_CS - сохраненная контрольная сумма программного обеспечения.
	// RTC->BK4R	- адрес хранения данных на карте
		//D0..15 - номер сектора с данными ФБ
		//D16..D31 - резерв
	// RTC->BK5R	- номер последней сохранённой архивной записи (индекс указателя записи в архив = кол-во записей в архиве)
	// RTC->BK6R	- время отключения.
	// RTC->BK7R	- дата отключения.
	// RTC->BK8R	- RadioNear, уставки ближнего радио.
		//D0-7 - PowerRN, мощность передатчика ближнего радио. 0 = +11 dB или 3 = +20 dB
		//D8-10 - ChannelRN, частотный канал ближнего радио. от 1 до 4, игнорируется BaudRateRN = 4
		//D11-15 - BaudRateRN, скорость ближнего радио. 0=1200, 1=2400, 2=4800, 3=9600, 4=19200, 5=38400, возможно только 4 или 2
	// RTC->BK9R - D<31..1> Зарезервировано; D<0> настройки дальнего радио =0 - GMSK; =1 - FFSK замкнутого типа; =2 - FFSK разомкнутого типа
	// RTC->BK10R - D<31...24> - Baudext GPRS, D<23...16> - Baud_COM1, D<15...8> - Baud_COM1, D<7...0> - Baud_COM0.
	// RTC->BK11R - номер SD карты, при несовпадении считаем карту новой
	// RTC->BK12R - D<31..8> Зарезервировано D<7..0> = период опроса входов DI в мсек
	// RTC->BK13R - D0 - отключалась батарея, проинициализировать таблицу слейвов.
	// RTC->BK14R - Зарезервировано
	// RTC->BK15R - Зарезервировано
	// RTC->BK16R - Зарезервировано
	// RTC->BK17R - Зарезервировано
	// RTC->BK18R - Зарезервировано
	// RTC->BK19R - Зарезервировано	
extern vu16 CSuserPrg;		// Контрольная сумма.
extern vu16 NumBlock;		// Номер записываемого блока.
//ErrCod

#define PACKET_QUE_ERROR              0
#define CRC_ERROR                     1
#define CRC_MDB_ERROR                 2
#define CRC_MW_ERROR                  3
#define MDB_QUE_ERROR                 4
#define PACK_UNDEFIND_STATE_ERROR     5
#define ETH_ERROR                     6
#define ETH_NEGOTIATION_ERROR         7

//ErrCodFB
#define PACK_TIMEOUT_ERROR            0
#define FLAG_UNDEFINED_STATE_ERROR    1
#define NEGATIVE_ACKNOWLEDGE_ERRROR   2
#define FB_ERROR                      4
#define CONFIG_CRC_ERROR              5
#define LWIP_MEMORY_ERROR             6

//=== Пакет для ФБ32 ===//
// Объявление общей структуры данных для ФБ32.
#define LOAD_BUFF_SIZE 256
#define RESERV_BUFF_SIZE 190
#define OWN_VARIABLE_BLOK_SIZE	(1024 + 256 + 256)		// Размер структуры - 1024 байт.
#define LenNumDI	18		// Количество входов DI.
extern vu8 SuperMaster; // Тот у кого исполняется ФБ 103

typedef union{		// Объединение структуры и массива.
#pragma pack(push)
#pragma pack(1)
	  struct {		// Структура разнотипных данных
		u16 MyAdr;			//"Адрес_RTM" 0, 1 RTM64-адрес.(в старшем бите - "связной")
		u16 MyAdrMB;		//"Адрес_Modbus" 2, 3 ModBus-адрес.(+ обработка есть, но не используется)
		u16 Rezerv;		//"Rezerv" 4, 5 there was ModBus-TCP-адрес.
		u8 IPadr[4];		//"IP_Адрес" 6...9 IP-адрес.&IP_ADDR_DEFAULT&
		u8 ErrCod;			//"Код_ошибки1" 10
		u8 ErrCodFB;			// "код_ошибки2" 5 10
		u8 CRC_SP[2];		//"CRC_описания_СП" 12, 13 резерв 1.
		//bit(0) - ошибка общения с микросхемой Ethernet
		u8 IPmask[4];		//"Маска_IP" 14...17 IP-маска.&IP_MASK_DEFAULT&
		u8 Res2[4];		//"Debug" 18...21 резерв 2.
		u8 IPgate[4];		//"Шлюз" 22...25 IP-адрес шлюза.&IP_GATE_DEFAULT&
		u8 Res3[4];		//"Резерв" 26...29 резерв 3.
		u8 MACadr0[6];		//"MAC1" 30...35 MAC-адрес.
		u8 MACadr1[6];		//"MAC2" 36...41 резерв 4.
		// Текущее время.
		u8 Cnt1God;		//"Год" 42 год.
		u8 Cnt1Mes;		//"Месяц" 43 месяц.
		u8 Cnt1Den;		//"День" 44 день.
		u8 Cnt1Chas;		//"Час" 45 час.
		u8 Cnt1Min;		//"Минута" 46 минута.
		u8 Cnt1Sec;		//"Секунда" 47 секунда.
		u16 CmdReset;		//"Команда_сброса" 48-49 5300=Перезагрузка контроллера (RESET).
		u16 CmdFBUpd;		//"Команда_обн_конф" 50-51 5400=Обновить конфигурацию из буфера, 5401=Скопировать рабочую конфиг в буфер/надо?
		u16 CmdPrgUpd;		//"Команда_конца_загрузки" 52-53 Команда оканчания загрузки файла прошивки pswCmdModeBOOT 5500 pswCmdModeBOOTandUPD 5502
		u16 CmdFB;			//"Управление_конфигурацией" 54-55 5600=отключить,5601=включить исполнение ФБ, 5602=сохранить данные на карту(принудительно)
		u16 CmdCRC;			//"Команда_расчета_CRC" 56-57 5700=посчитать црц буфера конфигурации,5701=буфера прошивки-не реализовано.
		u16 FileCRC;		//"CRC_файла_прошивки" 58-59 CRC файла.
		u16 BaudCOM0;		//"Настройка_COM1" 60,61 скорость СОМ0. BitRateValue[] = {0-default,1-2400,2-4800,3-9600,4-14400,5-19200,6-28800,7-38400,8-56000,9-57600,10-76800,11-115200};
		u16 BaudCOM1;		//"Настройка_COM2" 62,63 скорость СОМ1.
		u16 BaudCOMIntBUS;		//"Настройка_INT_BUS" 64,65 скорость СОМIntBUS.
		u16 BaudCOMext;		//"Настройка_COM_EXT" 66,67 скорость СОМExt (GPRS).-записи нет
		u32 WhileTimer;	  // служебный регистр
		u32 ExtDeviceStatus; // "статус_подключенного_устройства"BIT(0) - connected device
#define CONNECTED_6LWP_RESIST BIT(0)
#define INJECTED_6LWP BIT(1)
#define SEND_REQUEST_6LWP BIT(2)
#define CHECK_23BP BIT(3)
#define CONNECTED_23BP BIT(4)
#define CONNECTED_RS485 BIT(5)
#define CONNECTED_6LWP BIT(6)
#define POWER_TRANSMIT_IS_SENDED BIT(7) 
#define CHANNEL_NUMBER_IS_SENDED BIT(8) 
		u8 local_network_ipadr[4];		//"IP_Адрес_6LoWPAN" IP-адрес 6lowpan подсети &LOCAL_IP_ADDR_DEFAULT&
		u8 local_network_ipmask[4];		//"Маска_IP_6LoWPAN" IP-маска 6lowpan подсети &LOCAL_IP_MASK_DEFAULT&
    u32 AddConfig_r;  // "Адрес_конфигурации"
    u32 AddUser_r;  // "Адрес_прошивки"
    u32 AddrSpaceToFlash_w; // "Адрес_области"
    u16 CRC_ConfigFile;//"CRC_всего_файла"
    u16 CRC_SP_File;//"CRC_сетевых_переменных"
		u16 SP_DynArcNum;//"Количество_архивируемых_СП"
		u32 SizeArcSpaceSP;//"Размер_Области_Арх_ОднойСП"
		u16 ConfigNumber; //количество параллельно исполняемых конфигураций
		u16 CurrentConfig;  //номер текущей конфигурации
		u16 Res6[7];		//резерв 6. Скорости доп.СОМов.
		u32 CntTOut;		//"Время_отключения"124...127 Время отключения запакованное.
		u32 CntDOut;		//"Дата_отключения" 128...131 Дата отключения запакованная.
		u32 lowpan_network_settings;	  // "Настройки_6LoWPAN" power dbm in range[7:22] and channel number [11:26]
	//[0] 66* 132-133 размер другой копии конфигурации(не активной)
	//[1] 67* 134-135 увеличивается, если ошибка при обращении с картой
		u16 FreeStackSize;	//"Резерв" 136-137 Размер свободного стека в байтах
		u16 RNSets;			//"Настройки_Radio_Near" 138-139 настройки ближнего радио 
    //D0-7-PowerRN,мощность передатчика ближнего радио.0 = +11 dB или 3 = +20 dB
		//D8-10 - ChannelRN, частотный канал ближнего радио. от 0 до 7
		//D11-15 - BaudRateRN, скорость ближнего радио. 1=2400, 2=4800, 3=9600, 4=19200, 5=38400

		u32 Freq1617[2];	//"Частота_скоростных_каналов" 140-143 и 144-147 Частота на спецвыходах 15 и 16
		u32 CntDI[LenNumDI];		//"Счетчики_цифровых_входов" 148-219 счтечики с 0 по 17 (18 шт)
		u16 SostDO;			//"Состояние_выходов" 220...221
		u16 ADCchan[4];		//"Состояние_аналоговых_входов" 222...229
		s16 TemperatureSD;	//"Температура"
		u32 OldDI;      	//"Предыдущее_состояние_DI"
		u32 SostDI;			//"Состояние-DI"
		u16 DIFilter;			//"Фильтр_DI" период опроса входов DI - для ликвидации дребезга по счетным входам
		u16 Res8[6];		//"Резерв"
		u16 KernelFlags;	//"Флаги_исполнения_конф"
// Статистика цикломашины ФБ
		u16 KernelFullTime;			//"Время_цикла_конф_(по100мкс)"
		u16 KernelClearTime;		//"Резерв"
		u16 KernelLoadVarsTime;		//"Резерв"
		u16 KernelSaveVarsTime;		//"Резерв"
// Статистика менеджера пакетов
		u16 IdlePaketsNum;			//"Принятых_пакетов"
		u16 TimeOutsNum;			//"Пакетов_с_истекшим_таймаутом"
		u16 BrakePaketsNum;			//
// Ресурсы памяти контроллера
		u16 MaxCfgSize;				//"Макс_размер_конфиг(исполняемая_часть)"
		u16 MaxPrgSize;				//"Макс_размер_прошивки"
		u16 MaxFB_RAMsize;			//"ОЗУ_переменных"
		u16 SaveFB_RAMsize;			//"ОЗУ_сохраняемое_во_флеш"
		u16 ArcR7_RecNum;			//"Архивов_на_странице"
		u32 regR7_Index;			//"Номер_последнего_архива" всегда номер последнего архива
// Параметры текущей конфигурации
		u16 CfgSize;		//"Размер_конфигурации"
		u16 CfgTWICommSize;		//"Резерв"
		u16 NetworkVariableNumber;			//"Кол-во_СП"
		u16 OwnNetworkVariableNumber;	  //"Кол-во_СП_собственных"


// Системные переменные
		u16 RazReset;		//"Перезагрузок"
		u16 ResetSource;		//"Причина_перезагрузок"
		u16 VersChip;		//"Версия_ПО"
		u16 User;		//"BootFlags"
	//D0 = 1 - User 0 - Boot
// Флаги ошибок
	//D0 NoCfgFile			Отсутствует файл конфигурации
	//D1 BadCfgFileCRC		Неправильная CRС файла конфигурации
	//D2 BadCfgFileLengths	Неправильные длины блоков файла конфигурации
	//D3 BadCodeFB			В файле конфигурации присутствуют неподдерживаемые типы ФБ
	//D4 BadRegAddr			В файле конфигурации присутствует доступ к области за пределами ОЗУ ФБ
	//D5 BadRegCode		(new)В конфигурации есть неподдерживаемый тип регистра
	//D6 BadRegType		(new)В конфигурации есть неподдерживаемый тип данных регистра
	//D7 BadSeq			(new)В конфигурации есть неверный порядок описания регистров ФБ
// Прочее
    u8 modbus_shift;    //смещение регистров модбас "0/1"
    u8 modbus_function_revers;    //перенаправление 3 и 4 функции 0 - норм,1 - инверсия
		u16 PMRecvQue[2];				//"Элементов_очереди_приема" Количество занятых элементов очереди приема
		u16 GMSKFFSKSet;			//"Настройка_дальнего_радио"
	// =0 - GMSK; =1 - FFSK замкнутого типа; =2 - FFSK разомкнутого типа
		u16 RF_mode;				//
		u16 FBCfgSize;		// 
		u16 FBkernelRate;		//"Кол-во_тактов_в_сек"
		u16 RegTimeOut[CHANNEL_NUMBER];  	//Секунд с прихода последней команды от мастера канала
		u16 Ethernetstatus;//
		Int64U GlobalTick;//
		sKernelEventFlags KernelEventFlags;//
		u32 ConfigTime;//
    u32 GuID[3];//
		u8 Slave1[12];       // "cлейв 1. Mac0+chan+adr" 
		u8 Slave2[12];       // "cлейв 2. Mac0+chan+adr" 
		u8 Slave3[12];       // "cлейв 3. Mac0+chan+adr" 
		u8 Slave4[12];       // "cлейв 4. Mac0+chan+adr" 
		u8 Slave5[12];       // "cлейв 5. Mac0+chan+adr" 
		u8 Slave6[12];       // "cлейв 6. Mac0+chan+adr" 
		u8 Slave7[12];       // "cлейв 7. Mac0+chan+adr" 
		u8 Slave8[12];       // "cлейв 8. Mac0+chan+adr" 
		u8 Slave9[12];       // "cлейв 9. Mac0+chan+adr" 
		u8 Slave10[12];       // "cлейв 10. Mac0+chan+adr" 
		u8 Slave11[12];       // "cлейв 11. Mac0+chan+adr" 
		u8 Slave12[12];       // "cлейв 12. Mac0+chan+adr" 
		u8 Slave13[12];       // "cлейв 13. Mac0+chan+adr" 
		u8 Slave14[12];       // "cлейв 14. Mac0+chan+adr" 
		u8 Slave15[12];       // "cлейв 15. Mac0+chan+adr" 
		u8 Slave16[12];       // "cлейв 16. Mac0+chan+adr" 
		u8 Slave17[12];       // "cлейв 17. Mac0+chan+adr" 
		u8 Slave18[12];       // "cлейв 18. Mac0+chan+adr" 
		u8 Slave19[12];       // "cлейв 19. Mac0+chan+adr" 
		u8 Slave20[12];       // "cлейв 20. Mac0+chan+adr" 
		u8 Slave21[12];       // "cлейв 21. Mac0+chan+adr" 
		u8 Slave22[12];       // "cлейв 22. Mac0+chan+adr" 
		u8 Slave23[12];       // "cлейв 23. Mac0+chan+adr" 
		u8 Slave24[12];       // "cлейв 24. Mac0+chan+adr" 
		u8 Slave25[12];       // "cлейв 25. Mac0+chan+adr" 
		u8 Slave26[12];       // "cлейв 26. Mac0+chan+adr" 
		u8 Slave27[12];       // "cлейв 27. Mac0+chan+adr" 
		u8 Slave28[12];       // "cлейв 28. Mac0+chan+adr" 
		u8 Slave29[12];       // "cлейв 29. Mac0+chan+adr" 
		u8 Slave30[12];       // "cлейв 30. Mac0+chan+adr" 
		u8 Slave31[12];       // "cлейв 31. Mac0+chan+adr" 
		u8 Slave32[12];       // "cлейв 32. Mac0+chan+adr" 
		u16 MapTable[32];       // "Таблица соответсвия номер в ФБ к номеру в таблице зар. слейвов." 
		u16 SlaveCount;		// "Количество слейвов в таблице зар. слейвов"
		u32 AdrArch;				//410 820...821 адрес запрашиваемого архива, ст. мл.
		u8 DataArch[64];			//412 824...887 данные архива, 64 байта.
		u32 AdrConfig;				//444 888...891 адрес области конфигурации, ст. мл.
		u8 DataConfig[64];			//446 892...953 данные конфигурации, 64 байта.
		u32 AdrFlash;				//478 956...959 адрес области ПО в SDcard, ст. мл.
		u8 DataFlash[64];			//480 960...1023 данные ПО в SDcard, 64 байта.
    u8 Buff[LOAD_BUFF_SIZE];       // "Буф_для_записи" 
    u16 link_err;   //количество ошибок соединения
    u16 etharp_err; //количество ошибок arp
    u16 etharp_cachinit;  // количество инициализации cach arp
    u16 ip_frag_err;  //количесвто ошибок при фрагментации ip
    u16 ip_err; // общее количество ошибок ip
    u16 icmp_err; //количество ошибок ICMP
    u16 udp_err;  //количество ошибок UDP
    u16 tcp_err;  //количество ошибок TCP
    u16 mem_max_used; //максимальное количество задействованной памяти
    u16 mem_err;  //ошибок работы с памятью
    u8 tcp_seg_use; //количество использованных сегментов TCP
    u8 tcp_seg_err; //количество ошибок выделения сегментов TCP
    u8 tcp_pcb_use; //количесвто выделенных блоков памяти для TCP 
    u8 tcp_pcb_err; //количество ошибок выделения блоков памяти для TCP 
    u8 arp_err; //количество ошибок работы стека ARP
    u8 pbuf_pool_err; //количество ошибок выделения памяти
    u8 pbuf_ref_err;  //количество ошибок при ссылке на выделеную память
    u8 tcp_listen_err;  //количество ошибок в приходящих пакетах
    u16 route_number; //количество маршрутов 
		u32 NumRecvPacket[CHANNEL_NUMBER];  //количество принятых пакетов по каналам
    u8 reserv_buff[RESERV_BUFF_SIZE];
	} vars;
#pragma pack(pop)
	u8 Bytes[cstMaxFB_RAMsize+MAX_KERNEL_NUMBER*sizeof(KernelInfo_t)];
}  FB32_type;		//Адресное пространство.
extern FB32_type FB32blok;
//not included for some self
#define FUNCTION_TIMER(timer,...)					\
		TIM5->CNT = 0;\
		timer = TIM5->CNT;\
		TIM5->CR1 |=BIT(TIM2_CEN);\
		__VA_ARGS__ ;\
		timer = TIM5->CNT;\

typedef union {
  struct {
    u8 uint8_low;
    u8 uint8_high;
  }uint8;
	u16 uint16;
} uint8_16;

//Батарейный домен
//2051 байт используется для очереди архивов
//следующие 512 байт используются для энергонезависимой памяти FB32 используется в блоках 84 и 85
#define MAX_BAT_MEM_SIZE	256
extern u32 BateryMemFB32[];
#define cstTimeCOM	20
extern vu8 RxOn; // Флаг для включения приема после передачи
//=== СОМ0 - основной порт UART4 ===//
#define COM0	0
#define	CLK0	(MCLK/4)		// Clock
#define	Baud0	115200			// USART4 baud-rate.
extern vu8 CntTimeRxD0;		// Счетчик таймаута.
#define cstCOM0Shift 	6
extern vu8 COM_mode;
	//b0 - 
  //b4=1 - Пошел (но не ушел) последний байт через COMext.
  //b5=1 - Пошел (но не ушел) последний байт через COM1.
	//b6=1 - Пошел (но не ушел) последний байт через COMIntBUS.
	//b7=1 - Пошел (но не ушел) последний байт через СОМ0.

//=== СОМ1 - второй порт USART1 ===//
#define COM1	1
#define	CLK1	(MCLK/2)		// Clock
#define	Baud1	115200			// USART1 baud-rate.
extern vu8 CntTimeRxD1;		// Счетчик таймаута.
#define cstCOM1Shift 	6

extern vu8 SizeCOM1;		// Размер пакета по СОМ1.

//=== IntBUS - внешний порт USART6 ===//
#define COMIntBUS		2
#define	CLKIntBUS		(MCLK/2)		// Clock
#define	BaudIntBUS		(115200*15)			// USART6 baud-rate.
extern vu8 CntTimeRxDIntBUS;		// Счетчик таймаута.
#define cstCOMIntBUSShift 	4


//=== СОМext - дополнительный порт USART2 для расширений ===//
#define COMext	3
#define	CLKext	(MCLK/4)		// Clock
#define	Baudext	(115200)			// USART2 baud-rate.
extern vu8 CntTimeRxDext;		// Счетчик таймаута.
#define cstCOMExtShift 	6
extern vu8 PackInCOMext[];
extern vu8 PackOutCOMext[];

//=== COMrfm23 - дополнительный порт USART2 для расширений ===//
#define COMext_rfm23	4

//=== Радио дальнее ===//
extern vu16 RF_mode; // Режим работы Радио.
//b0...1 - =0 - перед передачей/приемом синхропробела, =1 -
// =3 - закончился синхропробел, начались передача/прием данных.
//b2=1 - конец передачи, выдать среднее значение в Радио.
//b3 - для GMSK:=1 - будет значимый перепад, =0 - будет незначимый перепад.
//b3 - для FFSK:=1 - принят уровень "H", =0 - принят уровень "L".
//b4=1 - идет передача бита модуляции GMSK.
//b5=1 - идет задержка перед передачей.
//b6=1 - идет передача в Радио.
//b7=1 - выдать пакет в Радио.
//b8=0 - принят пакет RTM64. =1 - неRTM.
//b9=1 - var-пакет.
//b10=0 - выдавать восходящий перепад, =1 - выдавать нисходящий перепад модуляции 4-FSK.
extern vu8 RF_PakCnt;		// Указатель принятого байта в приемный буфер.
extern uc16 MassUp[];		// Массив восходящей полусинусоиды 32 точки.
extern uc16 MassDown[];		// Массив нисходящей полусинусоиды 32 точки.
extern uc16 MassLow[];		// Массив низкого уровня 32 точки.
extern uc16 MassHigh[];		// Массив высокого уровня 32 точки.
extern uc16 MassEnd[];		// Массив среднего уровня 32 точки.
extern uc16 Mass12Sin[];		// Массив полусинусоиды верхней 32 точки.
extern uc16 Mass12SinNeg[];		// Массив полусинусоиды нижней 32 точки.
extern uc16 Mass24Sin[];		// Массив синусоиды 2400 Гц положительной 32 точки.
extern uc16 Mass24SinNeg[];		// Массив синусоиды 2400 Гц отрицательной 32 точки.
extern uc16 Mass36Sin[];		// Массив синусоиды 3600 Гц положительной 32 точки.
extern uc16 Mass36SinNeg[];		// Массив синусоиды 3600 Гц отрицательной 32 точки.
#define cstDelayRF	50		// Длительность задержки перед передачей в Радио - 100.
extern vu16 CntDelay;		// Длительность задержки перед передачей/длительность битового уровня при приеме.
extern vu8 Bit_mode;		// Режим выдачи полусинусоид.
	//b0...1 - для GMSK: 00 - низкий уровень, 01 - восходящий перепад, 10 - нисходящий перепад, 11 - высокий уровень.
	//b0...1 - для FFSK: 00 - верхняя полусинус, 01 - нижняя полусинус, 10 - положит.синусоида, 11 - отрицат.синусоида.
	//b2...b7 - не использовать.
	// При приеме - номер принятой полусинусоиды.
extern vu8 RF_iBit;		// Счетчик выданных/принятых битов.
extern vu8 RF_LastBit;		// Предыдущий выданный/принятый бит или счетчик битов до стаффинга для FFSK.
extern vu16 RF_Reg;		// Регистр приема.
#define	BaudRF	9600		// UART baud-rate - 9600.
#define HalfT0	MCLK/(4*BaudRF)		// Длительность перепада =3125 для модуляции GMSK.
extern vu16 CntDefen;		// Счетчик для ограничения длительности передачи.
#define	MaxDefen	2000		// Максимальная допустимая длительность передачи мсек.


//=== Радио ближнее ===//
#define cstDelayRN	3		// 3 мсек - задержка перед передачей в ближнее Радио.
#define cstChannelRN	1		// Частотный канал ближнего Радио по умолчанию.
#define cstBaudRateRN	4		// Скорость ближнего Радио по умолчанию.
#define cstPowerRN		3		// Мощность выходная ближнего Радио по умолчанию.

//=== SPI для ближнего Радио ===//
#define cstSPI		4		// 2 - Длина блока данных в SPI.
extern vu8 BufFromSPI[], Buf2SPI[];
extern vu8 CntByteSPI;		// Счетчик отправленных слов.
extern vu8 PtrByteSPI;		// Указатель переданного байта.
extern vu8 TimeSPI;		// Счетчик ожидания ответа по SPI.
extern vu16 CntDefenRN;	
extern vu16 CntDelayRN;
extern vu16 SPI_mode;		// 
	//b0=1 - длина пакета более 60 байт.
	//b1=1 - идет задержка перед передачей.
	//b2=1 - принят пакет RTM64. =0 - неRTM.
	//b3=1 - var-пакет.
	//b4=1 - есть устройство Радио.
	//b5=1 - передать пакет в Радио.
	//b6=1 - включить передачу.
	//b7=1 - заняли канал.
	//b8=0 - работа с ближним Радио.
//=== SPI FLASH ===//
#define SPIFLASHSIZE 280
extern vu8 BufFromSPI_FLASH[];
extern vu8 Buf2SPI_FLASH[];
extern vu8 TimeSPI_FLASH;
extern vu16 SPI_mode_FLASH;
extern vu16 CntByteSPI_FLASH;
extern vu16 PtrByteSPI_FLASH;
#define SetSPIIE_FLASH()      (SPI1->CR2 |=BIT(SPI_RXNEIE))           // Разрешить прерывание RX.
#define ResetSPIIE_FLASH()    (SPI1->CR2 &= ~BIT(SPI_RXNEIE))         // Запретить прерывание RX.

#define cstSizeRN		32		// Максимальный размер посылки, байтов данных. К ним добавляются спереди 2 байта, сзади CRC 2 байта.
// Посылка более cstSizeRN байт разбивается на пакеты по cstSizeRN байт, не более 64 пакетов.
extern vu8 SizeRN;		// Количество посылок в пакете (первый байт посылки).
extern vu8 NumRN;		// Номер посылки в пакете (второй байт посылки).
extern vu8 LenRN;		// Длина посылки на прием/передачу.
extern vu8 Radio_RSSI;		// Уровень принятого сигнала.

#define SetSPIIE()	(SPI3->CR2 |=BIT(SPI_RXNEIE))		// Разрешить прерывание RX.
#define ResetSPIIE()	(SPI3->CR2 &= ~BIT(SPI_RXNEIE))		// Запретить прерывание RX.

//=== RFM23 на плату расширения ===//
extern vu8 BufFromRFM23[], Buf2RFM23[];
extern vu8 CntByteRFM23;		// Счетчик отправленных слов.
extern vu8 PtrByteRFM23;		// Указатель переданного байта.
extern vu16 CntDefenRN23;	
extern vu16 CntDelayRN23;
extern vu16 RFM23_mode;	

extern vu8 SizeRN23;		// Количество посылок в пакете (первый байт посылки).
extern vu8 NumRN23;		// Номер посылки в пакете (второй байт посылки).
extern vu16 LenRN23;		// Длина посылки на прием/передачу.
extern vu8 Radio_RSSI23;		// Уровень принятого сигнала.

#define SetUSART2IE()	(USART2->CR1 |=BIT(USART_TCIE))		// Разрешить прерывание RX.TCIE
#define ResetUSART2IE()	(USART2->CR1 &= ~BIT(USART_TCIE))		// Запретить прерывание RX.

//=== Таймер ===//
extern vu8 SendPakFB;
extern vu8 Cnt100mkSec;		// Счетчик по 100 мксек.
extern vu8 Cnt10mSec;		// Счетчик по 10 мсек.
extern vu8 Cnt100mSec;		// Счетчик по 100 мсек.
extern vu8 Cnt1Sec;		// Старое значение счетчика.
extern vu8 Cnt1Min;		// Старое значение счетчика.
extern vu8 Cnt1Hour;		// Старое значение счетчика.
extern vu8 Cnt1DenOld;		// Старое значение счетчика.
extern vu8 Cnt1MesOld;		// Старое значение счетчика.
extern vu8 Cnt1GodOld;		// Старое значение счетчика.
extern vu16 FlTime;		// Флаги временных событий.
	//b0=1 - надо записать время в RTC.
	//b1=1 - 100 мсек.
	//b2=1 - 1 сек.
	//b3=1 - 1 мин.
	//b4=1 - 1 час.
	//b5=1 - 1 день.
	//b6=1 - 10 мсек.
	//b7=1 - время синхронизировано.
  //b8=1 - 1 мс
	//b9=1 - была синхронизация времени широковещательная
	//b10=1 - начать регистрацию у мастера канала
	//b11=1 - 1/64 сек
extern vs16 CntLedPaket, CntLedOtvet, CntLedError, CntLedTest;		// Счетчик действия светодиода.
extern u32 cntSecFromStart;		// Счетчик секунд со старта для измерения задержек
extern vu8 cntSecFromReset;		// Через сколько секунд перезагрузить контроллер
extern vu8 cntSecFromUpdateCfg; // Через сколько секунд начать обновление конфигурации
#define Reset_MCU(i)	(cntSecFromReset=i+1)		// Рестарт через n сек
#define Update_Cfg(i)	(cntSecFromUpdateCfg=i+1)		// Рестарт через n сек
#define GoritLed	50		// 50*1 мсек.

//=== АЦП и ЦАП ===//
extern vu16 ADCchanTSD;
#define cstADCbuf	4		// Количество каналов ADC.
#define cstADCdel	25.0		// Делитель для осреднения.
extern vu8 ADC_mode;		// Режимы работы АЦП.
	//D0=1 - 
	//D5=1 - 
	//D6=1 - 
	//D7=1 - 

//=== AI, DI, DO ===//
extern vu8 NumDI;		// номер тестируемого канала(мл), номер в буфере(ст).
extern vu32 CntDI[];		// Промежуточное значение счетчиков DI.
extern vu16 DIFilterCNT;	
extern vu16 IC3ReadValue1, IC3ReadValue2;
extern vu8 IC3CaptureNumber;
extern vu32 IC3Capture;
extern vu16 IC3UpG;			// Счетчик переполнения таймера для 3 канала capture
extern vu16 IC4ReadValue1, IC4ReadValue2;
extern vu8 IC4CaptureNumber;
extern vu32 IC4Capture;
extern vu16 IC4UpG;			// Счетчик переполнения таймера для 4 канала capture

//=== Переменные для ModBus ===//
extern vu8 modbus;		// Длительность ожидания ответа от ModBus-устройства в тиках по 0,1 сек.
//lwip
extern vu32 LocalTime;
//=== Общие ===//
extern vu16 TestShort[];
extern vu32 TestInt[];		// Временный.
extern vs8 Temperature;		// Температура знаковая.
extern vu32 DItest;
extern u32 ArchArea_Size;
extern u32 ARC_R7_MAXNUM;
extern vu8 Sln[]; // Массив номеров слейвов которые в структуре слейвов

//extern uc8 M1[];		// Текущая версия прошивки.
extern uc8 M2[];		// Закодированное слово "ИНТЕК".
extern vu8 NPmw;
extern vu8 nsc;
extern vu8 TimetoChan;
extern vu8 Var1;
extern vu8 Var2;
extern vu8 Var3;
extern vu8 Var4;
extern vu8 Var5;
extern vu32 Tick[];
extern Int64U CountTick;
extern u16 time_interval;
//_________ПАКЕТ___________


//main.c

#endif
