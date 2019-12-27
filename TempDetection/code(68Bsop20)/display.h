#ifndef __display_h
#define __display_h
// Hal: exp: #define P_led_1 P1.1 -----------------
#define P_led1 P1_4
#define P_led2 P3_6
#define P_led_com P1_0
#define P_bell P1_5
// Const: exp: #define D_data 1 ----------------
#define D_ledOn 1  //高电位亮
#define D_ledOff 0 //低点位灭
// Globle Var -----------------------------------------
#ifdef __display_c

#else

#endif

// Action Macro: exp: #define F_getData() ------
#define F_ledOn() P_led1 = D_ledOn
#define F_ledOff() P_led1 = D_ledOff
#define F_ledNeg() P_led1 = ~P_led1
// Function ------------------------------------
extern void LED_Disable(void);
#endif