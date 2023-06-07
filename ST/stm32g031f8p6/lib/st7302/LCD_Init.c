#include "LCD_Init.h"
// #include "delay.h"




// void LCD_GPIO_Init(void)
// {
// 	GPIO_InitTypeDef  GPIO_InitStructure;
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��A�˿�ʱ��
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//  	GPIO_Init(GPIOG, &GPIO_InitStructure);	  //��ʼ��GPIOG12
//  	GPIO_SetBits(GPIOG,GPIO_Pin_12);

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//  	GPIO_Init(GPIOD, &GPIO_InitStructure);	  //��ʼ��GPIOD1,5,15
//  	GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15);

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//  	GPIO_Init(GPIOE, &GPIO_InitStructure);	  //��ʼ��GPIOE8,10
//  	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_10);
// }


/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
	u8 i;
	LCD_CS_Clr();
  HAL_SPI_Transmit(&hspi1, &dat, 1, 1000);
	// for(i=0;i<8;i++)
	// {
	// 	LCD_SCLK_Clr();
	// 	if(dat&0x80)
	// 	{
	// 	   LCD_MOSI_Set();
	// 	}
	// 	else
	// 	{
	// 	   LCD_MOSI_Clr();
	// 	}
	// 	LCD_SCLK_Set();

	// 	dat<<=1;
	// }
  LCD_CS_Set();
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}




/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}



void LCD_Init(void)
{
	// LCD_GPIO_Init();//��ʼ��GPIO

	LCD_RES_Clr();//��λ
	HAL_Delay(100);
	LCD_RES_Set();
	HAL_Delay(100);

  HAL_Delay(100);

  HAL_Delay(300);  // HAL_Delay 300ms

  LCD_WR_REG(0x38);
  LCD_WR_REG(0xEB);//Enable OTP
  LCD_WR_DATA8(0x02);
  LCD_WR_REG(0xD7);//OTP Load Control
  LCD_WR_DATA8(0x68);
  LCD_WR_REG(0xD1);//Auto Power Control
  LCD_WR_DATA8(0x01);
  LCD_WR_REG(0xC0);//Gate Voltage Setting VGH=12V ; VGL=-5V
  LCD_WR_DATA8(0x80);
  LCD_WR_REG(0xC1);//VSH Setting
  LCD_WR_DATA8(0x28);//
  LCD_WR_DATA8(0x28);
  LCD_WR_DATA8(0x28);
  LCD_WR_DATA8(0x28);
  LCD_WR_DATA8(0x14);
  LCD_WR_DATA8(0x00);
  LCD_WR_REG(0xC2);//VSL Setting VSL=0
  LCD_WR_DATA8(0x00);
  LCD_WR_DATA8(0x00);
  LCD_WR_DATA8(0x00);
  LCD_WR_DATA8(0x00);
  LCD_WR_REG(0xCB);//VCOMH Setting
  LCD_WR_DATA8(0x14);//14  0C   7
  LCD_WR_REG(0xB4);//Gate EQ Setting HPM EQ LPM EQ
  LCD_WR_DATA8(0xE5);
  LCD_WR_DATA8(0x77);
  LCD_WR_DATA8(0xF1);
  LCD_WR_DATA8(0xFF);
  LCD_WR_DATA8(0xFF);
  LCD_WR_DATA8(0x4F);
  LCD_WR_DATA8(0xF1);
  LCD_WR_DATA8(0xFF);
  LCD_WR_DATA8(0xFF);
  LCD_WR_DATA8(0x4F);
  LCD_WR_REG(0x11);//Sleep out
  HAL_Delay(100);  // HAL_Delay 100ms
  LCD_WR_REG(0xC7);//OSC Setting
  LCD_WR_DATA8(0xA6);
  LCD_WR_DATA8(0xE9);
  LCD_WR_REG(0xB0);   //Duty Setting
  LCD_WR_DATA8(0x64);  //250duty/4=63

  LCD_WR_REG(0x36);//Memory Data Access Control
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0x4C);


  LCD_WR_REG(0x3A);//Data Format Select 4 write for 24 bit
  LCD_WR_DATA8(0x11);
  LCD_WR_REG(0xB9);//Source Setting
  LCD_WR_DATA8(0x23);
  LCD_WR_REG(0xB8);//Panel Setting Frame inversion
  LCD_WR_DATA8(0x09);
  LCD_WR_REG(0x2A);////Column Address Setting S61~S182
  LCD_WR_DATA8(0x05);
  LCD_WR_DATA8(0x36);
  LCD_WR_REG(0x2B);////Row Address Setting G1~G250
  LCD_WR_DATA8(0x00);
  LCD_WR_DATA8(0xC7);
  LCD_WR_REG(0xD0);
  LCD_WR_DATA8(0x1F);
  LCD_WR_REG(0x29);//Display on
  LCD_WR_REG(0xB9);//enable CLR RAM
  LCD_WR_DATA8(0xE3);
  HAL_Delay(100);
  LCD_WR_REG(0xB9);//enable CLR RAM
  LCD_WR_DATA8(0x23);
  LCD_WR_REG(0x72);
  LCD_WR_DATA8(0x00);         //Destress OFF
	LCD_WR_REG(0x39);//LPM
	LCD_WR_REG(0x2A);   //Column Address Setting
	LCD_WR_DATA8(0x19);
	LCD_WR_DATA8(0x23);  //35
	LCD_WR_REG(0x2B);   //Row Address Setting
	LCD_WR_DATA8(0);
	LCD_WR_DATA8(0x7C);
	LCD_WR_DATA8(0x2C);   //write image data
	HAL_Delay(120);
}

