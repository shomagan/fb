/*�� "��������� ���������� R7" (������������ ����)*/

#define FB88_ArrayMaxSize 192

typedef struct {
	Register_type InDNMNumber;                   // int8 Nomer packeta DNM prihodit iz drugogo bloka ili s vihoda OutDNMNumber  
	Register_type Enable;                  // bit ��������� ������ �������� ������� � �������� 
	Register_type SaveDNM;                   // bit ��������� ��������� ������� �� FLASH
	Register_type KnapReady;                   // bit ���������� ������ �����  
	Register_type KnapValue;                   // uint8 
	Register_type InArray[FB88_ArrayMaxSize];    // ������� ������
} fb00088_IN_type;
  
typedef struct {
	Register_type OutArray[FB88_ArrayMaxSize];  // �������� ������        Register_type State;
	Register_type State;     	// uint8 ���������  
	Register_type KnapValue;                   // uint8 ��������� ��������� ������� �� FLASH    
	Register_type OutDNMNumber;                   // int8 Nomer packeta DNM 
} fb00088_OUT_type;

