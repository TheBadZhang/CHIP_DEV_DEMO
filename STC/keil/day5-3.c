#include <reg52.h>
#include <stdlib.h>
#include "binary.h"
#define __TBZ_BUZZ_
#include "myheader.h"


void main () {
	unsigned char tmp, index = 0;
	TMOD = 1;
	EA = 1;
	while (1) {
		tmp = P1;
		tmp &= 0xf0;
		tmp |= beatCode [index];
		P1 = tmp;
		++index;
		index &= 0x07;
		delay (10);
		/*
		openBuzz (4000);
		delay (4000);
		stopBuzz ();
		openBuzz (1000);
		delay (4000);
		stopBuzz ();
		*/
	}
}