/* �� "������� ��������" */
#include <math.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00072.h"
#include "fb00087.h"
typedef float float32;

void fb00087_exec(void)
{
  fb00087_IN_type *IN = (fb00087_IN_type *) FBInputs;
  fb00087_VAR_type *VAR = (fb00087_VAR_type *) FBVars;
  fb00087_OUT_type *OUT = (fb00087_OUT_type *) FBOutputs;

  float32 fl, Mass, Vol, PlFl_Liquid, Wfl, Po, Pw;
    fl=0.0;
    Mass=0.0;
    Vol=0.0;
    PlFl_Liquid=0.0;
    Wfl=0.0;
    Po=0.0;
    Pw=0.0;

    if ((IN->Reset.Data.bit) || (!(IN->Enable.Data.bit))) { // ����� ������

        OUT->Summ_Mass_Liquid.Data.float32 = 0.0;        // float32 ������� ��������� ����� �������� � ��
        OUT->Summ_Volume_Liquid.Data.float32 = 0.0;      // float32 ������� ��������� ����� �������� � ���.�
        OUT->Summ_Mass_Gas.Data.float32 = 0.0;           // float32 ������� ��������� ����� ���� � ��
        OUT->Summ_Volume_Gas.Data.float32 = 0.0;         // float32 ������� ��������� ����� ���� � ���.�
        OUT->MASK_mode.Data.uint8 = 0;

        OUT->Density_Gas.Data.float32 = 0.0;             // float32 ������� ��������� ���� � �/���.��
        OUT->Sr_Temperature_Gas.Data.float32 = 0.0;      // float32 ������� ������� ����������� ���� � ����.�
        OUT->Sr_Wm_Water.Data.float32 = 0.0;             // float32 ������� �������� ���� ����
        OUT->Sr_Wc_Water.Data.float32 = 0.0;             // float32 ������� �������� ���� ����

        OUT->Mass_FlowRate_Water.Data.float32 = 0.0;     // float32 ������� �������� ����� ���� � �/���
        OUT->Volume_FlowRate_Water.Data.float32 = 0.0;   // float32 ������� �������� ����� ���� � ���.�/���
        OUT->Mass_FlowRate_Oil.Data.float32 = 0.0;       // float32 ������� �������� ����� ����� � �/���
        OUT->Volume_FlowRate_Oil.Data.float32 = 0.0;     // float32 ������� �������� ����� ����� � ���.�/���

        OUT->Pc_Gas.Data.float32 = 0.0;                  // float32 ������� ������� ������ �� �������� ���.�/�
        //    OUT->Sync_Liquid.Data.uint16 = 0;                // uint16  ���������� ������ ����� ����������
        OUT->Mass_FlowRate_Liquid.Data.float32 = 0.0;    // float32 ������� �������� ����� �������� � �/���
        OUT->Volume_FlowRate_Liquid.Data.float32 = 0.0;  // float32 ������� �������� ����� �������� � ���.�/���
        OUT->Sr_Density_Liquid.Data.float32 = 0.0;       // float32 ������� ������� ��������� �������� � �/���.��
        OUT->Sr_Temperature_Liquid.Data.float32 = 0.0;   // float32 ������� ������� ����������� �������� � ����.�
        OUT->Mass_FlowRate_Gas.Data.float32 = 0.0;       // float32 ������� �������� ����� ���� � �/���
        OUT->Volume_FlowRate_Gas.Data.float32 = 0.0;     // float32 ������� �������� ����� ���� � ���.�/���


        VAR->Value_Liquid_Old.Data.float32 = 0.0;        // float32
        VAR->Value_Gas_Old.Data.float32 = 0.0;           // float32
        VAR->Value_Dryness_Old.Data.float32 = 0.0;       // float32
        VAR->Value_Density_Liquid_Old.Data.float32 = 0.0;// float32
        VAR->Wm_Water.Data.float32 = 0.0;                // float32 �������� ���� ����
        VAR->Wc_Water.Data.float32 = 0.0;                // float32 �������� ���� ����
        VAR->Err_Mass_Liquid.Data.uint8 = 0;             // uint8
        VAR->Err_Mass_Gas.Data.uint8 = 0;                // uint8
        VAR->Err_Dryness_Liquid.Data.uint8 = 0;          // uint8
        VAR->Err_Summ_Liquid.Data.uint8 = 0;             // uint8
        VAR->Err_Summ_Gas.Data.uint8 = 0;                // uint8
        VAR->Summ_Mass_Water.Data.float32 = 0.0;         // float32
        VAR->Summ_Temperature_Liquid.Data.float32 = 0.0; // float32
        VAR->Summ_Temperature_Gas.Data.float32 = 0.0;    // float32
        VAR->Summ_CNT.Data.uint32 = 0;                   // uint32
        VAR->Summ_CNT_Gas.Data.uint32 = 0;               // uint32
        VAR->Enable_Old.Data.bit = 0;
    } else {
        if (VAR->Enable_Old.Data.bit) {
            if (IN->Enable_Dryness.Data.bit){//add mark of input data from dryness module meuser
              if (IN->Dryness_Liquid.Data.float32<0.0f){
                IN->Dryness_Liquid.Data.float32=0.0f;
             		LedErrorOn(100);
              }else if(IN->Dryness_Liquid.Data.float32>100.0f){
                IN->Dryness_Liquid.Data.float32=100.0f;
             		LedErrorOn(100);
              }
            }
            if ((IN->Enable_Liquid.Data.bit) && (!IN->Hold.Data.bit)) { // �������� ������ � ���������� ��������
                //======================================== ������ ������� �������� ========================================//
                if (fabsf(IN->Mass_Liquid.Data.float32-0.0f) >= 0.01f) {
                    if ((fabsf(IN->Mass_Liquid.Data.float32 - VAR->Value_Liquid_Old.Data.float32) >= 0.01f) && (IN->Density_Liquid.Data.float32 > 0.0001f)) {

                        Mass = IN->Mass_Liquid.Data.float32 - VAR->Value_Liquid_Old.Data.float32; // ���������� ���������� ����� ��������
                        OUT->Summ_Mass_Liquid.Data.float32 += Mass;                               // ��������� ������� ����� ��������

                        PlFl_Liquid = IN->Density_Liquid.Data.float32;

                        Vol = ((Mass / PlFl_Liquid) / 1000.0f);  // ���������� ������ �������� �� �� � ���.�
                        Vol = Vol * IN->Kp.Data.uint8 / 100;

                        if (Vol > 0.0f) OUT->Summ_Volume_Liquid.Data.float32 += Vol;         // ������� c�������� ����� ��������

                        VAR->Err_Summ_Liquid.Data.uint8 = 0;



                        if ((OUT->Summ_Mass_Liquid.Data.float32 == 0.0f) || (OUT->Summ_Volume_Liquid.Data.float32 == 0.0f))
                            OUT->Sr_Density_Liquid.Data.float32 = PlFl_Liquid;
                        else
                            OUT->Sr_Density_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 / OUT->Summ_Volume_Liquid.Data.float32) / 1000;  // ������� ��������� ��������
						
            						PlFl_Liquid = OUT->Sr_Density_Liquid.Data.float32;

						            VAR->Summ_Temperature_Liquid.Data.float32 += IN->Temperature_Liquid.Data.float32;  // ��������� ����������� �� �����
                        OUT->Sr_Temperature_Liquid.Data.float32 = VAR->Summ_Temperature_Liquid.Data.float32 / (++VAR->Summ_CNT.Data.uint32);  // ������� ����������� ��������
                    }
                } else {
                    if (++VAR->Err_Summ_Liquid.Data.uint8 >= 20) {
                        OUT->MASK_mode.Data.uint8 |= (1 << MASK_mode_D0);
                        VAR->Err_Summ_Liquid.Data.uint8 = 20;
                    }
                }
				
        				OUT->Mass_FlowRate_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 * k_sutok) / (float32)(IN->Time.Data.uint32 + 1);
                if (OUT->Sr_Density_Liquid.Data.float32 > 0.0001f){
	                  OUT->Volume_FlowRate_Liquid.Data.float32 = OUT->Mass_FlowRate_Liquid.Data.float32 / OUT->Sr_Density_Liquid.Data.float32;}      // ������� �������� ����� ��������
                //======================================== ������ ��������� �������� ========================================//
                // ���������� ��������� ����� � ������� ��������
        				if (IN->Pressure_Liquid.Data.uint16 >= 0.0f){
           					fl = calc_ro_oil(((float)IN->Density_Oil_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);}
			  	
				        Po = fl/1000;

                // ���������� ��������� ���� � ������� ��������
                if (IN->Pressure_Liquid.Data.uint16 >= 0.0f)
                    fl = calc_ro_water(((float)IN->Density_Water_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);

                Pw = fl/1000;

                if (IN->Enable_Dryness.Data.bit) {// �������� ������ � ����������
                    if (VAR->Value_Dryness_Old.Data.float32 == 0.0f) {
                        VAR->Value_Dryness_Old.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                        VAR->Wm_Water.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                    } else {
                        VAR->Value_Dryness_Old.Data.float32 = VAR->Wm_Water.Data.float32;
                        VAR->Wm_Water.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                    }

                    if(VAR->Value_Density_Liquid_Old.Data.float32 == 0.0f) {
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid; //IN->Density_Liquid.Data.float32
                        if (PlFl_Liquid > 0.0001f) VAR->Wm_Water.Data.float32 = VAR->Wm_Water.Data.float32 *(Pw/PlFl_Liquid);                // �������� ���� �����
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f){ Wfl = VAR->Value_Dryness_Old.Data.float32 * (Pw/VAR->Value_Density_Liquid_Old.Data.float32);}      // �������� ���� ����� �� ���������� ������
                        else{Wfl = VAR->Wm_Water.Data.float32 ;}
                    } else {
                        if (PlFl_Liquid > 0.0001f) VAR->Wm_Water.Data.float32 = VAR->Wm_Water.Data.float32*(Pw/ PlFl_Liquid);                // �������� ���� �����
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f){ Wfl = VAR->Value_Dryness_Old.Data.float32 * (Pw/VAR->Value_Density_Liquid_Old.Data.float32);}      // �������� ���� ����� �� ���������� ������
                        else{Wfl = VAR->Wm_Water.Data.float32 ;}
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                    }
                    VAR->Wm_Water.Data.float32 = (VAR->Wm_Water.Data.float32 + Wfl)/2.0f;
                    if (VAR->Wm_Water.Data.float32>1.0f){
                      VAR->Wm_Water.Data.float32 = 1.0f;
                    }else if(VAR->Wm_Water.Data.float32<0.0f){
                      VAR->Wm_Water.Data.float32 = 0.0f;
                    }
//                    if (Mass > 0.0) VAR->Wc_Water.Data.float32 = 1.0 - ((VAR->Wm_Water.Data.float32 + Wfl) / 2.0);  // �������� ���� ����
//                                                               1.0 - ((VAR->Wc_Water.Data.float32 + VAR->Value_Dryness_Old.Data.float32 * (Po/VAR->Value_Density_Liquid_Old.Data.float32)) / 2.0)
//                                                               1.0 - ((VAR->Wc_Water.Data.float32 + VAR->Wc_Water.Data.float32 * (Po/PlFl_Liquid)) / 2.0)
//                                                               1.0 - ((VAR->Wc_Water.Data.float32*(1+(Po/PlFl_Liquid)) / 2.0)
//                                                               (2.0 - VAR->Wc_Water.Data.float32*(1+(Po/PlFl_Liquid))) / 2.0
//                    else VAR->Wc_Water.Data.float32 = IN->Wc_Water_Save.Data.float32;
                } else {
                    // ������� ������������ �����
                    if (VAR->Value_Density_Liquid_Old.Data.float32 == 0.0f) {
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                        if ((Pw > PlFl_Liquid) && (Pw > Po) && (PlFl_Liquid > 0.0001f)) {
                            fl = (PlFl_Liquid - Pw) / (Po - Pw);
                            VAR->Wm_Water.Data.float32 = 1.0f - (fl * (Po / PlFl_Liquid));
                            if ((VAR->Wm_Water.Data.float32 <= 0.0f) || (VAR->Wm_Water.Data.float32 >= 1.0f)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        } else {
                            VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        }
                    } else {
                        if ((Pw > ((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2.0f)) && (Pw > Po) && (PlFl_Liquid > 0.0001f)) {
                            fl = (((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2.0f) - Pw) / (Po - Pw);
                            VAR->Wm_Water.Data.float32 = 1.0f - (fl * (Po / ((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2.0f)));
                            if ((VAR->Wm_Water.Data.float32 <= 0.0f) || (VAR->Wm_Water.Data.float32 >= 1.0f)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        } else {
                            VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        }
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                    }
                    if (VAR->Wm_Water.Data.float32 >= 1) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                }

                VAR->Summ_Mass_Water.Data.float32 += Mass * VAR->Wm_Water.Data.float32;              // ��������� ����� ����

                OUT->Mass_FlowRate_Water.Data.float32 = (VAR->Summ_Mass_Water.Data.float32 * k_sutok) / (float)(IN->Time.Data.uint32 + 1); // ������� �������� ����� ����
                OUT->Mass_FlowRate_Oil.Data.float32 = OUT->Mass_FlowRate_Liquid.Data.float32 - OUT->Mass_FlowRate_Water.Data.float32;

                OUT->Volume_FlowRate_Water.Data.float32 = OUT->Mass_FlowRate_Water.Data.float32 / Pw;                              // ������� �������� ����� ����
                OUT->Volume_FlowRate_Oil.Data.float32 = OUT->Mass_FlowRate_Oil.Data.float32 / Po;                                  // ������� �������� ����� �����

                if ((VAR->Wm_Water.Data.float32 <= 0.0f) || (VAR->Wm_Water.Data.float32 >= 1.0f)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                OUT->Sr_Wm_Water.Data.float32 = OUT->Mass_FlowRate_Water.Data.float32 / OUT->Mass_FlowRate_Liquid.Data.float32;       // ������� ������������ ����� � %*100*/
                OUT->Sr_Wc_Water.Data.float32 = OUT->Volume_FlowRate_Water.Data.float32 / OUT->Volume_FlowRate_Liquid.Data.float32;   //

                //======================================== ������ �������� ���� ========================================//

                // ��������� ���� 1:150 ����� � 60 ���*/
                if (IN->Enable_Gas.Data.bit) { // ���� ���� ���������� ����, ���������� ��� ���������
                    if (IN->Mass_Gas.Data.float32 >= 0.0f) {
                        if ((IN->Mass_Gas.Data.float32 >= VAR->Value_Gas_Old.Data.float32) && (VAR->Value_Gas_Old.Data.float32 > 0.0f)) {
                            // ���������� ������ ���� �� ������
                            fl = IN->Mass_Gas.Data.float32 - VAR->Value_Gas_Old.Data.float32;
                            OUT->Summ_Mass_Gas.Data.float32 += fl;
                            OUT->Density_Gas.Data.float32 = IN->Density_Gas.Data.uint16 / 10000.0f;
                            fl = (fl / OUT->Density_Gas.Data.float32);
                            fl = fl * IN->Kg.Data.uint8 / 100;


                            OUT->Summ_Volume_Gas.Data.float32 += fl;   // ������� c�������� ����� ���� � ���.�
                            OUT->Volume_FlowRate_Gas.Data.float32 = (OUT->Summ_Volume_Gas.Data.float32 * k_sutok *1000.0f) / (float)(IN->Time.Data.uint32 + 1);  // ������� �������� ����� ����
                        }

                        VAR->Summ_Temperature_Gas.Data.float32 += IN->Temperature_Gas.Data.float32;  // ��������� ����������� ���� �� �����
                        OUT->Sr_Temperature_Gas.Data.float32 = VAR->Summ_Temperature_Gas.Data.float32 / (++VAR->Summ_CNT_Gas.Data.uint32);  // ������� ����������� ����
                        VAR->Err_Summ_Gas.Data.uint8 = 0;
                    } else {
                        if (++VAR->Err_Summ_Gas.Data.uint8 >= 20) {
                            OUT->MASK_mode.Data.uint8 |= (1 << MASK_mode_D1);
                            VAR->Err_Summ_Gas.Data.uint8 = 20;
                        }
                    }

                    if (OUT->Mass_FlowRate_Oil.Data.float32 > 0.0f)
                        OUT->Pc_Gas.Data.float32 = OUT->Volume_FlowRate_Gas.Data.float32 / OUT->Mass_FlowRate_Oil.Data.float32;   // ������� ������
                } else {  // ���� ��� ����������� ����
                    OUT->Volume_FlowRate_Gas.Data.float32 = ((float)IN->Gas_Save.Data.uint16 / 100) * OUT->Mass_FlowRate_Oil.Data.float32;  // ������� �������� ����� ����
                    OUT->Pc_Gas.Data.float32 = (float32)(IN->Gas_Save.Data.uint16) / 100;   // ������� ������
                }
            }
        }
        VAR->Value_Liquid_Old.Data.float32 = IN->Mass_Liquid.Data.float32;        // ��������� ������� ��������� �������� ��� ���������� �����
        VAR->Value_Gas_Old.Data.float32 = IN->Mass_Gas.Data.float32;
        VAR->Enable_Old.Data.bit = IN->Enable.Data.bit;
    }
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00087_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00087_IN_type);
    case(1):
        return sizeof(fb00087_VAR_type);
    case(2):
        return sizeof(fb00087_OUT_type);
    default:
        return 0;
    }
}
