#define __init_c
#include "includeAll.h"
void SysInit()
{
	//启动后，立即清除看门狗
	F_clearWDT();
	//时钟初始化
	CLKCON = 0x03; // Clock div 1  7.3728Mhz
	STPPCK = 0;
	STPFCK = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SELFCK = 1; //系统时钟源选择。1:快时钟。
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	// // IO 模式初始化
	/* LED 端口模式初始化 */
	LEDInit();

	/* 按键端口初始化 */
	KeyInit();

	/* 数码管端口初始化 */
	//  SMGInit();

	/* 蜂鸣器端口初始化 */
	P1MODH &= P15MOD_Mask;
	P1MODH |= P15MOD_2;

	// T2 初始化  7.3728Mhz/2 = 3686400Hz
	// 3686400Hz/922 = 4000Hz = 0.25ms timer2 interrupt
	//RCP2H：Timer2 重载/捕获数据的高字节
	//定时0.25ms,低八位
	TL2 = (65536 - 922) % 256;
	//RCP2L：Timer2 重载/捕获数据的低字节
	RCP2L = TL2;

	//TR2: :Timer2 运行控制      1:允许Timer2 运行
	TR2 = 1;
	//ET2: :Timer2 中断使能控制  1:允许 Timer2 中断
	ET2 = 1;
	//EA: :总中断使能控制        1:每个中断通过其各个中断控制位使能或禁止
	EA = 1;

	P_led_com = 0; /* 根据电路图，con 口应恒为低 */
	//P_led_1 = 0;
	//P_led_2 = 0;
	P_buzz = 0;
}
//=============================================================================
void VarsInit() {}

void LEDInit()
{
	P1MODL &= P12MOD_Mask;
	P1MODL |= P12MOD_2;

	P1MODH &= P14MOD_Mask;
	P1MODH |= P14MOD_2;
}

void KeyInit()
{
	/* key 1 */
	P3MODH &= P34MOD_Mask;
	P3MODH |= P34MOD_0;

	/* key 2 */
	P3MODL &= P32MOD_Mask;
	P3MODL |= P32MOD_0;

	/* key 3 */
	P1MODH &= P17MOD_Mask;
	P1MODH |= P17MOD_0;

	/* key 4 */
	P1MODL &= P12MOD_Mask;
	P1MODL |= P12MOD_0;
}

void SMGInit(void)
{
	/* SMG A */
	P1MODH &= P14MOD_Mask;
	P1MODH |= P14MOD_2;

	/* SMG B */
	P3MODH &= P34MOD_Mask;
	P3MODH |= P34MOD_2;

	/* SMG C */
	P3MODH &= P35MOD_Mask;
	P3MODH |= P35MOD_2;

	/* SMG D */
	P1MODH &= P17MOD_Mask;
	P1MODH |= P17MOD_2;

	/* SMG E */
	P3MODH &= P36MOD_Mask;
	P3MODH |= P36MOD_2;

	/* SMG F */
	P1MODL &= P12MOD_Mask;
	P1MODL |= P12MOD_2;

	/* SMG G */
	P3MODL &= P32MOD_Mask;
	P3MODL |= P32MOD_2;

	/* SMG DG */
	P1MODL &= P13MOD_Mask;
	P1MODL |= P13MOD_2;
}