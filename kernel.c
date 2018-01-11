//kernel.c
#include <string.h>
#include <math.h>
#include <time.h>
#include "vars.h"
#include "kernel.h"
#include <stdio.h>
#define DEBUG_LOAD 0

Register_type FBInputs[cstFBInputsNum];
Register_type FBVars[cstFBVarsNum];
Register_type FBOutputs[cstFBOutputsNum];

u8 *pCFG;
u8 *pCFG_temp;
vu16 FB_N_In, FB_N_Vars, FB_N_Out;
vu32 CfgStartTime;
u8 *pStartCfg;
vu8 CntCfg1SecExec;
vu8 CntSaveFBRam;
u32 unix_time;
u32 BateryMemFB32[512];
extern KernelInfo_t KernelInfo;
const FB_Func fb_exec[]={
    fb00000_exec, fb00001_exec, fb00002_exec, fb00003_exec, FB00004_exec,
    fb00005_exec, fb00006_exec, fb00007_exec, fb00008_exec, fb00009_exec,
    fb00010_exec, fb00011_exec, fb00012_exec, fb00013_exec, fb00014_exec,
    fb00015_exec, fb00016_exec, fb00017_exec, fb00018_exec, fb00019_exec,
    fb00020_exec, fb00021_exec, fb00022_exec, fb00023_exec, fb00024_exec,
    fb00025_exec, fb00026_exec, fb00027_exec, fb00028_exec, fb00029_exec,
    fb00030_exec, fb00031_exec, fb00032_exec, fb00033_exec, fb00034_exec,
    fb00035_exec, fb00036_exec, fb00037_exec, fb00038_exec, fb00039_exec,
    fb00040_exec, fb00041_exec, fb00042_exec, fb00043_exec, fb00044_exec,
    fb00045_exec, fb00046_exec, fb00047_exec, fb00048_exec, fb00049_exec,
    fb00050_exec, fb00051_exec, fb00052_exec, fb00053_exec, fb00054_exec,
    fb00055_exec, fb00056_exec, fb00057_exec, fb00058_exec, fb00059_exec,
    fb00060_exec, fb00061_exec, fb00062_exec, fb00063_exec, fb00064_exec,
    fb00065_exec, fb00066_exec, fb00067_exec, fb00068_exec, fb00069_exec,
    fb00070_exec, fb00071_exec, fb00072_exec, fb00073_exec, fb00074_exec,
    fb00075_exec, fb00076_exec, fb00077_exec, fb00078_exec, fb00079_exec,
    fb00080_exec, fb00081_exec, fb00082_exec, fb00083_exec, fb00084_exec,
    fb00085_exec, fb00086_exec, fb00087_exec, fb00088_exec, fb00089_exec,
    fb00090_exec, fb00091_exec, fb00092_exec, fb00093_exec, fb00094_exec,
    fb00000_exec, fb00000_exec, fb00000_exec, fb00000_exec, fb00099_exec,
    fb00100_exec, fb00101_exec, fb00102_exec, fb00103_exec, fb00104_exec,
    fb00105_exec, fb00106_exec, fb00107_exec, fb00108_exec, fb00109_exec,
    fb00110_exec, fb00111_exec, fb00112_exec, fb00113_exec, fb00114_exec,
    fb00115_exec, fb00116_exec, fb00117_exec, fb00118_exec, fb00119_exec,
    fb00120_exec, fb00121_exec, fb00122_exec 
};
u8 GetNeed2SyncState(void){
  return 0;
}
u8 SetSystemOption(u16 address,u16 value){
    FB32blok.Bytes[address*2] = (u8)value;
    FB32blok.Bytes[address*2+1] = (u8)(value>>8);
    return 0x00;
}
u8 GetSystemOption (u16 address, u16* TempValue){
    *TempValue = (u16)(FB32blok.Bytes[address*2]);
    *TempValue = (u16)(FB32blok.Bytes[address*2+1])<<8;
    return 0x00;
}
void SysTimeWriteUNIX (u32 time_to_write){
    unix_time = time_to_write;
}
u32 GetSystemTime_t(void){
    time_t seconds;
    seconds = time(NULL);
		return seconds;
}

