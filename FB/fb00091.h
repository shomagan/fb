/* ФБ "Счетчик БГ" (заголовочный файл) */
                               
typedef struct {
	Register_type Enable;		//-1 bit 		- разрешение работы
	Register_type CounterDI;	//-2 uint32		- счетный вход
	Register_type UNIXTime;		//-3 time		- системное время в формате UNIX
	Register_type IntervalCNT;	//-4 uint16		- интервал в мин формирования интервальных счетчиков
	Register_type AvarRashod;	//-5 uint32		- уставка аварийного расхода
	Register_type EnaPeretok;	//-6 bit			- учитывать перетоки
	Register_type PeretokDI;	//-7 bit			- бит указывающий возникновение перетоков (остановка насоса, а счет идет)
	Register_type EnaNullNull;	//-8 bit			- бит выравнивания в 00:00
	Register_type Ena2Hours;	//-9 bit			- двухчасовки
} fb00091_IN_type;

typedef struct {
	Register_type EnaOld;			//-1 bit		- разрешение работы, предыдущее значение
	Register_type CounterDIOld;		//-2 uint32	- Счетный вход, предыдущее значение
	Register_type CounterMinOld;	//-3 uint32	- старое значение минутного счетчика
	Register_type CntTicksSec;		//-4 uint8	- Счетчик проходов конфигурации для определения секунд
	Register_type CntSeconds;		//-5 uint8	- счетчик секунд
	Register_type CntMinutes;		//-6 uint16	- счетчик прошедших минут для интервальных
	Register_type TimeBeg;			//-7 time	- время начала текущего замера
} fb00091_VAR_type;

typedef struct {
	Register_type MinCnt;			//-1 uint32	- Минутный счетчик
	Register_type MinCntDiff;		//-2 uint32	- Изменение минутного счетчика
	Register_type CNTInvT;			//-3 uint32	- Счетчик за текущий интервал
	Register_type CNTInvP;			//-4 uint32	- Счетчик за прошлый интервал
	Register_type CNTIntegrTS;		//-5 uint32	- Счетчик интегральный за текущие сутки
	Register_type CNTIntegrPS;		//-6 uint32	- Счетчик интегральный за прошлые сутки
	Register_type CNTInvTif;		//-7 uint32	- Счетчик за текущий интервал условию
	Register_type CNTInvPif;		//-8 uint32	- Счетчик за прошлый интервал по условию
	Register_type flAvarRash;		//-9 bit	- флаг аварийного расхода
	Register_type ArhInvEna;		//-10 bit		- Флаг, что текущие интервальные счетчики пора архивировать
	Register_type ArhInvDuration;	//-11 uint16	- Для архива, длительность замера
	Register_type ArhInvTimeBeg;	//-12 time		- Для архива, время начала замера
	Register_type ArhCNTInvT;		//-13 uint32	- Для архива, Счетчик за текущий интервал
	Register_type ArhInvPeretok;	//-14 bit		- Флаг, что текущие перетоки по интервальным счетчикам пора архивировать
	Register_type ArhCNTInvTif;		//-15 uint32	- Для архива, счетчик перетоков за текущий интервал
} fb00091_OUT_type;
u32 fb00091_var_size(u8 type);
