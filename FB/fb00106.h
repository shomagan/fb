/*Мультиплексор DI*/

typedef struct {
	Register_type Nbit;   // int8  Номер бита на выбор в канале
	Register_type Kanal[256-1]; // int16 Канал (1-16) бит
} fb00106_IN_type;

typedef struct {
	Register_type OUT;			// bit Значение
	Register_type Error;			// bit Ошибка
} fb00106_OUT_type;


void fb00106_exec (void);		// - Запись сетевых переменных

