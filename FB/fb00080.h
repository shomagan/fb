typedef struct {
	Register_type Dist;				// bit 1 - Дистанционный, 0 - Местный
	Register_type CmdOpen;			// bit Переход с 0 на 1 - Открыть
	Register_type CmdClose;			// bit Переход с 0 на 1 - Закрыть
	Register_type CmdStop;			// bit Переход с 0 на 1 - Остановить
	Register_type Opened;			// bit Открыта
	Register_type Closed;			// bit Закрыта
	Register_type Alarmed;			// bit Авария - муфта
	Register_type Uon;				// bit Наличие напряжения
	Register_type VPH; 				// uint16 -время полного хода
} fb00080_IN_type;

typedef struct {
	Register_type SecTimer;     	// uint8 Таймер отсчёта секунд
	Register_type ImpulsTime;		// uint8 Таймер удержания управляющих выходов
} fb00080_VAR_type;

typedef struct {
	Register_type OutOpen;			// bit выход управления открыть
	Register_type OutClose;			// bit выход управления закрыть
	Register_type OutStop;			// bit выход управления стоп
	Register_type Position; 		// uint16 предполагаемая позиция
	Register_type Sost; 			// uint16 состояние
	Register_type Timer; 			// uint16 обратный таймер времени хода задвижки
} fb00080_OUT_type;

#define	s00080_DIST					(1<<0)		//Дистанционный режим
#define	s00080_OPENED				(1<<1)		//Открыта
#define	s00080_CLOSED				(1<<2)		//Закрыта
#define	s00080_AVARMUFTA			(1<<3)		//Авария - муфта
#define	s00080_AVARVPHOPEN			(1<<4)		//Авария не дождались открытия
#define s00080_AVARVPHCLOSE			(1<<5)		//Авария не дождались закрытия
#define	s00080_OPENING				(1<<6)		//Открытвается
#define	s00080_CLOSING				(1<<7)		//Закрывается
#define	s00080_UON					(1<<8)		//Наличие напряжения
#define	s00080_RES1					(1<<9)		//Резерв
#define	s00080_RES2					(1<<10)		//Резерв
#define	s00080_RES3					(1<<11)		//Резерв
#define	s00080_RES4					(1<<12)		//Резерв
#define	s00080_RES5					(1<<13)		//Резерв
#define	s00080_RES6					(1<<14)		//Резерв
#define	s00080_RES7					(1<<15)		//Резерв


#define s00080_IMPULSTIME			3			//Время удержания управляющего сигнала в секундах

void fb00080_exec(void);
