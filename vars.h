#define CHANNEL_NUMBER 9
#ifndef _vars_h
#define _vars_h

#include "kernel.h"

//---DEFINE
#define RAM_START	0x20000000		// ������ ������� ���.
#define RAM_END		0x2001B3D4
#define STACK_TOP	0x2001C000		// ���� ����� � 0x2001C000 - 112 KB.
#define cstPrgSize		((USER_END>>10)-(USER_START>>10))		//(0x08060000-0x08010000)>>10;256� // ������������ ������ ����� ��������
#define BOOT_START	0x08000000		// ������ ������� Boot. ������ 96�.
#if debug_mega
  #define USER_START		0x08000000		// ������ ������� User. ������ 416�.
#else
  #define USER_START    0x08020000    // ������ ������� User. ������ 256�.
#endif
#define USER_END      0x08060000    // ����� ������� User. ������ 256�.
#define SP_START      0x08060000    // ������ ������� �������� ������� ����������. ������ 128�.
#define SP_END      0x08080000    // ����� ������� �������� ������� ����������. ������ 128�.
#define OPT_START	0x1FFFC000		// ������ ������� ������������ ������.
#define UNIQUEID	0x1FFF7A10		// ���������� 96 ������ ID.
#define KEY1	0x45670123		// ���� KEY1.
#define KEY2	0xCDEF89AB		// ���� KEY2.
#define OPTKEY1	0x08192A3B		// ���� OPTKEY1.
#define OPTKEY2	0x4C5D6E7F		// ���� OPTKEY2.
#define MCLK		120000000		// ������� ���������.
//=== ���������
#define	cstVer		1		// ������ �������� (����).
#define	cstMyAdr	3		// ����� (0...4095).
#define cstMyAdrMB	3
#define	cstIsSvjaznoj		0
#define	cstLINX_ON	1		//D0=1-COM1, D0=0-COM0; D1=1- �� ����.�/��, D2=1-�� �����.�/��.
#define	ChipTipe	4		// =1 - 8 �����, =2 - 32 ������, =3 - 128 �����, =4 - 512 �����, =5 - 256 �����.
#define LenNumDI 18
#define SIZE_CRC16 2
#define SIZE_CRC32 4
//=== ������ ===//
//=== Port PA ===//
//���� ������ �������������� ��� ���������� � ����� � FB32blok.vars.ADCchan[]
#define CS_FLASH_2  0		// Flash 2 w25q64hv
#define ETH_REFCLK	1		// ���� ������������ Ethernet
#define ETH_MDIO		2		// ����� ����� MDIO Ethernet
#define AINRADIO	  3		// ���� ADC1 (ADC123_IN3) ��� �������� ����� AIN4.
#define DACOUT1		  4		// ����� DAC1 ��� �������� �����.
#define SCK_FLASH		5		// �������� ��� ������ � ����������� ������ SPI1
#define MISO_FLASH	6		// Data input from flash M25PE16 SPI1
#define ETH_CRS   	7		// 
#define LEDOTVET  	8		// ����� LEDOTVET.
#define TXD1	      9		// ����� USART2_Tx - COM1.
#define RXD1	      10		// ����  USART2_Rx - COM1.
#define DI9     		11		// Digital input 9, init requare
#define DI10    		12		// Digital input 10, init requare
//#define SWD    		13		// Digital input 11, init requare
//#define SWCLK    		14		// Digital input 12, init requare
#define WR485_0		  15		// ����� ���������� ��������� ���1.
//=== Port PB ===//
#define AIN3  		0		// ���� ������ ADC3 (ADC123_IN0).
#define DI8		    1		// Digital input 8, init requare
#define SCK_RN		3		// ����� SPI3_SCK ������� ����������.
#define MISO_RN		4		// ���� SPI3_MISO ������� ����������.
#define MOSI_FLASH 5		//Data output to flash M25PE16  SPI1
#define GPRS_SCL 	6		// NSEL RFM23BP
#define GPRS_SDA_ 	7		// IRQ RFM23BP
#define DI17    	8		// Digital input 17, init requare
#define DI18    	9		// Digital input 18, init requare
#define ETHRXER		10		// ���� RxER Ethernet
#define ETHTXEN		11		// ����� TxEN Ethernet.
#define ETHTXD0		12		// ����� TxD0 Ethernet.
#define ETHTXD1		13		// ����� TxD1 Ethernet.
#define DI11      14   // Digital input 17, init requare
#define DI12      15   // Digital input 18, init requare
//=== Port PC ===//
#define AIN0		0		// ���� ������ ADC0 (ADC123_IN10).
#define ETHMDC		1		// ����� ����� MDC Ethernet.
#define AIN1		2		// ���� ������ ADC1 (ADC123_IN12).
#define AIN2		3		// ���� ������ ADC2 (ADC123_IN13).
#define ETH_RX0 4		// 
#define ETH_RX1 5		// 
#define TXD2		6		// ����� USART6_Tx - ���������.
#define RXD2		7		// ���� USART6_Rx - ���������.
#define CS_FLASH	8		// Cheep select M25PE16.
#define ETH_INTRP 9		// intrp  Ethernet.
#define TXD0		10		// ����� UART4_Tx - COM0.
#define RXD0		11		// ���� UART4_Rx - COM0.
#define MOSI_RN		12		// ����� SPI3_MOSI ������� ����������.
#define GPIO0_RN		13		// ���� GPIO0_RN �������� �����.
#define OSC32in		14		// ���� OSC32.
#define OSC32out	15		// ����� OSC32.
//=== Port PD ===//
#define GPRS_IO1  0   //
#define GPRS_IO2  1   //
#define GPRS_IO3  2   //
#define DI13      3   //
#define DI14      4   //
#define USART_TXD_X19      5   //
#define USART_RXD_X19      6   //
#define USART_CLK_X19      7   //
#define LEDTEST		8		// ����� LEDTEST.
#define LedPaket	9		// ����� LedPaket.
#define PTT			10		// ����� ���������� ��������� �������� �����.
#define WR485_2		11		// ����� ���������� ��������� ���2.
#define OUTDO2		12		// ����� DO2.	AF2 TIM4_CH1
#define OUTDO1		13		// ����� DO1.	AF2 TIM4_CH2
#define OUTDO0		14		// ����� DO0.	AF2 TIM4_CH3
#define OUTDO3		15		// ����� DO3.
//=== Port PE ===//
#define DI6   	0		// ����� ��������� ������� ���-������ 0 � 1.
#define DI7 		1		// ���� ������ JMP2.
#define IE_DI		2		// ����� ���������� DI1...16.
#define CS_RN		3		// ����� ������ CS ������� ����������.
#define IRQ_RN		4		// ���� IRQ ������� ����������.
#define DI1   	5		// Digital input 1, init requare
#define DI2   	6		// Digital input 2, init requare
#define TxAnt_RN		7		// ����� TxAnt ������� ����������.
#define RxAnt_RN		8		// ����� RxAnt ������� ����������.
#define DI3   	9		// Digital input 3, init requare
#define DI4   	10		// Digital input 4, init requare
#define DI5   	11		// Digital input 5, init requare
#define LEDERROR	12		// ����� LEDERROR.
#define DI16_FAST 		13		//
#define DI15_FAST 		14		//
#define JMP1		15		// ���� ������ JMP1.
//GPRS
#define OnPWRK() (GPIOE->BSRR=(BIT(LEDERROR) << 16))
#define OffPWRK() (GPIOE->BSRR=(BIT(LEDERROR) << 16))

