/* ФБ "Триггер со сбросом через N тактов" */

typedef struct {
	Register_type Input;      // bit
	Register_type SetTime;
} fb00029_IN_type;

typedef struct {
	Register_type Tics;
} fb00029_VAR_type;

typedef struct {
	Register_type Output;
} fb00029_OUT_type;
