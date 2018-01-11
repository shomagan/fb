/* ФБ "фильтр универсальный" */

typedef struct {
	Register_type Enable;  // bit
	Register_type Reset;  // bit
	Register_type FilterTime;     //uint16 filter time 
	Register_type Input;    //bit/uint8/uint16/uint32/float input signal 
} fb00115_IN_type;

typedef struct {
	Register_type OldOutput;    //float Output signal 
	Register_type TikTimer;    //uint32 Output signal 
} fb00115_VAR_type;

typedef struct {
	Register_type Output;    //bit/uint8/uint16/uint32/float Output signal 
} fb00115_OUT_type;
u32 fb00115_var_size(u8 type);
