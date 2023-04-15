#include "st7789.h"

#define DATA 1
#define CMD 0

unsigned int __xdata i, j, k;

//向液晶屏写一个8位数据/指令
void lcd_writeDC(uchar Data, uchar cmd) {
	CS = 0;
	DC = cmd;
	spi_writeByte (Data);
	// spi_soft_writeByte (Data);
	CS = 1;
}
//向液晶屏写一个16位数据
void lcd_writeWord(unsigned int Data) {
	CS = 0;
	DC = DATA;
	spi_writeWord (Data);
	CS = 1;
}

void lcd_reset() {
	RESET = 0;
	delay1ms(100);
	RESET = 1;
	delay1ms(100);
}
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial() {
	uchar __code value [] = {
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
	uchar __code datcmd [] = {
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
	delay1ms(120);
	FOR (i, sizeof (value)) {
		lcd_writeDC (value[i], datcmd[i]);
	}
	// Lcd_WriteIndex(0x36);
	// Lcd_WriteData(0x00);

	// Lcd_WriteIndex(0x3A);
	// Lcd_WriteData(0x05);

	// Lcd_WriteIndex(0xB2);
	// Lcd_WriteData(0x0C);
	// Lcd_WriteData(0x0C);
	// Lcd_WriteData(0x00);
	// Lcd_WriteData(0x33);
	// Lcd_WriteData(0x33);

	// Lcd_WriteIndex(0xB7);
	// Lcd_WriteData(0x35);

	// Lcd_WriteIndex(0xBB);
	// Lcd_WriteData(0x19);

	// Lcd_WriteIndex(0xC0);
	// Lcd_WriteData(0x2C);

	// Lcd_WriteIndex(0xC2);
	// Lcd_WriteData(0x01);

	// Lcd_WriteIndex(0xC3);
	// Lcd_WriteData(0x12);

	// Lcd_WriteIndex(0xC4);
	// Lcd_WriteData(0x20);

	// Lcd_WriteIndex(0xC6);
	// Lcd_WriteData(0x0F);

	// Lcd_WriteIndex(0xD0);
	// Lcd_WriteData(0xA4);
	// Lcd_WriteData(0xA1);

	// Lcd_WriteIndex(0xE0);
	// Lcd_WriteData(0xD0);
	// Lcd_WriteData(0x04);
	// Lcd_WriteData(0x0D);
	// Lcd_WriteData(0x11);
	// Lcd_WriteData(0x13);
	// Lcd_WriteData(0x2B);
	// Lcd_WriteData(0x3F);
	// Lcd_WriteData(0x54);
	// Lcd_WriteData(0x4C);
	// Lcd_WriteData(0x18);
	// Lcd_WriteData(0x0D);
	// Lcd_WriteData(0x0B);
	// Lcd_WriteData(0x1F);
	// Lcd_WriteData(0x23);

	// Lcd_WriteIndex(0xE1);
	// Lcd_WriteData(0xD0);
	// Lcd_WriteData(0x04);
	// Lcd_WriteData(0x0C);
	// Lcd_WriteData(0x11);
	// Lcd_WriteData(0x13);
	// Lcd_WriteData(0x2C);
	// Lcd_WriteData(0x3F);
	// Lcd_WriteData(0x44);
	// Lcd_WriteData(0x51);
	// Lcd_WriteData(0x2F);
	// Lcd_WriteData(0x1F);
	// Lcd_WriteData(0x1F);
	// Lcd_WriteData(0x20);
	// Lcd_WriteData(0x23);

	// Lcd_WriteIndex(0x21);

	// Lcd_WriteIndex(0x11);

	// Lcd_WriteIndex(0x29);
}

/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void lcd_setRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end) {
	// uchar __code value [] = {
	// 	0x2a, 0x00, 0xff, 0x00, 0xff,
	// 	0x2b, 0x00, 0xff, 0x00, 0xff,
	// 	0x2c
	// };
	// uchar __code datcmd [] = {
	// 	CMD, DATA, DATA, DATA, DATA,
	// 	CMD, DATA, DATA, DATA, DATA,
	// 	CMD
	// };
	// value [2] = x_start;
	// value [4] = x_end-1;
	// value [7] = y_start;
	// value [9] = y_end-1;
	// FOR (i, sizeof (value)) {
	// 	lcd_writeDC (value[i], datcmd[i]);
	// }
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
	lcd_setRegion(0, 0, 240, 240);
	FOR (i, 240) FOR (j, 240)
		lcd_writeWord(color);
}

//采用设置窗口方法填充字库数据，相比Gui_DrawFont_GBK16更快速
void Fast_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s) {
	while (*s) {
		if ((*s) >= 128) {
			FOR (k, sizeof(hz16) / sizeof(typFNT_GBK16_t)) {
				if (strcmp_eq_n (hz16[k].index, s, 2)) {
				// if ((hz16[k].index[0] == *(s)) && (hz16[k].index[1] == *(s + 1))) {
					lcd_setRegion(x, y, x + 16, y + 16);
					FOR (i, 32) {
						FOR (j, 8) {
							if (hz16[k].mask[i] & (0x80 >> j)) {
								lcd_writeWord(fc);
							} else if (fc != bc) {
								lcd_writeWord(bc);
							}
						}
					}
				}
			}
			s += 2;
			x += 16;
		} else
			s += 1;
	}
}
//此方法描绘汉字较慢
void Gui_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s) {
	uint __xdata x0;
	x0 = x;

	while (*s) {
		if ((*s) >= 128) {
			FOR (k, sizeof (hz16)) {
				if (strcmp_eq_n (hz16[k].index, s, 2)) {
				// if ((hz16[k].index[0] == *(s)) && (hz16[k].index[1] == *(s + 1))) {
					FOR (i, 16) {
						FOR (j, 8) {
							if (hz16[k].mask[i * 2] & (0x80 >> j))
								lcd_putPixel(x + j, y + i, fc);
							else if (fc != bc) {
								lcd_putPixel(x + j, y + i, bc);
							}
						}
						FOR (j, 8) {
							if (hz16[k].mask[i * 2 + 1] & (0x80 >> j))
								lcd_putPixel(x + j + 8, y + i, fc);
							else if (fc != bc) {
								lcd_putPixel(x + j + 8, y + i, bc);
							}
						}
					}
				}
			}
			s += 2;
			x += 16;
		} else
			s += 1;
	}
}
