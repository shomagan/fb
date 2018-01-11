/* ФБ "Счётчик массомер" */

#define k_sutok 86.40f
#define min_gas_pl 0.0001f
#define Pbar 0.1033f  //МПа
#define Patm 0.1033f  //МПа
#define T0   273.15f
#define T20  293.15f

typedef struct {
	Register_type Enable;                  // bit     1
	Register_type Hold;                    // bit     2  Останавливает счёт без сброса текущих параметров
	Register_type Reset;                   // bit     3
	Register_type Time;                    // uint32  4  Текущее количество секунд с начала замера

	Register_type Enable_Liquid;           // bit     5  Вход наличия массомера жидкости
	Register_type Mass_Liquid;             // float32 6  Вход счётчика суммарной массы жидкости в кг
	Register_type Density_Liquid;          // float32 7  Вход плотности жидкости в г/куб.см
	Register_type Mass_Rate_Liquid;        // float32 8  Вход массового расхода жидкости в кг/мин
	Register_type Temperature_Liquid;      // float32 9  Вход температуры жидкости в град С

	Register_type Enable_Gas;              // bit     10 Вход наличия массомера газа
	Register_type Mass_Gas;                // float32 11 Вход счётчика суммарной массы газа в кг
	Register_type Density_Gas;             // uint16  12 Уставка плотности газа по скважине кг/куб.м * 10000
	Register_type Mass_Rate_Gas;           // float32 13 Вход массового расхода газа в кг/мин
	Register_type Temperature_Gas;         // float32 14 Вход температуры газа в град С

	Register_type Enable_Dryness;          // bit     15 Вход наличия влагомера жидкости
	Register_type Dryness_Liquid;          // float32 16 Вход текущей влажности жидкости в %

	Register_type Pressure_Liquid;         // uint16  17 Давление жидкости в коллекторе в МПа * 1000

	Register_type Density_Liquid_Save;     // uint16  18 Уставка плотности жидкости по скважине г/куб.см * 10000
	Register_type Density_Oil_Save;        // uint16  19 Уставка плотности нефти по скважине г/куб.см * 10000
	Register_type Density_Water_Save;      // uint16  20 Уставка плотности воды по скважине г/куб.см * 10000
	Register_type Wm_Water_Save;           // float32 21 Уставка массовой доли воды
	Register_type Gas_Save;                // uint16  22 Уставка газового фактора по скважине куб.м/т * 100
	Register_type Kp;                      // uint8   23 Уставка поправочный коэффициент по жидкости * 100
	Register_type Kg;                      // uint8   24 Уставка поправочный коэффициент по газу * 100

} fb00087_IN_type;

typedef struct {
	Register_type Enable_Old;              // bit     1
	Register_type Value_Liquid_Old;        // float32 2
	Register_type Value_Gas_Old;           // float32 3
	Register_type Value_Dryness_Old;       // float32 4
	Register_type Value_Density_Liquid_Old;// float32 5
	Register_type Wm_Water;                // float32 6  Массовая доля воды
	Register_type Wc_Water;                // float32 7  Объёмная доля воды
	Register_type Err_Mass_Liquid;         // uint8   8
	Register_type Err_Mass_Gas;            // uint8   9
	Register_type Err_Dryness_Liquid;      // uint8   10
	Register_type Err_Summ_Liquid;         // uint8   11
	Register_type Err_Summ_Gas;            // uint8   12
	Register_type Summ_Mass_Water;         // float32 13
	Register_type Summ_Temperature_Liquid; // float32 14
	Register_type Summ_Temperature_Gas;    // float32 15
	Register_type Summ_CNT;                // uint32  16
	Register_type Summ_CNT_Gas;            // uint32  17
} fb00087_VAR_type;

#define MASK_mode_D0      0              // ошибка сумматора расходомера нефти
#define MASK_mode_D1      1              // ошибка сумматора расходомера газа

typedef struct {
	Register_type Summ_Mass_Liquid;        // float32 1  Текущая суммарная масса жидкости в кг
	Register_type Summ_Volume_Liquid;      // float32 2  Текущий суммарный объём жидкости в куб.м
	Register_type Mass_FlowRate_Liquid;    // float32 3  Текущий массовый дебит жидкости в т/сут
	Register_type Volume_FlowRate_Liquid;  // float32 4  Текущий объёмный дебит жидкости в куб.м/сут
	Register_type Sr_Density_Liquid;       // float32 5  Текущая средняя плотность жидкости в г/куб.см
	Register_type Sr_Temperature_Liquid;   // float32 6  Текущая средняя температура жидкости в град.С

	Register_type Summ_Mass_Gas;           // float32 7  Текущий суммарная масса газа в кг
	Register_type Summ_Volume_Gas;         // float32 8  Текущий суммарный объём газа в куб.м
	Register_type Mass_FlowRate_Gas;       // float32 9  Текущия массовый дебит газа в т/сут
	Register_type Volume_FlowRate_Gas;     // float32 10 Текущий объёмный дебит газа в куб.м/сут
	Register_type Density_Gas;             // float32 11 Текущая плотность газа в кг/куб.м
	Register_type Sr_Temperature_Gas;      // float32 12 Текущая средняя температура газа в град.С

	Register_type Sr_Wm_Water;             // float32 13 Средняя массовая доля воды
	Register_type Sr_Wc_Water;             // float32 14 Средняя объёмная доля воды
	Register_type Mass_FlowRate_Water;     // float32 15 Текущия массовый дебит воды в т/сут
	Register_type Volume_FlowRate_Water;   // float32 16 Текущий объёмный дебит воды в куб.м/сут
	Register_type Mass_FlowRate_Oil;       // float32 17 Текущия массовый дебит нефти в т/сут
	Register_type Volume_FlowRate_Oil;     // float32 18 Текущий объёмный дебит нефти в куб.м/сут

	Register_type Pc_Gas;                  // float32 19 Текущий газовый фактор по скважине куб.м/т
	Register_type MASK_mode;               // uint8   20 Режим работы ГЗУ
} fb00087_OUT_type;
u32 fb00087_var_size(u8 type);
