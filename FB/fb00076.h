/* ФБ "Масштаб величины" */

typedef struct {
	Register_type X_1;  // Т.1 входа
	Register_type X_2;  // Т.2 входа
	Register_type Y_1;  // Т.1 выхода
	Register_type Y_2;  // Т.2 выхода
	Register_type X;    // Несмасштабированный вход
} fb00076_IN_type;

typedef struct {
	Register_type Y;   // Смасштабированный выход
} fb00076_OUT_type;
