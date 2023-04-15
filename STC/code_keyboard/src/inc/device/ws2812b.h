 /********************************************************************

��    �ܣ� ��Ƭ��STC15F104E��WS2811����LED����仯�����е��籣�ֵĹ�
           �ܣ��ڲ�EEPROM���������������ã�ModeΪģʽѡ��ÿ��һ�λ�
		   ת��Ϊ��һ����ʽ��ʾ�������ִ���ʽһֱѭ����������Sel��ʱ��
		   �е���ʽѭ����ʾ��SpeedΪ�ٶȵ��ڣ����˼��ٶȣ�����ʾ��ʽ��
		   �������߲����䣬�߲ʽ��䣬��ˮ�����ǣ�����仯������ǰ��ˮ��
�� �� �ߣ�
�������ڣ�2012�� 8��
�������ڣ�2012��11��  (����Ϊ����ʾ��ÿ��50�㣬����仯�������ģ�������770K)��
��    ����

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

#define IAP_ADDRESS  0x1200			    //EEPROM��ʼ��ַ

#define NUMBER        500 			     //��������

sbit  DAI =P3^4;			            //�źŶ˿�


uint   speed=10;			            //�ٶ�
uchar  T1_Flag,DMX512_Data_Byte;


uchar T_R[5]={50,0,0,50,0};
uchar T_G[5]={0,50,0,50,0};
uchar T_B[5]={0,0,50,50,0};

//��������

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
�� �� ����void delay(uint z)

��    �ܣ���ʱ����
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
������:	void Delay4us()
        void Delay88us()

��  �ܣ���2821�������ݵ�ƽλ��ʱ
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
������:	void send_2821_star()
��  �ܣ���2821����DMX512��ʽ���ݰ���ʼ��ͷ
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
������: void send_2821_byte(uchar cod8)
��  ��: ��2821����һ���ֽ�����
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
��������void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3)
��  �ܣ���2821��������֡��һ�η�������ͨ��
****************************************************************/
void send_2821_24bits(uchar datt1,uchar datt2,uchar datt3)
{
	send_2821_byte(datt1);
	send_2821_byte(datt2);
	send_2821_byte(datt3);
}
/****************************************************************
������:	void send_2821_end()
��  �ܣ���2821����DMX512��ʽ����������ʹ������Ч
****************************************************************/
void send_2821_end()
{
	DAI=1;
 }

/******************************************
�� �� ����void Allbump()
��    �ܣ������߲�����
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
�� �� ����void time0_init()
��    �ܣ���ʱ����ʼ��
******************************************/
void time0_init()
{
	TMOD = 0x00;		//16λ�Զ���װ
	AUXR = 0x80;		//1Tģʽ

	TL0 = 0x7B;
	TH0 = 0xFF;          //1.11518us	(900k�ٶ�)		(TL0=D2 ;TH0=FF)750K  (TL0=7B ;TH0=FF)750K

	TR0=0;               //����ʱ��0
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
�� �� ����
��    �ܣ����������
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
������: void send_2821_byte(uchar cod8)
��  ��: ��2821����һ���ֽ�����
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
��������void send_2821_24bits(uchar dat1,uchar dat2,uchar dat3)
��  �ܣ���2821��������֡��һ�η�������ͨ��
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

  TF0=0; 	       //2usһλ����
}
