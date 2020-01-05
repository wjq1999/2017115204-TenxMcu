#define __main_c
#include "includeAll.h"
//=============================================================================

void main()
{

	SysInit();  //系统初始化
	VarsInit(); //变量初始化
	//使能看门狗
	F_turnOnWDT();
	//F_ledOn(1);
	//F_ledOn(2);

	while (1)
	{
		//喂狗
		F_clearWDT();
		//业务代码
		TimeProcess();
		TaskSetting();
		TaskProcess();
		DisplayProcess();
	}
}
void TimeProcess()
{
	static uint16_t timer5ms = 0;
	static uint16_t second = 0;

	if (b1ms)
	{
		// 1ms 执行一次
		b1ms = 0;
		timer5ms++;
		second++;
	}
	//每5ms以上获取一次键值
	if (timer5ms >= D_5ms * 5)
	{
		timer5ms = 0;
		GetKeys();
	}
	if (second >= D_1000ms)
	{
		// 1s 执行一次
		second = 0;
	}
}
//=============================================================================
void TaskProcess() {}
//=============================================================================

bit led_flag1 = 0;
bit led_flag2 = 0;
void TaskSetting()
{
	//KeyInit();
	if (D_keyValue1 == keyValue[0])
	{
		//F_ledNeg(1);
		led_flag2 = ~led_flag2;
		BuzzCount(100);
	}

	if (D_keyValue1 == keyValue[2])
	{
		//LEDInit();
		//F_ledNeg(1);
		led_flag2 = ~led_flag2;
	}

	if (D_keyValue1 == keyValue[3])
	{
		//LEDInit();
		//F_ledNeg(2);
		led_flag1 = ~led_flag1;
	}
	keyValue[0] = D_keyNull;
	keyValue[3] = D_keyNull;
	keyValue[2] = D_keyNull;
}
//=============================================================================
void DisplayProcess()
{
	//F_ledOn();
	if (led_flag1)
	{
		F_ledOn(1);
		//delayMs(1);
	}
	else
	{
		F_ledOff(1);
	}

	if (led_flag2)
	{
		F_ledOn(2);
		//delayMs(1);
	}
	else
	{
		F_ledOff(2);
	}
}
void delayMs(uint16_t msCount)
{
	uint16_t i, j;
	for (i = 0; i < msCount; i++)
	{
		for (j = 0; j < 1000; j++)
		{
			/* code */
			F_clearWDT();
		}
	}
}