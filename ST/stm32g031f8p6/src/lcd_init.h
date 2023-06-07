#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"

#define USE_HORIZONTAL 2  //???ùù?????????????? 0??1????? 2??3?????


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif



//-----------------LCD??????----------------

// #define LCD_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_0)//SCL=SCLK
// #define LCD_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_0)

// #define LCD_MOSI_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_1)//SDA=MOSI
// #define LCD_MOSI_Set() GPIO_SetBits(GPIOA,GPIO_Pin_1)

// #define LCD_RES_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)//RES
// #define LCD_RES_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_2)

// #define LCD_DC_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_3)//DC
// #define LCD_DC_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_3)

// #define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_4)//CS
// #define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define LCD_SCLK_Clr() clr(SCK)//SCL=SCLK
#define LCD_SCLK_Set() set(SCK)

#define LCD_MOSI_Clr() clr(MOSI)//SDA=MOSI
#define LCD_MOSI_Set() set(MOSI)
#define LCD_RES_Clr()  clr(RST)//RES
#define LCD_RES_Set()  set(RST)

#define LCD_DC_Clr()   clr(DC)//DC
#define LCD_DC_Set()   set(DC)

#define LCD_CS_Clr()   clr(CS)//CS
#define LCD_CS_Set()   set(CS)

// #define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_5)//BLK
// #define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_5)




// void LCD_GPIO_Init(void);//?????GPIO
void LCD_Writ_Bus(u8 dat);//???SPI???
void LCD_WR_DATA8(u8 dat);//ùù????????
void LCD_WR_DATA(u16 dat);//ùù?????????
void LCD_WR_REG(u8 dat);//ùù????????
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//??????????
void LCD_Init(void);//LCD?????

#ifdef __cplusplus
}
#endif

#endif




