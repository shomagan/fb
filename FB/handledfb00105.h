/*Запись сетевых переменных*/

typedef struct {
	Register_type Enable;   // bit  Разрешение на выполнение этой ФБ
	Register_type Run;   		// bit  Запуск отправки пакетов
	Register_type NSlave;     // int16 Номер устройства у кого запрашиваем СП в таблице слейвов
	Register_type Nsp;      // int8 размер данных на запись. количество значений на запись 
	Register_type IDsp; // int16 Сетевая переменная ID
	Register_type SP[256 - 6]; // Данные на запись. Максимум 249 байт // u8, u16, u32
} fb00105_IN_type;

typedef struct {
	Register_type PackNum;			// uint8 Номер в пакете который отправляем и который ищем в очереди ответов
	Register_type Trig;					// bit   Триггерное состояние
	Register_type Go;						// bit	 Отправляем пакет
} fb00105_VAR_type;

typedef struct {
	Register_type Exit; // bit выход. 1-запускаем след. ФБ(Нашли пакет или сброс по таймауту), 0-не запускаем, ищем пакет в ответах
	Register_type Exception; // bit выход. 1-запускаем след. ФБ(Нашли пакет или сброс по таймауту), 0-не запускаем, ищем пакет в ответах
	Register_type Ok;
} fb00105_OUT_type;

void fb00105_exec (void);		// - Запись сетевых переменных

u32 fb00105_var_size(u8 type);
