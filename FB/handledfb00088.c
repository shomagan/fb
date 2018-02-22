/*ФБ "Архиватор Динамограм R7" (заголовочный файл)*/
 
 
#include "../vars.h"
 
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00088.h"

#define flEnable (1<<0)     //флаг прошедшей процедуры записи ДНМ в выходной массив 
#define flSaveDNM (1<<1)    //флаг прошедшей процедуры архивирования 
#define flKnapPASS (1<<3)    //флаг флаг успешного расчета и записи  КНАП 

// BodySize 55 байт 

#define k1   4	//k - количество массивов  

void fb00088_exec ()
{
	fb00088_IN_type *IN = (fb00088_IN_type *) &FBInputs;
	fb00088_OUT_type *OUT = (fb00088_OUT_type *) &FBOutputs;
	u8 Hvost [7];
	u16 k;
	u8 i, n;

	if (IN->Enable.Data.bit && ((OUT->State.Data.uint8 & flEnable )==0)) {//ветвь создания выходного массива по типу "ДНМ новая"
		OUT->State.Data.uint8 |= 1;	//реализует реакцию только на появление сигнала Enable
		u32 TimeUNIX = GetSystemTime_t();	// получаем системное время (по приходу пакета) в UNIX	
		u8* Time;
		OUT->OutDNMNumber.Data.uint8 = IN->InDNMNumber.Data.uint8+1;//если приходит пакет инкрементируем счетчик пришедших пакетов(он выводится наружу для другого блока "Архиватор Динамограм R7" ) 
		
		k = 0; 
		
		for (; k < 63; k++)
			OUT->OutArray[k].Data.uint8 = IN->InArray[k].Data.uint8;//копируем первые 0 -  62 байт входного массива 
		
		OUT->OutArray[k].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//номер ДНМ
		for (; k < 126; k++ )
			OUT->OutArray[k+1].Data.uint8 = IN->InArray[k].Data.uint8;//копируем  63 -  125 байт входного массива
		
		OUT->OutArray[k + 1].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//номер ДНМ					
		for (; k < 185; k++ )
			OUT->OutArray[k + 2].Data.uint8 = IN->InArray[k].Data.uint8;//копируем первые 126 -  184(186 выходного) байт входного массива (внимание теряем 7 байт массива данных вместо них пишем время и номера ДНМ)

		Time = (u8*)(&TimeUNIX);
		OUT->OutArray[k + 2].Data.uint8 = *Time ;	//время Low 187					
		TimeUNIX >>= 8;
		OUT->OutArray[k + 3].Data.uint8 = *Time;	//время MLow 188					
		TimeUNIX >>= 8;
		OUT->OutArray[k + 4].Data.uint8 = *Time;	//время MHi 189				
		TimeUNIX >>= 8;
		OUT->OutArray[k + 5].Data.uint8 = *Time;	//время Hi 190					

		OUT->OutArray[k + 6].Data.uint8 = OUT->OutDNMNumber.Data.uint8;	//номер ДНМ байт 191					
        for (; k < 192; k++)
			Hvost[k - 185] = IN->InArray[k].Data.uint8;  // описыаем хвост для резерва и записи в архив
        
        OUT->State.Data.uint8&=~flKnapPASS; //каждый новый приход ДНМ обнуляет флаг расчитонного значения КНАП
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////**/
    if (IN->Enable.Data.bit && IN->KnapReady.Data.bit && ((OUT->State.Data.uint8 & flKnapPASS) == 0)) {//Кнап расчитался для этой ДНМ (если используется несколько последних ДНМ)
        OUT->State.Data.uint8 |= flKnapPASS;      //устанавливаем флаг удачной записи
        OUT->KnapValue.Data.uint8 = IN->KnapValue.Data.uint8;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////***/
	if (IN->SaveDNM.Data.bit && ((OUT->State.Data.uint8 & flSaveDNM) == 0)) {//ветвь создания 4-x архивов R7 для записи Динамограммы во флешь		
		OUT->State.Data.uint8 |= (1 << 1); 	//реализует реакцию только на появление сигнала SaveBuff	
   		u8 R7Buff[k1][R7_BodySize - 1];
		for (i = 0 ; i < k1 ; i++ ) {
			R7Buff[i][0] = 1;              
			R7Buff[i][1] = OUT->OutArray[63].Data.uint8;
			R7Buff[i][2] = k1;
			R7Buff[i][3] = i;
		}
		
		R7Buff[0][4] = OUT->OutArray[187].Data.uint8;	
		R7Buff[0][5] = OUT->OutArray[188].Data.uint8;
		R7Buff[0][6] = OUT->OutArray[189].Data.uint8;
		R7Buff[0][7] = OUT->OutArray[190].Data.uint8;
		R7Buff[0][8] = OUT->OutArray[0].Data.uint8;
		R7Buff[0][9] = OUT->OutArray[1].Data.uint8;
		R7Buff[0][10] = 0;	
        n = 3;
		for (; n < 45; n++)
			R7Buff[0][n + 9] = OUT->OutArray[n].Data.uint8;	    //заполнили первый массив Р7	
			
		for ( ; n < 62; n++)
			R7Buff[1][n - 41] = OUT->OutArray[n].Data.uint8;	//заполнили первую часть второго массива			
		
		n++;
		
		for ( ; n < 96; n++)
			R7Buff[1][n - 42] = OUT->OutArray[n].Data.uint8;	//заполнили вторуюб часть перввого массива			

		for ( ; n < 126; n++)
			R7Buff[2][n - 92] = OUT->OutArray[n].Data.uint8;	//заполнили первую часть третьего массива							
		
		n++;	
		
		for ( ; n < 147; n++)
			R7Buff[2][n - 93] = OUT->OutArray[n].Data.uint8;	//заполнили вторую часть третьего массива							
		
		for ( ; n < 187; n++)
			R7Buff[3][n-143] = OUT->OutArray[n].Data.uint8;	//заполнили 4 массив							
		
		n = 44;
		
		for ( ; n < R7_BodySize-4; n++)
			R7Buff[3][n] = Hvost[n - 44] ;	//заполнили хвост осталось 3 байта для КНАП ДНМ 							

        if (OUT->State.Data.uint8 & flKnapPASS)
            R7Buff[3][n] = 0xFF;
        else
            R7Buff[3][n] = 0x00;
        
		n++;
        
		R7Buff[3][n] = OUT->KnapValue.Data.uint8;
        
		n++;
        
		R7Buff[3][n] = 0;
		NewQ_Arc_R7(R7Buff[0], 19);  // Передаём тело архива архиватору
		NewQ_Arc_R7(R7Buff[1], 19);  // Передаём тело архива архиватору
		NewQ_Arc_R7(R7Buff[2], 19);  // Передаём тело архива архиватору
		NewQ_Arc_R7(R7Buff[3], 19);  // Передаём тело архива архиватору

	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////****/    

        
	if (!IN->Enable.Data.bit ) {
		OUT->State.Data.uint8 &= ~flEnable;
	}

	if (!IN->SaveDNM.Data.bit ) {
		(OUT->State.Data.uint8 &= ~flSaveDNM);
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00088_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00088_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00088_OUT_type);
    default:
        return 0;
    }
}