u8 WasAddOverflow(void){
    return 0;
}
void NewQ_Arc_R7(vu8 *pR7buffer, vu8 SubType){  // ������� ���� ������ ����������
    printf("add new arc with type - %u",SubType);
}
//=== ������ ��������� ������ Paket �� Tiks1ms mS ===//
void LedPaketOn(vs16 Tiks1ms){
}

//=== ������ ��������� LEDOTVET ===//
void LedOtvetOn(vs16 Tiks1ms){
}

//=== ������ ��������� LEDERROR ===//
void LedErrorOn(vs16 Tiks1ms){
    printf("error exeption in fb - %u",Tiks1ms);
}


//=== ������ ��������� LEDTEST ===//
void LedTestOn(vs16 Tiks1ms){
}


u16 check_file_crc(vu32 addr, vu32 length){
    u8 TmpBuff[64];
    u8 Bytes, BytesNum;
    u16 tmpcrc;
    tmpcrc = 0;
    while (length) {
        BytesNum = (length > 64) ? 64 : length;
        for (vu8 i=0;i<BytesNum;i++){
            TmpBuff[i] = *(vu8*)(addr+i);
        }
        Bytes = 0;
        while (Bytes < BytesNum) {
            tmpcrc = (u8)(tmpcrc >> 8) | (tmpcrc << 8);
            tmpcrc ^= TmpBuff[Bytes++];
            tmpcrc ^= (u8)(tmpcrc & 0xff) >> 4;
            tmpcrc ^= (tmpcrc << 8) << 4;
            tmpcrc ^= ((tmpcrc & 0xff) << 4) << 1;
            addr++;
            length--;
        }
    }
    return tmpcrc;
}

void fb00000_exec(void){}
u8 IsCorrectFloat(Flo32 Value){
	if (isnan(Value) || isinf(Value))
		return 0;
	else
		return 1;
}



Flo32 Void2Float32(Register_type *pReg){
	u32 a;
	switch (pReg->Type & DataTypeMask){   // Òèï âõîäà
	case KodBit:
		a = pReg->Data.bit;
		return ((Flo32)a);
	case KodInt8:
	case KodInt16:
	case KodInt32:
	case KodTime32:
		a = pReg->Data.uint32;
		return ((Flo32)a);
	case KodFloat32:
		return (pReg->Data.float32);
	default:
		return (0.0);
	}
}
//=== return pointer to value in kernel ram buff ===
void* get_pointer_to_value(vu8* current_variable){
  vu8 type;
  vu16 Adress;
  vu8* pointer_to_value;
  type = *current_variable;
  current_variable++;
  if (type & IsArrayMask){
    current_variable+=2;
  }
  Adress = (*(u16*)current_variable);
  current_variable+=2;  
	if (Adress < cstMaxFB_RAMsize){ 
    pointer_to_value = &FB32blok.Bytes[(Adress+OWN_VARIABLE_BLOK_SIZE)];
  }else{
    pointer_to_value = 0;
	}
  return (void*)pointer_to_value;
}
u8 OverflowInInt(vu8 Type,vu32 Value){
	if((((Type & DataTypeMask) == KodInt8) && (Value > 0xff)) || (((Type & DataTypeMask) == KodInt16) && (Value > 0xffff))) return 1;
	else return 0;
}

u8 VarSize(vu8 type){
	switch(type & DataTypeMask){
	case KodBit:
	case KodInt8:
		return 1;
	case KodInt16:
		return 2;
	case KodInt32:
	case KodFloat32:
	case KodTime32:
		return 4;
	}
	return 1;
}

void ClearFBregs (vu16 FBInputsNum,vu16 FBVarsNum,vu16 FBOutputsNum){
    u16 i;
  	for (i = 0; i < FBInputsNum; i++) {
    		FBInputs[i].Type = 0;
    		FBInputs[i].Data.uint32 = 0;
  	}
  	for (i = 0; i < FBVarsNum; i++) {
    		FBVars[i].Type = 0;
    		FBVars[i].Data.uint32 = 0;
  	}
  	for (i = 0; i < FBOutputsNum; i++) {
    		FBOutputs[i].Type = 0;
    		FBOutputs[i].Data.uint32 = 0;
  	}
}

u8 ReadInt8Cfg (void){
  	u8 ress;
  	ress = *pCFG;
  	pCFG++;
  	return ress;
}

u16 ReadInt16Cfg (void){
    u16 temp;
    temp = (*(u16*)pCFG);
    pCFG+=2;
    return (temp);
}

