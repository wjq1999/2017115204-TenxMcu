#define __main_c
#include "includeAll.h"
//=============================================================================
void main()
{
	uint8_t i = 0;

	SysInit();
	VarsInit();

	while (1)
	{
		SMGInit();
		SMG_Display(11);
		SMG_Display(55);
		// //喂狗
		//F_clearWDT();
		// // user coding
		//delayMs(20);
		//SMG_Disable();
		//GetKeys();
		// if (D_keyValue1 == keyValue)
		// {
		// 	P_led_com = 0;
		// 	F_ledNeg();
		// }
		//keyValue = D_keyNull;
		//F_ledOff();
		// SMGInit();
	}
}
//=============================================================================
void delayMs(uint16_t msCount)
{
	uint16_t i, j;
	for (i = 0; i < msCount; i++)
	{
		for (j = 0; j < 100; j++)
		{
			/* code */
			F_clearWDT();
		}
	}
}
