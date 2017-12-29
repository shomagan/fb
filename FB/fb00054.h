/* ФБ "Компоновщик данных в блоки" */

#define FB54_Mask_FlagsNum  32    // Флагов включения в одном входе-маске
#define FB54_InMaskSize     10    // Кол-во входов-масок
#define FB54_InArraySize    (256 - FB54_InMaskSize)
#define FB54_OutputkSize    256   // Максимальное кол-во выходов (в блоках)

typedef union {
	u8 in8[4];
	u16 in16[2];
	u32 in32;
	Flo32 fl32;
} sTempInput;

typedef struct {
	Register_type inBlokSize;                   // int8   Размер выходных блоков в байтах
	Register_type BigEndian;                  // bit    Порядок байт BigEndian
	Register_type Masks[FB54_InMaskSize];     // int32  Маски включения входных байт в выходные блоки
	Register_type InArrays[FB54_InArraySize]; // vtype  Входной массив
} fb00054_IN_type;

typedef struct {
	Register_type Bloks[FB54_OutputkSize];    // Выход (блоки данных)
} fb00054_OUT_type;

