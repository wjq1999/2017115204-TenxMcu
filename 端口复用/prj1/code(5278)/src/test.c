/*-----------------------------------------------
  ���ƣ�TM52F5278ʵ���ר�ò��Գ���
  ���ܣ��������ȣ�ͨ������S1�ı俪�ػ�״̬����ͨ��IAP���ܽ�ÿ�εĿ��ػ�״̬��¼�ڵ�Ƭ�����õ�FLASH�С�
  			��Σ�1  ͨ��ADת�����ܲɼ������������ĵ�ѹֵ�������ø�ֵͨ��PWM�Ե�����е��ٿ��ơ�
				  2  ������S3��һ������ֵ������洢��AT24C02�У��ϵ��ٽ�ֵ��������
				  3  ������S4��һ������ֵ������洢��AT93C46�У�ͬ���ϵ��ٶ�������
				  4	 ʹ�ú���ң���ϵ���������ȡ��С���ϵ���������ʵ��ͬ���Ĺ���
			���  �ֱ�ͨ������ܶ�̬ɨ�������LED�������ַ�ʽ��ͨ��ע�ͺʹ�test.h�е�internal_led��
				  �������ַ�ʽ�н����л�������ADֵ������S3��S4��ֵ��ʾ�ڶ�Ӧ��������ϡ�
  ��д��Peasant_zhang
  ���ڣ�2015 9.6
------------------------------------------------*/
#include <REGtenxTM52F5278.h>
#include <intrins.h>
#include <absacc.h>
#include "test.h"
#include "AT2402.h"
#include "AT93C46.h"
#include "led_driver.h"
#include "music.h"
#include "IrDA_receive.h"




u8 s1_cnt = 0; 			//�����жϼ�����������ɨ����ʱ
u8 s3_cnt = 0;
u8 s4_cnt = 0;


static u16 cnt0 = 0;	//����ad���ݲɼ���ʱ
static u16 cnt1 = 0; 	//��������ܶ�̬ɨ����ʱ��ʱ
static u8 dat_templ;   	//adת���ݴ��2λ����
u8 dat_temph;		   	//�����ݴ��8λADת��ֵ

bit s1_flag ; 			//������ʶ��Ĭ��Ϊ����״̬
bit ad_flag = 0;  
bit display_flag;		//�����������ʾ��־λ
u16 buzzer_cnt;			//�����������ʱ��������

bit beep_flg;
bit com0_flag;
bit com1_flag;
bit com2_flag;
bit com3_flag;
bit g_flag;				//4ms��ʱ
u8 s3_count = 0;		//����S3����0~9
u8 s4_count = 0;		//����S4����0~9
u8 com = 0;				//���ڶ�̬ɨ��λ���л�

u8 buffer[4] = {0,0,0,0};	//���ڻ���4λ�������ʾֵ��buffer[0],buffer[1]���ڻ���ADֵ��
							//buffer[2]���ڻ���24C02��buffer[3]���ڻ���94c02�е�ֵ


//��̬ɨ�蹲������ܱ���
u8 code duan_ma[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};


u16 dat;					//���Դ洢��Ԫ����������ʱ����

u8 switch_state;			//���ػ�״̬����

uchar IrDA_buf;			   //���ڴ洢������յ�������

u16 IrDA_cnt = 0 ;		   //���ڶԺ��Ⲩ�ν��м���
u16 UART_cnt;			   //��ʱ���ʹ�������

