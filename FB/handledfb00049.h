/* ФБ "Архиватор R7 "Изменение состояния объекта" (тип 17, подтип 4)" */

typedef struct {
	Register_type Enable;     // bit
	Register_type Sost16;     // int16 Sost и Sost1 в одном int16
} fb00049_IN_type;

typedef struct {
	Register_type OldSost16;  // int16 Старые Sost и Sost1 в одном int16
	Register_type Ok;         // bit  
} fb00049_OUT_type;
u32 fb00049_var_size(u8 type);
