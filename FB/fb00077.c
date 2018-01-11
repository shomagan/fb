/* ФБ "Архиватор R7 "Замер ГЗУ-Массомер" (тип 16)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00077.h"
/*Создает полный архив значений связанных с отводом
*но только по команде(например при смене отвода)
* Номер канала (Код ПСМ на начало замера)
* Время начала периода измерения
* Номер канала (Код ПСМ на конец замера)
* Суммарная масса ВНС за замер, кг 4 байта
* Массовый дебит ВНС, т/сут 4 байта
* Объёмный дебит газа, куб.м/сут 4 байта
* Массовый дебит нефти, т/сут 4 байта      
* Средняя плотность ВНС за замер т/куб.м *10000
* Средняя температура ВНС за замер град. С *100
* Обводнённость нефти *10000
* Лабораторная плотность нефти т/куб.м *10000
* Лабораторная плотность воды т/куб.м *10000
* Лабораторная плотность ВНС т/куб.м *10000		
* Газовый фактор куб.м/т *100 
* Длительность измерения в минутах
* Число циклов сепаратораФлаги архива		
* Не выдаётся в команде R7, но лежит в архиве
* Суммарный объём газа за замер
*/
void fb00077_exec (void)
{
	fb00077_IN_type *IN = (fb00077_IN_type *) FBInputs;
	fb00077_OUT_type *OUT = (fb00077_OUT_type *) FBOutputs;

	u8 R7Buff[R7_BodySize];
	u16 ui16Val;
	s16 si16Val;
	
	typedef union {
		u8 ch[4];
		Flo32 fl;
	} sValue;
	sValue Value;

	OUT->Ok.Data.bit = 0;
  
	if (IN->CmdARX.Data.bit) { // Если архивирование замера разрешено
		//Шапка (первые 9 байт) формируется Архиватором МегаФБ32. Заполняем тело архива
    
		// Номер канала (Код ПСМ на начало замера)
		R7Buff[0] = IN->StartOtvNum.Data.uint8;                   // 9 Номер отвода на начало замера
		// Время начала периода измерения
		R7Buff[1] = (u8) (IN->StartTime.Data.uint32 & 0xFF);    // 10
		R7Buff[2] = (u8) (IN->StartTime.Data.uint32>>8);        // 11
		R7Buff[3] = (u8) (IN->StartTime.Data.uint32>>16);       // 12
		R7Buff[4] = (u8) (IN->StartTime.Data.uint32>>24);       // 13
		// Номер канала (Код ПСМ на конец замера)
		R7Buff[5] = IN->EndOtvNum.Data.uint8;                     // 14 Номер отвода на конец замера
		// Суммарная масса ВНС за замер, кг 4 байта
		Value.fl = IN->Summ_Mass_Liquid.Data.float32;
		R7Buff[6] = Value.ch[0];                                  // 15            
		R7Buff[7] = Value.ch[1];                                  // 16
		R7Buff[8] = Value.ch[2];                                  // 17
		R7Buff[9] = Value.ch[3];                                  // 18
		// Массовый дебит ВНС, т/сут 4 байта
		Value.fl = IN->Mass_FlowRate_Liquid.Data.float32;
		R7Buff[10] = Value.ch[0];                                 // 19            
		R7Buff[11] = Value.ch[1];                                 // 20
		R7Buff[12] = Value.ch[2];                                 // 21
		R7Buff[13] = Value.ch[3];                                 // 22
		// Объёмный дебит газа, куб.м/сут 4 байта
		Value.fl = IN->Volume_FlowRate_Gas.Data.float32;
		R7Buff[14] = Value.ch[0];                                 // 23            
		R7Buff[15] = Value.ch[1];                                 // 24
		R7Buff[16] = Value.ch[2];                                 // 25
		R7Buff[17] = Value.ch[3];                                 // 26
		// Массовый дебит нефти, т/сут 4 байта      
		Value.fl = IN->Mass_FlowRate_Oil.Data.float32;
		R7Buff[18] = Value.ch[0];                                 // 27            
		R7Buff[19] = Value.ch[1];                                 // 28
		R7Buff[20] = Value.ch[2];                                 // 29
		R7Buff[21] = Value.ch[3];                                 // 30
		// Массовый дебит воды, т/сут 4 байта
		Value.fl = IN->Mass_FlowRate_Water.Data.float32;
		R7Buff[22] = Value.ch[0];                                 // 31            
		R7Buff[23] = Value.ch[1];                                 // 32
		R7Buff[24] = Value.ch[2];                                 // 33
		R7Buff[25] = Value.ch[3];                                 // 34
		// Средняя плотность ВНС за замер т/куб.м *10000
		ui16Val = (u16) (IN->Sr_Density_Liquid.Data.float32 * 10000);
		R7Buff[26] = (u8) (ui16Val & 0xFF);                    // 35            
		R7Buff[27] = (u8) (ui16Val >> 8);                      // 36
		// Средняя температура ВНС за замер град. С *100
		si16Val = (s16) (IN->Sr_Temperature_Liquid.Data.float32 * 100);
		R7Buff[28] = (s8) (si16Val & 0xFF);                    // 37            
		R7Buff[29] = (s8) (si16Val / 256);                     // 38
		// Обводнённость нефти *10000      
		ui16Val = (u16) (IN->Sr_Wm_Water.Data.float32 * 10000);
		R7Buff[30] = (u8) (ui16Val & 0xFF);                    // 39            
		R7Buff[31] = (u8) (ui16Val >> 8);                      // 40
		// Лабораторная плотность нефти т/куб.м *10000
		ui16Val = IN->Density_Oil_Save.Data.uint16;
		R7Buff[32] = (u8) (ui16Val & 0xFF);                    // 41            
		R7Buff[33] = (u8) (ui16Val >> 8);                      // 42
		// Лабораторная плотность воды т/куб.м *10000
		ui16Val = IN->Density_Water_Save.Data.uint16;
		R7Buff[34] = (u8) (ui16Val & 0xFF);                    // 43            
		R7Buff[35] = (u8) (ui16Val >> 8);                      // 44
		// Лабораторная плотность ВНС т/куб.м *10000		
		ui16Val = IN->Density_Liquid_Save.Data.uint16;
		R7Buff[36] = (u8) (ui16Val & 0xFF);                    // 45            
		R7Buff[37] = (u8) (ui16Val >> 8);                      // 46
		// Газовый фактор куб.м/т *100 
		ui16Val = (u16) (IN->Pc_Gas.Data.float32 * 100);
		R7Buff[38] = (u8) (ui16Val & 0xFF);                    // 47            
		R7Buff[39] = (u8) (ui16Val >> 8);                      // 48
		// Длительность измерения в минутах
		R7Buff[40] = (u8) (IN->CntTime.Data.uint16 & 0xFF);     // 49
		R7Buff[41] = (u8) (IN->CntTime.Data.uint16 >> 8);       // 50
		// Число циклов сепаратора
		R7Buff[42] = (u8) (IN->Sync_Liquid.Data.uint16 & 0xFF); // 51
		R7Buff[43] = (u8) (IN->Sync_Liquid.Data.uint16 >> 8);   // 52
		// Флаги архива
    R7Buff[44] = (u8)(IN->OtvNumber.Data.uint16 &0xff);                     // 54
    R7Buff[45] = (u8)(IN->OtvNumber.Data.uint16 >>8);                       // 55

		// Не выдаётся в команде R7, но лежит в архиве
		// Суммарный объём газа за замер
		Value.fl = IN->Summ_Volume_Gas.Data.float32;
		R7Buff[46] = Value.ch[0];                                 // 49            
		R7Buff[47] = Value.ch[1];                                 // 50
		R7Buff[48] = Value.ch[2];                                 // 51
		R7Buff[49] = Value.ch[3];                                 // 52
    
    Value.fl = IN->Volume_FlowRate_Liquid.Data.float32;
    R7Buff[50] = Value.ch[0];                                 // 60
    R7Buff[51] = Value.ch[1];                                 // 61
    R7Buff[52] = Value.ch[2];                                 // 62
    R7Buff[53] = Value.ch[3];                                 // 63

    
		NewQ_Arc_R7(R7Buff, 16);  // Передаём тело архива архиватору
		OUT->Ok.Data.bit = 1;
	}  
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00077_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00077_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00077_OUT_type);
    default:
        return 0;
    }
}
