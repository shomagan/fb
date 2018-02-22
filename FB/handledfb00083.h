/* ФБ "Архиватор R7 "Состояние DI КП КТПН" (тип 18)" */

typedef struct {
	Register_type CmdArch;		// bit      // Команда на архивацию
	Register_type NChan;		// uint8	// Номер канала
	Register_type AuthorArch;		// byte     // Инициатор создания архива
	Register_type SostDI;		// uint16   // Текущее состояние DI
	Register_type PrevSostDI;		// uint16   // Предыдущее состояние DI
	Register_type DurationSostDI;		// uint32   // Продолжительность предыдущего состояния DI
	Register_type EventTime;		// time     // Время возникновения события
} fb00083_IN_type;

typedef struct {
	Register_type Ok;		// bit
} fb00083_OUT_type;
u32 fb00083_var_size(u8 type);