//������
void main ()
{
	u8 i;
	sys_clk_init();		   //ϵͳʱ�ӳ�ʼ��
#ifdef internal_led
	led_controler();	   //��ʼ��Ϊ�ڲ�LED����
#endif
	gpio_init();		   //���ú����Ӧ��IO�ܽ�

	timer1_init();
//  uart_init();		   //����ռ�ö�ʱ��1Ϊ�����ʷ�����
  	adc_init();			   //��ʼ��AD
   	pwm_init();			   //��ʼ��PWM
   	timer0_init();		   //��ʼ����ʱ��0
	timer2_init();
	s1_flag = IAP_Read(switch_addr); 		//ȡ�����ػ�֮ǰ��״̬����ֵ
//	if(s1_flag != 1 && s1_flag != 0) {		//��IAP�д洢��ֵ�Ȳ���1Ҳ����0ʱ����ʼ��Ϊ0���ػ�״̬
//		s1_flag = 0;
//	}


//	led_disp();	 		//led��ʾ
//	lcd_seg_disp();
//	Segment8_4(); 		//����������ܲ���������ʾ

	dat = IAP_Read(switch_addr);		//����IAP�ܷ�������д
	IAP_Write(switch_addr, 0x03);
	dat = IAP_Read(switch_addr);

//	dat = c2404_read();		 //����IIC������д
//	c2404_write(0x0b);
//	Timer0_delay(20);
//	dat = c2404_read();

//	dat = Read(0x10);		//����SPI������д	
//	Write(0x10, 0x03);
//	Timer0_delay(20);
//	dat = Read(0x10);

//	IrDA_re();				//���Ժ����źŵĽ���
//	IrDA_process();


//	PINMOD |= TCOE; 				//ͨ��P1.4���2��Ƶ���ϵͳʱ��	
//	sing_the_song();
//	BUZZER = 0;
//	dat_temph = IAP_Read(ad_addr); 	//�������������ֵ

	s3_count = c2404_read();	    //��2404�ж�������S3������������ֵ
	s4_count = Read(0x10);			//��93c46�ж�ȡ����S4������������ֵ	  �����е�0x10Ϊ93c46�е�һ����ַ
#ifdef sing
	sing_the_song();
#endif

	
	for(;;) {
			IrDA_receive();

			while(g_flag){
				g_flag = 0;
				key_scan(); 				//����ɨ��
				IrDA_process();				//�������
				count_range();				//������Χ

				if(s1_flag) {				 //����ADת��������ת���õ��ĸ�8λ�͵�PWM�ĸ�8Ϊ
					ad_to_pwm_and_segdisply();
					PWM1DH  =  dat_temph; 		//ͨ��ADת������PWM1�����
				}

			    if(s1_flag) {
					PINMOD |= PWM1BOE;			//��PWM�������
				 } else {
				 	//PINMOD = 0;				//���Է��ֹر�pwm��P2.3���Ĭ��Ϊ�ߵ�ƽ
					PWM1DH  = 0x00;				//ͨ����PWM1DH��д0��ʹ�������
				}


				if (s1_flag) 				    //���䰴��ֵ
					EEPROM_record();
						
				if (s1_flag) {
				#ifndef internal_led
					display_flag = 1;	
				#else
					display_flag = 0;
					led_disp();				//LED������ʾ
				#endif
				} else {
				#ifndef internal_led
					display_flag = 1; 
				#else
					display_flag = 0;
					for (i = 0; i < 8; i++) 	//��LCD_RAM��ʼ��Ϊȫ����Ϩ��LED
						XBYTE[0xf000+i] = 0xff;
				#endif
				}

				if (s1_flag) {
					if(IAP_Read(switch_addr) != switch_on)
						IAP_Write(switch_addr, switch_on);  //ʹ��IAP��¼����״̬
		
	 			} else {
					if(IAP_Read(switch_addr != switch_off))
	 	 				IAP_Write(switch_addr, switch_off); //ʹ��IAP��¼�ػ�״̬
	 			} 

	 		}
			
				
	   }
}

//ϵͳʱ�ӳ�ʼ��
void sys_clk_init()
{
	
//	CLKPSC_H = 0;
//	CLKPSC_L = 0;
	_nop_();			 //���ڲ�����FRC = 7.3728MHZ�Ҳ���Ƶ�������һ��nopΪ0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLKCON = CLKPSC_Div2; //��ʱ�ӽ��ж���Ƶ
	_nop_();			 //���ڲ�����FRC = 7.3728MHZ�Ҳ���Ƶ�������һ��nopΪ0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	FCKTYPE	= 0;  	//�ڲ���ʱ��	7.3728Mhz	0.135us		   0Ϊ�ڲ�����
 	STPFCK = 0;  	//ֹͣ��ʱ��
	_nop_();			//���ڲ�����FRC = 7.3728MHZ�Ҳ���Ƶ�������һ��nopΪ0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SELFCK	= 1;  	//ѡ���ʱ��(Ĭ��Ϊ�ڲ�FRC)	0Ϊ��ʱ��
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
//	PINMOD |= TCOE; //ͨ��P1.4���2��Ƶ���ϵͳʱ��	
}

