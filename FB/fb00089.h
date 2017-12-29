/* �� "������� ������� ���������" (������������ ����) */

#include "../kernel.h"
typedef struct
{
  Register_type Enable;		//bit ���������� ������������
  Register_type Reset;		//bit ��������� ��������
  Register_type Input;		//bit ���� ��� ������
} fb00089_IN_type;

typedef struct {
	Register_type Input;	  //bit			���������� ������� ��� ������� ������
} fb00089_VAR_type;

typedef struct
{
  Register_type Output;		//uint8,16,32
} fb00089_OUT_type;

void fb00089_exec(void);
