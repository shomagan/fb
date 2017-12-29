/* ФБ "Селектор (без обнуления выходов)" */

#define Channels    32

typedef struct {
	Register_type Channel;            // № выхода
	Register_type Input;              // вход
} fb00071_IN_type;

typedef struct {
	Register_type Outputs[Channels];  // Выходы
} fb00071_OUT_type;
