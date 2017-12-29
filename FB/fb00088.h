/*ФБ "Архиватор Динамограм R7" (заголовочный файл)*/

#define FB88_ArrayMaxSize 192

typedef struct {
	Register_type InDNMNumber;                   // int8 Nomer packeta DNM prihodit iz drugogo bloka ili s vihoda OutDNMNumber  
	Register_type Enable;                  // bit Разрешает запись входного массива в выходной 
	Register_type SaveDNM;                   // bit Архивация выходного массива во FLASH
	Register_type KnapReady;                   // bit Разрешение записи Кнапа  
	Register_type KnapValue;                   // uint8 
	Register_type InArray[FB88_ArrayMaxSize];    // Входной массив
} fb00088_IN_type;
  
typedef struct {
	Register_type OutArray[FB88_ArrayMaxSize];  // Выходной массив        Register_type State;
	Register_type State;     	// uint8 состояние  
	Register_type KnapValue;                   // uint8 Архивация выходного массива во FLASH    
	Register_type OutDNMNumber;                   // int8 Nomer packeta DNM 
} fb00088_OUT_type;

