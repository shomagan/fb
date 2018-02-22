/* ФБ "двухчасовка (счётчик-архиватор)" */
                               
typedef struct {
	//Register_type Enable;			//- bit - разрешение архивирования
	Register_type CntNum;			//- uint8 - номер счётчика в архив
	Register_type Period;			//- uint16 - периодичность архивирования
	Register_type CounterIn;	//- uint32/float - увеличивающееся значение
  Register_type CounterHour;	//- uint8/float - увеличивающееся значение
} fb00093_IN_type;

typedef struct {
	Register_type OK;						//- bit - на 1 такт после архивирования (при этом CounterOut станет ПИ)
	Register_type CounterOut;		//- uint16/32/float - счетчик за текущий интервал (ТИ)
	Register_type OldCounterIn;	//- uint32 - значение входа в прошлый такт
	Register_type StartTime;		//- time - время начала замера (UnixTime)
	//держать три последных выхода в сохраняемой области памяти
} fb00093_OUT_type;

void fb00093_exec();
u32 fb00093_var_size(u8 type);
