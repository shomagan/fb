/* ФБ "Секунд с начала исполнения конфигурации" */

typedef struct {
	Register_type CfgTime;  // uint32/time32 - секунд с начала исполнения конфигурации
} fb00059_OUT_type;
u32 fb00059_var_size(u8 type);
