/* ФБ "Преобразователь UInt32 -> 4x UInt8" */

typedef struct {
	Register_type Input;  // uint32
} fb00114_IN_type;

typedef struct {
	Register_type One;  // 1
	Register_type Two;  // 2
	Register_type Three;  // 3
	Register_type Four;  // 4
} fb00114_OUT_type;
