/* ФБ "ПИД" */

typedef struct {    
	Register_type Enable;				// bit 0 - Ручное, 1 - Автоматическое
	Register_type ReverseU;			// bit 1- реверсивное управление
	Register_type Rezet;			// bit 1- сброс накопленных параметров
	Register_type RequireValue; 		// float Уставка регулирования
  Register_type CurrentValue;			// float Регулируемый параметр
	Register_type kP;		 		// float Коэффициент пропорциональности
	Register_type kI;		  		// float Коэффициент времени интегрирования
	Register_type kD;				// float Коэффициент времени интегрирования
	Register_type Position;	    	// float - необходимое положение регулятора в процентах
	Register_type GistTube;	 		// float Зона нечувствительности в единицах измеряемого параметра
} fb00099_IN_type;

typedef struct {
	Register_type prevEi;		// float - накопленная ошибка интегратора
	Register_type prevEi1;			// float - предыдущее значение ошибки регулирования
	Register_type prevUo;			// float - накопленное воздействия на регулирующий орган
	Register_type EnableOld;			// bit - для отслеживания первого такта включения
	Register_type NumberTick;			// uint32 - количество тактов после включения,для интервала работы
} fb00099_VAR_type;

typedef struct {
	Register_type Error;	     	// bit Индикация ошибки входных параметров
	Register_type Output;	    	// float - необходимое положение регулятора в процентах
	Register_type Test;				// float
} fb00099_OUT_type;

void fb00099_exec();
u32 fb00099_var_size(u8 type);
