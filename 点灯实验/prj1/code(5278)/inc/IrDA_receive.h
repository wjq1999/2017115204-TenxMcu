#ifndef  _IrDA_receive_h_
#define  _IrDA_receive_h_

//uint uchar�궨��
#define u8 		unsigned char
#define u16	 	unsigned int
#define uchar 	unsigned char
#define uint 	unsigned int

#define in P2_0

extern uchar sj[4];			    //���ý�������
extern u16 IrDA_cnt;		    //���ڶԺ��Ⲩ�ν��м���
extern bit biaoz;


void IrDA_receive(void);	 			//ע��TImer2_init�е�TR2Ҫ��0

//����һ���ֽ�
extern void SendByte(unsigned char dat);

//���������ֽ�
extern void SendWord(unsigned int dat);




#endif