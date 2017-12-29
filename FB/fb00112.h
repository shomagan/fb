/*Запись DO*/
#include "../kernel.h"

typedef struct {
	Register_type N;			// u8 количество элеметов
	Register_type Format;			// bit выравнивание байтов, влево - 1, 0 - по умолчанию. к примеру байты: 0х000312 -> 0x312000
	Register_type Input[254];			// u8 количество элеметов
} fb00112_IN_type;

typedef struct {
	Register_type Temp;			// uint8 Номер в пакете который отправляем и который ищем в очереди ответов
} fb00112_VAR_type;


typedef struct {
	Register_type Output[254];			// bit Ошибка
} fb00112_OUT_type;


void fb00112_exec (void);		// - Запись сетевых переменных

