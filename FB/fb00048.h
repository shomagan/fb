/* ФБ "Архиватор R7 "Замер БГ" (тип 17, подтип 2)" */

typedef struct {
	Register_type CmdARX;      // bit
	Register_type CntNum;      // int8  Номер счётчика
	Register_type Counter;     // int32 Счётчик
	Register_type StartTime;   // int32 Время начала замера
	Register_type CntTime;     // int16 Длительность замера
} fb00048_IN_type;

typedef struct {
	Register_type Ok;
} fb00048_OUT_type;
