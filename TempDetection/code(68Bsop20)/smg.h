#ifndef __SMG_H_
#define __SMG_H_

// Hal: exp: #define P_led P10 -----------------
#define SMG_COM1 P1_6
#define SMG_COM2 P1_1

#define SMG_A P1_4
#define SMG_B P3_4
#define SMG_C P3_5
#define SMG_D P1_7
#define SMG_E P3_6
#define SMG_F P1_2
#define SMG_G P3_2
#define SMG_DG P1_3

// Const: exp: #define D_data 1 ----------------

// Globle Var -----------------------------------------

// Action Macro: exp: #define F_getData() ------

// Function ------------------------------------
static void SMG_One_Display(uint8_t position, uint8_t number);
extern void SMG_Disable(void);
extern void SMG_Display(uint8_t number);

#endif