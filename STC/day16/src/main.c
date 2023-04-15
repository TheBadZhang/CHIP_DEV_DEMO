#define __STC15W4K32S
#define __TBZ_RANDOM_ENABLE_
#include "myheader.h"
// #include <8052.h>
#include "keyboard_vk.h"
#include "nokia5110.h"
#include "ttp229.h"
#include <stdio.h>


void keyboard (void) {
	uint r = TTP229B_get ();
	switch (r) {
		case VK_0: nokia5110_writeString (0,1,"love"); break;
		case VK_1: nokia5110_writeString (0,1,"you"); break;
		case (TTP229_VK_0|TTP229_VK_2|TTP229_VK_5): nokia5110_writeString (0,1,"i love you"); break;
		default: nokia5110_writeString(0,1,"Nokia 5110"); break;
	}
}

void main(){
	P0M1 = 0x00;
	P0M0 = 0x00;
	P1M1 = 0x00;
	P1M0 = 0x00;
    nokia5110_LCDInit();
    nokia5110_writeString(3,0,   "Value");
    nokia5110_writeString(0,1,"Nokia 5110");
    nokia5110_writeString(0,2,"Now Worked");
	int i;
    while(1) {
		// keyboard ();
		nokia5110_moveTo (0,0);
		FOR (i, 6*84) nokia5110_writeDat (rand ()&0xff);
	}
}