/// ������� �����.
#define SetCS_RN()		(GPIOE->BSRR=(BIT(CS_RN) << 16))		// ������� NSS->L.
#define ResetCS_RN()	(GPIOE->BSRR=BIT(CS_RN))		// ��������� NSS->H.

/// ����� RFM23.
#define SetCS_RFM23()		(GPIOB->BSRR=(BIT(GPRS_SCL) << 16))		// ������� NSS->L.
#define ResetCS_RFM23()	(GPIOB->BSRR=BIT(GPRS_SCL))		// ��������� NSS->H.

//#define SetSCK_RN()	(GPIOB->BSRR=BIT(SCK_RN))		// ��������� SCK_RN.
#define SetAntTx()	(GPIOE->BSRR=(BIT(RxAnt_RN)<<16)+BIT(TxAnt_RN))		// ����� RXANT � ���������� TXANT.
#define SetAntRx()	(GPIOE->BSRR=(BIT(TxAnt_RN)<<16)+BIT(RxAnt_RN))		// ����� TXANT � ���������� RXANT.

/// ������� �����. RFM23BP
//#define SetCS_RN()		(GPIOB->BSRR=(BIT(GPRS_SCL) << 16))		// ������� NSS->L.
//#define ResetCS_RN()	(GPIOB->BSRR=BIT(GPRS_SCL))		// ��������� NSS->H.

// FLASH.
#define SetCS_FLASH()		(GPIOC->BSRR=(BIT(CS_FLASH) << 16))		// ������� SD->L.
#define ResetCS_FLASH()	(GPIOC->BSRR=BIT(CS_FLASH))		// ��������� SD->H.
// FLASH2.
#define SetCS_FLASH_2()		(GPIOA->BSRR=(BIT(CS_FLASH_2) << 16))		// ������� SD->L.
#define ResetCS_FLASH_2()	(GPIOA->BSRR=BIT(CS_FLASH_2))		// ��������� SD->H.

// ������� �����.
#define SetPTT()		(GPIOD->BSRR = BIT(PTT))					// ��������� PTT.
#define ResetPTT()		(GPIOD->BSRR = (BIT(PTT) << 16))			// ����� PTT.

#define RS485On()		(GPIOA->BSRR=BIT(WR485_0))		// ��������� �������� RS485_0.
#define RS485Off()		(GPIOA->BSRR=(BIT(WR485_0)<<16))		// ����� �������� RS485_0.
#define RS485_2On()	(GPIOD->BSRR=BIT(WR485_2))		// ��������� �������� RS485_2.
#define RS485_2Off()	(GPIOD->BSRR=(BIT(WR485_2) << 16))		// ����� �������� RS485_2.
#define RS485_ExtOn()	(GPIOD->BSRR=BIT(USART_CLK_X19))		// ��������� �������� RS485_2.
#define RS485_ExtOff()	(GPIOD->BSRR=(BIT(USART_CLK_X19) << 16))		// ����� �������� RS485_2.

