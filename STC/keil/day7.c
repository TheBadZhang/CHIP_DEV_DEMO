#include <reg52.h>
#include <stdlib.h>

#define __TBZ_LED88_ENABLE_
#define __TBZ_LCD1602_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_

#include "myheader.h"

unsigned int i, cnt = 0;
int T = 0, td = 0;
char words[] = "!!!I LOVE YOU!!!";
char words2[]= "0A1B2C3D4E5F6+7-8*9/";

char tmp;
void main () {
	P1 = 0x00;
	LED = 0;
	TMOD = 0x1;
	TL0 = 0;
	TH0 = 0xc4;
	//经过了计算，这个数值作为起点，
	// 能够得到一个较为准确的0.1秒计时
	TF0 = 0;
	TR0 = 1;
	initLCD1602 ();
	while (1) {
		turn2Numbers (T);
		P1_8d_numbers [0] = 5;
		P1 = 10;
		P0 = B01111111;
		delay (1);
		// P1_8d_numbers [2] &= B01111111;
		show_P1_07 ();
		show_P1_8d ();
		lcdPrint (0, 0, words);
		lcdPrint (0, 1, words2);
		// delay (100);
		if (TF0){
			TF0 = 0;
			TL0 = 0;
			TH0 = 0xc4;
			++cnt;
			T += 2;
			if (cnt > 50) {
				cnt = 0;
				words2right (words);
				words2left (words2);
				for (i = 0; i < 8; ++i){
					bits2left (P1_07_love+i);
				}
				words2left (P1_07_love);
			}
		}
	}
}