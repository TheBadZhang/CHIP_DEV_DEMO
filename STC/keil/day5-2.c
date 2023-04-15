#include <reg52.h>
#include <stdlib.h>
#include "binary.h"
#include "myheader.h"

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;



unsigned int i, cnt = 0;
int T = 6000, td = 0;
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
	while (1) {
		turn2Numbers (T);
		show_P1_07 ();
		show_P1_8d ();
		if (TF0){
			TF0 = 0;
			TL0 = 0;
			TH0 = 0;
			++cnt;
			if (cnt > 13) {
				--T;
				cnt = 0;
			}
		}
	}
}