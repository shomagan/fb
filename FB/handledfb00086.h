/*ФБ "Резервуар" (заголовочный файл)*/

typedef struct {
	Register_type enable;	//bit 0- блокирует работу логики насоса
	Register_type hihi;     //bit команда ВКЛ все 
	Register_type hi;       //bit команда ВКЛ основные 
	Register_type lo;       //bit команда ОТКЛ
	Register_type main0;	//bit==1насос № - основной bit0=насос № - резервный
	Register_type main1;	//bit==1насос № - основной bit0=насос № - резервный
	Register_type main2;    //bit==1насос № - основной bit0=насос № - резервный
	Register_type main3;    //bit==1насос № - основной bit0=насос № - резервный
	Register_type auto0;	//bit1=насос в автомате и аварии нет bit0=насос не в автомате или есть авария
	Register_type auto1;	//bit1=насос в автомате и аварии нет bit0=насос не в автомате или есть авария
	Register_type auto2;    //bit1=насос в автомате и аварии нет bit0=насос не в автомате или есть авария
	Register_type auto3;    //bit1=насос в автомате и аварии нет bit0=насос не в автомате или есть авария
} fb00086_IN_type;

typedef struct {
	Register_type cmd0_ON;	//bit вкл/выкл насос № (расшиненный логический выход, см.доки)
	Register_type cmd0_OFF;
	Register_type cmd1_ON;
	Register_type cmd1_OFF;
	Register_type cmd2_ON;
	Register_type cmd2_OFF;
	Register_type cmd3_ON;
	Register_type cmd3_OFF;
	Register_type State;
} fb00086_OUT_type;


u32 fb00086_var_size(u8 type);
