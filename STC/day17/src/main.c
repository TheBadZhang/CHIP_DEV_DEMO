#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_

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

#include "myheader.h"
#include "max7219.h"


void main () {
	P0M0 = 0x00;
	P0M1 = 0x00;
	P1M0 = 0x00;
	P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
			delay1ms (1000);
	max7219_Init ();
	int i,j = 8, k;
	while (1) {
		FOR (j, 38) {
			FOR (k,4) FOR (i, 8) {
				max7219_MultiWrite (k, i+1,max7219_disp[(j+k)%38][i]);
			}
			delay1ms (5000);
		}
	}
}