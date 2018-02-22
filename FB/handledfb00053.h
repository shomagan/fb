/* ФБ "Часть массива" */

#define FB53_InArrayMaxSize    250
#define FB53_OutArrayMaxSize   250

typedef struct {
	Register_type StartByte;                  // int8   Начальный байт входного массива, с которого ФБ начнёт копировать элементы в выход
	Register_type NumBytes;                   // int8   Кол-во байт для копирования в выход
	Register_type InArray[FB53_InArrayMaxSize];    // Входной массив
} fb00053_IN_type;

typedef struct {
	Register_type OutArray[FB53_OutArrayMaxSize];  // Выходной массив
} fb00053_OUT_type;

typedef union{
	u8 uint8[250] ;
	u16 uint16[125];
	u32 uint32[62];
} Dataunion;
u32 fb00053_var_size(u8 type);
