/* ФБ "Алгебраическое сложение" */

#define MaxInputs 32

typedef struct {
	Register_type Inputs[MaxInputs];
} fb00014_IN_type;

typedef struct {
	Register_type Output;
	Register_type Overflow;
} fb00014_OUT_type;
