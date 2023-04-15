#include <reg52.h>
#include <stdlib.h>
#define __TBZ_LCD1602_
#define __TBZ_EFFECT_
#include "myheader.h"

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;



unsigned int i, cnt = 0;
int T = 6000, td = 0;
char words[16] = "!!!I LOVE YOU!!!";
char tmp;
void main () {
	P1 = 0x00;
	LED = 0;
	TMOD = 0x1;
	TL0 = 0;
	TH0 = 0x24;
	//经过了计算，这个数值作为起点，
	// 能够得到一个较为准确的毫秒计时
	TF0 = 0;
	TR0 = 1;
	// LCD1602_BLA = 0;
	initLCD1602 ();
	lcdPrint (0, 1, "Welcome to KST51");
	while (1) {
		turn2Numbers (T);
		show_P1_07 ();
		show_P1_8d ();
		P1 = B00010010; // 设置 P1 的值，使 P0 不会作用到其他灯上
				lcdPrint (0, 0, words);
		// delay (100);
		if (TF0){
			TF0 = 0;
			TL0 = 0;
			TH0 = 0;
			++cnt;
			if (cnt > 13) {
				--T;
				cnt = 0;
				words2right (words, 16);
				for (i = 0; i < 8; ++i){
					P1_07_love [i] = bits2left (P1_07_love [i]);
				}
				words2right (P1_07_love, 8);
			}
		}
	}
}