u32 ReadInt32Cfg (void){
    u32 temp;
  	temp = (*(u32*)pCFG);
  	pCFG+=4;
  	return (temp);//ress;
}

Flo32 ReadFloat32Cfg (void){
    typedef union{
        u32 a;
        Flo32 fl;
    } sValue;
    sValue Value;
    Value.a = *(u32*)pCFG;
    pCFG+=4;
    return Value.fl;
}

void LoadConst (vu8 type, vu16 ArraySize){
    u8 n;
    Register_type *pDest;
#if DEBUG_LOAD
    printf("load const var with type  %u",(u8)type);
#endif

  	pDest = FBInputs + FB_N_In;
  	if(ArraySize){
        FB_N_In += ArraySize;
  	}else{
    		ArraySize = 1;
    		FB_N_In++;
  	}
  	for (n = 0; n < ArraySize; n++) {
    		pDest->Type = type;
    		switch (type & DataTypeMask) {
    		case KodBit:
      			pDest->Data.uint32 = ReadInt8Cfg();
      			break;
    		case KodInt8:
      			pDest->Data.uint32= ReadInt8Cfg();
    	  		break;
    		case KodInt16:
    		  	pDest->Data.uint32 = ReadInt16Cfg();
    		  	break;
    		case KodInt32:
    		case KodTime32:
    		  	pDest->Data.uint32 = ReadInt32Cfg();
    		  	break;
    		case KodFloat32:
    		  	pDest->Data.float32 = ReadFloat32Cfg();
    		  	break;
        default:
#if DEBUG_LOAD
            printf("load const uncorrect type  %u",(u8)type);
#endif
            break;
    		}
    		pDest++;
  	}
}

void LoadVar (vu8 type, vu16 pAdress, vu16 ArraySize){
	vu16 shift = 0;
	vu8 n, i;
	Register_type *pDest;
	if (pAdress >= cstMaxFB_RAMsize){
    }else{
		if ((type & IsArrayMask) == 0){
            ArraySize = 1;
        }
		switch (type & RegTypeMask) {// Òèï äàííûõ
		case KodInput:
			pDest = FBInputs + FB_N_In;     // Áóäåì ïèñàòü â áóôåð âõîäîâ ÔÁøêè
			FB_N_In += ArraySize;
			break;
		case KodOutput:
			pDest = FBOutputs + FB_N_Out;   // Áóäåì ïèñàòü â áóôåð âûõîäîâ ÔÁøêè
			FB_N_Out += ArraySize;
			break;
		case KodVariable:
			pDest = FBVars + FB_N_Vars;     // Áóäåì ïèñàòü â áóôåð ïåðåìåííûõ ÔÁøêè
			FB_N_Vars += ArraySize;
			break;
		}

		for (n = 0; n < ArraySize; n++) { // Çàïèñü 1 ñòðóêòóðû âõîäîâ/âûõîäîâ
			pDest->Type = type;
			switch (type & DataTypeMask) {
			case KodBit:      // Çíà÷åíèå bit
			case KodInt8:     // Çíà÷åíèå int8
				pDest->Data.uint32 = FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE)+shift];
				shift++;
				break;
			case KodInt16:    // Çíà÷åíèå int16
				pDest->Data.uint32  = *(vu16*)(&FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE) + shift]);
				shift += 2;
				break;
			case KodInt32:    // Çíà÷åíèå int32
			case KodTime32:   // Çíà÷åíèå time32
			case KodFloat32:  // Çíà÷åíèå float32
				for (i = 0; i < 4; i++) 
					pDest->Data.arbytes[i] = FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE) + shift + i];
				shift += 4;
				break;
      default:
#if DEBUG_LOAD
          printf("load var uncorrect type  %u",(u8)type);
#endif
          break;

			}
			pDest++;
		}
	}
}

