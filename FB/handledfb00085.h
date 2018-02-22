/* ФБ "Чтение из батарейного домена" */

typedef struct {
	Register_type Address;		// uint16
} fb00085_IN_type;

typedef struct {
	Register_type Value;		// int8/16/32/Float32/Time
} fb00085_OUT_type;



u32 fb00085_var_size(u8 type);
