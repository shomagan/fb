/* "ГЗУ (Башнефть) v.2" */

typedef struct {
	Register_type Enable;       // bit    // Enable
	Register_type Hold;         // bit    // Отключает логику ФБ не сбрасывая состояние ГЗУ
	Register_type GP_enabled;   // bit    // Работа ГП разрешена
	Register_type KodPSM;       // int8   // Код ПСМ
	Register_type OtvMask;      // int32  // Отводы в замере
//------------------------------------------  
	Register_type GZU_OtvNum;   // int8   // Кол-во отводов
	Register_type ForwardTime;  // int16  // Время прямого хода (сек)
	Register_type ReverseTime;  // int16  // Время обратного хода (сек)
	Register_type StabTime;     // int16  // Время стабилизации (сек)
	Register_type TryNum;       // int8   // Кол-во холостых переводов
	Register_type APV_interval; // int16  // Интервал между попытками АПВ
	Register_type APV_TryNum;   // int8   // Попыток АПВ
//------------------------------------------  
	Register_type EndPeriod;    // bit    // Период замера окончен
	Register_type CmdSwitchOtv; // bit    // КМД Перевод отвода
	Register_type CmdStopReset; // bit    // КМД Сброс СТОПа
	Register_type ManualOtvNum; // int8   // Отвод для ручного замера
	Register_type ExtraOtvNum;  // int8   //Внеочередной  отвод
//  Register_type CmdManual;    // bit    // КМД Ручной замер
} fb00066_IN_type;

typedef struct {
	Register_type Timer1;       // int32
	Register_type Timer2;       // int32
	Register_type KodPSMOld;    // int8
	Register_type TryCount;     // int8
	Register_type APV_TryCount; // int8
	Register_type TempExtra;     // int8
} fb00066_VAR_type;

typedef struct {
	Register_type GP_ON;        // bit
	Register_type GP_OFF;       // bit
	Register_type Counting;     // bit
	Register_type EndPeriod;    // bit
	Register_type TekOtvod;     // int8
	Register_type GZUsost;      // int16
	Register_type ManualOtvNum; // int8   // Отвод для ручного замера
	Register_type TimerOut;     // int16
	Register_type TimerUstOut;  // int16
} fb00066_OUT_type;

// Задержка перед реакцией на изменение кода ПСМ
#define KluchDelay  15

// GZUsost
#define Enabled     (1<<0)  // Работа ФБ разрешена
#define Holded      (1<<1)  // ФБ заморожена
#define GP_En       (1<<2)  // Работа ГП разрешена
#define NeedPerevod (1<<3)  // Необходим перевод отвода

#define Forward     (1<<4)  // Идёт прямой ход
#define Reverse     (1<<5)  // Идёт обратный ход
#define Stab        (1<<6)  // Идёт стабилизация
#define Zamer       (1<<7)  // Идёт замер
#define Stop        (1<<8)  // Стоп
#define FullStop    (1<<9)  // Полный стоп

#define PSMbraked   (1<<10) // Причина стопа - неисправность ПСМ
#define GPbraked    (1<<11) // Причина стопа - неисправность ГП
#define TryCnt0     (1<<12) // Причина стопа - кончились попытки "холостого" переключения
#define Kluch       (1<<13) // Ручной перевод отвода ключём

#define Manual      (1<<14)  // Ручной режим
#define Manual1Cnt  (1<<15)  // Временный ручной замер (1 раз), затем циклический