//GPIO��ʼ��
void gpio_init()
{

	//����P3.3 P3.2 P2.5�ֱ�ΪΪS1,S3,S4�������룬 P3��Ĭ��Ϊ����̬
	P3MODL = 0x00;	//P3.3��Ĭ��Ϊ����״̬
	P3_3 = 1;		//����ģʽ�¿����ڲ�����
	P3_2 = 1;		//0ʱΪ���룬1ʱΪ�ڲ�����
	P2_5 = 1;		//����ģʽ�����ڲ�����
	
#ifndef internal_led
	//������ӦIO��Ϊ����ܶ�̬ɨ�������
	P0OE = 0xff;	//ʹ��P0�����
	P3MODH = P34MOD_2 | P35MOD_2 | P36MOD_2; 	//����P3.4,P3.5,P3.6Ϊ���
	P1MODH = 0x80;	 //���� P1.7ΪCMOS���
#else
	P3MODH = P34MOD_3 | P35MOD_3 | P36MOD_3; //����Ϊseg����lcd���
   	P1MODH = P17MOD_3 ; 
   	P0OE = 0xff;
#endif


	//��P1.0����ΪAD��
	P1MODL = 0x03;
	
	
	//����P2.3ΪPWM��
	P2MOD |= P2OE3;	 //�������Ϊ���������ʽ

	//����P1.4��P1.5�ֱ�ΪAT2402��scl��sda�ӿ�
	P1MODH |= P15MOD_0 | P14MOD_2; 	  //P1.5Ϊ��©��������������롣P1.4ΪCMOS���

	//����P2.2Ϊ�������, ��ӦCS
	P2MOD |= P2OE2;	 //�������Ϊ���������ʽ
	P1MODL |= P13MOD_0 | P12MOD_2 | P11MOD_2;

	//����P1.6Ϊ��Դ����Դ�������������
	P1MODH |= P16MOD_2;
	BUZZER = 0;			//��ʼ������Ϊ�ر�״̬
	//����P2.4Ϊ��Դ�����������
	P2MOD |= P2OE4;	 //�������Ϊ���������ʽ
	P2_4 = 0;

	//����P2_0Ϊ���������
	P2MOD |= P20MOD_0;
	P2_0 = 1;				//�����ڲ�����

}


//����������Ƿ�����������
void Segment8_4()
{
	P0OE = 0xff;	//ʹ��P0�����
	P3MODH |= P34MOD_2 | P35MOD_2 | P36MOD_2; 	//����P3.4,P3.5,P3.6Ϊ���
	P1MODH |= 0x80;	 //���� P1.7ΪCMOS���

	P0_0 = 0;  	//COM��
	P0_1 = 0;
	P0_2 = 0;
	P0_3 = 0;	//COM��
		 
	P0_4 = 0;	//���������
	P0_5 = 0;
	P0_6 = 0;
	P0_7 = 0;
	P3_4 = 0;
	P3_5 = 0;
	P3_6 = 0;
	P1_7 = 0;	//�������
}
	

// ���ڳ�ʼ��
void uart_init(void)

{

//����T1��ʱ,- �������Timer1�Զ���װģ,T1�ж�Ҫ�ر�
//ʵ�ʵĲ�����  9615

	 SM0=0;
	 SM1=1;	             // SM1\SM0=01   UART mode=1 ;8λ���ݴ���   //��9λ�� ��żУ��λ
 	 SM2=0;		   	     //Mode 1, 3     �����ʲ��� 9600 = (SMOD+1) x Fsysclk / (32 x 2 x (256-TH1)) --- ��ʹ��Timer1 �Զ�����ģʽ
 	 PCON=0x80;          //SMOD=1
				   
	 TL1=244;		   	 //��������4MHZ����ͨ������ 256-TH1Ӧ����13.2, ��ôTH1=256-13.2=242.8 Լ��243 
 	 TH1=244;			 //��Ϊ������������·��ͨ�����Բ�����B���ؾ�ȷ��9600, ֻҪ������·��һ��ʹ����ͬ�ľ��� TH1Ҳ��ͬ����׼ȷͨ��
 	 TMOD=0x20;         //T1����8λ��װģʽ

		 				//ʵ�ʵĲ�����  9615= (1+1) x 4000 000 / (32 x 2 x (256-243)) 

		 				//9615/9600=1.0016
	 TI=0;			    //���巢���ж� ��־
	 RI=0;				//��������ж� ��־
  	 T2CON=0;
	 TR1=1;	            //TIMER1 ����
//	 REN=1;		        //UART�����վ�ʹ��
// 	 IPH=0x10;    //UART�ж���Ϊ�����ȼ�
// 	 EA=1;              //ȫ���жϴ�
//	 ES=1;
}


