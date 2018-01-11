/*Запись DO*/
#include "../kernel.h"
extern vu8 Buff_Pack[];
typedef struct {
	Register_type Enable;			// bit Запуск
	Register_type Reset;			// bit Перезагрузка логики ФБ
	Register_type Chanel;			// uint8 Канал
	Register_type Type;			// uint8 Тип устройства
	// 0 Прямая отправка
	// 1 - Sonomer 500 Теплосчетчик
	// 2 - Меркурий 230 Электросчетчик
	// 3 - Пульсар водосчетчик RS485
	// 4 - Меркурий 203.2Т Электросчетчик
	// 5 - Контроллер на матлабе
	Register_type Options;			// uint8 Опции конкретного устройства
	// 0 - По умолчанию отправка пакета, ФБ выполнена если не пришел ответ или пришел не вверный ответ
	// 1 - Отправка пакета 1 раз и ФБ выполнена, без ожидания какого либо ответа
	// 2 - Отправка пакета каждый раз пока не получим нужный ответ
	Register_type Stady;			// uint8 
	Register_type Nbyte;			// uint8 
	Register_type Byte[256];			// uint8 Байты на запись в канал
} fb00111_IN_type;

typedef struct {
	Register_type TimeOut;			// uint8 Номер в пакете который отправляем и который ищем в очереди ответов
	Register_type LogEnd;					// bit  Логика выполнена
	Register_type SR;						// bit	 Переменная сохранит бит Run - Exit когда Enable = 0
	Register_type Temp; 				//uint8 
} fb00111_VAR_type;


typedef struct {
	Register_type Error;			// bit Ошибка
	Register_type Ok;			// bit Хорошо
	Register_type Run;			// bit 1 после исполнения логики ФБ
	Register_type Data[256 - 3];			// u8 Данные
} fb00111_OUT_type;


void fb00111_exec (void);		// - Запись сетевых переменных
vu16 MbusCRC(vu8 *buff, vu8 len);		// Расчет crc в канале M-bus
vu8 AnalizData(vu8 len);		// Анализ принятых данных от приборов
vu8 FillBuf (void);				// Заполение буфера на отправку, расчет CRC
u16 m_crc16(vu8* pck, vu8 len); // Расчет crc Matlab
u32 fb00111_var_size(u8 type);
