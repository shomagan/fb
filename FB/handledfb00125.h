/*ФБ "Вход - выход сквозной" */

typedef struct {
	Register_type rtm_address_config;  // uint16
} fb00125_IN_type;
typedef struct {
	Register_type Previos[256];  // bit/u8/u16/u32/float
} fb00125_VAR_type;

typedef struct {
	Register_type NewValue[256];  // bit/u8/u16/u32/float
} fb00125_OUT_type;
u32 fb00125_var_size(u8 type);
