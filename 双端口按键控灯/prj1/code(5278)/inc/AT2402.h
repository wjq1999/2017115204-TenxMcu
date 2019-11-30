#ifndef __2402_h_
#define __2402_h_

#include <REGtenxTM52F5278.h>
#include "delay.h"

#define	scl	P1_4  //ģ��io���账��˫���״̬
#define sda P1_5

#define dev_addrw  0xa0		//2404  -> 1 0 1 0 A2 A1 P0 R/W
							//2402  -> 1 0 1 0 A2 A1 A0 R/W
#define dev_addrr  0xa1     //1 -> R
#define word_addr  0x02		//addr  -> 9bit ��5λ -32pages����4λ-16bytes




void c2402_app(void);
void iic_start(void);	  //����iic
void iic_stop(void);	  //ֹͣiic
void iic_write(u8);		  //д�ֽ�

bit iic_ack(void);
u8 iic_read(void);		 //���ֽ�
bit c2404_write(u8 dat);
u8 c2404_read(void);





#endif