//����һ���ֽ�
void SendByte(unsigned char dat)
{
 	SBUF = dat;
 	while(!TI);
      TI = 0;
}

//����int������	   
void SendWord(unsigned int dat)
{
   u8 a, b;

   a =  dat;
   SendByte(a);			 //�ȷ��͵�λ�ֽ�
   b = dat >> 8;
   SendByte(b);			 //�ٷ��͸�λ�ֽ�

} 

//����һ���ַ���
void SendStr(const unsigned char *s)
{
 	while(*s!='\0')// \0 ��ʾ�ַ���������־��
                //ͨ������Ƿ��ַ���ĩβ
  	{
  		SendByte(*s);
  		s++;
  	}
}
   
//ADC��ʼ��
void adc_init()
{
	OPTION |= ADCKS_sys_16;   //ADCʱ��Ϊϵͳʱ�ӵ�16��Ƶ
	CHSEL = 0x40;		     //ͨ��ѡ��Ϊ4ͨ��������ΪP1.0
	
}

//PWM��ʼ��
void pwm_init()
{
 	PWMCON |= PWM0CKS_4;    //PWM0 clock =FRC Double frequence
	PWM1PRD = 0x80;			//����Ϊ 256
	PWM1DH  = 0x40;
//	PWM0DL  = 0x00;
	PINMOD |= PWM1BOE ;	    
}



//�ⲿ�ж�0��ʼ��
void int0_init()
{
 	IT0=1;				//�����䴥��
 	EX0=1;				//���ⲿ�ж�0
 	EA=1;				//�����ж�
}


//��ʱ��0��ʼ��   
//��ʱ������ʱ�ӵĻ�׼Ƶ��Ϊϵͳʱ�ӵ�1/2  
//�˴�ʹ���ڲ����Ӳ�����2��Ƶ��õ��ļ�����λʱ��Ϊ 0.5425us
void timer0_init()	  	
{
	TMOD |= 0x01;	   //����Ϊ8

	TH0 = 0xe3;		   //��ʱ4ms
	TL0 = 0x33;
	TR0 = 1;
	ET0 = 1;
	EA = 1;		
}

//��ʱ��1��ʼ��  ��ʱԼ5.5��΢��

//void timer1_init()	  	
//{
//	TMOD |= 0x10;	   //��ʱ��1����Ϊ16λ����
//
//	TH1 = 0xff;		   
//	TL1 = 0xf6;
////	TR1 = 1;
//	ET1 = 1;		   
//	PT1 = 1;		   //���ö�ʱ��1Ϊ�����ȼ��ж�
//	EA = 1;		
//}


//��ʱ��2��ʼ��  ��ʱԼ20��΢��
void timer2_init()
{
	TL2 = 0xb6;			 //20��usʱ����ֵΪ0xffdb	  40us->ffb6
	TH2 = 0xff;
    RCP2H = 0xff;				
  	RCP2L = 0xb6;
	IPH |= 0x20;		//����PT2HΪ1	 ��ʱ���жϾ���������ȼ�
	IP  |= 0x20;		//����PT2Ϊ1
  	ET2=1;                     //�򿪶�ʱ���ж�
  	EA=1;                      //�����ж�
//	TR2=1;                     //�򿪶�ʱ������
}


//�ⲿ�ж�0�жϷ������
//void int0_isr() interrupt 0 using 0
//{
//  
////	cnt++;
////
////	if(cnt > 1)
////		cnt = 0;
//
//}

//��ʱ�ж�0������� ϵͳ2��Ƶʱ ��ʱ4ms
void timer0_isr() interrupt 1 
{
	TH0 += 0xe3;		  
	TL0 += 0x33;

	g_flag = 1;
	//��Ӧ�İ������¿�ʼ������ʱ
	if(key_flag0 == 1){
		key_flag0 = 0;
		s3_cnt++;
	}

	if(key_flag2 == 1) {
		key_flag2 = 0;
		s4_cnt++;
	}

	if(key_flag4 == 1) {
		key_flag4 = 0;
		s1_cnt++;
	}

	cnt0++;
	buzzer_cnt++; 
	
	source_beep();

	if(display_flag && s1_flag == 1) 
		segment_scan();	 		//����ܶ�̬ɨ��
	 if(display_flag && s1_flag == 0)
	 	seg_send_weidata(0xff);		//�ر��������ʾ

//   UART_cnt++;				//���ڷ��Ͷ�ʱ����
}

