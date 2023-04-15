#ifndef __TBZ_SSD1306_H_
#define __TBZ_SSD1306_H_

#include "i2c.h"
#include "math.h"
#include "font.h"

#define OLED_ADDR B01111000
#define OLED_CMD  0x00
#define OLED_DATA 0x40
#define OLED_MODE 0


//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0x10
#define X_WIDTH 	128
#define Y_WIDTH 	64


void Delay_50ms(unsigned int Del_50ms);

void Delay_1ms(unsigned int Del_1ms);


#define OLED_WR_Byte(a,b) I2C_WriteRegister (OLED_ADDR, b, a)


/**
 * @brief 使用 filter function 填充屏幕
 * @param func 传入当前页和地址(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant);

void OLED_Set_Page (unsigned char page);
//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y);
//开启OLED显示
void OLED_Display_On(void);
//关闭OLED显示
void OLED_Display_Off(void);

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);

//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);

//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no);

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

//初始化SSD1306
void OLED_Init(void);


#endif