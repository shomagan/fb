/* ÔÁ "Çàäâèæêà" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00080.h"

void fb00080_exec(void) {
/*	fb00078_IN_type *IN = (fb00078_IN_type *) FBInputs;
	fb00078_VAR_type *VAR = (fb00078_VAR_type *) FBVars;
	fb00078_OUT_type *OUT = (fb00078_OUT_type *) FBOutputs;
*/
	fb00080_IN_type *IN = (fb00080_IN_type *) FBInputs;
	fb00080_VAR_type *VAR = (fb00080_VAR_type *) FBVars;
	fb00080_OUT_type *OUT = (fb00080_OUT_type *) FBOutputs;

//	unsigned char NeedImpuls;
	unsigned int varSost;

	if(KernelInfo.EventFlags.Bit.CfgFirstExec) { //ïåðâûé çàïóñê
		OUT->OutOpen.Data.bit = 0;
		OUT->OutClose.Data.bit = 0;
		OUT->OutStop.Data.bit = 0;
		OUT->Timer.Data.uint16 = 0;
		OUT->Sost.Data.uint16 = 0;
		VAR->SecTimer.Data.uint8 = 0;
		VAR->ImpulsTime.Data.uint8 = 0;
		varSost = 0;
	} else { // íå ïåðâûé çàïóñê

		VAR->SecTimer.Data.uint8++;

//		NeedImpuls = (VAR->ImpulsTime.Data.uint8 > 0) ? 1 : 0;

		varSost = OUT->Sost.Data.uint16;

		if(IN->Dist.Data.bit == 0) { //Åñëè ìåñòíûé ðåæèì
			varSost = 0;
			OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
			OUT->OutOpen.Data.bit = 0;
			OUT->OutClose.Data.bit = 0;
			OUT->OutStop.Data.bit = 0;
			VAR->ImpulsTime.Data.uint16 = 0;
		} else { //Åñëè äèñòàíöèîííûé ðåæèì
			varSost |= s00080_DIST;
			if(IN->CmdStop.Data.bit || IN->Alarmed.Data.bit) { //Åñëè êîìàíäà ñòîï èëè àâàðèÿ
				OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
				OUT->OutStop.Data.bit = 1;		//Âûäàòü èìïóëüñ íà âûõîä ÑÒÎÏ
//				NeedImpuls = 1;
				VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Âðåìÿ èìïóëüñà óäåðæàíèÿ óïðàâëÿþùåãî ñèãíàëà â ñåê.
				OUT->OutClose.Data.bit = 0;		//ñáðîñèòü âûõîä óïðàâëåíèÿ ÇÀÊÐÛÒÜ
				OUT->OutOpen.Data.bit = 0;		//ñáðîñèòü âûõîä óïðàâëåíèÿ ÎÒÊÐÛÒÜ
				varSost &= ~s00080_OPENING;		//ñáðîñèòü ôëàã ÎÒÊÐÛÂÀÅÒÑß
				varSost &= ~s00080_CLOSING;		//ñáðîñèòü ôëàã ÇÀÊÐÛÂÀÅÒÑß

			} else { // îòðàáîòêà êîìàíä îòêðûòèÿ è çàêðûòèÿ
				if((IN->CmdOpen.Data.bit) && (!(varSost & s00080_CLOSING))) { // Åñëè Êîìàíäà îòêðûòü, è íå ÇÀÊÐÛÂÅÒÑß
					if(!IN->Opened.Data.bit&&(!OUT->OutStop.Data.bit)) {	//è íå ÎÒÊÐÛÒÀ
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Âðåìÿ èìïóëüñà óäåðæàíèÿ óïðàâëÿþùåãî ñèãíàëà â ñåê.
						OUT->OutOpen.Data.bit = 1;	//âûäàòü óïðàâëÿþùèé èìïóëüñ íà âûõîä ÎÒÊÐÛÒÜ
						varSost |= s00080_OPENING;	//âûñòàâèèòü ôëàã ÎÒÊÐÛÂÅÒÑß
						varSost &= ~s00080_CLOSING;	//ñáðîñèòü ôëàã ÇÀÊÐÛÂÀÅÒÑß
						varSost &= ~s00080_AVARMUFTA;	//ñáðîñèòü ôëàã ÀÂÀÐÈß ÏÎ ÌÓÔÒÅ
						varSost &= ~s00080_AVARVPHOPEN;	//ñáðîñèò ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÎÒÊÐÛÒÈß
						varSost &= ~s00080_AVARVPHCLOSE;	//ñáðîñèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÇÀÊÐÛÒÈß
					}
				}
				if((IN->CmdClose.Data.bit) && (!(varSost & s00080_OPENING))) { // Åñëè Êîìàíäà çàêðûòü, è íå îòêðûâàåòñÿ
					if(!IN->Closed.Data.bit&&(!OUT->OutStop.Data.bit)) {	//è íå ÇÀÊÐÛÒÀ
						OUT->Timer.Data.uint16 = IN->VPH.Data.uint16;
//						NeedImpuls = 1;
						VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME; // Âðåìÿ èìïóëüñà óäåðæàíèÿ óïðàâëÿþùåãî ñèãíàëà â ñåê.
						OUT->OutClose.Data.bit = 1;	//âûäàòü óïðàâëÿþùèé èìïóëüñ íà âûõîä ÇÀÊÐÛÒÜ
						varSost |= s00080_CLOSING;	//âûñòàâèòü ôëàã ÇÀÊÐÛÂÀÅÒÑß
						varSost &= ~s00080_OPENING;	//ñáðîñèòü ôëàã ÎÒÊÐÛÂÀÅÒÑß
						varSost &= ~s00080_AVARMUFTA; //ñáðîñèòü ôëàã ÀÂÀÐÈß ÏÎ ÌÓÔÒÅ
						varSost &= ~s00080_AVARVPHOPEN;	//ñáðîñèò ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÎÒÊÐÛÒÈß
						varSost &= ~s00080_AVARVPHCLOSE; //ñáðîñèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÇÀÊÐÛÒÈß
					}
				}
			}
		
//			if(NeedImpuls) { // Îòðàáîòêà èìïóëüñà óäåðæàíèÿ óïðàâëÿþùåãî ñèãíàëà îòêðûòèÿ, çàêðûòèÿ, ñòîï
 			if(VAR->ImpulsTime.Data.uint8 == 0) { //Âðåìÿ óäåðæàíÿè  èìïóëüñà âûøëî?
 				OUT->OutClose.Data.bit = 0;		// åñëè âûøëî, òî ñáðîñèòü óïðàâëÿþùèå âûõîäû Çàêðûòèÿ Îòêðûòèÿ Ñòîï
 				OUT->OutOpen.Data.bit = 0;
 				OUT->OutStop.Data.bit = 0;
 			} else {
 				if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
 					VAR->ImpulsTime.Data.uint8--;	//åñëè íå âûøëî, òî äåêðåìåíèðîâàòü ñ÷åò÷èê ñåêóíä óäåðæàíèÿ óïðàâëÿþùåãî èìïóëüñà
 				}
 			}
//			}
			
			if(varSost & s00080_OPENING) {	//åñëè çàäâèæêà ÎÒÊÐÛÂÅÒÑß
				if(OUT->Timer.Data.uint16 == 0) {	//åñëè çàêîí÷èëîñü ÂÐÅÌß ÏÎËÍÎÃÎ ÕÎÄÀ
					varSost &= ~s00080_OPENING;	//ñáðîñèòü ôëàã ÎÒÊÐÛÂÀÅÒÑß
					varSost |= s00080_AVARVPHOPEN;	//âûñòàâèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÎÒÊÐÛÒÈß
					OUT->OutStop.Data.bit = 1;		//âûäàòü èìïóëüñ íà âûõîä ÑÒÎÏ
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else { //âðåìÿ ïîëíîãî õîäà íå âûøëî
					if(IN->Opened.Data.bit) { //Åñëè çàäâèæêà ÎÒÊÐÛÒÀ
						varSost &= ~s00080_OPENING;	//ñáðîñèòü ôëàã îòêðûâàåòñÿ
						varSost &= ~s00080_AVARVPHOPEN;	//ñáðîñèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÒÜ ÎÒÊÐÛÒÈß
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//åñëè íå âûøëî âðåìÿ ïîëíîãî õîäà, òî äåêðåìåíòèðîâàòü ñ÷åò÷èê ñåêóíä âðåìåíè ïîëíîãî õîäà
						}	
					}
				}
			}
			
			if(varSost & s00080_CLOSING) {	//åñëè çàäâèæêà ÇÀÊÐÛÂÀÅÒÑß
				if(OUT->Timer.Data.uint16 == 0) {	//åñëè çàêîí÷èëîñü ÂÐÅÌß ÏÎËÍÎÃÎ ÕÎÄÀ
					varSost &= ~s00080_CLOSING;	//ñáðîñèò ôëàã ÇÀÊÐÛÂÀÅÒÑß
					varSost |= s00080_AVARVPHCLOSE;	//âûñòàâèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÇÀÊÐÛÒÈß
					OUT->OutStop.Data.bit = 1;	//âûäàòü èìïóëüñ íà âûõîä ÑÒÎÏ
//					NeedImpuls = 1;
					VAR->ImpulsTime.Data.uint8 = s00080_IMPULSTIME;
				} else {	//âðåìÿ ïîëíîãî õîäà íå âûøëî
					if(IN->Closed.Data.bit) {	//Åñëè çàäâèæêà ÇÀÊÐÛÒÀ
						varSost &= ~s00080_CLOSING;	//ñáðîñèò ôëàã ÇÀÊÐÛÂÀÅÒÑß
						varSost &= ~s00080_AVARVPHCLOSE;	//ñáðîñèòü ôëàã ÀÂÀÐÈß ÍÅ ÄÎÆÄÀËÈÑÜ ÇÀÊÐÛÒÈß
					} else {
						if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
							OUT->Timer.Data.uint16--;	//åñëè íå âûøëî âðåìÿ ïîëíîãî õîäà, òî äåêðåìåíòèðîâàòü ñ÷åò÷èê ñåêóíä âðåìåíè ïîëíîãî õîäà
						}	
					}
				}
			}
		}
	} //íå ïåðâûé çàïóñê

	if(IN->Alarmed.Data.bit) {		//èçìåíèòü ñîñòîÿíèå ÀÂÀÐÈÈ ÏÎ ÌÓÔÒÅ â ñîîòâåòñâèè ñ âõîäîì
		varSost |= s00080_AVARMUFTA;
	} else {
		varSost &= ~s00080_AVARMUFTA;
	}

	if(IN->Opened.Data.bit) {		//èçìåíèòü ñîñòîÿíèå ÎÒÊÐÛÒÀ â ñîîòâåòñâèè ñ âõîäîì
		varSost |= s00080_OPENED;
	} else {
		varSost &= ~s00080_OPENED;
	}

	if(IN->Closed.Data.bit) {		//èçìåíèòü ñîñòîÿíèå ÇÀÊÐÛÒÀ â ñîîòâåòñâèè ñ âõîäîì
		varSost |= s00080_CLOSED;
	} else {
		varSost &= ~s00080_CLOSED;
	}

	if(IN->Uon.Data.bit) {			//èçìåíèòü ñîñòîÿíèå ÍÀËÈ×ÈÅ ÍÀÏÐßÆÅÍÈß ñîîòâåòñâèè ñ âõîäîì
		varSost |= s00080_UON;
	} else {
		varSost &= ~s00080_UON;
	}

	OUT->Sost.Data.uint16 = varSost;

	if(VAR->SecTimer.Data.uint8 == KernelInfo.FBkernelRate) {
		VAR->SecTimer.Data.uint8 = 0;
	}
}
