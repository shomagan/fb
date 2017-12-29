/* ФБ "Архиватор R7 универсальный (тип 18)" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00030.h"

/*Создает только один архив длинны 54 байта
 *на входе массив из любых типо данных 
 */
void fb00030_exec(void)
{
	fb00030_IN_type *IN = (fb00030_IN_type *) FBInputs;
	fb00030_OUT_type *OUT = (fb00030_OUT_type *) FBOutputs;

	u8 R7Buff[R7_BodySize];
	u8 i_bit, i_byte, i_reg;
	u8 LastType;
	u16 k;
  i_bit = 0;
  i_byte = 0;
  i_reg = 0;
  LastType = 0;
	OUT->Ok.Data.bit = 0;
  
	if (IN->Enable.Data.bit) {
		while (i_byte < R7_BodySize) {
			switch (IN->R7Data[i_reg].Type & DataTypeMask) {
			case KodBit:
				if (LastType == KodBit) {
					R7Buff[i_byte-1] = (IN->R7Data[i_reg].Data.bit << i_bit);
					if ((++i_bit) > 7) {
						i_bit = 0;
						i_byte++;
					}
				} else {
					R7Buff[i_byte] = IN->R7Data[i_reg].Data.bit;
					LastType = KodBit;
					i_bit = 1;
				}
				break;
			case KodInt8:
				R7Buff[i_byte++] = IN->R7Data[i_reg].Data.uint8;
				break;
			case KodInt16:
				for (k = 0; k < 2; k++)
					R7Buff[i_byte + k] = IN->R7Data[i_reg].Data.arbytes[k];
				i_byte += 2;
				break;
			case KodInt32:
			case KodTime32:
			case KodFloat32:
				for (k = 0; k < 4; k++)
					R7Buff[i_byte + k] = IN->R7Data[i_reg].Data.arbytes[k];
				i_byte += 4;
				break;
			default:
				for (k = i_byte; k < R7_BodySize; k++)
					R7Buff[k] = 0;
				i_byte = R7_BodySize;
				break;
			}
			i_reg++;
		}
   	NewQ_Arc_R7(R7Buff, 18);  // Передаём тело архива архиватору
		OUT->Ok.Data.bit = 1;
	}
}
