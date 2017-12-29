/* ФБ "Преобразователь UInt16 -> 2x UInt8" */

typedef struct {
	Register_type Input;  // uint16
} fb00063_IN_type;

typedef struct {
	Register_type LoByte;  // Младший байт
	Register_type HiByte;  // Старший байт
} fb00063_OUT_type;