#define LedPaketOff()	(GPIOD->BSRR = (BIT(LedPaket) << 16))	 	// ���������� LedPaket.
#define LedOtvetOff()	(GPIOA->BSRR = (BIT(LEDOTVET) << 16))	 	// ���������� LEDOTVET.
#define LedErrorOff()	(GPIOE->BSRR = (BIT(LEDERROR) << 16))	 	// ���������� LEDERROR.
#define LedTestOff()	(GPIOD->BSRR = (BIT(LEDTEST) << 16))	 	// ���������� LEDTEST.
// �������� �����.
#define SetTest6()		(GPIOE->BSRR = BIT(PINTEST6))		// ��������� PINTEST6.
#define ResetTest6()	(GPIOE->BSRR = (BIT(PINTEST6) << 16))		// ����� PINTEST6.
#define _PORTE(i) (*((__O unsigned long *) (PERIPH_BB_BASE + ((GPIOE_BASE+0x0C-PERIPH_BASE) * 0x20) + (i*4)))) // Bit Bang ������

//=== ������ � BKPSRAM ===//
// ������� �� RTC_BKP - ��������������� �������, 20 ����.
//!!!������������� ���������, ��������, �������������� � �������������� ������
	// RTC->BK0R	- ���������������� ����.
		//D0...D7 - ResetSource, ������� ������������ - bit0-OBL,bit1-pinRST,bit2-POR,bit3-SWR,bit4-IWDG,bit5-WWDG,bit6-LPRST.
		//D9...8 - ������.
		//D10 = 1 - ���������� �� �� SDcard � User_Flash.
		//D11 = 0 - User-��������� ��� �� �����������.
		//D12 = 1 - User-��������� ��������.
		//D13 - ��������� �������.
		//D14 = 1 - IsSvjaznoj.
		//D15 - Boot=1 - �������� �� User-���������, =0 - �� Boot-���������.
		//D16...D23 - ModbusRTU �����
		//D24..D31 - ���������������
	// RTC->BK1R	- (D0...D11) MyAdr, (D12-15 ������ ���� 0) (D16...D31) ���������� ������������.
	// RTC->BK2R	- (D0...D15) RFDelay, �������� ��� �������� �����, (D16...D31) RNDelay, �������� ��� �������� �����.
	// RTC->BK3R	- BKP_CS - ����������� ����������� ����� ������������ �����������.
	// RTC->BK4R	- ����� �������� ������ �� �����
		//D0..15 - ����� ������� � ������� ��
		//D16..D31 - ������
	// RTC->BK5R	- ����� ��������� ���������� �������� ������ (������ ��������� ������ � ����� = ���-�� ������� � ������)
	// RTC->BK6R	- ����� ����������.
	// RTC->BK7R	- ���� ����������.
	// RTC->BK8R	- RadioNear, ������� �������� �����.
		//D0-7 - PowerRN, �������� ����������� �������� �����. 0 = +11 dB ��� 3 = +20 dB
		//D8-10 - ChannelRN, ��������� ����� �������� �����. �� 1 �� 4, ������������ BaudRateRN = 4
		//D11-15 - BaudRateRN, �������� �������� �����. 0=1200, 1=2400, 2=4800, 3=9600, 4=19200, 5=38400, �������� ������ 4 ��� 2
	// RTC->BK9R - D<31..1> ���������������; D<0> ��������� �������� ����� =0 - GMSK; =1 - FFSK ���������� ����; =2 - FFSK ������������ ����
	// RTC->BK10R - D<31...24> - Baudext GPRS, D<23...16> - Baud_COM1, D<15...8> - Baud_COM1, D<7...0> - Baud_COM0.
	// RTC->BK11R - ����� SD �����, ��� ������������ ������� ����� �����
	// RTC->BK12R - D<31..8> ��������������� D<7..0> = ������ ������ ������ DI � ����
	// RTC->BK13R - D0 - ����������� �������, ������������������� ������� �������.
	// RTC->BK14R - ���������������
	// RTC->BK15R - ���������������
	// RTC->BK16R - ���������������
	// RTC->BK17R - ���������������
	// RTC->BK18R - ���������������
	// RTC->BK19R - ���������������	
extern vu16 CSuserPrg;		// ����������� �����.
extern vu16 NumBlock;		// ����� ������������� �����.
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

//=== ����� ��� ��32 ===//
// ���������� ����� ��������� ������ ��� ��32.
#define LOAD_BUFF_SIZE 256
#define RESERV_BUFF_SIZE 190
#define OWN_VARIABLE_BLOK_SIZE	(1024 + 256 + 256)		// ������ ��������� - 1024 ����.
#define LenNumDI	18		// ���������� ������ DI.
extern vu8 SuperMaster; // ��� � ���� ����������� �� 103

