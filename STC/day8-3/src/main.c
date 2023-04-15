// #define __TBZ_LED88_ENABLE_
// #define __TBZ_LCD1602_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
// #define __TBZ_MOTOR_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __TBZ_BUZZ_MUSIC_

#include "myheader.h"


void main () {
	EA = 1;
	TMOD = 1;
	int f = 0, duration = 1000;
	while (1) {
		char keys = keystate ();
		if (keys == VK_LEFT) {
			// arrayReverse (beatCode);
		} else if (keys == VK_RIGHT) {
			// arrayReverse (beatCode);
		} else if (keys == VK_DOWN) {
			--f;
		} else if (keys == VK_UP) {
			++f;
		}
		if (duration < 18) {
			duration = 18;
		}
		f &= B0111;
		openBuzz (buzzzz[f]);
		// P0 = keystate();
		delay(duration);
	}
}

void interruptTimer0 () __interrupt 1
{
	TH0 = T0RH;
	TL0 = T0RL;
	// BUZZ ^= 1;
	BUZZ = !BUZZ;
}