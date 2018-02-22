/* ФБ "Master канала": Чтение сетевых переменных, синхронизация времени с слейвами */

typedef struct {
	Register_type Enable;   // bit  Разрешение на выполнение этой ФБ
	Register_type Run;   		// bit  Запуск отправки пакетов
	Register_type Chanel;   // int8 Если указываем канал больше 10-го (несуществующий) то отправляем пакет всем зарегистрированным слейвам, меньше 10-го то тому кого указали в ФБ для регистрации только по этому каналу
	Register_type Direct;   // bit  NSlv это адрес напрямую - 1. 0 - NSlv это номер который еще надо сопоставить с таблицей слейвов
	Register_type NSlv;     // int16 Номер устройства у кого запрашиваем СП в таблице слейвов
	Register_type NSP;      // int8 Количество СП
	Register_type InSP[256]; // int16 Сетевая переменная N
} fb00103_IN_type;

typedef struct {
	Register_type PackNum;			// uint8 Номер в пакете который отправляем и который ищем в очереди ответов
	Register_type Trig;					// bit   Триггерное состояние
	Register_type SR;						// bit	 Переменная сохранит бит Run - Exit когда Enable = 0
	Register_type SyncTimeFB; 	//bit		 Флаг отправки времени в канал слейву, только раз в минуту
} fb00103_VAR_type;

typedef struct {
	Register_type Exit; // bit выход. 1-запускаем след. ФБ(Нашли пакет или сброс по таймауту), 0-не запускаем, ищем пакет в ответах
	Register_type Exception;               // Ошибка, пакет не дошел
	Register_type Ok; // Все хорошо
	Register_type SP[256 - 3]; // максимум 251 байта Данные сетевых переменных
} fb00103_OUT_type;

void fb00103_exec (void);		// - Чтение сетевых переменных
u32 fb00103_var_size(u8 type);
