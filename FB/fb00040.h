/* �� "�������� (� ���������� �������)" */

#define Channels    32

typedef struct {
	Register_type Channel;            // � ������
	Register_type Input;              // ����
} fb00040_IN_type;

typedef struct {
	Register_type Outputs[Channels];  // ������
} fb00040_OUT_type;
