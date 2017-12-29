/* ФБ "Преобразователь массива uint16_BE->массив uint8" */

typedef struct {
	Register_type BigEndian;    // Входные элементы
	Register_type Input[256-1];  // Входные элементы
} fb00065_IN_type;

typedef struct {
	Register_type Output[256];  // Выходной массив
} fb00065_OUT_type;
