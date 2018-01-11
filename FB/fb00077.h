/* ФБ "Архиватор R7 "Замер ГЗУ-Массомер" (тип 16)" */

typedef struct {
	Register_type CmdARX;                 // bit      // Команда на архивацию
	Register_type StartOtvNum;            // int8     // Номер отвода на начало замера
	Register_type EndOtvNum;              // int8     // Номер отвода на конец замера
	Register_type StartTime;              // int32    // Время начала замера
	Register_type CntTime;                // int16    // Длительность замера

	Register_type Summ_Mass_Liquid;       // float32  // Суммарная масса ВНС за замер, кг 4 байта
	Register_type Mass_FlowRate_Liquid;   // float32  // Текущия массовый дебит жидкости в т/сут
	Register_type Volume_FlowRate_Gas;    // float32  // Текущий объёмный дебит газа в куб.м/сут 
	Register_type Mass_FlowRate_Oil;      // float32  // Текущия массовый дебит нефти в т/сут
	Register_type Mass_FlowRate_Water;    // float32  // Текущия массовый дебит воды в т/сут
	Register_type Sr_Density_Liquid;      // float32  // Текущая средняя плотность жидкости в г/куб.см 
	Register_type Sr_Temperature_Liquid;  // float32  // Текущая средняя температура жидкости в град.С 
	Register_type Sr_Wm_Water;            // float32  // Средняя массовая доля воды 
	Register_type Density_Oil_Save;       // uint16   // Уставка плотности нефти по скважине г/куб.см * 10000 
	Register_type Density_Water_Save;     // uint16   // Уставка плотности воды по скважине г/куб.см * 10000
	Register_type Density_Liquid_Save;    // uint16   // Уставка плотности жидкости по скважине г/куб.см * 10000
	Register_type Pc_Gas;                 // float32  // Текущий газовый фактор по скважине куб.м/т
	Register_type Summ_Volume_Gas;        // float32  // Текущий суммарный объём газа в куб.м 
	Register_type Sync_Liquid;            // uint16   // Количество циклов слива сепаратора
  Register_type Volume_FlowRate_Liquid; // float32  // Текущий объёмный дебит жидкости в куб.м/сут 
  Register_type OtvNumber;              // uint16   // номер скважены по паспорту
} fb00077_IN_type;

typedef struct {
	Register_type Ok;
} fb00077_OUT_type;
u32 fb00077_var_size(u8 type);
