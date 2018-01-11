/* �� "������� ���������� ��������" */
#define ARRAY_KNAP 40
#define TIME_PERIOD_NUMBER 5
#define WATT_SIZE 3
typedef struct {
  Register_type DigitInput;   // uint16 //��������� ������ 
                              // 0x01 - ��������� ��������� ���������  
                              // 0x02 - 
                              // 0x04 - 
                              // 0x08 - 
                              // 0x10
                              // 0x20 - 
                              // 0x40 - ����� ���� 
                              // 0x80 - ����� ������
  Register_type DigitInversion;//uint16 //�������� ������ �������� ������
  Register_type Mode;         // uint8  //������ ������
                                 // 0x00 - �������� �� ������ ������/�������, ��������� � ������ ���������� �����������
                                 // 0x10 - ���� (���������� �� � �������� ��������� ������ )
                                 // 0x00 - ������� 
                                 // 0x30 - �� ���������� �� ���������� �������� ��������� ������
                                 // 0x70 - �� ���������� �� �� ���������� �������� ��������� ������
                                 // 0x01 - ���������� �� ����������� � ������ AvtoDownTimeMode
                                 // 0x41 - �� ���������� �������� ��������� ������
                                 // 0x02 - ���������� �� ������� 
                                 // 0x22 - �� ���������� �� ���������� �������� ��������� ������
                                 // 0x42 - �� ���������� �� �� ���������� �������� ��������� ������
                                 // 0x8Z - ���������� ��������� ����� ������ ��� ����
  Register_type DownTime;      // uint16 // ����� ���������� � ������� � ������ ������ �� �������
  Register_type UpTime;        // uint16 // ����� ������ � ������� ��� ������ ������ �� �������
  Register_type DisregardTime; // uint16 //(���) ����� ������ ����� ������� � ������� �������� ���������� ������� ������ �������� � ����
  Register_type InputPressure; // uint16 // ������� �������� �� ������
  Register_type MaxPressure;   // uint16 // ������������ ������� �������� �� ������
  Register_type DownTimeBigPressure;     // uint16 // ����� ���������� � ������� ���� ��������� ��������
  Register_type MinPressure;   // uint16 // ����������� ������� �������� �� ������ 
  Register_type DownTimeLowPressure;     // uint16 // ����� ���������� � ������� ���� �������� ���� ���������
  Register_type Knap;          // uint8  // ���� ����������� � ���������� � �������
	Register_type KnapOK;        // bit    // ������� ����
	Register_type KnapPorog;     // uint8  // ���� ����� ������
	Register_type KnapIgnor;     // uint16 // ���-�� ������������ ����
	Register_type KnapCalc;      // uint8 // ���-�� ��������� ���� ��� ��������, � ����������� ��(�� ��������� 10)
	Register_type KNAPTime;    // uint16(���) // ����� � ���������� ���� ����� �������� ������������ ���� ������
	Register_type SPTime;        // uint16 // ����� ���������� ��� ��(������)
	Register_type SPTimeShift;   // uint16 // ��������� ������� ���������� � ������ AvtoDownTimeMode(������)
	Register_type SP_Num;  // uint16  // ���-�� ������� ���������� ��� ������� ��� ����� ���� ����� ������
                                         // ����� ������� ������� ���������� ���������,���� � ����� �� ������
                                         // ���� �������� ���� ����� ������ �� ������� �������������
	Register_type APV_Num;      // uint16   // ���-�� ��� ����� �����
//	Register_type APV_Interval; // uint16  // �������� ��� ����� �����
	Register_type Protection;   // bit     // ������
  Register_type ActuatorTime;       // uint32  //(�������) ����� ������ �������� �� ��������� ��� ���������,����������
	Register_type ActuatorRestart;		//uint16		���������� ������� �������� ��������� ��������� ���������
  Register_type TimeBeforeStart;       // uint8  //(�������)  
  Register_type Time[TIME_PERIOD_NUMBER*2];       // uint16  //������ �� ������ �����, � ������� ��������
  Register_type Watt[WATT_SIZE];       // uint16  //WATT[0] - volteg,WATT[1] - current, WATT[2] - WATT
} fb00068_IN_type;

