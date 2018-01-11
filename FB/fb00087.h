/* �� "������� ��������" */

#define k_sutok 86.40f
#define min_gas_pl 0.0001f
#define Pbar 0.1033f  //���
#define Patm 0.1033f  //���
#define T0   273.15f
#define T20  293.15f

typedef struct {
	Register_type Enable;                  // bit     1
	Register_type Hold;                    // bit     2  ������������� ���� ��� ������ ������� ����������
	Register_type Reset;                   // bit     3
	Register_type Time;                    // uint32  4  ������� ���������� ������ � ������ ������

	Register_type Enable_Liquid;           // bit     5  ���� ������� ��������� ��������
	Register_type Mass_Liquid;             // float32 6  ���� �������� ��������� ����� �������� � ��
	Register_type Density_Liquid;          // float32 7  ���� ��������� �������� � �/���.��
	Register_type Mass_Rate_Liquid;        // float32 8  ���� ��������� ������� �������� � ��/���
	Register_type Temperature_Liquid;      // float32 9  ���� ����������� �������� � ���� �

	Register_type Enable_Gas;              // bit     10 ���� ������� ��������� ����
	Register_type Mass_Gas;                // float32 11 ���� �������� ��������� ����� ���� � ��
	Register_type Density_Gas;             // uint16  12 ������� ��������� ���� �� �������� ��/���.� * 10000
	Register_type Mass_Rate_Gas;           // float32 13 ���� ��������� ������� ���� � ��/���
	Register_type Temperature_Gas;         // float32 14 ���� ����������� ���� � ���� �

	Register_type Enable_Dryness;          // bit     15 ���� ������� ��������� ��������
	Register_type Dryness_Liquid;          // float32 16 ���� ������� ��������� �������� � %

	Register_type Pressure_Liquid;         // uint16  17 �������� �������� � ���������� � ��� * 1000

	Register_type Density_Liquid_Save;     // uint16  18 ������� ��������� �������� �� �������� �/���.�� * 10000
	Register_type Density_Oil_Save;        // uint16  19 ������� ��������� ����� �� �������� �/���.�� * 10000
	Register_type Density_Water_Save;      // uint16  20 ������� ��������� ���� �� �������� �/���.�� * 10000
	Register_type Wm_Water_Save;           // float32 21 ������� �������� ���� ����
	Register_type Gas_Save;                // uint16  22 ������� �������� ������� �� �������� ���.�/� * 100
	Register_type Kp;                      // uint8   23 ������� ����������� ����������� �� �������� * 100
	Register_type Kg;                      // uint8   24 ������� ����������� ����������� �� ���� * 100

} fb00087_IN_type;

typedef struct {
	Register_type Enable_Old;              // bit     1
	Register_type Value_Liquid_Old;        // float32 2
	Register_type Value_Gas_Old;           // float32 3
	Register_type Value_Dryness_Old;       // float32 4
	Register_type Value_Density_Liquid_Old;// float32 5
	Register_type Wm_Water;                // float32 6  �������� ���� ����
	Register_type Wc_Water;                // float32 7  �������� ���� ����
	Register_type Err_Mass_Liquid;         // uint8   8
	Register_type Err_Mass_Gas;            // uint8   9
	Register_type Err_Dryness_Liquid;      // uint8   10
	Register_type Err_Summ_Liquid;         // uint8   11
	Register_type Err_Summ_Gas;            // uint8   12
	Register_type Summ_Mass_Water;         // float32 13
	Register_type Summ_Temperature_Liquid; // float32 14
	Register_type Summ_Temperature_Gas;    // float32 15
	Register_type Summ_CNT;                // uint32  16
	Register_type Summ_CNT_Gas;            // uint32  17
} fb00087_VAR_type;

#define MASK_mode_D0      0              // ������ ��������� ����������� �����
#define MASK_mode_D1      1              // ������ ��������� ����������� ����

typedef struct {
	Register_type Summ_Mass_Liquid;        // float32 1  ������� ��������� ����� �������� � ��
	Register_type Summ_Volume_Liquid;      // float32 2  ������� ��������� ����� �������� � ���.�
	Register_type Mass_FlowRate_Liquid;    // float32 3  ������� �������� ����� �������� � �/���
	Register_type Volume_FlowRate_Liquid;  // float32 4  ������� �������� ����� �������� � ���.�/���
	Register_type Sr_Density_Liquid;       // float32 5  ������� ������� ��������� �������� � �/���.��
	Register_type Sr_Temperature_Liquid;   // float32 6  ������� ������� ����������� �������� � ����.�

	Register_type Summ_Mass_Gas;           // float32 7  ������� ��������� ����� ���� � ��
	Register_type Summ_Volume_Gas;         // float32 8  ������� ��������� ����� ���� � ���.�
	Register_type Mass_FlowRate_Gas;       // float32 9  ������� �������� ����� ���� � �/���
	Register_type Volume_FlowRate_Gas;     // float32 10 ������� �������� ����� ���� � ���.�/���
	Register_type Density_Gas;             // float32 11 ������� ��������� ���� � ��/���.�
	Register_type Sr_Temperature_Gas;      // float32 12 ������� ������� ����������� ���� � ����.�

	Register_type Sr_Wm_Water;             // float32 13 ������� �������� ���� ����
	Register_type Sr_Wc_Water;             // float32 14 ������� �������� ���� ����
	Register_type Mass_FlowRate_Water;     // float32 15 ������� �������� ����� ���� � �/���
	Register_type Volume_FlowRate_Water;   // float32 16 ������� �������� ����� ���� � ���.�/���
	Register_type Mass_FlowRate_Oil;       // float32 17 ������� �������� ����� ����� � �/���
	Register_type Volume_FlowRate_Oil;     // float32 18 ������� �������� ����� ����� � ���.�/���

	Register_type Pc_Gas;                  // float32 19 ������� ������� ������ �� �������� ���.�/�
	Register_type MASK_mode;               // uint8   20 ����� ������ ���
} fb00087_OUT_type;
u32 fb00087_var_size(u8 type);
