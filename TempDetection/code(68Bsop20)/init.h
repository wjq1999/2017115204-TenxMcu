#ifndef __init_h
#define __init_h
//Hal: exp: #define P_led P10 ----------------

//Const: exp: #define D_data 1 ---------------

//Globle var ---------------------------------

#ifdef __init_c

#else

#endif

//Action Macro: exp: #define F_getData() -----

// Function ------------------------------------
void SysInit();
void VarsInit();
void LEDInit();
void KeyInit();
void SMGInit(void);

#endif