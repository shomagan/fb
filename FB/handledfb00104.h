/*ФБ архивирования сетевых переменных*/

typedef struct {    
	Register_type Enable;	 		//bit команда на архивироние(импульсная)
	Register_type GUID;	 		  //uint16 сетевую переменную с этим GUID будим архивировать
} fb00104_IN_type;
typedef struct {
	Register_type OK;	    	// bit выставляетс если нашли СП и по маске ее можно архивировать 
} fb00104_OUT_type;

void fb00104_exec();
u32 fb00104_var_size(u8 type);
