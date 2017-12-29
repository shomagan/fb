/* ФБ преобразовать 2хuint16 -> uint32 */
                               
typedef volatile struct {
	Register_type BigIn16;		//- uint16 		- старшее число uint16
	Register_type LitIn16;		//- uint16		- младшее число uint16
} fb00092_IN_type;

typedef volatile struct {
	Register_type OutNum;		//- uint32		- число uint32
} fb00092_OUT_type;