//��ʱ�ж�1������� 
//void timer1_isr() interrupt 3 
//{
//   	IrDA_cnt++;
//  	TH1 = 0xff;		   
//	TL1 = 0xf6;
////   	BUZZER = ~BUZZER;
//}


//��ʱ�ж�2������� 
void timer2_isr() interrupt 5 
{
   TF2 = 0;					//��Ӷ����ָ���ռ��ʱ��
   IrDA_cnt++;
   
// BUZZER = ~BUZZER;
}

//����ɨ��
void key_scan()
{
  //��ⰴ��S3
	if (P3_2 == 0) {
		   key_flag0 = 1;	  			//�������¿�ʼ��ʱ������־��1
			if (s3_cnt >= 8) {			//��ʱ30ms�������������
				s3_cnt = 0;
				if (key_flag1 == 0) {  	//������⣬���ó�����Ч���ü�ⰴ���ɿ���Ч�ʸ�
					key_flag1 = 1;
					s3_count++;
					key_flag6 = 1;		//��Ϊ2402д�ı�־λ
					beep_flg = 1;
				}		
			}
	} else {
		key_flag0 = 0;
		key_flag1 = 0;
		s3_cnt = 0;
	}

	//��ⰴ��S4
	if (P2_5 == 0) {
		   key_flag2 = 1;
			if (s4_cnt >= 8) {
				s4_cnt = 0;
				if (key_flag3 == 0) {
					key_flag3 = 1;
					s4_count++;		  
					key_flag7 = 1;		 //��Ϊ93c46д�ı�־λ
					beep_flg = 1;
				}		
			}
	} else {
		key_flag2 = 0;
		key_flag3 = 0;
		s4_cnt = 0;
	}

	//��ⰴ��S1
	if (P3_3 == 0) {
		   key_flag4 = 1;
			if (s1_cnt >= 8) {
				s1_cnt = 0;
				if (key_flag5 == 0) {
					key_flag5 = 1;
					s1_flag = ~s1_flag;
					beep_flg = 1;
				}		
			}
	} else {
		key_flag4 = 0;
		key_flag5 = 0;
		s1_cnt = 0;
	}

	
	
}

//�����źŶԿ��ػ����������Ĵ���
void IrDA_process()
{
	if (biaoz == 1) {
		biaoz = 0;
		IrDA_buf = sj[2];
	}

	switch(IrDA_buf) {

	case 0x11:				//���ػ���
		IrDA_buf = 0;
		s1_flag = ~s1_flag;
		beep_flg = 1;
		break;
	case 0x22:			    //��Ӧ����s4
		IrDA_buf = 0;
		key_flag6 = 1;		 //��Ϊ2402д�ı�־λ
		s4_count++;		  
		key_flag7 = 1;		 //��Ϊ93c46д�ı�־λ
		beep_flg = 1;
		break;
	case 0x33:			   //��Ӧ����s3

		IrDA_buf = 0;
		s3_count++;
		key_flag6 = 1;
		key_flag7 = 1;

		beep_flg = 1;
		break;
	default: break;
	}
}

//-----------------------------------------------------------
//ͨ��K1�������ƿ��ػ�״̬����ʹ��IAP��¼���ػ�״̬�µ�״̬��
//-----------------------------------------------------------

//IAP��¼���ػ�״̬
void  switch_rec(void)
{
  	if (s1_flag == 1) {
		IAP_Write(switch_addr, switch_on);  //ʹ��IAP��¼����״̬
		
	 } else if(s1_flag == 2) {
	 	 IAP_Write(switch_addr, switch_off); //ʹ��IAP��¼�ػ�״̬
	 } 
}

