/* ФБ "Системное время: текущая дата и время в int32" */

typedef struct {
	Register_type SystemTime;
	Register_type Need2Sync;
} fb00023_OUT_type;
u32 fb00023_var_size(u8 type);