void SaveVar (vu8 type, vu16 pAdress, vu16 ArraySize){
	vu16 shift = 0;
	vu8 n, i;
	Register_type *pDest;
	if (pAdress >= cstMaxFB_RAMsize){
    }else{
		if ((type & IsArrayMask) == 0){
            ArraySize = 1;
        }
		switch (type & RegTypeMask) {
		case KodOutput:
			pDest = FBOutputs + FB_N_Out;
			FB_N_Out += ArraySize;
			break;
		case KodVariable:
			pDest = FBVars + FB_N_Vars;
			FB_N_Vars += ArraySize;
			break;
		}

		for (n = 0; n < ArraySize; n++) {
			switch (type & DataTypeMask) {
			case KodBit:
			case KodInt8:
				FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE)+shift] = pDest->Data.uint8;
				shift++;
				break;
			case KodInt16:
				for (i = 0; i < 2; i++) {
                    FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE) + shift + i] = pDest->Data.arbytes[i];
                }
                shift += 2;
				break;
			case KodInt32:
			case KodTime32:
			case KodFloat32:
				for (i = 0; i < 4; i++) {
					FB32blok.Bytes[(pAdress+OWN_VARIABLE_BLOK_SIZE) + shift + i] = pDest->Data.arbytes[i];
                }
				shift += 4;
				break;
      default:
#if DEBUG_LOAD
          printf("save var uncorrect type  %u",(u8)type);
#endif
          break;


			}
			pDest++;
		}
	}
}

u8 LoadFBRegister (void){
    vu16 ArraySize;
    vu8 type;
    type = *pCFG;
#if DEBUG_LOAD
    printf("load fb var with type  %u",(u8)type);
#endif

    while((type !=0xFF)&&(pCFG<(KernelInfo.pStartCFG+KernelInfo.CfgSize))){
        ArraySize = 0;
        pCFG++;
        if (type & IsArrayMask){
            ArraySize = ReadInt16Cfg ();
        }

        switch (type & RegTypeMask) {
        case KodConst:
            LoadConst (type, ArraySize);
        break;
        case KodVariable:
            if (FB_N_Vars == 0){
                pCFG_temp = (type & IsArrayMask) ? pCFG-3 : pCFG-1;
            }
        case KodOutput:
            if ((FB_N_Vars == 0) && (FB_N_Out == 0)){
                pCFG_temp = (type & IsArrayMask) ? pCFG-3 : pCFG-1;
            }
        case KodInput:
            LoadVar (type, ReadInt16Cfg(), ArraySize);
        break;
        default:
  #if DEBUG_LOAD
            printf("load fb register uncorrect type  %u",(u8)type);
  #endif
            break;


        }
        type = *pCFG;
    }
    return (type);
}

u8 SaveFBRegister(void){
    vu16 ArraySize;
    vu8 type;
    type = *pCFG;
    while((type!=0xFF)&&(pCFG<(KernelInfo.pStartCFG+KernelInfo.CfgSize))){    // Çàïèñü âûõîäîâ è ïåðåìåííûõ ýòîé ÔÁ.
        ArraySize = 0;
        pCFG++;
        switch (type & RegTypeMask) {
        case KodVariable:
        case KodOutput:
            if (type & IsArrayMask){
                ArraySize = ReadInt16Cfg();
            }
            SaveVar (type, ReadInt16Cfg(), ArraySize); // Íà÷àëüíûé àäðåñ è êîëè÷åñòâî
        break;
        case KodConst:
        case KodInput:
        break;
        }
        type = *pCFG;
    }
    return (type);
}

void KernelCycle(void){
    vu16 CodeFB;
    u16 k;
    pCFG = (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgTWICommSize+7);
    do{
        if(pCFG < (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgSize)){
            CodeFB=ReadInt16Cfg();
#if DEBUG_LOAD
            printf("execute fb number %u",(u16)CodeFB);
#endif

            FB_N_In=FB_N_Out=FB_N_Vars=0;
            pCFG_temp=0;
            LoadFBRegister();
            if(CodeFB<(sizeof(fb_exec)>>2)){
                fb_exec[CodeFB]();
            }else{
                FB32blok.vars.ErrCodFB |= 1<<FB_ERROR;
            }
            if(pCFG_temp){pCFG=pCFG_temp;}
            FB_N_Out=FB_N_Vars=0;
            SaveFBRegister();
            pCFG++;
            KernelInfo.pCFG = pCFG;
        }else{
            KernelInfo.EventFlags.Bit.Perfoming = 0;
            KernelInfo.EventFlags.Bit.CfgFirstExec=0;
            KernelInfo.StopTick = FB32blok.vars.GlobalTick;
            FB32blok.vars.KernelFullTime =(KernelInfo.StopTick - KernelInfo.StartTick);
        }
    }while (pCFG < (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgSize));
}
