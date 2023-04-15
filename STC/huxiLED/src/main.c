#include <8052.h>
// #include "led88.h"

#define uint unsigned int
#define uchar unsigned char
// sbit PWM = P2 ^ 0; // P2.0输出pwm
#define PWM P0
int time; // 定义占空比的变量
int T = 100, D = 2;
int MAX = 70, MIN = -2, cnt, i;
char flag = 4;
void main() {
	TMOD = 0x02;
	TH0 = 0xf0;
	TL0 = 0xf0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	P1 = 0xee;
	while (1){}
}

void tim0() __interrupt 1 {
	++ time;
	if (time >= T) {
		time = 0;
		++ cnt;
		if (cnt >= 8) {
			if (flag) ++D;
			else --D;
			// ++D;
			if (D > MAX) flag=0;
			if (D < MIN) flag=1;
			cnt = 0;
		}
	}
	if (time <= D) { // 占空比D/T
		P0 = 0x00;
	}
	else
		P0 = 0xff;
	++P1;
	P1 &= 0xe7;
}