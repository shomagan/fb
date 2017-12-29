/* ФБ "Селектор (с обнулением выходов)" */

#define Channels    32

typedef struct {
	Register_type Channel;            // № выхода
	Register_type Input;              // вход
} fb00040_IN_type;

typedef struct {
	Register_type Outputs[Channels];  // Выходы
} fb00040_OUT_type;
