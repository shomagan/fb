/* �� ������ "DI ������� 0 ��������� 1" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

typedef struct {
	Register_type DI;			// bit
	Register_type Bit01;		// bit
	Register_type dT;			// uint8
} fb00094_IN_type;

typedef struct {
	Register_type DIOld;		// bit
	Register_type CntSec;		// uint32
} fb00094_VAR_type;

typedef struct {
	Register_type DO;			// bit
} fb00094_OUT_type;

void fb00094_exec(void){
fb00094_IN_type *IN=(fb00094_IN_type *) FBInputs;
fb00094_VAR_type *VAR=(fb00094_VAR_type *) FBVars;
fb00094_OUT_type *OUT=(fb00094_OUT_type *) FBOutputs;

	if(KernelInfo.EventFlags.Bit.CfgFirstExec){
		VAR->CntSec.Data.uint32 = cntSecFromStart;	
		OUT->DO.Data.bit = VAR->DIOld.Data.bit = IN->DI.Data.bit;	
		  
	} 
	else {
		if(IN->DI.Data.bit == VAR->DIOld.Data.bit){	//���� �� ���������
			if(IN->DI.Data.bit == IN->Bit01.Data.bit){ //������� �� ����, ������� �����
				if((cntSecFromStart - VAR->CntSec.Data.uint32) >= IN->dT.Data.uint32) 
					OUT->DO.Data.bit = IN->Bit01.Data.bit; 	// ��������!
				//else //OUT->DO.Data.bit = ~IN->Bit01.Data.bit; 	// �� �������� ���
			}
			else  OUT->DO.Data.bit = ~IN->Bit01.Data.bit;
		}
		else{			//��������� �� �����
			if(IN->DI.Data.bit == IN->Bit01.Data.bit) 		//�� ����� ��������� �� ����, ������� �����
				VAR->CntSec.Data.uint32 = cntSecFromStart; 	// �������� ����� ������ - ������ �����			
			OUT->DO.Data.bit = ~IN->Bit01.Data.bit; 	// �� �������� ���	
			VAR->DIOld.Data.bit = IN->DI.Data.bit;
		}
	}
}
