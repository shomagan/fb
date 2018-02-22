/*ФБ "Резервуар"*/
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00086.h"

void fb00086_exec ()
{
	fb00086_IN_type *IN = (fb00086_IN_type *) &FBInputs;
	fb00086_OUT_type *OUT = (fb00086_OUT_type *) &FBOutputs;
	
	Register_type *pMain, *pAuto, *pCmd_ON, *pCmd_OFF;
	u8 tmp, Cmd; //3-откл все,2-вкл все,1-ничего не делать,0-вкл основные
	u8 i;
	
	Cmd = 1;//установка начальной команды "Нет"
	i = 4;
	if (IN->enable.Data.bit) {
		if (IN->lo.Data.bit) tmp = 1; else tmp = 0;   //отключить все
		if (IN->hi.Data.bit) tmp += 2; //вкл основные 
		if (IN->hihi.Data.bit) tmp += 4; //вкл все 
		switch (tmp) {
		case 0: //нет сигналов
			break;
		case 2: //только сигнал верхнего уровня
			//если есть основные в автомате
			if ((IN->main0.Data.bit && IN->auto0.Data.bit) || (IN->main1.Data.bit && IN->auto1.Data.bit) || (IN->main2.Data.bit && IN->auto2.Data.bit) || (IN->main3.Data.bit && IN->auto3.Data.bit)) {
				Cmd = 0;//вкл основные
			} else {
				Cmd = 2;//вкл все (среди управляемых нет главных)
			}
			break;
		case 4: //сигнал аварийного верхнего уровня
		case 6: //оба сигнала верхних уровней
			Cmd = 2; //включить все
			break;
		default:
			Cmd = 3; //1,3,5,7 - есть сигнал нижнего уровня
			//отключаем все
		}
	}
	
	i = 4;
	pMain = &(IN->main0);
	pAuto = &(IN->auto0);
	pCmd_ON = &(OUT->cmd0_ON);
	pCmd_OFF = &(OUT->cmd0_OFF);
	while (i--) {		
		if (pAuto->Data.bit == 0)
			tmp = 1; //не в автомате, ничего не делаем
		else if (Cmd) //если команда не "вкл основные"
			 tmp = Cmd;
		else if (pMain->Data.bit) //основным, надо дать команду на включение
			 tmp = 2;
		else //не основной, ничего не надо делать
			tmp = 1;

		pCmd_ON->Data.bit=(tmp==0x02) ? 1:0;// если есть команда на включение устанавливаем ВКЛ 
		pCmd_OFF->Data.bit=(tmp==0x03) ? 1:0;// если есть команда на выключение устанавливаем ОТКЛ 
		pMain++;
		pAuto++;
		pCmd_ON = pCmd_OFF + 1;//переходим к следующему насосу
		pCmd_OFF = pCmd_ON + 1;
	}
	//производим непрерывное отображение состояния входов и поданной команды
    
	OUT->State.Data.uint8 = (IN->enable.Data.bit ?1:0) | (IN->hihi.Data.bit ?2:0) | (IN->hi.Data.bit ?4:0) | (IN->lo.Data.bit ?8:0)\
		| (Cmd == 0 ? 16:0) | (Cmd == 2 ? 32:0) | (Cmd == 3 ? 64:0);
	 //3-откл все,2-вкл все,1-ничего не делать,0-вкл основные
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00086_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00086_IN_type);
    case(1):
        return 0;
    case(2):
        return sizeof(fb00086_OUT_type);
    default:
        return 0;
    }
}
