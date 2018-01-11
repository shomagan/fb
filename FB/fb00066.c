/* �� "��� (��������) v.2" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00066.h"

//==============================================================================
void fb00066_exec(void)
{
	u8 FBkernelRate;
  fb00066_IN_type *IN = (fb00066_IN_type *) FBInputs;
  fb00066_VAR_type *VAR = (fb00066_VAR_type *) FBVars;
  fb00066_OUT_type *OUT = (fb00066_OUT_type *) FBOutputs;

  OUT->GP_ON.Data.bit = OUT->GP_OFF.Data.bit = OUT->EndPeriod.Data.bit = 0;
  
	if (KernelInfo.EventFlags.Bit.CfgFirstSec&&(IN->KodPSM.Data.uint8 & 0x0F)) {
		OUT->TimerUstOut.Data.uint16 = OUT->TimerOut.Data.uint16 = 0;
		OUT->GZUsost.Data.uint16=0;
		OUT->ManualOtvNum.Data.uint8=IN->KodPSM.Data.uint8 & 0x0F; // ��� ���� ����� ��� ������ ��������� ������� � ������� � ����� ����� ������ � ������ �������� ������� �����
	}
	FBkernelRate = KernelInfo.FBkernelRate;
  if ((FB_N_In!=17)||(FB_N_Vars!=6)||(FB_N_Out!=9)){
    LedErrorOn(30);
  }
//------------------------------------------------------------------------------
  if (IN->Enable.Data.bit) // ��������� ������ ���
//------------------------------------------------------------------------------
  {
    if (IN->Hold.Data.bit)   // Hold = 1
      OUT->GZUsost.Data.uint16 |= Holded;
    else                     // Hold = 0
    {
      OUT->GZUsost.Data.uint16 &= ~Holded;
      if ( (IN->GP_enabled.Data.bit) && ((OUT->GZUsost.Data.uint16 & GP_En) == 0) ) // ��������� (����������) ��
      {
        OUT->GZUsost.Data.uint16 = 0;
        VAR->TryCount.Data.uint8 = 0;
        VAR->APV_TryCount.Data.uint8 = 0;
      }
      OUT->GZUsost.Data.uint16 |= Enabled;

//------------------------------------------------------------------------------
      if (IN->ManualOtvNum.Data.uint8 != OUT->ManualOtvNum.Data.uint8)    // ���� ��������� � ������ ��� ������� ������
      {
        if (IN->ManualOtvNum.Data.uint8 <= IN->GZU_OtvNum.Data.uint8)     // ���� �� ����� "� ������ ��� ������� ������" ���������� ��������
        {
          //if (OUT->GZUsost.Data.uint16 & Zamer)
           // OUT->EndPeriod.Data.bit = 1;

          if (IN->ManualOtvNum.Data.uint8 == 0)   // ���� ���������� ������������� �� ������� ������ � �����������
          {
            OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // ���������� ����, ���������� �������
            //OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ���������� �������

            OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
						
            OUT->GP_OFF.Data.bit = 1;
            //OUT->GZUsost.Data.uint16 |= Reverse;
            //VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16*FBkernelRate;
            VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
						VAR->TempExtra.Data.uint8 = 0;
            if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
              VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F) - 1;
            else if (IN->KodPSM.Data.uint8 & 0x0F)
              VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
          }
          else /*if ((OUT->GZUsost.Data.uint16 & Forward) == 0) */                  // ���� ���������� ������������� �� ������������ ������ � ������ � ������ �� ������ ���
          {
            OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked);
            //OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ���������� �������
						VAR->TempExtra.Data.uint8 = 0;
            if ((IN->KodPSM.Data.uint8 & 0x0F) == IN->ManualOtvNum.Data.uint8)        // ����� �� ������ ������
            {
              OUT->GP_OFF.Data.bit = 1;
              //OUT->GZUsost.Data.uint16 |= Reverse;
             // VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16*FBkernelRate;

              if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
                VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F) - 1;
              else if (IN->KodPSM.Data.uint8 & 0x0F)
                VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
            }

            OUT->TekOtvod.Data.uint8 = IN->ManualOtvNum.Data.uint8;
            VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
            OUT->GZUsost.Data.uint16 |= Manual;
          }
        }
      }
	  	//------------------------------------------------------------------------------
      if (IN->ExtraOtvNum.Data.uint8 && (IN->ExtraOtvNum.Data.uint8 <= IN->GZU_OtvNum.Data.uint8)) {    // ������������ ����� // ������� �������� ������������!
      //------------------------------------------------------------------------------
       // if (OUT->GZUsost.Data.uint16 & (Manual)) { // � ������ ������ �� ����������� � ������������ �����, ���������� ��������� ������������� ������
         // VAR->TempExtra.Data.uint8=0;
       // } else {
          if (!VAR->TempExtra.Data.uint8) VAR->TempExtra.Data.uint8 = IN->ExtraOtvNum.Data.uint8; 
       // }
      }
      if ((IN->GP_enabled.Data.bit) && !(OUT->GZUsost.Data.uint16 & (Forward | Reverse | GPbraked)) && (VAR->TempExtra.Data.uint8 != 0)) { // � �������� ������������� ������ ���-�� ����... ���� ������� ��� ��� ���������� 
        if (IN->KodPSM.Data.uint8 != VAR->TempExtra.Data.uint8) {// �������� ������������� ������ ��� �� ���������
          if (OUT->GZUsost.Data.uint16 & Zamer) {	OUT->EndPeriod.Data.bit = 1; }
          OUT->GZUsost.Data.uint16 &= ~(Stab |Stop | FullStop | Zamer  | PSMbraked | GPbraked | TryCnt0 | Kluch);  // ���������� ���
          OUT->GZUsost.Data.uint16 |= NeedPerevod; 
        } else {
          VAR->TempExtra.Data.uint8 = 0; // �������� ������ ������������� ������
        }
      }
