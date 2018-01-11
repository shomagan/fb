/*������ DO*/
#include "../kernel.h"
extern vu8 Buff_Pack[];
typedef struct {
	Register_type Enable;			// bit ������
	Register_type Reset;			// bit ������������ ������ ��
	Register_type Chanel;			// uint8 �����
	Register_type Type;			// uint8 ��� ����������
	// 0 ������ ��������
	// 1 - Sonomer 500 ������������
	// 2 - �������� 230 ��������������
	// 3 - ������� ����������� RS485
	// 4 - �������� 203.2� ��������������
	// 5 - ���������� �� �������
	Register_type Options;			// uint8 ����� ����������� ����������
	// 0 - �� ��������� �������� ������, �� ��������� ���� �� ������ ����� ��� ������ �� ������� �����
	// 1 - �������� ������ 1 ��� � �� ���������, ��� �������� ������ ���� ������
	// 2 - �������� ������ ������ ��� ���� �� ������� ������ �����
	Register_type Stady;			// uint8 
	Register_type Nbyte;			// uint8 
	Register_type Byte[256];			// uint8 ����� �� ������ � �����
} fb00111_IN_type;

typedef struct {
	Register_type TimeOut;			// uint8 ����� � ������ ������� ���������� � ������� ���� � ������� �������
	Register_type LogEnd;					// bit  ������ ���������
	Register_type SR;						// bit	 ���������� �������� ��� Run - Exit ����� Enable = 0
	Register_type Temp; 				//uint8 
} fb00111_VAR_type;


typedef struct {
	Register_type Error;			// bit ������
	Register_type Ok;			// bit ������
	Register_type Run;			// bit 1 ����� ���������� ������ ��
	Register_type Data[256 - 3];			// u8 ������
} fb00111_OUT_type;


void fb00111_exec (void);		// - ������ ������� ����������
vu16 MbusCRC(vu8 *buff, vu8 len);		// ������ crc � ������ M-bus
vu8 AnalizData(vu8 len);		// ������ �������� ������ �� ��������
vu8 FillBuf (void);				// ��������� ������ �� ��������, ������ CRC
u16 m_crc16(vu8* pck, vu8 len); // ������ crc Matlab
u32 fb00111_var_size(u8 type);
