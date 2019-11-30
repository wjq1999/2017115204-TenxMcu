/*-----------------------------------------------
  名称：IO口高低电平控制
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过查表获得1个字节的值然后赋值给P1端口，ROM允许情况可以设置更多表格
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

/*------------------------------------------------
                   查表表格
------------------------------------------------*/
unsigned char code table[]={0x7f,0xbf,0xdf,0xef,
                            0xf7,0xfb,0xfd,0xfe,
				0xff,0xff,0x00,0x00,
				0x55,0x55,0xaa,0xaa};
						//rom允许情况可以无限添加
/*------------------------------------------------
                  函数声明
------------------------------------------------*/
void Delay(unsigned int t); //函数声明
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
                  
unsigned char i;  //定义一个无符号字符型局部变量 i 取值范围 0~255

while (1)         //主循环
  {
 for(i=0;i<16;i++)   //加入 for循环，表明for循环大括号中的程序循环
                     //执行16次，表明表格中有16个元素
    {
     P1=table[i];
     Delay(30000);
    }
                     //主循环中添加其他需要一直工作的程序
  }
}
/*------------------------------------------------
 延时函数，含有输入参数 unsigned int t，无返回值
 unsigned int 是定义无符号整形变量，其值的范围是
 0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
 while(--t);
}