typedef union{		// ����������� ��������� � �������.
#pragma pack(push)
#pragma pack(1)
	  struct {		// ��������� ����������� ������
		u16 MyAdr;			//"�����_RTM" 0, 1 RTM64-�����.(� ������� ���� - "�������")
		u16 MyAdrMB;		//"�����_Modbus" 2, 3 ModBus-�����.(+ ��������� ����, �� �� ������������)
		u16 Rezerv;		//"Rezerv" 4, 5 there was ModBus-TCP-�����.
		u8 IPadr[4];		//"IP_�����" 6...9 IP-�����.&IP_ADDR_DEFAULT&
		u8 ErrCod;			//"���_������1" 10
		u8 ErrCodFB;			// "���_������2" 5 10
		u8 CRC_SP[2];		//"CRC_��������_��" 12, 13 ������ 1.
		//bit(0) - ������ ������� � ����������� Ethernet
		u8 IPmask[4];		//"�����_IP" 14...17 IP-�����.&IP_MASK_DEFAULT&
		u8 Res2[4];		//"Debug" 18...21 ������ 2.
		u8 IPgate[4];		//"����" 22...25 IP-����� �����.&IP_GATE_DEFAULT&
		u8 Res3[4];		//"������" 26...29 ������ 3.
		u8 MACadr0[6];		//"MAC1" 30...35 MAC-�����.
		u8 MACadr1[6];		//"MAC2" 36...41 ������ 4.
		// ������� �����.
		u8 Cnt1God;		//"���" 42 ���.
		u8 Cnt1Mes;		//"�����" 43 �����.
		u8 Cnt1Den;		//"����" 44 ����.
		u8 Cnt1Chas;		//"���" 45 ���.
		u8 Cnt1Min;		//"������" 46 ������.
		u8 Cnt1Sec;		//"�������" 47 �������.
		u16 CmdReset;		//"�������_������" 48-49 5300=������������ ����������� (RESET).
		u16 CmdFBUpd;		//"�������_���_����" 50-51 5400=�������� ������������ �� ������, 5401=����������� ������� ������ � �����/����?
		u16 CmdPrgUpd;		//"�������_�����_��������" 52-53 ������� ��������� �������� ����� �������� pswCmdModeBOOT 5500 pswCmdModeBOOTandUPD 5502
		u16 CmdFB;			//"����������_�������������" 54-55 5600=���������,5601=�������� ���������� ��, 5602=��������� ������ �� �����(�������������)
		u16 CmdCRC;			//"�������_�������_CRC" 56-57 5700=��������� ��� ������ ������������,5701=������ ��������-�� �����������.
		u16 FileCRC;		//"CRC_�����_��������" 58-59 CRC �����.
		u16 BaudCOM0;		//"���������_COM1" 60,61 �������� ���0. BitRateValue[] = {0-default,1-2400,2-4800,3-9600,4-14400,5-19200,6-28800,7-38400,8-56000,9-57600,10-76800,11-115200};
		u16 BaudCOM1;		//"���������_COM2" 62,63 �������� ���1.
		u16 BaudCOMIntBUS;		//"���������_INT_BUS" 64,65 �������� ���IntBUS.
		u16 BaudCOMext;		//"���������_COM_EXT" 66,67 �������� ���Ext (GPRS).-������ ���
		u32 WhileTimer;	  // ��������� �������
		u32 ExtDeviceStatus; // "������_�������������_����������"BIT(0) - connected device
#define CONNECTED_6LWP_RESIST BIT(0)
#define INJECTED_6LWP BIT(1)
#define SEND_REQUEST_6LWP BIT(2)
#define CHECK_23BP BIT(3)
#define CONNECTED_23BP BIT(4)
#define CONNECTED_RS485 BIT(5)
#define CONNECTED_6LWP BIT(6)
#define POWER_TRANSMIT_IS_SENDED BIT(7) 
#define CHANNEL_NUMBER_IS_SENDED BIT(8) 
		u8 local_network_ipadr[4];		//"IP_�����_6LoWPAN" IP-����� 6lowpan ������� &LOCAL_IP_ADDR_DEFAULT&
		u8 local_network_ipmask[4];		//"�����_IP_6LoWPAN" IP-����� 6lowpan ������� &LOCAL_IP_MASK_DEFAULT&
    u32 AddConfig_r;  // "�����_������������"
    u32 AddUser_r;  // "�����_��������"
    u32 AddrSpaceToFlash_w; // "�����_�������"
    u16 CRC_ConfigFile;//"CRC_�����_�����"
    u16 CRC_SP_File;//"CRC_�������_����������"
		u16 SP_DynArcNum;//"����������_������������_��"
		u32 SizeArcSpaceSP;//"������_�������_���_�������"
		u16 ConfigNumber; //���������� ����������� ����������� ������������
		u16 CurrentConfig;  //����� ������� ������������
		u16 Res6[7];		//������ 6. �������� ���.�����.
		u32 CntTOut;		//"�����_����������"124...127 ����� ���������� ������������.
		u32 CntDOut;		//"����_����������" 128...131 ���� ���������� ������������.
		u32 lowpan_network_settings;	  // "���������_6LoWPAN" power dbm in range[7:22] and channel number [11:26]
	//[0] 66* 132-133 ������ ������ ����� ������������(�� ��������)
	//[1] 67* 134-135 �������������, ���� ������ ��� ��������� � ������
		u16 FreeStackSize;	//"������" 136-137 ������ ���������� ����� � ������
		u16 RNSets;			//"���������_Radio_Near" 138-139 ��������� �������� ����� 
    //D0-7-PowerRN,�������� ����������� �������� �����.0 = +11 dB ��� 3 = +20 dB
		//D8-10 - ChannelRN, ��������� ����� �������� �����. �� 0 �� 7
		//D11-15 - BaudRateRN, �������� �������� �����. 1=2400, 2=4800, 3=9600, 4=19200, 5=38400

		u32 Freq1617[2];	//"�������_����������_�������" 140-143 � 144-147 ������� �� ����������� 15 � 16
		u32 CntDI[LenNumDI];		//"��������_��������_������" 148-219 �������� � 0 �� 17 (18 ��)
		u16 SostDO;			//"���������_�������" 220...221
		u16 ADCchan[4];		//"���������_����������_������" 222...229
		s16 TemperatureSD;	//"�����������"
		u32 OldDI;      	//"����������_���������_DI"
		u32 SostDI;			//"���������-DI"
		u16 DIFilter;			//"������_DI" ������ ������ ������ DI - ��� ���������� �������� �� ������� ������
		u16 Res8[6];		//"������"
		u16 KernelFlags;	//"�����_����������_����"
// ���������� ����������� ��
		u16 KernelFullTime;			//"�����_�����_����_(��100���)"
		u16 KernelClearTime;		//"������"
		u16 KernelLoadVarsTime;		//"������"
		u16 KernelSaveVarsTime;		//"������"
// ���������� ��������� �������
		u16 IdlePaketsNum;			//"��������_�������"
		u16 TimeOutsNum;			//"�������_�_��������_���������"
		u16 BrakePaketsNum;			//
// ������� ������ �����������
		u16 MaxCfgSize;				//"����_������_������(�����������_�����)"
		u16 MaxPrgSize;				//"����_������_��������"
		u16 MaxFB_RAMsize;			//"���_����������"
		u16 SaveFB_RAMsize;			//"���_�����������_��_����"
		u16 ArcR7_RecNum;			//"�������_��_��������"
		u32 regR7_Index;			//"�����_����������_������" ������ ����� ���������� ������
// ��������� ������� ������������
		u16 CfgSize;		//"������_������������"
		u16 CfgTWICommSize;		//"������"
		u16 NetworkVariableNumber;			//"���-��_��"
		u16 OwnNetworkVariableNumber;	  //"���-��_��_�����������"


// ��������� ����������
		u16 RazReset;		//"������������"
		u16 ResetSource;		//"�������_������������"
		u16 VersChip;		//"������_��"
		u16 User;		//"BootFlags"
	//D0 = 1 - User 0 - Boot
// ����� ������
	//D0 NoCfgFile			����������� ���� ������������
	//D1 BadCfgFileCRC		������������ CR� ����� ������������
	//D2 BadCfgFileLengths	������������ ����� ������ ����� ������������
	//D3 BadCodeFB			� ����� ������������ ������������ ���������������� ���� ��
	//D4 BadRegAddr			� ����� ������������ ������������ ������ � ������� �� ��������� ��� ��
	//D5 BadRegCode		(new)� ������������ ���� ���������������� ��� ��������
	//D6 BadRegType		(new)� ������������ ���� ���������������� ��� ������ ��������
	//D7 BadSeq			(new)� ������������ ���� �������� ������� �������� ��������� ��
// ������
    u8 modbus_shift;    //�������� ��������� ������ "0/1"
    u8 modbus_function_revers;    //��������������� 3 � 4 ������� 0 - ����,1 - ��������
		u16 PMRecvQue[2];				//"���������_�������_������" ���������� ������� ��������� ������� ������
		u16 GMSKFFSKSet;			//"���������_��������_�����"
	// =0 - GMSK; =1 - FFSK ���������� ����; =2 - FFSK ������������ ����
		u16 RF_mode;				//
		u16 FBCfgSize;		// 
		u16 FBkernelRate;		//"���-��_������_�_���"
		u16 RegTimeOut[CHANNEL_NUMBER];  	//������ � ������� ��������� ������� �� ������� ������
		u16 Ethernetstatus;//
		Int64U GlobalTick;//
		sKernelEventFlags KernelEventFlags;//
		u32 ConfigTime;//
    u32 GuID[3];//
		u8 Slave1[12];       // "c���� 1. Mac0+chan+adr" 
		u8 Slave2[12];       // "c���� 2. Mac0+chan+adr" 
		u8 Slave3[12];       // "c���� 3. Mac0+chan+adr" 
		u8 Slave4[12];       // "c���� 4. Mac0+chan+adr" 
		u8 Slave5[12];       // "c���� 5. Mac0+chan+adr" 
		u8 Slave6[12];       // "c���� 6. Mac0+chan+adr" 
		u8 Slave7[12];       // "c���� 7. Mac0+chan+adr" 
		u8 Slave8[12];       // "c���� 8. Mac0+chan+adr" 
		u8 Slave9[12];       // "c���� 9. Mac0+chan+adr" 
		u8 Slave10[12];       // "c���� 10. Mac0+chan+adr" 
		u8 Slave11[12];       // "c���� 11. Mac0+chan+adr" 
		u8 Slave12[12];       // "c���� 12. Mac0+chan+adr" 
		u8 Slave13[12];       // "c���� 13. Mac0+chan+adr" 
		u8 Slave14[12];       // "c���� 14. Mac0+chan+adr" 
		u8 Slave15[12];       // "c���� 15. Mac0+chan+adr" 
		u8 Slave16[12];       // "c���� 16. Mac0+chan+adr" 
		u8 Slave17[12];       // "c���� 17. Mac0+chan+adr" 
		u8 Slave18[12];       // "c���� 18. Mac0+chan+adr" 
		u8 Slave19[12];       // "c���� 19. Mac0+chan+adr" 
		u8 Slave20[12];       // "c���� 20. Mac0+chan+adr" 
		u8 Slave21[12];       // "c���� 21. Mac0+chan+adr" 
		u8 Slave22[12];       // "c���� 22. Mac0+chan+adr" 
		u8 Slave23[12];       // "c���� 23. Mac0+chan+adr" 
		u8 Slave24[12];       // "c���� 24. Mac0+chan+adr" 
		u8 Slave25[12];       // "c���� 25. Mac0+chan+adr" 
		u8 Slave26[12];       // "c���� 26. Mac0+chan+adr" 
		u8 Slave27[12];       // "c���� 27. Mac0+chan+adr" 
		u8 Slave28[12];       // "c���� 28. Mac0+chan+adr" 
		u8 Slave29[12];       // "c���� 29. Mac0+chan+adr" 
		u8 Slave30[12];       // "c���� 30. Mac0+chan+adr" 
		u8 Slave31[12];       // "c���� 31. Mac0+chan+adr" 
		u8 Slave32[12];       // "c���� 32. Mac0+chan+adr" 
		u16 MapTable[32];       // "������� ����������� ����� � �� � ������ � ������� ���. �������." 
		u16 SlaveCount;		// "���������� ������� � ������� ���. �������"
		u32 AdrArch;				//410 820...821 ����� �������������� ������, ��. ��.
		u8 DataArch[64];			//412 824...887 ������ ������, 64 �����.
		u32 AdrConfig;				//444 888...891 ����� ������� ������������, ��. ��.
		u8 DataConfig[64];			//446 892...953 ������ ������������, 64 �����.
		u32 AdrFlash;				//478 956...959 ����� ������� �� � SDcard, ��. ��.
		u8 DataFlash[64];			//480 960...1023 ������ �� � SDcard, 64 �����.
    u8 Buff[LOAD_BUFF_SIZE];       // "���_���_������" 
    u16 link_err;   //���������� ������ ����������
    u16 etharp_err; //���������� ������ arp
    u16 etharp_cachinit;  // ���������� ������������� cach arp
    u16 ip_frag_err;  //���������� ������ ��� ������������ ip
    u16 ip_err; // ����� ���������� ������ ip
    u16 icmp_err; //���������� ������ ICMP
    u16 udp_err;  //���������� ������ UDP
    u16 tcp_err;  //���������� ������ TCP
    u16 mem_max_used; //������������ ���������� ��������������� ������
    u16 mem_err;  //������ ������ � �������
    u8 tcp_seg_use; //���������� �������������� ��������� TCP
    u8 tcp_seg_err; //���������� ������ ��������� ��������� TCP
    u8 tcp_pcb_use; //���������� ���������� ������ ������ ��� TCP 
    u8 tcp_pcb_err; //���������� ������ ��������� ������ ������ ��� TCP 
    u8 arp_err; //���������� ������ ������ ����� ARP
    u8 pbuf_pool_err; //���������� ������ ��������� ������
    u8 pbuf_ref_err;  //���������� ������ ��� ������ �� ��������� ������
    u8 tcp_listen_err;  //���������� ������ � ���������� �������
    u16 route_number; //���������� ��������� 
		u32 NumRecvPacket[CHANNEL_NUMBER];  //���������� �������� ������� �� �������
    u8 reserv_buff[RESERV_BUFF_SIZE];
	} vars;
#pragma pack(pop)
	u8 Bytes[cstMaxFB_RAMsize+MAX_KERNEL_NUMBER*sizeof(KernelInfo_t)];
}  FB32_type;		//�������� ������������.
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