//------------------------------------------------------------------------------
      if ( IN->CmdStopReset.Data.bit && (OUT->GZUsost.Data.uint16 & (Stop | FullStop)) ) // ������� ������ �����
//------------------------------------------------------------------------------
      {
        OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // ���������� ����, ���������� �������

        if (OUT->GZUsost.Data.uint16 & Zamer)
          OUT->EndPeriod.Data.bit = 1;
        OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ���������� �������
        OUT->GZUsost.Data.uint16 |= Reverse;
        OUT->GP_OFF.Data.bit = 1;
        VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16*FBkernelRate;
        VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
				VAR->TempExtra.Data.uint8 = 0;
        if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
          VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F) - 1;
        else if (IN->KodPSM.Data.uint8 & 0x0F)
          VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
      }

//------------------------------------------------------------------------------
      if (IN->CmdSwitchOtv.Data.bit) // ������� �������� ������
//------------------------------------------------------------------------------
      {
        OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked);  // ���������� ����, ���������� �������
        
        if (OUT->GZUsost.Data.uint16 & Manual1Cnt)
          OUT->GZUsost.Data.uint16 &= ~(Manual1Cnt); // | Manual
        if (OUT->GZUsost.Data.uint16 & Zamer)
          OUT->EndPeriod.Data.bit = 1;
        VAR->TryCount.Data.uint8 = VAR->APV_TryCount.Data.uint8 = 0;
        OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ������� ����� �� ��������� ��������� ���� ���� ����� ���� ������ �� �������� ���
        OUT->GZUsost.Data.uint16 |= NeedPerevod;
				u8 otvod;
				otvod = IN->KodPSM.Data.uint8 & 0x0F;
				for (u8 j=0; j<14; j++){
					if (++otvod >= IN->GZU_OtvNum.Data.uint8){
						otvod = 1;
					}

					if (IN->OtvMask.Data.uint16 & (1 << ((otvod & 0x0F) - 1))){
               VAR->TempExtra.Data.uint8 = otvod; break;}
					else VAR->TempExtra.Data.uint8=0;
				}
      }

