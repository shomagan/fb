/* ФБ "Счётчик массомер" */
 
 
#include <math.h>
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00072.h"
#include "handledfb00087.h"
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

    if ((IN->Reset.Data.bit) || (!(IN->Enable.Data.bit))) { // Сброс замера

        OUT->Summ_Mass_Liquid.Data.float32 = 0.0;        // float32 Текущая суммарная масса жидкости в кг
        OUT->Summ_Volume_Liquid.Data.float32 = 0.0;      // float32 Текущий суммарный объём жидкости в куб.м
        OUT->Summ_Mass_Gas.Data.float32 = 0.0;           // float32 Текущая суммарная масса газа в кг
        OUT->Summ_Volume_Gas.Data.float32 = 0.0;         // float32 Текущий суммарный объём газа в куб.м
        OUT->MASK_mode.Data.uint8 = 0;

        OUT->Density_Gas.Data.float32 = 0.0;             // float32 Текущая плотность газа в г/куб.см
        OUT->Sr_Temperature_Gas.Data.float32 = 0.0;      // float32 Текущая средняя температура газа в град.С
        OUT->Sr_Wm_Water.Data.float32 = 0.0;             // float32 Средняя массовая доля воды
        OUT->Sr_Wc_Water.Data.float32 = 0.0;             // float32 Средняя объёмная доля воды

        OUT->Mass_FlowRate_Water.Data.float32 = 0.0;     // float32 Текущия массовый дебит воды в т/сут
        OUT->Volume_FlowRate_Water.Data.float32 = 0.0;   // float32 Текущий объёмный дебит воды в куб.м/сут
        OUT->Mass_FlowRate_Oil.Data.float32 = 0.0;       // float32 Текущия массовый дебит нефти в т/сут
        OUT->Volume_FlowRate_Oil.Data.float32 = 0.0;     // float32 Текущий объёмный дебит нефти в куб.м/сут

        OUT->Pc_Gas.Data.float32 = 0.0;                  // float32 текущий газовый фактор по скважине куб.м/т
        //    OUT->Sync_Liquid.Data.uint16 = 0;                // uint16  Количество циклов слива сепаратора
        OUT->Mass_FlowRate_Liquid.Data.float32 = 0.0;    // float32 Текущий массовый дебит жидкости в т/сут
        OUT->Volume_FlowRate_Liquid.Data.float32 = 0.0;  // float32 Текущий объёмный дебит жидкости в куб.м/сут
        OUT->Sr_Density_Liquid.Data.float32 = 0.0;       // float32 Текущая средняя плотность жидкости в г/куб.см
        OUT->Sr_Temperature_Liquid.Data.float32 = 0.0;   // float32 Текущая средняя температура жидкости в град.С
        OUT->Mass_FlowRate_Gas.Data.float32 = 0.0;       // float32 Текущия массовый дебит газа в т/сут
        OUT->Volume_FlowRate_Gas.Data.float32 = 0.0;     // float32 Текущий объёмный дебит газа в куб.м/сут


        VAR->Value_Liquid_Old.Data.float32 = 0.0;        // float32
        VAR->Value_Gas_Old.Data.float32 = 0.0;           // float32
        VAR->Value_Dryness_Old.Data.float32 = 0.0;       // float32
        VAR->Value_Density_Liquid_Old.Data.float32 = 0.0;// float32
        VAR->Wm_Water.Data.float32 = 0.0;                // float32 Массовая доля воды
        VAR->Wc_Water.Data.float32 = 0.0;                // float32 Объёмная доля воды
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
            if ((IN->Enable_Liquid.Data.bit) && (!IN->Hold.Data.bit)) { // Включена работа с массомером жидкости
                //======================================== Расчёт добытой жидкости ========================================//
                if (fabsf(IN->Mass_Liquid.Data.float32-0.0f) >= 0.01f) {
                    if ((fabsf(IN->Mass_Liquid.Data.float32 - VAR->Value_Liquid_Old.Data.float32) >= 0.01f) && (IN->Density_Liquid.Data.float32 > 0.0001f)) {

                        Mass = IN->Mass_Liquid.Data.float32 - VAR->Value_Liquid_Old.Data.float32; // Вычисление приращения массы жидкости
                        OUT->Summ_Mass_Liquid.Data.float32 += Mass;                               // Добавляем счетчик массы жидкости

                        PlFl_Liquid = IN->Density_Liquid.Data.float32;

                        Vol = ((Mass / PlFl_Liquid) / 1000.0f);  // Приращение объёма жидкости из кг в куб.м
                        Vol = Vol * IN->Kp.Data.uint8 / 100;

                        if (Vol > 0.0f) OUT->Summ_Volume_Liquid.Data.float32 += Vol;         // Текущий cуммарный объём жидкости

                        VAR->Err_Summ_Liquid.Data.uint8 = 0;



                        if ((OUT->Summ_Mass_Liquid.Data.float32 == 0.0f) || (OUT->Summ_Volume_Liquid.Data.float32 == 0.0f))
                            OUT->Sr_Density_Liquid.Data.float32 = PlFl_Liquid;
                        else
                            OUT->Sr_Density_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 / OUT->Summ_Volume_Liquid.Data.float32) / 1000;  // Средняя плотность жидкости
						
            						PlFl_Liquid = OUT->Sr_Density_Liquid.Data.float32;

						            VAR->Summ_Temperature_Liquid.Data.float32 += IN->Temperature_Liquid.Data.float32;  // Суммарная температура за замер
                        OUT->Sr_Temperature_Liquid.Data.float32 = VAR->Summ_Temperature_Liquid.Data.float32 / (++VAR->Summ_CNT.Data.uint32);  // Средняя температура жидкости
                    }
                } else {
                    if (++VAR->Err_Summ_Liquid.Data.uint8 >= 20) {
                        OUT->MASK_mode.Data.uint8 |= (1 << MASK_mode_D0);
                        VAR->Err_Summ_Liquid.Data.uint8 = 20;
                    }
                }
				
        				OUT->Mass_FlowRate_Liquid.Data.float32 = (OUT->Summ_Mass_Liquid.Data.float32 * k_sutok) / (float32)(IN->Time.Data.uint32 + 1);
                if (OUT->Sr_Density_Liquid.Data.float32 > 0.0001f){
	                  OUT->Volume_FlowRate_Liquid.Data.float32 = OUT->Mass_FlowRate_Liquid.Data.float32 / OUT->Sr_Density_Liquid.Data.float32;}      // Текущий объёмный дебит жидкости
                //======================================== Расчёт влажности жидкости ========================================//
                // Приведение плотности нефти к рабочим условиям
        				if (IN->Pressure_Liquid.Data.uint16 >= 0.0f){
           					fl = calc_ro_oil(((float)IN->Density_Oil_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);}
			  	
				        Po = fl/1000;

                // Приведение плотности воды к рабочим условиям
                if (IN->Pressure_Liquid.Data.uint16 >= 0.0f)
                    fl = calc_ro_water(((float)IN->Density_Water_Save.Data.uint16)/10, OUT->Sr_Temperature_Liquid.Data.float32, IN->Pressure_Liquid.Data.uint16);

                Pw = fl/1000;

                if (IN->Enable_Dryness.Data.bit) {// Включена работа с влагомером
                    if (VAR->Value_Dryness_Old.Data.float32 == 0.0f) {
                        VAR->Value_Dryness_Old.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                        VAR->Wm_Water.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                    } else {
                        VAR->Value_Dryness_Old.Data.float32 = VAR->Wm_Water.Data.float32;
                        VAR->Wm_Water.Data.float32 = (IN->Dryness_Liquid.Data.float32/100.0f);
                    }

                    if(VAR->Value_Density_Liquid_Old.Data.float32 == 0.0f) {
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid; //IN->Density_Liquid.Data.float32
                        if (PlFl_Liquid > 0.0001f) VAR->Wm_Water.Data.float32 = VAR->Wm_Water.Data.float32 *(Pw/PlFl_Liquid);                // Массовая доля нефти
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f){ Wfl = VAR->Value_Dryness_Old.Data.float32 * (Pw/VAR->Value_Density_Liquid_Old.Data.float32);}      // Массовая доля нефти на предыдущем замере
                        else{Wfl = VAR->Wm_Water.Data.float32 ;}
                    } else {
                        if (PlFl_Liquid > 0.0001f) VAR->Wm_Water.Data.float32 = VAR->Wm_Water.Data.float32*(Pw/ PlFl_Liquid);                // Массовая доля нефти
                        if (VAR->Value_Density_Liquid_Old.Data.float32 > 0.0001f){ Wfl = VAR->Value_Dryness_Old.Data.float32 * (Pw/VAR->Value_Density_Liquid_Old.Data.float32);}      // Массовая доля нефти на предыдущем замере
                        else{Wfl = VAR->Wm_Water.Data.float32 ;}
                        VAR->Value_Density_Liquid_Old.Data.float32 = PlFl_Liquid;
                    }
                    VAR->Wm_Water.Data.float32 = (VAR->Wm_Water.Data.float32 + Wfl)/2.0f;
                    if (VAR->Wm_Water.Data.float32>1.0f){
                      VAR->Wm_Water.Data.float32 = 1.0f;
                    }else if(VAR->Wm_Water.Data.float32<0.0f){
                      VAR->Wm_Water.Data.float32 = 0.0f;
                    }
//                    if (Mass > 0.0) VAR->Wc_Water.Data.float32 = 1.0 - ((VAR->Wm_Water.Data.float32 + Wfl) / 2.0);  // Массовая доля воды
//                                                               1.0 - ((VAR->Wc_Water.Data.float32 + VAR->Value_Dryness_Old.Data.float32 * (Po/VAR->Value_Density_Liquid_Old.Data.float32)) / 2.0)
//                                                               1.0 - ((VAR->Wc_Water.Data.float32 + VAR->Wc_Water.Data.float32 * (Po/PlFl_Liquid)) / 2.0)
//                                                               1.0 - ((VAR->Wc_Water.Data.float32*(1+(Po/PlFl_Liquid)) / 2.0)
//                                                               (2.0 - VAR->Wc_Water.Data.float32*(1+(Po/PlFl_Liquid))) / 2.0
//                    else VAR->Wc_Water.Data.float32 = IN->Wc_Water_Save.Data.float32;
                } else {
                    // Текущая обводнённость нефти
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

                VAR->Summ_Mass_Water.Data.float32 += Mass * VAR->Wm_Water.Data.float32;              // Суммарная масса воды

                OUT->Mass_FlowRate_Water.Data.float32 = (VAR->Summ_Mass_Water.Data.float32 * k_sutok) / (float)(IN->Time.Data.uint32 + 1); // Текущий массовый дебит воды
                OUT->Mass_FlowRate_Oil.Data.float32 = OUT->Mass_FlowRate_Liquid.Data.float32 - OUT->Mass_FlowRate_Water.Data.float32;

                OUT->Volume_FlowRate_Water.Data.float32 = OUT->Mass_FlowRate_Water.Data.float32 / Pw;                              // Текущий объёмный дебит воды
                OUT->Volume_FlowRate_Oil.Data.float32 = OUT->Mass_FlowRate_Oil.Data.float32 / Po;                                  // Текущий объёмный дебит нефти

                if ((VAR->Wm_Water.Data.float32 <= 0.0f) || (VAR->Wm_Water.Data.float32 >= 1.0f)) VAR->Wm_Water.Data.float32 = IN->Wm_Water_Save.Data.float32;
                OUT->Sr_Wm_Water.Data.float32 = OUT->Mass_FlowRate_Water.Data.float32 / OUT->Mass_FlowRate_Liquid.Data.float32;       // Текущая обводнённость нефти в %*100*/
                OUT->Sr_Wc_Water.Data.float32 = OUT->Volume_FlowRate_Water.Data.float32 / OUT->Volume_FlowRate_Liquid.Data.float32;   //

                //======================================== Расчёт добытого газа ========================================//

                // Плотность газа 1:150 запас в 60 раз*/
                if (IN->Enable_Gas.Data.bit) { // Если есть расходомер газа, используем его показания
                    if (IN->Mass_Gas.Data.float32 >= 0.0f) {
                        if ((IN->Mass_Gas.Data.float32 >= VAR->Value_Gas_Old.Data.float32) && (VAR->Value_Gas_Old.Data.float32 > 0.0f)) {
                            // Приращение объёма газа за отсчёт
                            fl = IN->Mass_Gas.Data.float32 - VAR->Value_Gas_Old.Data.float32;
                            OUT->Summ_Mass_Gas.Data.float32 += fl;
                            OUT->Density_Gas.Data.float32 = IN->Density_Gas.Data.uint16 / 10000.0f;
                            fl = (fl / OUT->Density_Gas.Data.float32);
                            fl = fl * IN->Kg.Data.uint8 / 100;


                            OUT->Summ_Volume_Gas.Data.float32 += fl;   // Текущий cуммарный объём газа в куб.м
                            OUT->Volume_FlowRate_Gas.Data.float32 = (OUT->Summ_Volume_Gas.Data.float32 * k_sutok *1000.0f) / (float)(IN->Time.Data.uint32 + 1);  // Текущий объёмный дебит газа
                        }

                        VAR->Summ_Temperature_Gas.Data.float32 += IN->Temperature_Gas.Data.float32;  // Суммарная температура газа за замер
                        OUT->Sr_Temperature_Gas.Data.float32 = VAR->Summ_Temperature_Gas.Data.float32 / (++VAR->Summ_CNT_Gas.Data.uint32);  // Средняя температура газа
                        VAR->Err_Summ_Gas.Data.uint8 = 0;
                    } else {
                        if (++VAR->Err_Summ_Gas.Data.uint8 >= 20) {
                            OUT->MASK_mode.Data.uint8 |= (1 << MASK_mode_D1);
                            VAR->Err_Summ_Gas.Data.uint8 = 20;
                        }
                    }

                    if (OUT->Mass_FlowRate_Oil.Data.float32 > 0.0f)
                        OUT->Pc_Gas.Data.float32 = OUT->Volume_FlowRate_Gas.Data.float32 / OUT->Mass_FlowRate_Oil.Data.float32;   // Газовый фактор
                } else {  // Если нет расходомера газа
                    OUT->Volume_FlowRate_Gas.Data.float32 = ((float)IN->Gas_Save.Data.uint16 / 100) * OUT->Mass_FlowRate_Oil.Data.float32;  // Текущий объёмный дебит газа
                    OUT->Pc_Gas.Data.float32 = (float32)(IN->Gas_Save.Data.uint16) / 100;   // Газовый фактор
                }
            }
        }
        VAR->Value_Liquid_Old.Data.float32 = IN->Mass_Liquid.Data.float32;        // Запаомним текущее показание счетчика для следующего цикла
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
