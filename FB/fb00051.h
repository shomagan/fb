/* �� "��������� R7 "��������� AI" (��� 17, ������ 6)" */

typedef struct {
	Register_type Enable;     // bit
	Register_type AINum;      // int8   ����� ����� AI
	Register_type AI_Gist;    // int16  ����������
	Register_type AI;      // int16  AI
} fb00051_IN_type;

typedef struct {
	Register_type AI_Old;     // int16  ������ �������� AI
	Register_type Ok;         // bit  
} fb00051_OUT_type;