typedef struct {
	Register_type KernelClk;    // uint32
	Register_type Knap_Summ;    // uint16 // ����������� ����� ���� ��� ������� ��������
	Register_type KnapCalc;     // uint32 //  ����������
	Register_type KnapFail;     // uint8  //  ����������
	Register_type SecTimer;     // uint32 // ����� � ������ � ��������
	Register_type MinTimer;     // uint32 // ����� � ������ � �������
	Register_type ActuatorTimer;// uint32 // ������ ������� ��������� ���������
	Register_type ActuatorRestartCnt;		  //uint16		���������� ������� �������� ��������� ��������� ���������
  Register_type Input_mask;   // uint16		�������
	Register_type PRESSURE_FILT;// uint16 // ��� ������� ��������
} fb00068_VAR_type;

typedef struct {
	Register_type FirstStartTime;    // time(uint32) // ���� ������� ���������������� �������
	Register_type FullOperationTimer; // uint32(������) // ����� ����� ������ � ���� FirstStartTime
	Register_type FullDownTimer;      // uint32(������) // ����� ����� ������� � ���� FirstStartTime
	Register_type DayUpTimer;         // uint16(������) // �������� ����� ������ 
	Register_type PrevDayUpTimer;       // uint16(������) // �������� ����� ������  
	Register_type LastSostTimer;      // uint32(������) // ����� ���������� �������(������/�������)
	Register_type KnapAverage;        // uint8  // ���� ������� �� ��������� ���
  Register_type Knap;         // uint8  // ���� ����������� � ���������� � �������
	Register_type CntIgnor;     // uint16 // �������� ������������ ����
	Register_type KNAPTimer;    // uint16(���) // ����� � ���������� ���� 
	Register_type CntRestartSP; // uint16  // �������� ������� �������������� �� ��
	Register_type SPTimer;      // uint16 // �������� ������ �����������
  Register_type DownTimer;    // uint16 // �������� ������ �������
  Register_type UpTimer;      // uint16 // �������� ������ ������
  Register_type DisregardTimer;      // uint16 // �������� ������ ������������ ������
	Register_type CntRestartAPV;// uint16  // �������� ������� ���
	Register_type APVTimer;     // uint16 // �������� ������ ���
	Register_type State;        // uint32 // ��������� ��
/*
#define PUSK_ACTUATOR bit(0)
#define OPERATOR bit(1)
#define AVTODOWNTIME bit(2)
#define TIMER bit(3)
#define SP bit(4)
#define PRESSURE_BIG bit(5)
#define PRESSURE_LOW bit(6)
#define START_TIME bit(7)
#define UP_TIME bit(8)
#define DOWN_TIME bit(9)
#define KNAP_LOSS bit(10)
#define EXTERNAL_PROTECT bit(11)
#define BEFORSTART bit(12)
*/
	Register_type ActuatorOn;      // bit    // �������� ��������� 
	Register_type ActuatorOff;     // bit    // ��������� ���������
	Register_type FBTime;          // uint32 // ����� ���������� �� � ����������
  Register_type TimerBeforeStart;   //uint8		����� �� �������
	Register_type WattPreviuDay;          // float // watt/hours
	Register_type WattCurrentDay;          // float // watt/hours
} fb00068_OUT_type;
#define FILTPRESSURE 4 //������� ��� ���������� ������ ��������� �������� ��� 
               //����������� ����� ������ �� ��������


//state OUT->State.Data.uint32
#define PUSK_ACTUATOR 0
#define OPERATOR 1
#define TIME 2
#define TIMER 3

#define SP 4
#define PRESSURE_BIG 5
#define PRESSURE_LOW 6
#define START_TIME 7

#define UP_TIME 8
#define DOWN_TIME 9
#define KNAP_LOSS 10
#define EXTERNAL_PROTECT 11

#define BEFORSTART 12
#define SP_MODE 13
#define PRESSURE_MODE 14
#define IMPULSE_MODE 15

#define SECTION1 16
#define SECTION2 17
#define SECTION3 18
#define SECTION4 19
#define SECTION5 20
#define TIMING_PUSK 21
//input 
#define ACTUATOR 0
#define ARM_BUTTON 1
#define AVTO_BUTTON 2

//mode
#define PUSK 4
#define ENABLE_SP 5  // ������� �� ����� ������
#define ENABLE_PRESSURE 6
#define IMPULSE 0x80

#define OPERATOR_MODE 0x01 // �������� �� ������ ������/�������, ��������� � ������ ���������� �����������
#define TIMER_MODE 0x02    // ���������� �� ������� 
#define TIME_MODE 0x04  // ����� ������ �� ����������             

//time
#define SEC 0
#define MINUT 1

void fb00068_exec(void);

u32 fb00068_var_size(u8 type);
