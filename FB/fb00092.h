/* �� ������������� 2�uint16 -> uint32 */
                               
typedef volatile struct {
	Register_type BigIn16;		//- uint16 		- ������� ����� uint16
	Register_type LitIn16;		//- uint16		- ������� ����� uint16
} fb00092_IN_type;

typedef volatile struct {
	Register_type OutNum;		//- uint32		- ����� uint32
} fb00092_OUT_type;
