#define __SMG_C_
#include "includeAll.h"
//=============================================================================

/* 0~9 数字的数码管编码 */
/* 从左到右 依次为 dp g f e d c b a */
const uint8_t number_code[11] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void SMG_Display(uint8_t number)
{
    uint16_t i;

    for (i = 0; i < 500; i++)
    {
        SMG_One_Display(2, number / 10);
        delayMs(3);
        SMG_One_Display(1, number % 10);
        delayMs(3);
        //F_clearWDT();
    }
}

static void SMG_One_Display(uint8_t position, uint8_t number)
{
    /* 选择数码管的位置 */
    /* 根据电路图，电平为低时该位被选中 */
    if (position == 1)
    {
        SMG_COM1 = 0;
        SMG_COM2 = 1;
    }
    else if (position == 2)
    {
        SMG_COM1 = 1;
        SMG_COM2 = 0;
    }

    /* 数据显示 */
    SMG_A = 0x01 & (number_code[number] >> 0);

    SMG_B = 0x01 & (number_code[number] >> 1);

    SMG_C = 0x01 & (number_code[number] >> 2);

    SMG_D = 0x01 & (number_code[number] >> 3);

    SMG_E = 0x01 & (number_code[number] >> 4);

    SMG_F = 0x01 & (number_code[number] >> 5);

    SMG_G = 0x01 & (number_code[number] >> 6);

    SMG_DG = 0x01 & (number_code[number] >> 7);
}
void SMG_Disable(void)
{
    SMG_COM1 = 0;
    SMG_COM2 = 0;
    SMG_A = 0x00;
    SMG_B = 0x00;
    SMG_C = 0x00;
    SMG_D = 0x00;
    SMG_E = 0x00;
    SMG_F = 0x00;
    SMG_G = 0x00;
    SMG_DG = 0x00;
    SMG_COM1 = 1;
    SMG_COM2 = 1;
}