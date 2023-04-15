 /********************************************************************

功    能： 单片机STC15F104E和WS2811控制LED灯珠变化并带有掉电保持的功
           能（内部EEPROM）。三个按键作用：Mode为模式选择，每按一次会
		   转换为另一种样式显示，并保持此样式一直循环，当按下Sel键时所
		   有的样式循环显示，Speed为速度调节（共八级速度）。显示样式有
		   ：整体七彩跳变，七彩渐变，流水，流星，单点变化，后向前流水。
创 建 者：
创建日期：2012年 8月
更新日期：2012年11月  (更新为段显示，每段50点，整体变化不做更改，工作于770K)。
版    本：

********************************************************************/
#include<IAP15F105W.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int  uint;


#define CMD_IDLE      0                //Stand-By
#define CMD_READ      1                //Byte-Read
#define CMD_PROGRAM   2                //Byte-Program
#define CMD_ERASE     3                //Sector-Erase
/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
#define ENABLE_IAP      0x82             //if SYSCLK<20MHz

#define IAP_ADDRESS  0x1200			    //EEPROM开始地址

#define NUMBER        500 			     //级联个数

sbit  DAI =P3^4;			            //信号端口


uint   speed=10;			            //速度
uchar  T1_Flag,DMX512_Data_Byte;


uchar T_R[5]={50,0,0,50,0};
uchar T_G[5]={0,50,0,50,0};
uchar T_B[5]={0,0,50,50,0};

//函数申明

//void send_24bits(uchar dat1,uchar dat2,uchar dat3);
//void rst();
void delay1();
void time0_init();

void send_2821_star();
void send_2821_byte(uchar cod8);
void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3);
void send_2821_end();
void Send_Data(uchar dat);

/******************************************
函 数 名：void delay(uint z)

功    能：延时函数
******************************************/
void Delay(uint x)
{
	uint y;
	for(;x>0;x--)
	{
		for(y=0;y<6000;y++);
	}
}

/******************************************
函数名:	void Delay4us()
        void Delay88us()

功  能：向2821发送数据电平位延时
********************************************/
void Delay4us()		//@33.1776MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 23;//29//24//23//22
	while (--i);
}
void Delay_4us()		//@33.1776MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 28;//29//24//23//22
	while (--i);
}
void Delay88us()		//@33.1776MHz
{
	unsigned char i,j;

	_nop_();
	_nop_();
	i = 3;
	j = 211;
	do
	{
		while (--j);
	} while (--i);
}
/*******************************************************
函数名:	void send_2821_star()
功  能：向2821发送DMX512格式数据包开始包头
*******************************************************/
void send_2821_star()
{
  DAI=1;
	Delay4us();
	DAI=0;
  Delay88us();	//88us BREAK

  DAI=1;
  Delay4us();
  Delay4us();   //8us MAB

}
/************************************************************
函数名: void send_2821_byte(uchar cod8)
功  能: 向2821发送一个字节数据
*************************************************************/
void send_2821_byte(uchar dat)
{
	uint i;
	DAI=0;
	Delay_4us();
	for(i=0;i<8;i++)
	{
		if(dat & 0x01)
		{
			DAI=1;
		}
		else
		{
			DAI=0;
		}
		Delay4us();
		dat=dat>>1;
	}
	DAI=1;
	//for(i=0;i<1;i++)
	Delay_4us();
	Delay_4us();
}
/***************************************************************
函数名：void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3)
功  能：向2821发送数据帧，一次发送三个通道
****************************************************************/
void send_2821_24bits(uchar datt1,uchar datt2,uchar datt3)
{
	send_2821_byte(datt1);
	send_2821_byte(datt2);
	send_2821_byte(datt3);
}
/****************************************************************
函数名:	void send_2821_end()
功  能：向2821发送DMX512格式包结束，并使数据生效
****************************************************************/
void send_2821_end()
{
	DAI=1;
 }

/******************************************
函 数 名：void Allbump()
功    能：整体七彩跳变
******************************************/
/*void Allbump()
{
  uint i,Count=0;
	uchar h=0;
	while(1)
	{

		send_2821_star();
		Send_Data(0);  //0

		Send_Data(0);  //1
		Send_Data(0);  //2
		Send_Data(0);  //3

		Send_Data(T_R[h]); //4
		Send_Data(T_G[h]); //5
		Send_Data(T_B[h]); //6

		for(i=0;i<300;i++)
		{
			Send_Data(0); //4
			Send_Data(0); //5
			Send_Data(0); //6
		}

		send_2821_end();
		Count++;
		if(Count>15)
		{
			Count=0;
			h++;
			if(h>3)
			{
				h=0;
			}
		}
	}
}
*/
/******************************************
函 数 名：void time0_init()
功    能：定时器初始化
******************************************/
void time0_init()
{
	TMOD = 0x00;		//16位自动重装
	AUXR = 0x80;		//1T模式

	TL0 = 0x7B;
	TH0 = 0xFF;          //1.11518us	(900k速度)		(TL0=D2 ;TH0=FF)750K  (TL0=7B ;TH0=FF)750K

	TR0=0;               //开定时器0
	ET0=1;
	EA=1;
	PT0=1;
}
void Flowing()
{
	uint i;
	uchar Stack;
	Stack=0;
	while(1)
	{
		send_2821_star();
		send_2821_byte(0);
		for(i=0;i<Stack;i++)
		{
			send_2821_24bits(255,0,255);
		}
		for(i=0;i<32-Stack;i++)
		{
			send_2821_24bits(0,0,0);
		}
		send_2821_end();
		Delay(100);
		Stack++;
		if(Stack>32)
		{
			break;
		}
	}
}
/******************************************
函 数 名：
功    能：主函数入口
******************************************/
void main()
{
	P3M0=0x04;//P3M0=0x00;
	P3M1=0xFB;
	time0_init();
	T1_Flag=1;
	while(1)
	{
		Flowing();
		//Allbump();
		//send_2821_24bits(255,255,255);
		//Send_24bits(255,255,255);
	}
}

/************************************************************
函数名: void send_2821_byte(uchar cod8)
功  能: 向2821发送一个字节数据
*************************************************************/
/*void send_2821_byte(uchar cod8)
{
	ET1=0;
	T1_Flag=1;
  DMX512_Data_Byte=cod8;
	DAI=0;
	TR0=1;
  while(T1_Flag!=0);
  ET1=1;
}
*/


/***************************************************************
函数名：void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3)
功  能：向2821发送数据帧，一次发送三个通道
****************************************************************/

/*void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3)
{

  send_2821_byte(dat1);

  send_2821_byte(dat2);

  send_2821_byte(dat3);
}
*/

void  timer0()  interrupt 1 using 1
{
  if(T1_Flag<=8)
	{
		if(DMX512_Data_Byte&0x01)
			{DAI=1;}
	  else
			{DAI=0;}
		DMX512_Data_Byte=DMX512_Data_Byte>>1;
	}

	else
		DAI=1;
  T1_Flag++;
	if(T1_Flag==11)
	{
		TR0=0;
		T1_Flag=0;
  }

  TF0=0; 	       //2us一位数据
}
