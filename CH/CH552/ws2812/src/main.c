#include "lint.h"
// #include "ch552_reg_sdcc.h"


#define Fsys 24000000

__sfr __at(0xb9) CLOCK_CFG;
__sfr __at(0x90) P1;
__sbit __at(0x91) P1_1;
__sfr __at(0x92) P1_MOD_OC;
__sfr __at(0x93) P1_DIR_PU;
__sfr __at(0xfc) SPI0_SETUP;
__sfr __at(0xfb) SPI0_CK_SE;
__sfr __at(0xfa) SPI0_CTRL;
__sfr __at(0xf9) SPI0_DATA;
__sfr __at(0xf8) SPI0_STAT;
__sbit __at(0xfb) S0_FREE;
__sfr __at(0xa1) SAFE_MOD;

#define _nop_() __asm NOP __endasm


#define ws2812_1() SPI0_DATA = 0b01111110;while(S0_FREE==0);
#define ws2812_0() SPI0_DATA = 0b01100000;while(S0_FREE==0);


void ws2812_write_byte(unsigned char dat) {
	if(dat&0b00000001){ws2812_1()}else{ws2812_0()};
	if(dat&0b00000010){ws2812_1()}else{ws2812_0()};
	if(dat&0b00000100){ws2812_1()}else{ws2812_0()};
	if(dat&0b00001000){ws2812_1()}else{ws2812_0()};
	if(dat&0b00010000){ws2812_1()}else{ws2812_0()};
	if(dat&0b00100000){ws2812_1()}else{ws2812_0()};
	if(dat&0b01000000){ws2812_1()}else{ws2812_0()};
	if(dat&0b10000000){ws2812_1()}else{ws2812_0()};
}

static long __xdata __holdrand = 1L;
void srand (unsigned int seed) {
	__holdrand = (long)seed;
}
int rand (void) {
	return(((__holdrand = __holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}
int main () {
	SAFE_MOD = 0x55;
	SAFE_MOD = 0xaa;
	CLOCK_CFG = 0b10000110;   // set fsys=24MHz
	SAFE_MOD = 0x00;

	SPI0_SETUP = 0x00;
	SPI0_CK_SE = 3;           //24 MHz 3·ÖÆµ µÃ 8MHz
	SPI0_CTRL = 0b01100000;

	P1_MOD_OC = 0b11111111;
	P1_DIR_PU = 0b00000000;


	P1_1 = 1;
	int i = 0, j;
	while (1) {

		// P1 = ~P1;
		srand (233);
		for (i = 0; i < 40; i++) {
			ws2812_write_byte((int)rand());
			ws2812_write_byte((int)rand());
			ws2812_write_byte((int)rand());
		}
		// WS2812_IO = 0;
		for (i = 0; i<3000;i++) {

				_nop_();
		}

	}



}