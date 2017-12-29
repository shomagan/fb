/* "Ñ÷¸ò÷èê" */

typedef struct {
	Register_type Enable;       // bit
	Register_type Reset;        // bit
	Register_type Value;        // int8/16/32/float32
} fb00037_IN_type;

typedef struct {
	Register_type Enable_Old;   // bit
	Register_type Value_Old;    // int8/16/32
} fb00037_VAR_type;

typedef struct {
	Register_type Counter;        // int8/16/32
} fb00037_OUT_type;
