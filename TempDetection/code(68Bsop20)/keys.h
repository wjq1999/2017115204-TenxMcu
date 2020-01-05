#ifndef __keys_h
#define __keys_h

#define P_key_1 P3_4
#define P_key_2 P3_2
#define P_key_3 P1_7
#define P_key_4 P1_2

// Const: exp: #define D_data 1 ----------------
#define D_keyNull 0
#define D_keyValue1 1
#define D_keyValue2 2
// Globle Var -----------------------------------------
#ifdef __keys_c
uint8_t keyValue[4];
#else
extern uint8_t keyValue[4];
#endif

// Action Macro: exp: #define F_getData() ------

// Function ------------------------------------
void GetKeys();
#endif