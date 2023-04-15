#ifndef __TBZ_ST7789_H_
#define __TBZ_ST7789_H_
#define __TBZ_SPI_ENABLE_
#include "myheader.h"
#include "mystring.h"
#include "device/font.h"


//---------------------------液晶屏接线说明-------------------------------------//
//接线前请参考液晶屏说明书第10页引脚定义
#define BLK P0_7    //接模块BL引脚，背光可以采用IO控制或者PWM控制，也可以直接接到高电平常亮
#define SCL P1_5    //接模块CLK引脚         接裸屏Pin9_SCL
#define SDA P1_3    //接模块DIN/MOSI引脚    接裸屏Pin8_SDA
#define DC P1_0     //接模块D/C引脚         接裸屏Pin7_A0
#define CS P1_7     //接模块CE引脚          接裸屏Pin12_CS      //! 测试屏幕没有片选引脚，此处不做额外处理
#define RESET P1_1  //接模块RST引脚         接裸屏Pin6_RES
//---------------------------End of液晶屏接线---------------------------------//

//定义常用颜色
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D
#define GRAY1 0x8410
#define GRAY2 0x4208


//向液晶屏写一个8位数据/指令
void lcd_writeDC(uchar Data, uchar cmd);
//向液晶屏写一个16位数据
void lcd_writeWord(unsigned int Data);

void lcd_reset ();
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial();
/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void lcd_setRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end);

void lcd_putPixel (uint x_start, uint y_start, uint color);
// 使用一种颜色清空屏幕
void lcd_clear (int color);

//采用设置窗口方法填充字库数据，相比Gui_DrawFont_GBK16更快速
void Fast_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s);
//此方法描绘汉字较慢
void Gui_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s);

#endif