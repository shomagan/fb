/* ФБ "Архиватор R7 "Изменение AI" (тип 17, подтип 6)" */

typedef struct {
	Register_type Enable;     // bit
	Register_type AINum;      // int8   Номер входа AI
	Register_type AI_Gist;    // int16  Гистерезис
	Register_type AI;      // int16  AI
} fb00051_IN_type;

typedef struct {
	Register_type AI_Old;     // int16  Старое значение AI
	Register_type Ok;         // bit  
} fb00051_OUT_type;
