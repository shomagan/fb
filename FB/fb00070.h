/* "Преобразователь маршруса RTM64var -> RTM64" */

typedef struct {
	Register_type Module_Addr;     // int16
	Register_type Module_IntAddr;  // int16
	Register_type RTM_Rout[8];     // int16
} fb00070_IN_type;

typedef struct {
	Register_type Module_Addr;     // int16
	Register_type Module_IntAddr;  // int16
	Register_type RTM_Rout[8];     // int16
} fb00070_OUT_type;
u32 fb00070_var_size(u8 type);
