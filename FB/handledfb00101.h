/* ФБ "Автомат управления приводом" */
typedef struct {
  Register_type Enable;        // bit //enable
  Register_type Avtomat;       //bit  1 - avtomat
  //Register_type Reverse;       //bit  //1 - реверсивное управление
  Register_type Revers;       //bit  //1 - реверсивное управление
  Register_type DisbalanceEnable;//bit  //1 - учитывать дисбаланс возможного несоответсвия показания входного и выходного 
                                                  // параметра положения задвижки
  Register_type GistMore;      //float // на сколько должно быть больше в процентах
  Register_type GistLess;      //float // на сколько должно быть меньше в процентах
  Register_type PositionInc;     //uint16// на сколько изменить позицию если NeceseryParam(необходимое значение) больше CurrParam(текущего)
  Register_type PositionDec;     //uint16// на сколько изменить позицию если NeceseryParam(необходимое значение) меньше CurrParam(текущего)
  Register_type DisregardTime; //uint16// задержка реакции в сек NeceseryParam CurrParam
  Register_type NeceseryPosition; // uint16 // 
  Register_type CurrPosition;     // uint16 // 
  Register_type MaxPosition;      // uint16 // 
  Register_type MinPosition;      // uint16 // 
  Register_type NeceseryParam;   // uint16/float // !!!тип с CurrParam должен совпадать
  Register_type CurrParam;        // uint16/float //!!!тип с NeceseryParam должен совпадать 
} fb00101_IN_type;

typedef struct {
  Register_type KernelClk;
} fb00101_VAR_type;

typedef struct {
	Register_type WritePosition; // bit // !!!разрешение записи позиции задвижки
                                      // 0 - напортачили в типах или в MaxPosition MinPosition
	Register_type BigParam;      // bit //
	Register_type LowParam;      //  bit // 
	Register_type State;         //  uint32// 
  Register_type ReverseTime;   // uint16//обратный таймер бездействия
	Register_type OutPosition;         // uint16 // 
} fb00101_OUT_type;
void fb00101_exec(void);
u32 fb00101_var_size(u8 type);
