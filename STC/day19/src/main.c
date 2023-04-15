#define __TBZ_SSD1306_ENABLE_
#define __TBZ_RANDOM_ENABLE_
#define I2C_Delay()
#include "myheader.h"
#include "st7789.h"
#include "spi.h"
char tmp;

__sfr __at(0xb3) P4M1;
__sfr __at(0xb4) P4M0;
__sfr __at(0xb1) P3M1;
__sfr __at(0xb2) P3M0;
__sfr __at(0x95) P2M1;
__sfr __at(0x96) P2M0;
__sfr __at(0x91) P1M1;
__sfr __at(0x92) P1M0;
__sfr __at(0x93) P0M1;
__sfr __at(0x94) P0M0;

__sfr __at(0xa2) P_SW1;   // 外设端口切换控制寄存器 1

__sfr __at(0x83) AUXR;
__sfr __at(0xd6) T2H;
__sfr __at(0xd7) T2L;

unsigned char func(char x, char y) __reentrant {
	return rand ();
}

void main () {
	P0M0 = 0x00;
	P0M1 = 0x00;
	P1M0 = 0x00;
	P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	SPI_Init_t spi_Init;
	spi_Init.MSType = SPI_Type_Master;
	spi_Init.ClkSrc = SPI_SCLK_DIV_4;
	spi_Init.Order = SPI_Tran_MSB;
	spi_Init.CLType = SPI_Mode_2;
	spi_Init.Run = SPI_Run;
	P_SW1 = 0x00;
	spi_init (&spi_Init);
	OLED_Init ();
	srand (123);
	lcd_initial();
	while (1) {
		OLED_Fill (func);
		// delay1ms(10000);
		lcd_clear(WHITE);
		Fast_DrawFont_GBK16(8, 10, BLUE, YELLOW, "中文测试");
		Fast_DrawFont_GBK16(16, 50, BLUE, WHITE, "欢迎您");
		Fast_DrawFont_GBK16(8, 70, GREEN, BLUE, "因为专注");
		Fast_DrawFont_GBK16(8, 90, WHITE, BLUE, "所以专业");

		delay1ms(1800);
	}
}