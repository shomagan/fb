/* ФБ "Архиватор R7 "Протокол работы объекта" (тип 17, подтип 7)" */

typedef struct {
  Register_type CmdARX;     // bit
  Register_type EventID;    // int8   Код события
  Register_type DD0;        // int8   Байт 0 описания события
  Register_type DD1;        // int8   Байт 1 описания события
  Register_type DD2;        // int8   Байт 2 описания события
  Register_type DD3;        // int8   Байт 3 описания события
} fb00052_IN_type;

typedef struct {
  Register_type Ok;         // bit  
} fb00052_OUT_type;
