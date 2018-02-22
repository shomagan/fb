/* ФБ "Насос с АПВ" */
 
 
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "handledfb00079.h"


void fb00079_exec()
{
	fb00079_IN_type *IN = (fb00079_IN_type *) &FBInputs;
	fb00079_VAR_type *VAR = (fb00079_VAR_type *) &FBVars;
	fb00079_OUT_type *OUT = (fb00079_OUT_type *) &FBOutputs;

	VAR->SecTimer.Data.uint8++;

	if (IN->ActuatorTime.Data.uint32 < 3)
		IN->ActuatorTime.Data.uint32 = 3;
	if (IN->TimeNonStop.Data.uint32 < 5)
		IN->TimeNonStop.Data.uint32 = 5;
	if (IN->APV_Interval.Data.uint32 < 30)
		IN->APV_Interval.Data.uint32 = 30;

	if (KernelInfo.EventFlags.Bit.CfgFirstExec) {
		OUT->stUprav.Data.bit = 0;
		OUT->State.Data.uint32 = 0;
		OUT->Control_ON.Data.bit = OUT->Control_OFF.Data.bit = 0;
		OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
		OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
		OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
		OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
		OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;
	} else {
		if (OUT->State.Data.uint32 & s00079_Dist) {

			if (OUT->State.Data.uint32 <= s00079_UpravMask) {
				OUT->stUprav.Data.bit = 1;
			} else {
				OUT->stUprav.Data.bit = 0;
			}

			
			if ((!(OUT->stUprav.Data.bit)) && (IN->ResetAlarm.Data.bit)) {
				if (IN->Actuator.Data.bit) {
					OUT->State.Data.uint32 &= ~(s00079_ActuatorFail_ON);
				} else {
					OUT->State.Data.uint32 &= ~(s00079_ActuatorFail_OFF | s00079_ActuatorFail_ON | s00079_flAlarm | s00079_flBlock | s00079_APV_TryCnt_Null);
				}
			}

			if (IN->Alarm.Data.bit) {
				if (((OUT->State.Data.uint32 & s00079_flAlarm) == 0)) {
					OUT->State.Data.uint32 |= s00079_flAlarm;
					OUT->State.Data.uint32 |= s00079_Need_OFF;
					OUT->State.Data.uint32 &= ~s00079_Need_ON;
					OUT->State.Data.uint32 &= ~s00079_ReinitAPV;
					VAR->CntReinitAPV.Data.uint32 = IN->TimeNonStop.Data.uint32 << 1;
				}
			}

			if (OUT->State.Data.uint32 == s00079_BlockMask) {
				OUT->State.Data.uint32 |= s00079_flBlock;
				OUT->State.Data.uint32 |= s00079_Need_OFF;
				OUT->State.Data.uint32 &= ~s00079_Need_ON;
			}

			if (IN->Cmd_ON.Data.bit) {
				OUT->State.Data.uint32 |= s00079_Need_ON;
				OUT->State.Data.uint32 &= ~s00079_Need_OFF;
			}

			if (IN->Cmd_OFF.Data.bit) {
				OUT->State.Data.uint32 |= s00079_Need_OFF;
				OUT->State.Data.uint32 &= ~s00079_Need_ON;
			}


			if (OUT->State.Data.uint32 & s00079_Need_ON) {
				if ((OUT->State.Data.uint32 == s00079_StartMask1) || (OUT->State.Data.uint32 == s00079_StartMask2)) {
					OUT->State.Data.uint32 |= (s00079_WaitActuator | s00079_ExpectActuator | s00079_WaitImpONOFF);
					OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
					OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
					OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
				}
				OUT->State.Data.uint32 &= ~s00079_Need_ON;				
			}

			if (OUT->State.Data.uint32 & s00079_Need_OFF) {
				if (IN->Actuator.Data.bit) {
					OUT->State.Data.uint32 &= ~s00079_ExpectActuator;
					OUT->State.Data.uint32 |= (s00079_WaitActuator | s00079_WaitImpONOFF);
					OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
					OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
					OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
				}
				OUT->State.Data.uint32 &= ~s00079_Need_OFF;
			}

			if (OUT->State.Data.uint32 & s00079_WaitActuator) {
				if (OUT->CntActRestart.Data.uint16) {
					if (OUT->State.Data.uint32 & s00079_WaitImpONOFF) {
						if (OUT->CntImpONOFF.Data.uint8 == 0) {
							OUT->Control_ON.Data.bit = 0;
							OUT->Control_OFF.Data.bit =0;
						} else {
							if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
								OUT->CntImpONOFF.Data.uint8--;
							}
							if (OUT->State.Data.uint32 & s00079_ExpectActuator) {
								OUT->Control_ON.Data.bit = 1;
								OUT->Control_OFF.Data.bit = 0;
							} else {
								OUT->Control_ON.Data.bit = 0;
								OUT->Control_OFF.Data.bit = 1;
							}
						}
					}
					if (OUT->CntActTime.Data.uint32) {
						if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->CntActTime.Data.uint32--;
						}
					} else {
						OUT->CntActRestart.Data.uint16--;
						OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
						OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
						if ((OUT->State.Data.uint32 & s00079_ExpectActuator) && (IN->Actuator.Data.bit)) {
							OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
							OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
							OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
							OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
							OUT->State.Data.uint32 &= ~(s00079_WaitActuator | s00079_WaitImpONOFF | s00079_ExpectActuator);
							OUT->State.Data.uint32 |= s00079_WaitBlock;
						} else if ((!(OUT->State.Data.uint32 & s00079_ExpectActuator)) && (!(IN->Actuator.Data.bit))) {
							OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
							OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
							OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
							OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
							OUT->State.Data.uint32 &= ~(s00079_WaitActuator | s00079_WaitImpONOFF | s00079_ExpectActuator);
						}
					}

				} else {
					if (OUT->State.Data.uint32 & s00079_ExpectActuator) {
						OUT->State.Data.uint32 |= s00079_ActuatorFail_ON;
						OUT->State.Data.uint32 |= s00079_WaitImpSTOP;
						OUT->CntImpONOFF.Data.uint8 = IN->ImpulsONOFFTime.Data.uint8;
					} else {
						OUT->State.Data.uint32 |= s00079_ActuatorFail_OFF;
					}
					OUT->State.Data.uint32 &= ~(s00079_WaitActuator | s00079_ExpectActuator | s00079_WaitImpONOFF);
					OUT->Control_ON.Data.bit = 0;
					OUT->Control_OFF.Data.bit = 0;
				}
			}

			if (OUT->State.Data.uint32 & s00079_WaitBlock) {
				if (OUT->CntNonStop.Data.uint32) {
					if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
						OUT->CntNonStop.Data.uint32--;
					}
				} else {
					OUT->State.Data.uint32 &= ~s00079_WaitBlock;
				}
			}

			if (OUT->State.Data.uint32 & s00079_WaitImpSTOP) {
				if (OUT->CntImpONOFF.Data.uint8) {
					if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
						OUT->CntImpONOFF.Data.uint8--;
					}
					OUT->Control_OFF.Data.bit = 1;
					OUT->Control_ON.Data.bit = 0;
				} else {
					OUT->Control_OFF.Data.bit = 0;
					OUT->Control_ON.Data.bit = 0;
					OUT->State.Data.uint32 &= ~s00079_WaitImpSTOP;					
				}
			}

