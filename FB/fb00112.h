/*������ DO*/
#include "../kernel.h"

typedef struct {
	Register_type N;			// u8 ���������� ��������
	Register_type Format;			// bit ������������ ������, ����� - 1, 0 - �� ���������. � ������� �����: 0�000312 -> 0x312000
	Register_type Input[254];			// u8 ���������� ��������
} fb00112_IN_type;

typedef struct {
	Register_type Temp;			// uint8 ����� � ������ ������� ���������� � ������� ���� � ������� �������
} fb00112_VAR_type;


typedef struct {
	Register_type Output[254];			// bit ������
} fb00112_OUT_type;


void fb00112_exec (void);		// - ������ ������� ����������

