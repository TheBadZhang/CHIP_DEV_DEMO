#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"
#include <8052.h>
#include "spi.h"
#include "device/nokia5110.h"
#include <stdio.h>
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

#define FOSC            11059200UL
#define BRT             (65536 - FOSC / 115200 / 4)
void UartSend(char dat)
{
    while (!TI);
    TI = 0;
    SBUF = dat;
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
	SPI_Init_t spi_init;
	spi_init.MSType = SPI_Type_Master;
	spi_init.ClkSrc = SPI_SCLK_DIV_16;
	spi_init.Order = SPI_Tran_MSB;
	spi_init.CLType = SPI_Mode_0;
	spi_init.Run = SPI_Run;
	P_SW1 = 0x00;
	spi_Init (&spi_init);
	uint8_t __code heart[] = {
		B00000000,
		B01100110,
		B11111111,
		B11111111,
		B11111111,
		B01111110,
		B00111100,
		B00011000
	};
	uint8_t __xdata data[4] = {
		0x00, 0x00, 0x00, 0x00
	};
	int j, x = 2;
	uint8_t a = 1;

    SCON = 0x5a;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR = 0x15;
	nokia5110_LCDInit ();
	char __xdata num[8];
	while (1) {
		// FOR(j, 8) {
			// spi_writeByte(~heart[j]);
			// spi_writeByte(0xff);
			// spi_writeByte(0xff);
			// spi_writeByte(~heart[j]);
			data [3] = ~heart[0];
			data [1] = 0xff;    // 这个是绿
			data [2] = 0xff;
			data [0] = B00000001 << j;     // 这一字节数据控制哪里不显示
			spi_writeBytes(data, sizeof(data));
			delay1ms(1000);
		// }
		if (j == 255) j = 0;
		j++;
		// sprintf(num,"%d", data[0]);
		// nokia5110_writeString(0,0,num);
		// delay1ms(10);
		// a <<= 1;
		// if (a == 0) a = 1;
		// if (data[0] == 255) data[0] = 0;
	}
}