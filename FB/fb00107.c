/*������ DO*/
#include "../vars.h"
#include <string.h>
#include "../kernel.h"
#include "../regs.h"

#include "fb00107.h"
#define BIT(x)	(1<<(x))

void fb00107_exec(void)
{
	fb00107_IN_type *IN = (fb00107_IN_type *) FBInputs;
	fb00107_OUT_type *OUT = (fb00107_OUT_type *) FBOutputs;
	
	vu8 i, j;
	vu8 Nbit;
	OUT->Error.Data.bit=0;
	
	Nbit = IN->Nbit.Data.uint8;
	
	for (i=0; i<16;i++){ // �������� ������ ���������� �� � ���, ����� �� ������ �������� ��� � �������������
		OUT->OUT[i].Data.uint8 = IN->IN[i].Data.uint8;
	}
	
	if (Nbit && (Nbit<64)) { // �������� �� ������ � �� 0
		Nbit--;  							//Nbit ������ � 1 DO. 
		if (Nbit>=4){ // 4 DO � ����� ������
				i=(Nbit)/4;
				j=Nbit-i*4;
				if (IN->Bit.Data.bit) {OUT->OUT[i].Data.uint8 |= (BIT(j) | BIT(j+4));} 
				else {
					OUT->OUT[i].Data.uint8 &= ~BIT(j);
					OUT->OUT[i].Data.uint8 |= BIT(j+4);
				}
		} else {
				if (IN->Bit.Data.bit) {OUT->OUT[0].Data.uint8 |= (BIT(Nbit) | BIT(Nbit+4));} 
				else {
					OUT->OUT[0].Data.uint8 &= ~BIT(Nbit);
					OUT->OUT[0].Data.uint8 |= BIT(Nbit+4);
				} // ����� ��������� DO �� �����. ������ 4 ���� �����.
		}

	} else OUT->Error.Data.bit=1; // ������!
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00107_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00107_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00107_OUT_type);
    default:
        return 0;
    }
}
