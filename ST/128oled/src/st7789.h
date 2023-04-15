#ifndef __TBZ_ST7789_H_
#define __TBZ_ST7789_H_
#define __TBZ_SPI_ENABLE_

#include "core.h"

//---------------------------液晶屏接线说明-------------------------------------//
//接线前请参考液晶屏说明书第10页引脚定义
//---------------------------End of液晶屏接线---------------------------------//

//定义常用颜色
#define RED    0xf800
#define GREEN  0x07e0
#define BLUE   0x001f
#define WHITE  0xffff
#define BLACK  0x0000
#define YELLOW 0xFFE0
#define GRAY0  0xEF7D
#define GRAY1  0x8410
#define GRAY2  0x4208


/**
 * @brief 向液晶屏写一个8位数据/指令
 *
 * @param Data
 * @param cmd
 */
void lcd_writeDC(uchar Data, uchar cmd);
/**
 * @brief 向液晶屏写一个16位数据
 *
 * @param Data
 */
void lcd_writeWord(unsigned int Data);

void lcd_reset ();
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial();
/**
 * @brief 设置lcd显示区域，在此区域写点数据自动换行
 *
 * @param x_start
 * @param y_start
 * @param x_end
 * @param y_end
 */
void lcd_setRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end);
/**
 * @brief
 *
 * @param x_start
 * @param y_start
 * @param color
 */
void lcd_putPixel (uint x_start, uint y_start, uint color);
/**
 * @brief 使用一种颜色清空屏幕
 *
 * @param color
 */
void lcd_clear (int color);

/**
 * @brief 采用设置窗口方法填充字库数据，相比Gui_DrawFont_GBK16更快速
 *
 * @param x
 * @param y
 * @param fc
 * @param bc
 * @param s
 */
#endif
