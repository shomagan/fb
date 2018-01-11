/* �� "��������� R7 "����� ���-��������" (��� 16)" */

typedef struct {
	Register_type CmdARX;                 // bit      // ������� �� ���������
	Register_type StartOtvNum;            // int8     // ����� ������ �� ������ ������
	Register_type EndOtvNum;              // int8     // ����� ������ �� ����� ������
	Register_type StartTime;              // int32    // ����� ������ ������
	Register_type CntTime;                // int16    // ������������ ������

	Register_type Summ_Mass_Liquid;       // float32  // ��������� ����� ��� �� �����, �� 4 �����
	Register_type Mass_FlowRate_Liquid;   // float32  // ������� �������� ����� �������� � �/���
	Register_type Volume_FlowRate_Gas;    // float32  // ������� �������� ����� ���� � ���.�/��� 
	Register_type Mass_FlowRate_Oil;      // float32  // ������� �������� ����� ����� � �/���
	Register_type Mass_FlowRate_Water;    // float32  // ������� �������� ����� ���� � �/���
	Register_type Sr_Density_Liquid;      // float32  // ������� ������� ��������� �������� � �/���.�� 
	Register_type Sr_Temperature_Liquid;  // float32  // ������� ������� ����������� �������� � ����.� 
	Register_type Sr_Wm_Water;            // float32  // ������� �������� ���� ���� 
	Register_type Density_Oil_Save;       // uint16   // ������� ��������� ����� �� �������� �/���.�� * 10000 
	Register_type Density_Water_Save;     // uint16   // ������� ��������� ���� �� �������� �/���.�� * 10000
	Register_type Density_Liquid_Save;    // uint16   // ������� ��������� �������� �� �������� �/���.�� * 10000
	Register_type Pc_Gas;                 // float32  // ������� ������� ������ �� �������� ���.�/�
	Register_type Summ_Volume_Gas;        // float32  // ������� ��������� ����� ���� � ���.� 
	Register_type Sync_Liquid;            // uint16   // ���������� ������ ����� ����������
  Register_type Volume_FlowRate_Liquid; // float32  // ������� �������� ����� �������� � ���.�/��� 
  Register_type OtvNumber;              // uint16   // ����� �������� �� ��������
} fb00077_IN_type;

typedef struct {
	Register_type Ok;
} fb00077_OUT_type;
u32 fb00077_var_size(u8 type);
