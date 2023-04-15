#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#include "myheader.h"


void main () {
	// P1 = 0x0e;
	P1 = 0xe;
	while (1) {
		// P2 = B01010101; 
		P0 = keystate ();
	}
}