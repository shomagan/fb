/*Запись DO*/

typedef struct {
	Register_type Nbit;   // int8  Номер бита на выбор в канале
	Register_type Bit; // int16 Канал (1-16) бит
	Register_type IN[256-2];			// bit Значение
} fb00107_IN_type;

typedef struct {
	Register_type Error;			// bit Ошибка
	Register_type OUT[256-1];			// bit Значение
} fb00107_OUT_type;


void fb00107_exec (void);		// - Запись сетевых переменных

u32 fb00107_var_size(u8 type);
