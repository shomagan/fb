/* �� "��������� R7 ������������� (��� 18)" */

typedef struct {
	Register_type Enable;      // bit
	Register_type R7Data[R7_BodySize];
} fb00030_IN_type;

typedef struct {
	Register_type Ok;
} fb00030_OUT_type;
