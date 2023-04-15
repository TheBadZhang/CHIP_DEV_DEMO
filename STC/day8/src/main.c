#define __TBZ_LED88_ENABLE_
#define __TBZ_LCD1602_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_

#include "myheader.h"

char words[] = "!!!I LOVE YOU!!!";
char words2[]= "0A1B2C3D4E5F6+7-8*9/";

char tmp;
void main () {
	
	TMOD = 0x1;
	TL0 = 0;
	TH0 = 0xc4;
	//经过了计算，这个数值作为起点，
	// 能够得到一个较为准确的0.1秒计时
	TF0 = 0;
	TR0 = 1;
	initLCD1602 ();
	P0 = 0xff;
	P1 = 0xe;
	char k;
	char toUp = 1;
	while (1) {
		// show_P1_07 ();
		// show_P1_8d ();
		lcdPrint (0, 0, words);
		lcdPrint (0, 1, words2);
		P0 = 0xff;
		P1 = 0xe;
		k = keystate();
		if (k == 0xff) {
			toUp = 1;
		} else if (toUp == 1) {
			toUp = 0;
			if (k == VK_LEFT) {
				words2left (words);
			} else if (k == VK_RIGHT) {
				words2right (words);
			}
			P0 = keystate();
		}
		delay(300);
	}
}