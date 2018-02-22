/* ФБ "Архиватор R7 "Замер ГЗУ" (тип 17, подтип 1)" */

typedef struct {
	Register_type CmdARX;      // bit
	Register_type OtvNum;      // int8  Номер отвода 
	Register_type Counter;     // int32 Счётчик
	Register_type StartTime;   // int32 Время начала замера
	Register_type CntTime;     // int16 Длительность замера
} fb00047_IN_type;

typedef struct {
	Register_type Ok;
} fb00047_OUT_type;
u32 fb00047_var_size(u8 type);
