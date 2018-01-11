/* ФБ "Массив int8/16 -> 1 bit/int/float" */

#define FB55_InArrayMaxSize    4

typedef union {
	vu8 in8[4];
	vu16 in16[2];
	vu32 in32;
	Flo32 fl32;
} sTempValue;


typedef struct {
	Register_type BigEndian;                    // bit Порядок байт BigEndian
	Register_type InArray[FB55_InArrayMaxSize]; // Входной массив
} fb00055_IN_type;

typedef struct {
	Register_type Out;                          // Выходной элемент
} fb00055_OUT_type;
u32 fb00055_var_size(u8 type);