//����״̬
void switch_onn()
{

	dat_temph = IAP_Read(ad_addr); 	//�������������ֵ
	s3_count = c2404_read();	    //��2404�ж�������S3������������ֵ
	s4_count = Read(0x10);			//��93c46�ж�ȡ����S4������������ֵ	  �����е�0x10Ϊ93c46�е�һ����ַ
#ifdef sing
	sing_the_song();
#endif
	while(s1_flag == 1) {			//'=='Ϊ�߼��жϷ�
		PINMOD |= PWM1BOE;			//��PWM������� 
		ad_to_pwm_and_segdisply();
		count_range();
		IrDA_receive();				//���к����źŵĽ���
			
					
#ifndef internal_led
		display_flag = 1;	
#else
		display_flag = 0;
		led_disp();				//LED������ʾ
#endif

	}

}

//�ػ�״̬
void switch_offf()
{
	u8 i;

	IAP_Write(ad_addr, dat_temph);		//�ػ�����ADת����ֵ

	while (s1_flag == 2) {
		IrDA_receive();					//���к����źŵĽ���
										//�ػ�״̬�½��к����źŵĽ���
//		key_scan();
#ifndef internal_led
		display_flag = 1; 
//		seg_send_weidata(0xff);		//�ر��������ʾ
#else
		display_flag = 0;
		for (i = 0; i < 8; i++) 	//��LCD_RAM��ʼ��Ϊȫ��
			XBYTE[0xf000+i] = 0xff;
#endif
//		PINMOD = 0;						//���Է��ֹر�pwm��P2.3���Ĭ��Ϊ�ߵ�ƽ
		PWM1DH  = 0x00;					//ͨ����PWM1DH��д0��ʹ�������
	}
	

}


//����S3ֵ�÷�ΧΪ0~9������S4֮�ķ�ΧΪ0~F
void count_range()
{

 	if (s3_count >= 10)
		s3_count = 0;
	if (s4_count >= 16)
		s4_count = 0;
	
	buffer[2] = s3_count;			 //���Ӽ���ֵ�洢����Ӧ�Ļ��嵥Ԫ
	buffer[3] = s4_count;
}

//����ֵ�仯ʱ����ֵ���䵽EEPROM��
void EEPROM_record() 
{
	if(key_flag6 == 1) {			//����ֵÿ�仯һ����24c02��¼һ��
		key_flag6 = 0;
		c2404_write(buffer[2]);
		source_beep();

	}	

    if(key_flag7 == 1) {			//����ֵÿ�仯һ����93c46��¼һ��
		key_flag7 = 0;
		Write(0x10, buffer[3]);		   //0x10Ϊ�洢��ַ
		source_beep();
	}	

}


//AD�ɼ�
void ad_conver()
{

  	if (cnt0 >= 250) {			//1s����һ��ADת��ֵ
		cnt0 = 0;
		ADSOC = 1;			   //����ADת��
		while (ADSOC == 1);    //ADSOC = AD start of conversion
		
		dat_temph = ADCDH;	   //ȡ����8λ

	}
	
}


//IAP�����ݹ���,ʹ��IAP����keil��������Ϊsmall�洢ģʽ
u8 IAP_Read(u16 addr)
{
	u8  dat_temp;

	SWCMD = 0x65;   	//ʹ��IAP_ALL����д����
//	INTE1 = 0xa0;		//5274b/78bҪ��
	dat_temp = XBYTE[addr];
    SWCMD = 0x00;   	//д����ֵ�ر�д����
	return dat_temp;
}

//IAPд���ݵ�rom
void IAP_Write(u16 addr, u8 dat)
{
   	SWCMD = 0x65;   	//ʹ��IAP_ALL����д����
//	INTE1 = 0xa0;		//5274b/78bҪ��
	XBYTE[addr] = dat;
//	Timer0_delay(5);	//д�����ݴ�Լ��500us,�˴���ʱ5ms
  	SWCMD = 0x00;   	//д����ֵ�ر�д����
}


//LED��ʼ��
void led_controler()
{
	u8 i;

	//lcdĬ��ʱ��Ϊsrc
	LCDCON2 |= LCDPSC_32;  //lcd����32��Ƶ
	LCDCON2 |= SELLED;     //ѡ��ledģʽ
	LCDPIN |= LCDPIN_0;    //P3.4~P3.6,P1.7 mode;0: I/O mode;1: LCD/LED SEG4~7
	LCDCON |= LCDON;	  //����lcd����	

	for (i = 0; i < 8; i++) 	//��LCD_RAM��ʼ��Ϊȫ��
		XBYTE[0xf000+i] = 0xff;

}

