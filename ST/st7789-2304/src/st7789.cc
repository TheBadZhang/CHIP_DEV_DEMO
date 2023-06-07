#include "st7789.h"
#include "common.h"

#define DATA 1
#define CMD 0

#define RESET1 set(RST)
#define RESET0 clr(RST)
#define DC1 set(DC)
#define DC0 clr(DC)

//向液晶屏写一个8位数据/指令
void lcd_writeDC(uchar Data, uchar cmd) {
	if (cmd) DC1;
	else DC0;
	HAL_SPI_Transmit(&hspi1, &Data, 1, 100);
}
//向液晶屏写一个16位数据
void lcd_writeWord(unsigned int Data) {
	DC1;
	HAL_SPI_Transmit(&hspi1, (uint8_t *) & Data, 2, 100);
}

void lcd_reset() {
	RESET0;
	HAL_Delay(100);
	RESET1;
	HAL_Delay(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial() {
	uchar value [] = {
		0x36, 0x00,
		0x3A, 0x05,
		0xB2, 0x0C, 0x0C, 0x00, 0x33, 0x33,
		0xb7, 0x35,
		0xbb, 0x19,
		0xc0, 0x2c,
		0xc2, 0x01,
		0xc3, 0x12,
		0xc4, 0x20,
		0xc6, 0x0f,
		0xd0, 0xa4, 0xa1,
		0xe0, 0xd0, 0x04, 0x0d, 0x11, 0x13, 0x2b, 0x3f, 0x54, 0x4c, 0x18, 0x0d, 0x0b, 0x1f, 0x23,
		0xe1, 0xd0, 0x04, 0x0c, 0x11, 0x13, 0x2c, 0x3f, 0x44, 0x51, 0x2f, 0x1f, 0x1f, 0x20, 0x23,
		0x21,
		0x11,
		0x29
	};
	uchar datcmd [] = {
		CMD, DATA,
		CMD, DATA,
		CMD, DATA, DATA, DATA, DATA, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA,
		CMD, DATA, DATA,
		CMD, DATA, DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,
		CMD, DATA, DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,  DATA,
		CMD,
		CMD,
		CMD
	};
	lcd_reset(); //RESET before LCD Init.
			 //	Lcd_WriteIndex(0x11);//Sleep exit
	HAL_Delay(120);
	FOR0 (i, 0, sizeof (value)) {
		lcd_writeDC (value[i], datcmd[i]);
	}
}

/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void lcd_setRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end) {
	lcd_writeDC(0x2a,CMD);
	lcd_writeDC(0x00,DATA);
	lcd_writeDC(x_start,DATA);
	lcd_writeDC(0x00,DATA);
	lcd_writeDC(x_end-1,DATA);

	lcd_writeDC(0x2b,CMD);
	lcd_writeDC(0x00,DATA);
	lcd_writeDC(y_start,DATA);
	lcd_writeDC(0x00,DATA);
	lcd_writeDC(y_end-1,DATA);
	lcd_writeDC(0x2c,CMD);
}

void lcd_putPixel (uint x_start, uint y_start, uint color) {
	lcd_setRegion (x_start, y_start, x_start + 1, y_start + 1);
	lcd_writeWord (color);
}
// 使用一种颜色清空屏幕
void lcd_clear (int color) {
	lcd_setRegion(0, 0, 100, 200);
	FOR0 (i, 0, 100) FOR0 (j, 0, 200)
		lcd_writeWord(color);
}