//------------------------------------------------------------------------------
      // �� ����
      if (!(OUT->GZUsost.Data.uint16 & (Stop | FullStop | GPbraked) ) )
//------------------------------------------------------------------------------
      {
        if (VAR->Timer1.Data.uint32)
          VAR->Timer1.Data.uint32--;

//------------------------------------------------------------------------------
        if ((OUT->GZUsost.Data.uint16 & (Stab | Forward | Reverse | Zamer)) == 0) // ��� ������ �� ������
//------------------------------------------------------------------------------
        {
          if ( ((IN->KodPSM.Data.uint8 & 0x0F) == 0) || ((IN->KodPSM.Data.uint8 & 0x0F) > IN->GZU_OtvNum.Data.uint8) )
            OUT->GZUsost.Data.uint16 |= NeedPerevod;

          if (OUT->GZUsost.Data.uint16 & NeedPerevod) // ����� ������� ������
          {
            if (IN->GP_enabled.Data.bit)   // ������ �� ���������
            {
              OUT->GZUsost.Data.uint16 &= ~NeedPerevod;
              OUT->GZUsost.Data.uint16 |= Forward;
              OUT->GP_ON.Data.bit = 1;
              VAR->Timer1.Data.uint32 = IN->ForwardTime.Data.uint16 * FBkernelRate;
							OUT->TimerUstOut.Data.uint16 = IN->ForwardTime.Data.uint16;
              if (IN->KodPSM.Data.uint8 & 0x0F)
                VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
            }
            else                              // ������ �� ���������, ��������� � ������ �����
            {
              if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
                VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
              else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
                VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;

              OUT->GZUsost.Data.uint16 &= ~NeedPerevod;
              OUT->GZUsost.Data.uint16 |= (Reverse | Manual);
              OUT->GP_OFF.Data.bit = 1;
              VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * FBkernelRate;
							OUT->TimerUstOut.Data.uint16 = IN->ReverseTime.Data.uint16;
            }
          }
          else
          {
            // (����������� ������ � ����� �������� ������� ����� ��� ������ ����� � ����� �� ������ ������)
            if  ((((OUT->GZUsost.Data.uint16 & Manual) == 0) && 
                      (IN->OtvMask.Data.uint16 & (1 << ((IN->KodPSM.Data.uint8 & 0x0F) - 1))) &&
                      ((IN->KodPSM.Data.uint8 & 0x0F) == OUT->ManualOtvNum.Data.uint8)) || \
                  ((OUT->GZUsost.Data.uint16 & Manual) &&
                      ((IN->KodPSM.Data.uint8 & 0x0F) == OUT->ManualOtvNum.Data.uint8) ) )
            {
              OUT->GZUsost.Data.uint16 |= Stab;
              VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * FBkernelRate;
							OUT->TimerUstOut.Data.uint16=IN->StabTime.Data.uint16;
              VAR->Timer2.Data.uint32 = 0;
              OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
              VAR->TryCount.Data.uint8 = 0;

              if (IN->KodPSM.Data.uint8 & 0x0F)
                VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
            }
            else // ����� �������� ������
              OUT->GZUsost.Data.uint16 |= NeedPerevod;
          }
        }
//------------------------------------------------------------------------------
        else if (OUT->GZUsost.Data.uint16 & Forward)                            // ������ ���
//------------------------------------------------------------------------------
        {
					if (IN->ForwardTime.Data.uint16!=OUT->TimerUstOut.Data.uint16) // ���������� ����� ������� ���� �� ����� ������� ����
					{
						if (IN->ForwardTime.Data.uint16<=OUT->TimerOut.Data.uint16) { // ����� ����� ������ ��� ��� ��������, �� ����� ������������
							OUT->TimerUstOut.Data.uint16 = 0;
							VAR->Timer1.Data.uint32=0;
						} else {
							VAR->Timer1.Data.uint32 = (IN->ForwardTime.Data.uint16 - OUT->TimerOut.Data.uint16) * FBkernelRate; // ���������� ������ � ���� �� �����
							OUT->TimerUstOut.Data.uint16=IN->ForwardTime.Data.uint16;
						}
					}
          OUT->TimerOut.Data.uint16 = (FBkernelRate) ? (IN->ForwardTime.Data.uint16 - (VAR->Timer1.Data.uint32 / FBkernelRate)) : 0;

          if ((!VAR->Timer1.Data.uint32) || (!IN->GP_enabled.Data.bit) )
          {
            OUT->GZUsost.Data.uint16 &= ~Forward;
            OUT->GZUsost.Data.uint16 |= Reverse;
            OUT->GP_OFF.Data.bit = 1;
            VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16*FBkernelRate;
            OUT->TimerUstOut.Data.uint16 = IN->ReverseTime.Data.uint16;
          }
        }
//------------------------------------------------------------------------------
        else if (OUT->GZUsost.Data.uint16 & Reverse)                            // �������� ���
//------------------------------------------------------------------------------
        {
					if (IN->ReverseTime.Data.uint16!=OUT->TimerUstOut.Data.uint16) // ���������� ����� ��������� ���� �� ����� ��������� ����
					{
						if (IN->ReverseTime.Data.uint16<=OUT->TimerOut.Data.uint16) { // ����� ����� ������ ��� ��� ��������, �� ����� ������������
							OUT->TimerUstOut.Data.uint16 = 0;
							VAR->Timer1.Data.uint32=0;
						} else {
							VAR->Timer1.Data.uint32 = (IN->ReverseTime.Data.uint16 - OUT->TimerOut.Data.uint16) * FBkernelRate; // ���������� ������ � ���� �� �����
							OUT->TimerUstOut.Data.uint16=IN->ReverseTime.Data.uint16;
						}
					}
          OUT->TimerOut.Data.uint16 = (FBkernelRate) ? (IN->ReverseTime.Data.uint16 - (VAR->Timer1.Data.uint32 / FBkernelRate)) : 0;
          
					if (!VAR->Timer1.Data.uint32)
          {
            OUT->GZUsost.Data.uint16 &= ~Reverse;

            if (OUT->GZUsost.Data.uint16 & NeedPerevod) // ����� ������� ������ (���� ������� ������������ ������)
              OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // ����� ������� ������
            else
            {
              if ( ((OUT->GZUsost.Data.uint16 & Kluch) == 0) || ((OUT->GZUsost.Data.uint16 & Manual) == 0) )
              {
                // �������� ���������� ���������� ������������
                //--------------------------------------------------------------------
                if (VAR->KodPSMOld.Data.uint8 == (IN->KodPSM.Data.uint8 & 0x0F))
                  OUT->GZUsost.Data.uint16 |= (GPbraked | Stop);        // ���������� �� (���=0)
                else if (((IN->KodPSM.Data.uint8 & 0x0F) == 0) || ((IN->KodPSM.Data.uint8 & 0x0F) > IN->GZU_OtvNum.Data.uint8))
                  OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // ���������� ������ ���
                else if (VAR->KodPSMOld.Data.uint8 >= IN->GZU_OtvNum.Data.uint8) // ���� ������� ����� ��������� � �����
                {
                  if ((IN->KodPSM.Data.uint8 & 0x0F) > 1){
                    OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // ���������� ������ ���
									}else{
										VAR->TryCount.Data.uint8 = 0;
									}
                }
                else if ((IN->KodPSM.Data.uint8 & 0x0F) != (VAR->KodPSMOld.Data.uint8 + 1)){
                  OUT->GZUsost.Data.uint16 |= (PSMbraked | Stop);       // ���������� ������ ���
								}else{
									VAR->TryCount.Data.uint8 = 0;
								}
                //--------------------------------------------------------------------
              }

              if ((OUT->GZUsost.Data.uint16 & (PSMbraked | GPbraked | Stop)) == 0)  // ��� ����� ��� ��-�� ������������ ������� ���
              {
                OUT->TekOtvod.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);

                if ( (OUT->GZUsost.Data.uint16 & Manual) == 0)  // ����������� ������, �������� ������
                {
                  if (IN->OtvMask.Data.uint16 & (1 << ((IN->KodPSM.Data.uint8 & 0x0F) - 1)) ) // ����� �������� ������ �����
                  {
                    OUT->GZUsost.Data.uint16 |= Stab;
                    VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * FBkernelRate;
                    VAR->Timer2.Data.uint32 = 0;
                    VAR->TryCount.Data.uint8 = 0;
                  }
                  else
                  {
                    if (VAR->TryCount.Data.uint8 < IN->TryNum.Data.uint8){
                      OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // ����� ������� ������
                      OUT->GZUsost.Data.uint16 |= NeedPerevod;
                      VAR->TryCount.Data.uint8++;
                    }
                    else{
                      OUT->GZUsost.Data.uint16 |= (Stop | TryCnt0);
                      VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * FBkernelRate;  // ���� ������ ��� ������� � ���� - ������� Timer2 (��� ������� ��������� ���)
                    }
                  }
                }
                else    // ������ �����
                {
                  if ( ((IN->KodPSM.Data.uint8 & 0x0F) == OUT->ManualOtvNum.Data.uint8) || (OUT->GZUsost.Data.uint16 & Manual1Cnt) ) // ����� �� ������ ������, �������� ������������ � �����
                  {
                    OUT->GZUsost.Data.uint16 |= Stab;
                    VAR->Timer1.Data.uint32 = IN->StabTime.Data.uint16 * FBkernelRate;
                    VAR->Timer2.Data.uint32 = 0;
                    VAR->TryCount.Data.uint8 = 0;
                  }
                  else    // ����� ��� ������������
                  {
                    if (VAR->TryCount.Data.uint8 < IN->TryNum.Data.uint8)
                    {
                      OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // ����� ������� ������
                      OUT->GZUsost.Data.uint16 |= NeedPerevod;
                      VAR->TryCount.Data.uint8++;
                    }
                    else
                    {
                      OUT->GZUsost.Data.uint16 |= (Stop | TryCnt0);
                      VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * FBkernelRate;  // ���� ������ ��� ������� � ���� - ������� Timer2 (��� ������� ��������� ���)
                    }
                  }
                }
              }
              else
              {
                if (OUT->GZUsost.Data.uint16 & Stop)
                  VAR->Timer2.Data.uint32 = IN->APV_interval.Data.uint16 * 60 * FBkernelRate;  // ���� ������ ��� ������� � ���� - ������� Timer2 (��� ������� ��������� ���)
              }
            }
          }
        }