//���������� �����
//2051 ���� ������������ ��� ������� �������
//��������� 512 ���� ������������ ��� ����������������� ������ FB32 ������������ � ������ 84 � 85
#define MAX_BAT_MEM_SIZE	256
extern u32 BateryMemFB32[];
#define cstTimeCOM	20
extern vu8 RxOn; // ���� ��� ��������� ������ ����� ��������
//=== ���0 - �������� ���� UART4 ===//
#define COM0	0
#define	CLK0	(MCLK/4)		// Clock
#define	Baud0	115200			// USART4 baud-rate.
extern vu8 CntTimeRxD0;		// ������� ��������.
#define cstCOM0Shift 	6
extern vu8 COM_mode;
	//b0 - 
  //b4=1 - ����� (�� �� ����) ��������� ���� ����� COMext.
  //b5=1 - ����� (�� �� ����) ��������� ���� ����� COM1.
	//b6=1 - ����� (�� �� ����) ��������� ���� ����� COMIntBUS.
	//b7=1 - ����� (�� �� ����) ��������� ���� ����� ���0.

//=== ���1 - ������ ���� USART1 ===//
#define COM1	1
#define	CLK1	(MCLK/2)		// Clock
#define	Baud1	115200			// USART1 baud-rate.
extern vu8 CntTimeRxD1;		// ������� ��������.
#define cstCOM1Shift 	6

