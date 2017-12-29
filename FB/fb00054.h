/* �� "����������� ������ � �����" */

#define FB54_Mask_FlagsNum  32    // ������ ��������� � ����� �����-�����
#define FB54_InMaskSize     10    // ���-�� ������-�����
#define FB54_InArraySize    (256 - FB54_InMaskSize)
#define FB54_OutputkSize    256   // ������������ ���-�� ������� (� ������)

typedef union {
	u8 in8[4];
	u16 in16[2];
	u32 in32;
	Flo32 fl32;
} sTempInput;

typedef struct {
	Register_type inBlokSize;                   // int8   ������ �������� ������ � ������
	Register_type BigEndian;                  // bit    ������� ���� BigEndian
	Register_type Masks[FB54_InMaskSize];     // int32  ����� ��������� ������� ���� � �������� �����
	Register_type InArrays[FB54_InArraySize]; // vtype  ������� ������
} fb00054_IN_type;

typedef struct {
	Register_type Bloks[FB54_OutputkSize];    // ����� (����� ������)
} fb00054_OUT_type;

