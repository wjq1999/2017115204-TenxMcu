#define __init_c
#include "includeAll.h"
//=============================================================================
void SysInit()
{
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
	SELFCK = 1;
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
	// IO 模式初始化
	/* 数码管端口初始化 */
	SMGInit();

	/* LED 端口初始化 */
	P1MODH |= P14MOD_2;
	P3MODH |= P36MOD_2;

	/* 按键端口初始化 */
	P3MODH = P34MOD_0;
	P_led_com = 0; /* 根据电路图，com 口应恒为低 */
	P_led1 = 1;

	// IO 状态初始化
	P_bell = 0;
}
//=============================================================================
void VarsInit() {}

void SMGInit(void)
{
	P1MODL = P12MOD_2 | P13MOD_2;
	P1MODH = P14MOD_2 | P17MOD_2;
	P3MODL = P32MOD_2;
	P3MODH = P34MOD_2 | P35MOD_2 | P36MOD_2;
}