//led�������ʾ
void led_disp()
{
	com0_disp(buffer[3]);	  //��ʾ����S4��1������ֵ
	com1_disp(buffer[2]);	  //��ʾ����S3��1������ֵ
	com2_disp(buffer[1]);	  //��ʾADת��ֵ�ĸ�4λ
	com3_disp(buffer[0]);	  //��ʾADת��ֵ�ĵ�4λ
}

//lcd ����
void lcd_controler()
{
	//lcdĬ��ʱ��Ϊsrc��Ϊ������ʱ��Դ������ϵͳʱ�ӹ���
	LCDCON2 |= LCDPSC_32;  //lcd����32��Ƶ
//	LCDCON2 |= SELLED;     //ѡ��ledģʽ
	LCDPIN |= LCDPIN_0 | LCDPIN_1;    //P3.4~P3.6,P1.7 mode;0: I/O mode;1: LCD/LED SEG4~7
	LCDCON |= LCDON;	  //����lcd����	

}



//lcd �������ʾ
void lcd_seg_disp()
{
	u8 i;

   	lcd_controler();

   	for (i = 0; i < 8; i++) 	 //��LCD_RAM����
		XBYTE[0xf000+i] = 0x00;

	XBYTE[0xf000] = 0x60;		//��ʾ1
	XBYTE[0xf001] = 0x7d;	   //��ʾ0

}



//ADֵ��ΪPWMռ�ձ��������������ʾ���������
void ad_to_pwm_and_segdisply()
{
	ad_conver();				//ADת��
	buffer[1] = dat_temph/16;	//��AD��ֵͨ���������ʮ�����Ƶ���ʽ��ʾ����00~FF
	buffer[0] = dat_temph%16;
}

//--------------------------------
//ʹ������ܶ�̬ɨ����ʾ����
//--------------------------------

//����ܶ�̬ɨ��
void segment_scan()
{

	 switch (com)
	 {
	 	case 0: 
			 seg_send_weidata(0x0f);		 //��������
			 seg_send_duandata(duan_ma[buffer[0]]);	//�Ͷ���
			 seg_send_weidata(0x0e);		//��λ��
			 com = 1;
			break;
		case 1: 
			 seg_send_weidata(0x0f);		//����
			 seg_send_duandata(duan_ma[buffer[1]]);	//�Ͷ���
			 seg_send_weidata(0x0d);		//��λ��
			 com = 2;
			break;
		case 2: 
			 seg_send_weidata(0x0f);		//����
			 seg_send_duandata(duan_ma[buffer[2]]);	//�Ͷ���
			 seg_send_weidata(0x0b);		//��λ��
			 com = 3;
			 break;
		case 3: 
			 seg_send_weidata(0x0f);		//��������
			 seg_send_duandata(duan_ma[buffer[3]]);	//�Ͷ���
			 seg_send_weidata(0x07);		//��λ��
			 com = 0;
			 break;
		default:
			break;
	}


}

//����ܶ�̬ɨ��֮�Ͷ�������
void seg_send_duandata(u8 buffer)
{
//  P0 = (P0&0x0f)|_crol_(buffer&0x0f,4);  		//��ӦP0.4~P0.7

//	P3 = (P3&0x8f)|(buffer & 0x70);			  	//��ӦP3.4~P3.6	  ��������밴��K1�������ͻ
//	P1 = (P1&0x7f)|(buffer & 0x80);				//��ӦP1.7
    P0_4 = buffer & 0x01;						//ʹ��λ���������ȡֵ���⣬��Ч����
	P0_5 = buffer & 0x02;
	P0_6 = buffer & 0x04;
	P0_7 = buffer & 0x08;
	P3_4 = buffer & 0x10;
	P3_5 = buffer & 0x20;
	P3_6 = buffer & 0x40;
	P1_7 = buffer & 0x80;
}

//����ܶ�̬ɨ��֮��λ������
void seg_send_weidata(u8 buffer)
{
//   	P0 = (P0&0xf0)|buffer;
	P0_0 = buffer & 0x01;						//ʹ��λ���������ȡֵ���⣬��Ч����
	P0_1 = buffer & 0x02;
	P0_2 = buffer & 0x04;
	P0_3 = buffer & 0x08;
}
	


//��Դ������
void source_beep(void)
{
	if(beep_flg) 
		BUZZER = 1;
	if(buzzer_cnt >= 80) {
		BUZZER = 0;
		buzzer_cnt = 0;
		beep_flg = 0;
	}	

}