//------------------------------------------------------------------------------
        else if (OUT->GZUsost.Data.uint16 & Stab)                            // ������������
//------------------------------------------------------------------------------
        {
					if (IN->StabTime.Data.uint16!=OUT->TimerUstOut.Data.uint16) // ���������� ����� ������������ �� ����� ������������
					{
						if (IN->StabTime.Data.uint16<=OUT->TimerOut.Data.uint16) { // ����� ����� ������ ��� ��� ��������, �� ����� ������������
							OUT->TimerUstOut.Data.uint16 = 0;
							VAR->Timer1.Data.uint32=0;
						} else {
							VAR->Timer1.Data.uint32 = (IN->StabTime.Data.uint16 - OUT->TimerOut.Data.uint16) * FBkernelRate; // ���������� ������ � ���� �� �����
							OUT->TimerUstOut.Data.uint16=IN->StabTime.Data.uint16;
						}
					}
          OUT->TimerOut.Data.uint16 = (FBkernelRate) ? (IN->StabTime.Data.uint16 - (VAR->Timer1.Data.uint32 / FBkernelRate)) : 0;
          if (!VAR->Timer1.Data.uint32)
          {
            OUT->GZUsost.Data.uint16 &= ~Stab;
            OUT->GZUsost.Data.uint16 |= Zamer;
          }
          else
          {
            if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) // �� ����� ������������ ��������� ��� ���
              OUT->GZUsost.Data.uint16 |= Kluch;
            else
            {
              OUT->GZUsost.Data.uint16 &= ~Kluch;
              VAR->Timer2.Data.uint16 = 0;
            }

            if (OUT->GZUsost.Data.uint16 & Kluch)
            {
              if (++VAR->Timer2.Data.uint16 > (KluchDelay*FBkernelRate))  // 15 ������ �������� ����� ��� ���
              {
                if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
                  VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
                else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
                  VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;

                OUT->GZUsost.Data.uint16 &= ~Stab;
                OUT->GZUsost.Data.uint16 &= ~Kluch;
                OUT->GZUsost.Data.uint16 |= (Reverse | Manual | Manual1Cnt);
                OUT->GP_OFF.Data.bit = 1;
                OUT->EndPeriod.Data.bit = 1;
                VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * FBkernelRate;
              }
            }
          }
        }
