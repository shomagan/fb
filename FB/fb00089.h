/* ФБ "Счетчик входных импульсов" (заголовочный файл) */

#include "../kernel.h"
typedef struct
{
  Register_type Enable;		//bit разрешение тактирования
  Register_type Reset;		//bit обнуление счетчика
  Register_type Input;		//bit вход для тактов
} fb00089_IN_type;

typedef struct {
	Register_type Input;	  //bit			Внутренний счетчик для отсчета секунд
} fb00089_VAR_type;

typedef struct
{
  Register_type Output;		//uint8,16,32
} fb00089_OUT_type;

void fb00089_exec(void);
