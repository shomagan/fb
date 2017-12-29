/* �� "������� ��������" */
#include <math.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00072.h"

//---------- ������� ���������� ��������� ����� � ������� �������� �� �� 2632 --------------
Flo32 calc_ro_oil(Flo32 ro_in/*��/���.�*/, Flo32 temp, u32 press /*���*1000*/)
{
	Flo32 ro;
	Flo32 Gt;
	Flo32 A15;

	if ((ro_in > 500) && (ro_in < 2000))
		Gt = (Flo32) (exp (-1.6208f + 0.00021592f * temp + (870960.0f / (ro_in * ro_in)) + (4.2092f * temp * 1000 / (ro_in * ro_in))) / 1000);
  else{
    Gt = 1; //���������� �����
  }
	A15 = 613.97226f / (ro_in * ro_in);
	ro = (Flo32) (ro_in * exp ((-1) * A15 * (temp - 15) * (1 + 0.8f * A15 * (temp - 15))));
	ro = ro / (1 - ((Gt * ((Flo32)press)) / 1000));

	return ro;
}

void fb00072_exec (void)
{
	fb00072_IN_type *IN = (fb00072_IN_type *) FBInputs;
	fb00072_VAR_type *VAR = (fb00072_VAR_type *) FBVars;
	fb00072_OUT_type *OUT = (fb00072_OUT_type *) FBOutputs;

	Flo32 fl = 0.0, Mass = 0.0, Vol = 0.0, PlFl_Liquid = 0.0, Wfl = 0.0, Po = 0.0, Pw = 0.0;

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


                        if ((OUT->Summ_Mass_Liquid.Data.float32 == 0) || (OUT->Summ_Volume_Liquid.Data.float32 == 0))
                            OUT->Sr_Density_Liquid.Data.float32 = PlFl_Liquid;
                        else
                            OUT->Sr_Density_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 / OUT->Summ_Volume_Liquid.Data.float32) / 1000;  // ������� ��������� ��������



						VAR->Summ_Temperature_Liquid.Data.float32 += IN->Temperature_Liquid.Data.float32;  // ��������� ����������� �� �����
                        OUT->Sr_Temperature_Liquid.Data.float32 = VAR->Summ_Temperature_Liquid.Data.float32 / (++VAR->Summ_CNT.Data.uint32);  // ������� ����������� ��������
                    }
                } else {
                    if (++VAR->Err_Summ_Liquid.Data.uint8 >= 20) {
                        OUT->MASK_mode.Data.uint8 |= (1 << MASK_mode_D0);
                        VAR->Err_Summ_Liquid.Data.uint8 = 20;
                    }
                }
				// ������� �������� ����� ��������
                OUT->Mass_FlowRate_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 * k_sutok) / (Flo32)(IN->Time.Data.uint32 + 1);
                if (OUT->Sr_Density_Liquid.Data.float32 > 0.0001f)
 	               OUT->Volume_FlowRate_Liquid.Data.float32 = OUT->Mass_FlowRate_Liquid.Data.float32 / OUT->Sr_Density_Liquid.Data.float32;      // ������� �������� ����� ��������

                //======================================== ������ ��������� �������� ========================================//
                // ���������� ��������� ����� � ������� ��������
				if (IN->Pressure_Liquid.Data.uint16 >= 0.0)
					fl = calc_ro_oil(((float)IN->Density_Oil_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);
				
				Po = fl/1000;

                // ���������� ��������� ���� � ������� ��������
                if (IN->Pressure_Liquid.Data.uint16 >= 0.0)
                    fl = calc_ro_water(((float)IN->Density_Water_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);

                Pw = fl/1000;

                if (IN->Enable_Dryness.Data.bit) {// �������� ������ � ����������
                    if (VAR->Value_Dryness_Old.Data.float32 == 0) {
                        VAR->Value_Dryness_Old.Data.float32 = VAR->Wc_Water.Data.float32 = 1.0f - (IN->Dryness_Liquid.Data.float32 / 100.0f);     // �������� ���� �����
                    } else {
                        VAR->Value_Dryness_Old.Data.float32 = VAR->Wc_Water.Data.float32;
                        VAR->Wc_Water.Data.float32 = 1.0f - (IN->Dryness_Liquid.Data.float32 / 100.0f);     // �������� ���� �����
                    }

                    if(VAR->Value_Density_Liquid_Old.Data.float32 == 0) {
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                        if (PlFl_Liquid > 0.0001f) VAR->Wc_Water.Data.float32 = VAR->Wc_Water.Data.float32 * (Po/PlFl_Liquid);                // �������� ���� �����
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f) Wfl = VAR->Value_Dryness_Old.Data.float32 * (Po/VAR->Value_Density_Liquid_Old.Data.float32);      // �������� ���� ����� �� ���������� ������
                    } else {
                        if (PlFl_Liquid > 0.0001f) VAR->Wc_Water.Data.float32 = VAR->Wc_Water.Data.float32*(Po/ PlFl_Liquid);                // �������� ���� �����
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f) Wfl = VAR->Value_Dryness_Old.Data.float32 * (Po / VAR->Value_Density_Liquid_Old.Data.float32);      // �������� ���� ����� �� ���������� ������
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                    }

                    if (Mass > 0.0f) VAR->Wm_Water.Data.float32 = 1 - ((VAR->Wc_Water.Data.float32 + Wfl) / 2);  // �������� ���� ����
                    else VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                } else {
                    // ������� ������������ �����
                    if (VAR->Value_Density_Liquid_Old.Data.float32 == 0) {
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                        if ((Pw > PlFl_Liquid) && (Pw > Po) && (PlFl_Liquid > 0.0001f)) {
                            fl = (PlFl_Liquid - Pw) / (Po - Pw);
                            VAR->Wm_Water.Data.float32 = 1 - (fl * (Po / PlFl_Liquid));
                            if ((VAR->Wm_Water.Data.float32 <= 0) || (VAR->Wm_Water.Data.float32 >= 1)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        } else {
                            VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        }
                    } else {
                        if ((Pw > ((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2)) && (Pw > Po) && (PlFl_Liquid > 0.0001f)) {
                            fl = (((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2) - Pw) / (Po - Pw);
                            VAR->Wm_Water.Data.float32 = 1 - (fl * (Po / ((PlFl_Liquid + VAR->Value_Density_Liquid_Old.Data.float32) / 2)));
                            if ((VAR->Wm_Water.Data.float32 <= 0.0f) || (VAR->Wm_Water.Data.float32 >= 1.0f)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        } else {
                            VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                        }
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                    }
                    if (VAR->Wm_Water.Data.float32 >= 1.0f) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
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
                        if ((IN->Mass_Gas.Data.float32 >= VAR->Value_Gas_Old.Data.float32) && (VAR->Value_Gas_Old.Data.float32 > 0.0f) && (IN->Density_Gas.Data.float32 > 0.0001f)) {
                            // ���������� ������ ���� �� ������
                            fl = IN->Mass_Gas.Data.float32 - VAR->Value_Gas_Old.Data.float32;
                            OUT->Summ_Mass_Gas.Data.float32 += fl;
                            fl = (fl / IN->Density_Gas.Data.float32)/1000.0f;
                            fl = fl * IN->Kg.Data.uint8 / 100;
                            // ���������� � ���������� ��������
                            if (IN->Pressure_Liquid.Data.uint16 > 0)  // �������� �� ������������ �����
                                fl = fl*((T20*(((float)IN->Pressure_Liquid.Data.uint16)/1000+Pbar))/(Patm*(T0+OUT->Sr_Temperature_Gas.Data.float32)));

                            OUT->Density_Gas.Data.float32 = IN->Density_Gas.Data.float32;
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
                    OUT->Volume_FlowRate_Gas.Data.float32 = ((Flo32)IN->Gas_Save.Data.uint16 / 100) * OUT->Mass_FlowRate_Oil.Data.float32;  // ������� �������� ����� ����
                    OUT->Pc_Gas.Data.float32 = (Flo32)(IN->Gas_Save.Data.uint16) / 100;   // ������� ������
                }
            }
        }
        VAR->Value_Liquid_Old.Data.float32 = IN->Mass_Liquid.Data.float32;        // ��������� ������� ��������� �������� ��� ���������� �����
        VAR->Value_Gas_Old.Data.float32 = IN->Mass_Gas.Data.float32;
        VAR->Enable_Old.Data.bit = IN->Enable.Data.bit;
    }
}
//---------- ������� ���������� ������������ ��������� ���� � ������� �������� ��� ����. 0 - 100 --------------
Flo32 calc_ro_water (Flo32 ro_in/*��/���.�*/, Flo32 temp, u16 press /*���*1000*/) {
    Flo32 ro;

    if (temp < 5) {
        ro=1.00176;
    } else {
        if ((temp >= 5) && (temp <= 90)) {
            ro = ((-0.000013f)*(temp*temp*temp*temp) + 0.004f*(temp*temp*temp) - 0.7394f*(temp*temp) + 4.6f*temp + 100173) / 100000;
        } else {
            ro=0.96706f;
        }
    }

    ro = (ro_in * ro) / (1-(0.00046f*((float)press)/1000));

    return ro;
}
//---------------------------------------------------------------------------------------------------------

//---------- ������� ���������� ��������� ����� � ������� �������� ��� ����. -50, 0, 50, 100, 150 --------------
Flo32 calc_ro_tabl (Flo32 ro_in, s16 temp) {
    Flo32 ro;

    if (temp > 150) temp = 150;

    switch (temp) {
        case -50: ro = (6.42913E-05f*ro_in+0.83378703f)*ro_in+1.42633E+02f; break;
        case -40: ro = (5.55416E-05f*ro_in+0.8562389f )*ro_in+1.23195E+02f; break;
        case -30: ro = (4.64214E-05f*ro_in+0.87944813f)*ro_in+1.03308E+02f; break;
        case -20: ro = (3.70353E-05f*ro_in+0.90324762f)*ro_in+8.30808E+01f; break;
        case -10: ro = (2.95668E-05f*ro_in+0.92420167f)*ro_in+6.38398E+01f; break;
        case   0: ro = (1.88157E-05f*ro_in+0.95065442f)*ro_in+4.22670E+01f; break;
        case  10: ro = (9.33093E-06f*ro_in+0.97539572f)*ro_in+2.11520E+01f; break;
        case  20: ro = ro_in; break;
        case  30: ro = (-1.01056E-05f*ro_in+1.0260019f)*ro_in-2.18031E+01f; break;
        case  40: ro = (-1.80674E-05f*ro_in+1.0484841f)*ro_in-4.22355E+01f; break;
        case  50: ro = (-2.67470E-05f*ro_in+1.0722282f)*ro_in-6.32402E+01f; break;
        case  60: ro = (-3.51667E-05f*ro_in+1.0955748f)*ro_in-8.41279E+01f; break;
        case  70: ro = (-4.33278E-05f*ro_in+1.118512f )*ro_in-1.04885E+02f; break;
        case  80: ro = (-5.11979E-05f*ro_in+1.1409644f)*ro_in-1.25469E+02f; break;
        case  90: ro = (-5.87847E-05f*ro_in+1.1629332f)*ro_in-1.45872E+02f; break;
        case 100: ro = (-6.60873E-05f*ro_in+1.1844035f)*ro_in-1.66080E+02f; break;
        case 110: ro = (-7.30935E-05f*ro_in+1.2053401f)*ro_in-1.86070E+02f; break;
        case 120: ro = (-7.98327E-05f*ro_in+1.2257879f)*ro_in-2.05856E+02f; break;
        case 130: ro = (-8.62953E-05f*ro_in+1.2457182f)*ro_in-2.25419E+02f; break;
        case 140: ro = (-9.00849E-05f*ro_in+1.2602269f)*ro_in-2.42221E+02f; break;
        case 150: ro = (-9.58898E-05f*ro_in+1.278646f )*ro_in-2.60933E+02f; break;
        default:  ro = (-2.67470E-05f*ro_in+1.0722282f)*ro_in-6.32402E+01f; break; // ������� ��� ����� temp=+50 ��.
    }
    return ro;
}
//---------------------------------------------------------------------------------------------------------

//------------------ ������� ���������� ��������� � ������� �������� ����� ����. ����. --------------------
Flo32 calc_ro (Flo32 ro_in, Flo32 temp) {
  // ----- ���������� ��������� ���������� -----
    s16 range;  			  // ��������� ����������� (-50,0,50,100,150)
    Flo32 koef_flo;     	    	  // ����������� ��� ���������� ����������������� ��������
    Flo32 ro_out;
    koef_flo =0;
    if ((ro_in < 690) || (ro_in > 1075)) {// �������� ������������ ��������� �����
        // ��� ����� ��������� ���� ������������ ��������� �����
    }

    if ((temp<(-50)) || (temp>150)) {// �������� ������������ �����������
        range=50;
        koef_flo=0;
        // ��� ����� ��������� ���� ������������ �����������
    } else {
        if (temp < 0) {// ���������� ������ ��������� � �������� ��������� temp
            temp *= (-1);
            range = (((u8)(temp/10)) * 10 + 10);
            range *= (-1);
            temp *= (-1);
            koef_flo=1; //���������� �����
        } else {
            range = (((u8)(temp/10))*10);	 //
            koef_flo = (temp-range)/10; 			 // �������� ����������� ��� ���������� ����������������� ��������
        }
    }
    ro_out = calc_ro_tabl(ro_in, range) - (calc_ro_tabl(ro_in, range)-calc_ro_tabl(ro_in, range+10)) * koef_flo;
    return ro_out;
}
//---------------------------------------------------------------------------------------------------------
