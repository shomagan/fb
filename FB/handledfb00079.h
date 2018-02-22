/* ФБ "Насос без АПВ" */

typedef struct {
	Register_type Dist_mode;			//bit			1 - Дистанционный режим 0 - местный режим
	Register_type Cmd_ON;				//bit			Команда включить (импульсный вход желательно 1 такт исполнения конфигурации)
	Register_type Cmd_OFF;				//bit			Команда отключить (импульсный вход желательно 1 такт исполнения конфигурации)
	Register_type Actuator;				//bit			Состояние пускателя 1 - замкнут 0 - разомкнут
	Register_type Alarm;				//bit			Авария
	Register_type Block;				//bit			Блокировка
	Register_type ResetAlarm;			//bit			Сброс аварий(импульсный вход желательно 1 такт исполнения конфигурации)
	Register_type ImpulsONOFFTime;		//uint8			Время в сек в течении которого действует выход управления на пускатель НА
	Register_type ActuatorTime;			//uint32		Время в сек ожидания желаемого состояния пускателя
	Register_type ActuatorRestart;		//uint16		Количество попыток ожидания желаемого состояния пускателя
	Register_type TimeNonStop;			//uint32		Время пуска НА в сек (в течении которого не реагировать на блокировки на время пуска)
	Register_type APV_TryNum;			//uint16		Количество попыток АПВ
	Register_type APV_Interval;			//uint32		Время между попытками АПВ
} fb00079_IN_type;

typedef struct {
	Register_type SecTimer;				//uint8			Внутренний счетчик для отсчета секунд
	Register_type CntReinitAPV;			//uint32		Внутренний счетчик переинициализации АПВ
} fb00079_VAR_type;

typedef struct {
	Register_type Control_ON;			//bit			Выход на включение пускателя НА
	Register_type Control_OFF;			//bit			Выход на выключение пускателя НА
	Register_type stUprav;				//bit			Признак, что НА воспринимает управляющие команды
	Register_type CntActTime;			//uint32		Счетчик времени в сек ожидания состояния пускателя
	Register_type CntActRestart;		//uint16		Счетчик количества попыток ожидания состояния пускателя
	Register_type CntNonStop;			//uint32		Счетчик вемени в сек времени пуска НА (начинает работать после ожидания состояния пускателя)
	Register_type APV_TryCnt;			//uint16		Счетчик попыток АПВ
	Register_type APV_Timer;			//uint32		Счетчик времени в сек между попытками АПВ
	Register_type CntImpONOFF;			//uint8			Счетчик времени в сек управляюжего воздействия на пускатель
	Register_type State;				//uint32		Текущее состояние алгоритма работы НАСОС с АПВ (расшифровка ниже)
} fb00079_OUT_type;

//--------------- Состояния алгоритма работы НАСОС с АПВ ------------------
#define s00079_Dist				(1<<0)		//Флаг дистанционного режима
#define s00079_Actuator			(1<<1)		//Флаг замкнутого пускателя
#define s00079_Block			(1<<2)		//Признак наличия блокировки
#define s00079_Alarm			(1<<3)		//Признак наличия аварии

#define s00079_APVon			(1<<4)		//Флаг указывающий что НА нстроен на АПВ
#define s00079_flAlarm			(1<<5)		//Флаг наличия аварии, сбрасывается по входу Сброс аварии
#define s00079_flBlock			(1<<6)		//Флаг наличия блокировки
#define s00079_WaitActuator		(1<<7)		//Режим отработки ОЖИДАНИЕ ПУСКАТЕЛЯ

#define s00079_ExpectActuator	(1<<8)		//При режиме отработки ОЖИДАНИЕ ПУСКАТЕЛЯ показывает желаемое состояние пускателя 1-Замкнут 0-Разомкнут
#define s00079_WaitBlock		(1<<9)		//Ожидание игнорирования блокировки на время пуска
#define s00079_WaitAPV			(1<<10)		//Ожидание интервала между попытками АПВ
#define s00079_APV_TryCnt_Null	(1<<11)		//Флаг что кончиличь попытки АПВ

#define s00079_Need_ON			(1<<12)		//Необходимо включить
#define s00079_Need_OFF			(1<<13)		//Необходимо отключить
#define s00079_ActuatorFail_OFF	(1<<14)		//Не дождались пускателя при выключении
#define s00079_ActuatorFail_ON	(1<<15)		//Не дождались пускателя при включении

#define s00079_ReinitAPV		(1<<16)		//Ожидание инициализации АПВ после очередного автоматического запуска после аварии
											//т.е. если НА запустился по попытке АПВ, то ждем когда попытки АПВ вернуть в начальное значение
#define s00079_WaitImpONOFF		(1<<17)		//Флаг ожидания импульса включения или отключения
#define s00079_WaitImpSTOP		(1<<18)		//Флаг принудительного импульса отключения после неудачного включения (не дождались пускателя на включение)

//------------------ Маски условий ---------------------------
#define s00079_StartMask1		(s00079_Dist | s00079_Need_ON)	//1-ая маска условий при которых можно запустить насос
#define s00079_StartMask2		(s00079_Dist | s00079_Block | s00079_Need_ON)	//2-ая маска условий при которых можно запустить насос
#define s00079_BlockMask		(s00079_Block | s00079_Actuator | s00079_Dist)	//маска условий при которых срабатывает блокировка
#define s00079_UpravMask		(s00079_APVon | s00079_Alarm | s00079_Block | s00079_Actuator | s00079_Dist)	//маска условий при которых насос воспринимает команды включения и отключения
#define s00079_APVMask1ON		(s00079_flAlarm | s00079_APVon | s00079_Dist)
#define s00079_APVMask2ON		(s00079_ReinitAPV | s00079_flAlarm | s00079_APVon | s00079_Dist)
#define s00079_APVMask1OFF		~(s00079_APVMask1ON)
#define s00079_APVMask2OFF		~(s00079_APVMask2ON)

void fb00079_exec(void);
u32 fb00079_var_size(u8 type);
