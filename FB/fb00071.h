/* �� "�������� (��� ��������� �������)" */

#define Channels    32

typedef struct {
	Register_type Channel;            // � ������
	Register_type Input;              // ����
} fb00071_IN_type;

typedef struct {
	Register_type Outputs[Channels];  // ������
} fb00071_OUT_type;
u32 fb00071_var_size(u8 type);
