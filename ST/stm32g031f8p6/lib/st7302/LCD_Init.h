#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#ifdef __cplusplus
extern "C" {
#endif
// #include "sys.h"
#include "common.h"

//Ĭ��0������ʾ
//�޸�Ϊ1������ʾʱ ���������2�����ص� �޷���ʾ����� ��Ҫע��
#define USE_HORIZONTAL 0  //������ʾ����


//-----------------LCD�˿ڶ���----------------

// #define LCD_SCLK_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_12)//SCL
// #define LCD_SCLK_Set() GPIO_SetBits(GPIOG,GPIO_Pin_12)

// #define LCD_MOSI_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_5)//SDA
// #define LCD_MOSI_Set() GPIO_SetBits(GPIOD,GPIO_Pin_5)

// #define LCD_RES_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_4)//RES
// #define LCD_RES_Set() GPIO_SetBits(GPIOD,GPIO_Pin_4)

// #define LCD_DC_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_15)//DC
// #define LCD_DC_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_15)

// #define LCD_CS_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_1)//CS
// #define LCD_CS_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_1)




// #define LCD_SCLK_Clr() clr(CLK)//SCL
// #define LCD_SCLK_Set() set(CLK)

// #define LCD_MOSI_Clr() clr(SDA)//SDA
// #define LCD_MOSI_Set() set(SDA)

#define LCD_RES_Clr() clr(RST)//RES
#define LCD_RES_Set() set(RST)

#define LCD_DC_Clr()  clr(DC)//DC
#define LCD_DC_Set()  set(DC)

#define LCD_CS_Clr()  clr(CS)//CS
#define LCD_CS_Set()  set(CS)



void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Init(void);//LCD��ʼ��

#ifdef __cplusplus
}
#endif
#endif