extern vu8 SizeCOM1;		// ������ ������ �� ���1.

//=== IntBUS - ������� ���� USART6 ===//
#define COMIntBUS		2
#define	CLKIntBUS		(MCLK/2)		// Clock
#define	BaudIntBUS		(115200*15)			// USART6 baud-rate.
extern vu8 CntTimeRxDIntBUS;		// ������� ��������.
#define cstCOMIntBUSShift 	4


//=== ���ext - �������������� ���� USART2 ��� ���������� ===//
#define COMext	3
#define	CLKext	(MCLK/4)		// Clock
#define	Baudext	(115200)			// USART2 baud-rate.
extern vu8 CntTimeRxDext;		// ������� ��������.
#define cstCOMExtShift 	6
extern vu8 PackInCOMext[];
extern vu8 PackOutCOMext[];

//=== COMrfm23 - �������������� ���� USART2 ��� ���������� ===//
#define COMext_rfm23	4

//=== ����� ������� ===//
extern vu16 RF_mode; // ����� ������ �����.
//b0...1 - =0 - ����� ���������/������� �������������, =1 -
// =3 - ���������� ������������, �������� ��������/����� ������.
//b2=1 - ����� ��������, ������ ������� �������� � �����.
//b3 - ��� GMSK:=1 - ����� �������� �������, =0 - ����� ���������� �������.
//b3 - ��� FFSK:=1 - ������ ������� "H", =0 - ������ ������� "L".
//b4=1 - ���� �������� ���� ��������� GMSK.
//b5=1 - ���� �������� ����� ���������.
//b6=1 - ���� �������� � �����.
//b7=1 - ������ ����� � �����.
//b8=0 - ������ ����� RTM64. =1 - ��RTM.
//b9=1 - var-�����.
//b10=0 - �������� ���������� �������, =1 - �������� ���������� ������� ��������� 4-FSK.
extern vu8 RF_PakCnt;		// ��������� ��������� ����� � �������� �����.
extern uc16 MassUp[];		// ������ ���������� ������������� 32 �����.
extern uc16 MassDown[];		// ������ ���������� ������������� 32 �����.
extern uc16 MassLow[];		// ������ ������� ������ 32 �����.
extern uc16 MassHigh[];		// ������ �������� ������ 32 �����.
extern uc16 MassEnd[];		// ������ �������� ������ 32 �����.
extern uc16 Mass12Sin[];		// ������ ������������� ������� 32 �����.
extern uc16 Mass12SinNeg[];		// ������ ������������� ������ 32 �����.
extern uc16 Mass24Sin[];		// ������ ��������� 2400 �� ������������� 32 �����.
extern uc16 Mass24SinNeg[];		// ������ ��������� 2400 �� ������������� 32 �����.
extern uc16 Mass36Sin[];		// ������ ��������� 3600 �� ������������� 32 �����.
extern uc16 Mass36SinNeg[];		// ������ ��������� 3600 �� ������������� 32 �����.
#define cstDelayRF	50		// ������������ �������� ����� ��������� � ����� - 100.
extern vu16 CntDelay;		// ������������ �������� ����� ���������/������������ �������� ������ ��� ������.
extern vu8 Bit_mode;		// ����� ������ ������������.
	//b0...1 - ��� GMSK: 00 - ������ �������, 01 - ���������� �������, 10 - ���������� �������, 11 - ������� �������.
	//b0...1 - ��� FFSK: 00 - ������� ���������, 01 - ������ ���������, 10 - �������.���������, 11 - �������.���������.
	//b2...b7 - �� ������������.
	// ��� ������ - ����� �������� �������������.