//			if ((OUT->State.Data.uint32 & s00079_APVMask1ON) || (OUT->State.Data.uint32 & s00079_APVMask2ON)) {
//				if ((!(OUT->State.Data.uint32 & s00079_APVMask1OFF)) || (!(OUT->State.Data.uint32 & s00079_APVMask2OFF))) {
//					if (OUT->APV_TryCnt.Data.uint16) {
//						if (OUT->APV_Timer.Data.uint32) {
//							if (VAR->SecTimer.Data.uint8 == FBkernelRate) {
//								OUT->APV_Timer.Data.uint32--;
//							}
//						} else {
//							OUT->APV_TryCnt.Data.uint16--;
//							OUT->State.Data.uint32 &= ~(s00079_ActuatorFail_OFF | s00079_ActuatorFail_ON | s00079_flAlarm | s00079_flBlock);
//							OUT->State.Data.uint32 |= s00079_Need_ON;
//						}
//					} else {
//						OUT->State.Data.uint32 |= s00079_APV_TryCnt_Null;
//					}
//				}
//			}

//			if (OUT->State.Data.uint32 & s00079_ReinitAPV) {
//				if (VAR->CntReinitAPV.Data.uint32 == 0) {
//					OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
//					OUT->APV_TryCnt.Data.uint32 = IN->APV_Interval.Data.uint32;
//					OUT->State.Data.uint32 &= s00079_ReinitAPV;
//				} else {
//					if (VAR->SecTimer.Data.uint8 == FBkernelRate) {
//						VAR->CntReinitAPV.Data.uint32--;
//					}
//				}
//			}

		} else {
			OUT->stUprav.Data.bit = 0;
			OUT->State.Data.uint32 = 0;
			OUT->Control_ON.Data.bit = OUT->Control_OFF.Data.bit = 0;
			OUT->CntActTime.Data.uint32 = IN->ActuatorTime.Data.uint32;
			OUT->CntActRestart.Data.uint16 = IN->ActuatorRestart.Data.uint16;
			OUT->CntNonStop.Data.uint32 = IN->TimeNonStop.Data.uint32;
			OUT->APV_TryCnt.Data.uint16 = IN->APV_TryNum.Data.uint16;
			OUT->APV_Timer.Data.uint32 = IN->APV_Interval.Data.uint32;
		}

		if (IN->Dist_mode.Data.bit) {
			OUT->State.Data.uint32 |= s00079_Dist;
			if (IN->APV_TryNum.Data.uint16 > 0)
				OUT->State.Data.uint32 |= s00079_APVon;
			else
				OUT->State.Data.uint32 &= ~s00079_APVon;
		} else {
			OUT->State.Data.uint32 &= ~s00079_Dist;
		}

		if (IN->Alarm.Data.bit)
			OUT->State.Data.uint32 |= s00079_Alarm;
		else
			OUT->State.Data.uint32 &= ~s00079_Alarm;

		if (IN->Block.Data.bit)
			OUT->State.Data.uint32 |= s00079_Block;
		else
			OUT->State.Data.uint32 &= ~s00079_Block;
		
		if (IN->Actuator.Data.bit)
			OUT->State.Data.uint32 |= s00079_Actuator;
		else
			OUT->State.Data.uint32 &= ~s00079_Actuator;

		if (VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate)
			VAR->SecTimer.Data.uint8 = 0;
	}
}
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00079_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00079_IN_type);
    case(1):
        return sizeof(fb00079_VAR_type);
    case(2):
        return sizeof(fb00079_OUT_type);
    default:
        return 0;
    }
}
