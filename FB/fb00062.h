/* ФБ "Фиксатор переменной (ОЗУ)" */

typedef struct {
	Register_type Fix;  // bit
	Register_type Var_In[256-1];  // Запоминаемый вход
} fb00062_IN_type;

typedef struct {
	Register_type Var_Out[256-1];  // Запомненный выход
} fb00062_OUT_type;