extern vu8 RF_iBit;		// ������� ��������/�������� �����.
extern vu8 RF_LastBit;		// ���������� ��������/�������� ��� ��� ������� ����� �� ��������� ��� FFSK.
extern vu16 RF_Reg;		// ������� ������.
#define	BaudRF	9600		// UART baud-rate - 9600.
#define HalfT0	MCLK/(4*BaudRF)		// ������������ �������� =3125 ��� ��������� GMSK.
extern vu16 CntDefen;		// ������� ��� ����������� ������������ ��������.
#define	MaxDefen	2000		// ������������ ���������� ������������ �������� ����.


//=== ����� ������� ===//
#define cstDelayRN	3		// 3 ���� - �������� ����� ��������� � ������� �����.
#define cstChannelRN	1		// ��������� ����� �������� ����� �� ���������.
#define cstBaudRateRN	4		// �������� �������� ����� �� ���������.
#define cstPowerRN		3		// �������� �������� �������� ����� �� ���������.

//=== SPI ��� �������� ����� ===//
#define cstSPI		4		// 2 - ����� ����� ������ � SPI.
extern vu8 BufFromSPI[], Buf2SPI[];
extern vu8 CntByteSPI;		// ������� ������������ ����.
extern vu8 PtrByteSPI;		// ��������� ����������� �����.
extern vu8 TimeSPI;		// ������� �������� ������ �� SPI.
extern vu16 CntDefenRN;	
extern vu16 CntDelayRN;
extern vu16 SPI_mode;		// 
	//b0=1 - ����� ������ ����� 60 ����.
	//b1=1 - ���� �������� ����� ���������.
	//b2=1 - ������ ����� RTM64. =0 - ��RTM.
	//b3=1 - var-�����.
	//b4=1 - ���� ���������� �����.
	//b5=1 - �������� ����� � �����.
	//b6=1 - �������� ��������.
	//b7=1 - ������ �����.
	//b8=0 - ������ � ������� �����.
//=== SPI FLASH ===//
#define SPIFLASHSIZE 280
extern vu8 BufFromSPI_FLASH[];
extern vu8 Buf2SPI_FLASH[];
extern vu8 TimeSPI_FLASH;
extern vu16 SPI_mode_FLASH;
extern vu16 CntByteSPI_FLASH;
extern vu16 PtrByteSPI_FLASH;
#define SetSPIIE_FLASH()      (SPI1->CR2 |=BIT(SPI_RXNEIE))           // ��������� ���������� RX.
#define ResetSPIIE_FLASH()    (SPI1->CR2 &= ~BIT(SPI_RXNEIE))         // ��������� ���������� RX.

