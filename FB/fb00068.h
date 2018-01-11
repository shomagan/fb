/* ФБ "Автомат управления приводом" */
#define ARRAY_KNAP 40
#define TIME_PERIOD_NUMBER 5
#define WATT_SIZE 3
typedef struct {
  Register_type DigitInput;   // uint16 //Состояние входов 
                              // 0x01 - Состояние пускателя двигателя  
                              // 0x02 - 
                              // 0x04 - 
                              // 0x08 - 
                              // 0x10
                              // 0x20 - 
                              // 0x40 - Дверь одна 
                              // 0x80 - Дверь другая
  Register_type DigitInversion;//uint16 //Инверсия логики цифровых входов
  Register_type Mode;         // uint8  //Режимы работы
                                 // 0x00 - зависимо от кнопки ручной/автомат, находимся в режиме управления диспетчером
                                 // 0x10 - Пуск (игнорируем СП и давление выходного насоса )
                                 // 0x00 - Останов 
                                 // 0x30 - не игнорируем СП игнорируем давление выходного насоса
                                 // 0x70 - не игнорируем СП не игнорируем давление выходного насоса
                                 // 0x01 - Управление по динамогрмме в режиме AvtoDownTimeMode
                                 // 0x41 - не игнорируем давление выходного насоса
                                 // 0x02 - Управление по таймеру 
                                 // 0x22 - не игнорируем СП игнорируем давление выходного насоса
                                 // 0x42 - не игнорируем СП не игнорируем давление выходного насоса
                                 // 0x8Z - импульсный пускатель иначе просто вкл выкл
  Register_type DownTime;      // uint16 // Время накопления в минутах в режиме работы по таймеру
  Register_type UpTime;        // uint16 // Время работы в минутах при режиме работы по таймеру
  Register_type DisregardTime; // uint16 //(сек) время работы после запуска в течении которого игнорируем входные данные давления и кнап
  Register_type InputPressure; // uint16 // входное давление на насосе
  Register_type MaxPressure;   // uint16 // максимальное входное давление на насосе
  Register_type DownTimeBigPressure;     // uint16 // Время накопления в минутах если превышено давление
  Register_type MinPressure;   // uint16 // минимальное входное давление на насосе 
  Register_type DownTimeLowPressure;     // uint16 // Время накопления в минутах если давление ниже заданного
  Register_type Knap;          // uint8  // кнап расчитанный и полученный с датчика
	Register_type KnapOK;        // bit    // Получен Кнап
	Register_type KnapPorog;     // uint8  // Кнап срыва подачи
	Register_type KnapIgnor;     // uint16 // Кол-во игнорируемых Кнап
	Register_type KnapCalc;      // uint8 // Кол-во расчетных Кнап для среднего, и определения СП(по умолчанию 10)
	Register_type KNAPTime;    // uint16(сек) // Время с последнего кнап после которого выставляется флаг небыло
	Register_type SPTime;        // uint16 // Время накопления при СП(минуты)
	Register_type SPTimeShift;   // uint16 // Изменение времени накопления в режиме AvtoDownTimeMode(минуты)
	Register_type SP_Num;  // uint16  // Кол-во попыток накопления при которых нет кнапа выше срыва подачи
                                         // после которых небудит повторного включения,если в какой то момент
                                         // кнап превысит кнап срыва подачи то счетчик востановиться
	Register_type APV_Num;      // uint16   // Кол-во АПВ после защит
//	Register_type APV_Interval; // uint16  // Интервал АПВ после защит
	Register_type Protection;   // bit     // Защиты
  Register_type ActuatorTime;       // uint32  //(секунды) Время подачи импульса на пускатель для включения,выключения
	Register_type ActuatorRestart;		//uint16		Количество попыток ожидания желаемого состояния пускателя
  Register_type TimeBeforeStart;       // uint8  //(секунды)  
  Register_type Time[TIME_PERIOD_NUMBER*2];       // uint16  //минуты от начала суток, в которые стартуем
  Register_type Watt[WATT_SIZE];       // uint16  //WATT[0] - volteg,WATT[1] - current, WATT[2] - WATT
} fb00068_IN_type;

typedef struct {
	Register_type KernelClk;    // uint32
	Register_type Knap_Summ;    // uint16 // Накопленная сумма Кнап для расчета среднего
	Register_type KnapCalc;     // uint32 //  количество
	Register_type KnapFail;     // uint8  //  количество
	Register_type SecTimer;     // uint32 // время с начала в секундах
	Register_type MinTimer;     // uint32 // время с начала в минутах
	Register_type ActuatorTimer;// uint32 // Таймер времени включения пускателя
	Register_type ActuatorRestartCnt;		  //uint16		Количество попыток ожидания желаемого состояния пускателя
  Register_type Input_mask;   // uint16		зеркало
	Register_type PRESSURE_FILT;// uint16 // Для фильтра давления
} fb00068_VAR_type;

typedef struct {
	Register_type FirstStartTime;    // time(uint32) // дата первого контроллируемого запуска
	Register_type FullOperationTimer; // uint32(минуты) // общее время работы с даты FirstStartTime
	Register_type FullDownTimer;      // uint32(минуты) // общее время простоя с даты FirstStartTime
	Register_type DayUpTimer;         // uint16(минуты) // суточное время работы 
	Register_type PrevDayUpTimer;       // uint16(минуты) // суточное время работы  
	Register_type LastSostTimer;      // uint32(минуты) // время последнего события(запуск/останов)
	Register_type KnapAverage;        // uint8  // Кнап средний по последним ДНМ
  Register_type Knap;         // uint8  // кнап расчитанный и полученный с датчика
	Register_type CntIgnor;     // uint16 // Осталось игнорируемых Кнап
	Register_type KNAPTimer;    // uint16(сек) // Время с последнего кнап 
	Register_type CntRestartSP; // uint16  // Осталось попыток восстановления из СП
	Register_type SPTimer;      // uint16 // обратный Таймер накопленная
  Register_type DownTimer;    // uint16 // обратный Таймер простоя
  Register_type UpTimer;      // uint16 // обратный Таймер работы
  Register_type DisregardTimer;      // uint16 // обратный Таймер безаварийной работы
	Register_type CntRestartAPV;// uint16  // Осталось попыток АПВ
	Register_type APVTimer;     // uint16 // обратный Таймер АПВ
	Register_type State;        // uint32 // Состояние ФБ
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
	Register_type ActuatorOn;      // bit    // включить Пускатель 
	Register_type ActuatorOff;     // bit    // выключить Пускатель
	Register_type FBTime;          // uint32 // время выполнения фб в мксекундах
  Register_type TimerBeforeStart;   //uint8		время до запуска
	Register_type WattPreviuDay;          // float // watt/hours
	Register_type WattCurrentDay;          // float // watt/hours
} fb00068_OUT_type;
#define FILTPRESSURE 4 //сколько сек исполнения должно держаться давление для 
               //выставления флага авария по давлению


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
#define ENABLE_SP 5  // раотаем по срыву подачи
#define ENABLE_PRESSURE 6
#define IMPULSE 0x80

#define OPERATOR_MODE 0x01 // зависимо от кнопки ручной/автомат, находимся в режиме управления диспетчером
#define TIMER_MODE 0x02    // Управление по таймеру 
#define TIME_MODE 0x04  // режим работы по расписанию             

//time
#define SEC 0
#define MINUT 1

void fb00068_exec(void);

u32 fb00068_var_size(u8 type);
