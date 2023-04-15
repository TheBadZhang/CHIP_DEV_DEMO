// #define __TBZ_LED88_ENABLE_
#define __TBZ_LCD1602_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
// #define __TBZ_LED7SEG_ENABLE_
#define __TBZ_MOTOR_ENABLE_

#include "myheader.h"

// char words[] = "!!!I LOVE YOU!!!";
// char words2[]= "0A1B2C3D4E5F6+7-8*9/";

char tmp;
void main () {
	TMOD = 0x1;
	TL0 = 0;
	TH0 = 0xc4;
	//经过了计算，这个数值作为起点，
	// 能够得到一个较为准确的0.1秒计时
	TF0 = 0;
	TR0 = 1;
	// initLCD1602 ();
	P0 = 0xff;
	P1 = 0xe;
	unsigned char index = 0, index2 = 0;
	int duration = 18;
	// wordsReverse (words);
	while (1) {
		// show_P1_07 ();
		// show_P1_8d ();
		// lcdPrint (0, 0, words);
		// lcdPrint (0, 1, words2);
		// P0 = 0xff;
		// P1 = 0xe;
		P1 = P1 & 0xf0 | beatCode [index++];
		index &= sizeof(beatCode)-1;
		char keys = keystate ();
		if (keys == VK_LEFT) {
			arrayReverse (beatCode);
		} else if (keys == VK_RIGHT) {
			arrayReverse (beatCode);
		} else if (keys == VK_DOWN) {
			duration += 100;
		} else if (keys == VK_UP) {
			duration -= 100;
		}
		if (duration < 18) {
			duration = 18;
		}
		// P0 = keystate();
		delay(duration);
	}
}