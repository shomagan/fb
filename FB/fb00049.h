/* �� "��������� R7 "��������� ��������� �������" (��� 17, ������ 4)" */

typedef struct {
	Register_type Enable;     // bit
	Register_type Sost16;     // int16 Sost � Sost1 � ����� int16
} fb00049_IN_type;

typedef struct {
	Register_type OldSost16;  // int16 ������ Sost � Sost1 � ����� int16
	Register_type Ok;         // bit  
} fb00049_OUT_type;
