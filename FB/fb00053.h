/* �� "����� �������" */

#define FB53_InArrayMaxSize    250
#define FB53_OutArrayMaxSize   250

typedef struct {
	Register_type StartByte;                  // int8   ��������� ���� �������� �������, � �������� �� ����� ���������� �������� � �����
	Register_type NumBytes;                   // int8   ���-�� ���� ��� ����������� � �����
	Register_type InArray[FB53_InArrayMaxSize];    // ������� ������
} fb00053_IN_type;

typedef struct {
	Register_type OutArray[FB53_OutArrayMaxSize];  // �������� ������
} fb00053_OUT_type;

typedef union{
	u8 uint8[250] ;
	u16 uint16[125];
	u32 uint32[62];
} Dataunion;