//------------------------------------------------------------------------------
        else if (OUT->GZUsost.Data.uint16 & Zamer)                            // �����
//------------------------------------------------------------------------------
        {
          if ( (IN->EndPeriod.Data.bit) && ((OUT->GZUsost.Data.uint16 & Kluch)==0) )
          {
            if (OUT->GZUsost.Data.uint16 & Manual)  // ������ �����
            {
              if (OUT->GZUsost.Data.uint16 & Manual1Cnt){
                OUT->GZUsost.Data.uint16 = 0;                            // ���������� ��� �������
                OUT->GZUsost.Data.uint16 |= NeedPerevod;                 // ����� �������
                VAR->TryCount.Data.uint8 = 0;				
							} else {
								OUT->EndPeriod.Data.bit = IN->EndPeriod.Data.bit;
								OUT->Counting.Data.bit = 1;
							}
            }
            else                                      // ����������� ������
            {
              OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer);  // ����� ������� ������
              OUT->GZUsost.Data.uint16 |= NeedPerevod;
              VAR->TryCount.Data.uint8 = 0;
            }
          }
          else
          {
            if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) // �� ����� ������ ��������� ��� ���
              OUT->GZUsost.Data.uint16 |= Kluch;
            else
            {
              OUT->GZUsost.Data.uint16 &= ~Kluch;
              VAR->Timer2.Data.uint16 = 0;
            }
          }

          if (OUT->GZUsost.Data.uint16 & Kluch)
          {
            if (++VAR->Timer2.Data.uint16 > (KluchDelay*FBkernelRate))  // 15 ������ �������� ����� ��� ���
            {
              if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
                VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
              else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
                VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;
              OUT->GZUsost.Data.uint16 = 0;
              OUT->GZUsost.Data.uint16 |= (Reverse | Manual | Manual1Cnt);
              OUT->GP_OFF.Data.bit = 1;
              OUT->EndPeriod.Data.bit = 1;
              VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * FBkernelRate;
            }
          }
        }
