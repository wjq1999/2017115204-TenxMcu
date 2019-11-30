#ifndef _TEST_H_
#define _TEST_H_

//uint uchar�궨��
#define u8 		unsigned char
#define u16	 	unsigned int
#define uchar 	unsigned char
#define uint 	unsigned int


#define switch_addr 0x1f00		 //���ػ�״̬�洢��ַ
#define ad_addr		0x1f01		 //ADֵ�洢��ַ

#define switch_on	0x01		 //����
#define switch_off	0x00		 //�ػ�
/*------------------------------------------------
 *	  		����ѡ��
/*------------------------------------------------ */
//#define	internal_led				//ע�͵�����Ϊ����ܶ�̬ɨ�跽ʽ��ʾ����ע��Ϊ�ڲ�led������ʾ
									//ע��ʹ���ڲ�LED����������º�������������ģ���̬ɨ�軹����
//#define 	sing					//ȥ��ע�Ϳ���ͨ����Դ�������ȳ��裬�ٵ��������
/*-------------------------------------------------*/
#define BUZZER P1_6

u8 bdata	key_flag;  				//������ʶλ

//--------------------------------------------------------------------------------------------
sbit 		key_flag7		= key_flag^7;
sbit 		key_flag6		= key_flag^6;	
sbit 		key_flag5		= key_flag^5;	
sbit 		key_flag4		= key_flag^4;	
sbit 		key_flag3		= key_flag^3;	
sbit 		key_flag2		= key_flag^2;	
sbit 		key_flag1		= key_flag^1;	
sbit 		key_flag0		= key_flag^0;		



//ϵͳʱ�ӳ�ʼ��
void sys_clk_init(void);

//GPIO��ʼ��
void gpio_init(void);

//ADC��ʼ��
void adc_init(void);

//PWM��ʼ��
void pwm_init(void);

//�ж�0��ʼ��
void int0_init(void);

//��ʱ��0��ʼ��
void timer0_init(void);

//��ʱ��1��ʼ��  ��ʱԼ5.5��΢��
void timer1_init(void);	  	


//��ʱ��2��ʼ��
void timer2_init(void);


//����ɨ��
void key_scan(void);

//AD�ɼ�������ʾ
void ad_conver(void);

//AD��ʾ
void ad_display(void);

//���ڳ�ʼ��
void uart_init(void);

//����һ���ֽ�
void SendByte(unsigned char dat);

//����int������
void SendWord(unsigned int dat);

//����һ���ַ���
void SendStr(unsigned char *s);

//IAP����
u8 IAP_Read(u16 addr);
void IAP_Write(u16 addr, u8 dat);

//LED��ʼ��
void led_controler(void);

//LED��ʾ
void led_disp(void);


//lcd��ʼ��

void lcd_controler(void);

//LCD�������ʾ
void lcd_seg_disp(void);

//SPI��ʼ��
void spi_init(void);


//����ܲ��Ժ���
void Segment8_4(void);

//����ܶ�̬ɨ��
void segment_scan(void);

//����ܶ�̬ɨ��֮�Ͷ�������
void seg_send_duandata(u8 buffer);

//����ܶ�̬ɨ��֮��λ������
void seg_send_weidata(u8 buffer);


////����ܶ�̬ɨ��֮��ʱ��0��ʱ
//void Timer0_delay(u16 ms);


//ADֵ��ΪPWMռ�ձ��������������ʾ���������
void ad_to_pwm_and_segdisply(void);

//����ֵ�仯ʱ����ֵ���䵽EEPROM��
void EEPROM_record(void); 

//����״̬
void switch_onn(void);		//ע�⣺������������궨�����ظ�

//�ػ�״̬
void switch_offf(void);

//IAP��¼���ػ�״̬
void  switch_rec(void);

//����S3,S4ֵ�÷�ΧΪ0~9
void count_range(void);

//��Դ������
void source_beep(void);

//�����źŶԿ��ػ����������Ĵ���
void IrDA_process(void);



#endif