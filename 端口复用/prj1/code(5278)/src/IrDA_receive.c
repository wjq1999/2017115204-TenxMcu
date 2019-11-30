#include <REGtenxTM52F5278.h>
#include "IrDA_receive.h"
#include "intrins.h"

uchar sj[4];		//���ý�������


bit biaoz;


void IrDA_receive() 
{
	 uchar i;
	 uchar j;
	 bit startflag;
	 u16 re_dat[2];

	if(!in) {						    //�½��أ���ƽ����Ч
		_nop_();			 	
		_nop_();
		_nop_();
		_nop_();						//nop��ʱ���ж�������,��ֹ�󴥷�
		_nop_();			 
		_nop_();
		_nop_();						
		if(!in) {						//Լ9.2ms�ĵ͵�ƽ
			TR2 = 1;
			while(!in){
				if(IrDA_cnt > 300)		//��ʱ��2����20us->600 40us-> 
					break;
			}
			TR2 = 0;
			re_dat[0] = IrDA_cnt;
			
		 }

		 if(in&& (re_dat[0] > 150)){	//Լ4.6ms�ĸߵ�ƽ	20us->400 40us->
				TR2 = 1;
				IrDA_cnt = 0;
				while(in) {
					if(IrDA_cnt > 150)	//20us->300 40us->
						break;
				}
				TR2 = 0;

				re_dat[1] = IrDA_cnt;
		}
		
		IrDA_cnt = 0;
		//20us->400 600 200 300 40us->
		if(re_dat[0] > 150 && re_dat[0] < 300 	 //֡ͷ�ĵ�ƽʱ���ڴ���������Ϊ����Ч֡ͷ
			&& re_dat[1] > 90 && re_dat[1] < 150)	
			startflag = 1;
		re_dat[0] = 0;
		re_dat[1] = 0;
	}
		

	if(startflag) {					  //֡ͷ��Ч�������� ��ʽΪ 2�ֽ�ID�룬 1�ֽ����ݣ� 1�ֽ����ݵķ�	
		startflag = 0;				  //��ĸ�ʽ�ο�ircode�ĵ�
		IrDA_cnt = 0;
		re_dat[0] = 0;
		re_dat[1] = 0;
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 8; j++) {
				sj[i] >>= 1;
				if(!in) {
					_nop_();
					_nop_();
					_nop_();
					_nop_();
					_nop_();				
					_nop_();
					TR2 = 1;
					while(!in) {						
						if(IrDA_cnt > 20)	 //20us->35 40us->
							break;
					}
					TR2 = 0;
					re_dat[0] = IrDA_cnt;				//34 3d 3e
			  }
			  if(in && (re_dat[0] > 6  && re_dat[0] < 20)) {  //20us->20 40 40us->
					IrDA_cnt = 0;
					
					TR2 = 1;
					while(in) {
						if(IrDA_cnt > 55)	//20us->110 40us->
						break;
					}
					TR2 = 0;

					re_dat[1] = IrDA_cnt;	 			
					IrDA_cnt = 0;

					re_dat[0] = re_dat[0] + re_dat[1];
				}

 					if(re_dat[0] > 40 && re_dat[0] < 75)	//��ʱΪ1 	 20us->90 150 40us->
						sj[i] |= 0x80;
					if(re_dat[0] > 16 && re_dat[0] < 40)	//��ʱΪ0   20us->40 80 40us-> 
						sj[i] &= 0x7f;
					re_dat[0] = 0;
			}

		}
	   	  if(i>=4)						   	//4�ֽ��������꣬biaoz��λ
		  	 biaoz=1;

	  }
	  
 }
  
  