//------------------------------------------------------------------------------
      }
//------------------------------------------------------------------------------
      else  // ����
//------------------------------------------------------------------------------
      {
        if ( (OUT->GZUsost.Data.uint16 & FullStop) == 0)  // ���� �� ������ ����
        {
          if (VAR->APV_TryCount.Data.uint8 >= IN->APV_TryNum.Data.uint8)  // ��������� ������� ��� ���
          {
            OUT->GZUsost.Data.uint16 |= FullStop;
            OUT->TimerOut.Data.uint16 = 0;
            OUT->TimerUstOut.Data.uint16 = 0;
          }
          else
          {
            if (VAR->Timer2.Data.uint32)
              VAR->Timer2.Data.uint32--;
            else
            {
              VAR->APV_TryCount.Data.uint8++;
              OUT->GZUsost.Data.uint16 &= ~(Stop | PSMbraked | GPbraked | TryCnt0 | Kluch);
              OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ���������� �������

              VAR->TryCount.Data.uint8 = 0;
              VAR->Timer1.Data.uint32 = 0;
            }
          }
          OUT->TimerOut.Data.uint16 = (FBkernelRate) ? (IN->APV_interval.Data.uint16 - (VAR->Timer2.Data.uint32/(60*FBkernelRate))) : 0;
          OUT->TimerUstOut.Data.uint16 = IN->APV_interval.Data.uint16;
        }

        if ((IN->KodPSM.Data.uint8 & 0x0F) != OUT->TekOtvod.Data.uint8) // �� ����� �����(���� �������) ��������� ��� ���
        {
          OUT->TekOtvod.Data.uint8 = VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F);
          OUT->GZUsost.Data.uint16 |= Kluch;
          VAR->Timer1.Data.uint32 = 0;
        }

        if (OUT->GZUsost.Data.uint16 & Kluch)
        {
          if (++VAR->Timer1.Data.uint32 > (KluchDelay*FBkernelRate))  // 15 ������ �������� ����� ��� ���
          {
            if ((IN->KodPSM.Data.uint8 & 0x0F) == 1)
              VAR->KodPSMOld.Data.uint8 = IN->GZU_OtvNum.Data.uint8;
            else if ((IN->KodPSM.Data.uint8 & 0x0F) > 1)
              VAR->KodPSMOld.Data.uint8 = (IN->KodPSM.Data.uint8 & 0x0F)-1;

            OUT->GZUsost.Data.uint16 &= ~(Stop | FullStop | TryCnt0 | GPbraked | PSMbraked | Manual);  // ���������� ����, ���������� �������
            OUT->GZUsost.Data.uint16 &= ~(Stab | Forward | Reverse | Zamer | Kluch);  // ���������� �������
            OUT->GZUsost.Data.uint16 |= (Reverse | Manual| Manual1Cnt);
            OUT->GP_OFF.Data.bit = 1;
            VAR->Timer1.Data.uint32 = IN->ReverseTime.Data.uint16 * FBkernelRate;
          }
        }
      }

      if ( (OUT->GZUsost.Data.uint16 & Stop) && ((OUT->GZUsost.Data.uint16 & Kluch) == 0) )  // ���� ���� �� ���� �������� ������
        OUT->TekOtvod.Data.uint8 = IN->KodPSM.Data.uint8 & 0x0F;
    }
  }
