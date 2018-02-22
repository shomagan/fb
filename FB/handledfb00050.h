/* ФБ "Архиватор R7 "Изменение DI" (тип 17, подтип 5)" */

typedef struct {
	Register_type Enable;     // bit
	Register_type DINum;      // int8 Номер входа DI
	Register_type DI;         // bit  DI
} fb00050_IN_type;

typedef struct {
	Register_type DI_Old;     // bit Старое значение DI
	Register_type Ok;         // bit  
} fb00050_OUT_type;
u32 fb00050_var_size(u8 type);