#define cstSizeRN		32		// ������������ ������ �������, ������ ������. � ��� ����������� ������� 2 �����, ����� CRC 2 �����.
// ������� ����� cstSizeRN ���� ����������� �� ������ �� cstSizeRN ����, �� ����� 64 �������.
extern vu8 SizeRN;		// ���������� ������� � ������ (������ ���� �������).
extern vu8 NumRN;		// ����� ������� � ������ (������ ���� �������).
extern vu8 LenRN;		// ����� ������� �� �����/��������.
extern vu8 Radio_RSSI;		// ������� ��������� �������.

#define SetSPIIE()	(SPI3->CR2 |=BIT(SPI_RXNEIE))		// ��������� ���������� RX.
#define ResetSPIIE()	(SPI3->CR2 &= ~BIT(SPI_RXNEIE))		// ��������� ���������� RX.

//=== RFM23 �� ����� ���������� ===//
extern vu8 BufFromRFM23[], Buf2RFM23[];
extern vu8 CntByteRFM23;		// ������� ������������ ����.
extern vu8 PtrByteRFM23;		// ��������� ����������� �����.
extern vu16 CntDefenRN23;	
extern vu16 CntDelayRN23;
extern vu16 RFM23_mode;	

extern vu8 SizeRN23;		// ���������� ������� � ������ (������ ���� �������).
extern vu8 NumRN23;		// ����� ������� � ������ (������ ���� �������).
extern vu16 LenRN23;		// ����� ������� �� �����/��������.
extern vu8 Radio_RSSI23;		// ������� ��������� �������.

#define SetUSART2IE()	(USART2->CR1 |=BIT(USART_TCIE))		// ��������� ���������� RX.TCIE
#define ResetUSART2IE()	(USART2->CR1 &= ~BIT(USART_TCIE))		// ��������� ���������� RX.

//=== ������ ===//
extern vu8 SendPakFB;
extern vu8 Cnt100mkSec;		// ������� �� 100 �����.
extern vu8 Cnt10mSec;		// ������� �� 10 ����.
extern vu8 Cnt100mSec;		// ������� �� 100 ����.
extern vu8 Cnt1Sec;		// ������ �������� ��������.
extern vu8 Cnt1Min;		// ������ �������� ��������.
extern vu8 Cnt1Hour;		// ������ �������� ��������.
extern vu8 Cnt1DenOld;		// ������ �������� ��������.
extern vu8 Cnt1MesOld;		// ������ �������� ��������.
extern vu8 Cnt1GodOld;		// ������ �������� ��������.
extern vu16 FlTime;		// ����� ��������� �������.
	//b0=1 - ���� �������� ����� � RTC.
	//b1=1 - 100 ����.
	//b2=1 - 1 ���.
	//b3=1 - 1 ���.
	//b4=1 - 1 ���.
	//b5=1 - 1 ����.
	//b6=1 - 10 ����.
	//b7=1 - ����� ����������������.
  //b8=1 - 1 ��
	//b9=1 - ���� ������������� ������� �����������������
	//b10=1 - ������ ����������� � ������� ������
	//b11=1 - 1/64 ���
extern vs16 CntLedPaket, CntLedOtvet, CntLedError, CntLedTest;		// ������� �������� ����������.
extern u32 cntSecFromStart;		// ������� ������ �� ������ ��� ��������� ��������
extern vu8 cntSecFromReset;		// ����� ������� ������ ������������� ����������
extern vu8 cntSecFromUpdateCfg; // ����� ������� ������ ������ ���������� ������������
#define Reset_MCU(i)	(cntSecFromReset=i+1)		// ������� ����� n ���
#define Update_Cfg(i)	(cntSecFromUpdateCfg=i+1)		// ������� ����� n ���
#define GoritLed	50		// 50*1 ����.

//=== ��� � ��� ===//
extern vu16 ADCchanTSD;
#define cstADCbuf	4		// ���������� ������� ADC.
#define cstADCdel	25.0		// �������� ��� ����������.
extern vu8 ADC_mode;		// ������ ������ ���.
	//D0=1 - 
	//D5=1 - 
	//D6=1 - 
	//D7=1 - 

//=== AI, DI, DO ===//
extern vu8 NumDI;		// ����� ������������ ������(��), ����� � ������(��).
extern vu32 CntDI[];		// ������������� �������� ��������� DI.
extern vu16 DIFilterCNT;	
extern vu16 IC3ReadValue1, IC3ReadValue2;
extern vu8 IC3CaptureNumber;
extern vu32 IC3Capture;
extern vu16 IC3UpG;			// ������� ������������ ������� ��� 3 ������ capture
extern vu16 IC4ReadValue1, IC4ReadValue2;
extern vu8 IC4CaptureNumber;
extern vu32 IC4Capture;
extern vu16 IC4UpG;			// ������� ������������ ������� ��� 4 ������ capture

//=== ���������� ��� ModBus ===//
extern vu8 modbus;		// ������������ �������� ������ �� ModBus-���������� � ����� �� 0,1 ���.
//lwip
extern vu32 LocalTime;
//=== ����� ===//
extern vu16 TestShort[];
extern vu32 TestInt[];		// ���������.
extern vs8 Temperature;		// ����������� ��������.
extern vu32 DItest;
extern u32 ArchArea_Size;
extern u32 ARC_R7_MAXNUM;
extern vu8 Sln[]; // ������ ������� ������� ������� � ��������� �������

//extern uc8 M1[];		// ������� ������ ��������.
extern uc8 M2[];		// �������������� ����� "�����".
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
//_________�����___________


//main.c

#endif
