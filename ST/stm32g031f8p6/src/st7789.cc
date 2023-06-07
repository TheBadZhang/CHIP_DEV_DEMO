#include "st7789.h"
#include "common.h"

#define DATA 1
#define CMD 0

#define RESET1 HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin, HIGH)
#define RESET0 HAL_GPIO_WritePin(RST_GPIO_Port,RST_Pin, LOW)
#define DC1 HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, HIGH)
#define DC0 HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, LOW)

void LCD_Writ_Bus(u8 dat) {
	clr(CS);
	// HAL_SPI_Transmit_DMA(&hspi1, &dat, 1);
	// while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, &dat, 1, 100);
	// LL_SPI_TransmitData8(SPI1, dat);
	// for(char i=0;i<8;i++) {
	// 	clr(SCK);
	// 	if(dat&0x80) {
	// 		set(SDA);
	// 	} else {
	// 		clr(SDA);
	// 	}
	// 	set(SCK);
	// 	dat<<=1;
	// }
	set(CS);
}

//向液晶屏写一个8位数据/指令
void lcd_writeDC(uchar Data, uchar cmd) {
	if (cmd) DC1;
	else DC0;
	LCD_Writ_Bus(Data);
	// HAL_SPI_Transmit(&hspi1, &Data, 1, 100);
}
//向液晶屏写一个16位数据
void lcd_writeWord(unsigned int Data) {
	DC1;
	LCD_Writ_Bus(Data >> 8);
	LCD_Writ_Bus(Data);
	// HAL_SPI_Transmit(&hspi1, (uint8_t *) & Data, 2, 100);
}

void lcd_reset() {
	RESET0;
	HAL_Delay(100);
	RESET1;
	HAL_Delay(100);
}
#define LCD_ROTATE_180
//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1
void lcd_initial() {
	uchar value [] = {
		0x36,
		#ifdef LCD_ROTATE_180
		0x70,
		#else
		0x00,
		#endif
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
	lcd_setRegion(0, 0, 240, 240);
	// FOR0 (i, 0, 320) FOR0 (j, 0, 173)
	for (int i = 0; i < 240*240; i++)
		lcd_writeWord(color);
}