//------------------------------------------------------------------------------
  else  // Enable = 0
//------------------------------------------------------------------------------
  {
    OUT->GZUsost.Data.uint16 &= ~Enabled;
    OUT->GZUsost.Data.uint16 = 0;
    VAR->Timer1.Data.uint32 = VAR->Timer2.Data.uint32 = 0;
    VAR->APV_TryCount.Data.uint8 = 0;
    OUT->EndPeriod.Data.bit = 1;
  }

  if (IN->GP_enabled.Data.bit)
    OUT->GZUsost.Data.uint16 |= GP_En;
  else
    OUT->GZUsost.Data.uint16 &= ~GP_En;
	if (!KernelInfo.EventFlags.Bit.CfgFirstSec){
		OUT->ManualOtvNum.Data.uint8 = (OUT->GZUsost.Data.uint16 & Manual) ? IN->ManualOtvNum.Data.uint8 : 0;
	}
  //OUT->ManualOtvNum.Data.uint8 = (OUT->GZUsost.Data.uint16 & Manual1Cnt) ? IN->KodPSM.Data.uint8 : OUT->ManualOtvNum.Data.uint8;
  OUT->Counting.Data.bit = ( (OUT->GZUsost.Data.uint16 & Zamer) && ((OUT->GZUsost.Data.uint16 & Kluch)==0) ) ? 1 : 0;
}
//==============================================================================
/*
  type 0 - IN,1- VAR,2 - OUT
  return size struct, or 0 if struct not
*/    unsigned int fb00066_var_size(unsigned char type) {
    switch(type){
    case(0):
        return sizeof(fb00066_IN_type);
    case(1):
        return sizeof(fb00066_VAR_type);
    case(2):
        return sizeof(fb00066_OUT_type);
    default:
        return 0;
    }
}
