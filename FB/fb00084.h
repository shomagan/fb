/* ФБ "Запись в батарейный домен" */

typedef struct {
	Register_type EnWrite;			// bit
	Register_type Address;			// uint16
	Register_type Value;			// int8/16/32/float32/time
} fb00084_IN_type;

typedef struct {
	Register_type Ok;				// bit
} fb00084_OUT_type;
