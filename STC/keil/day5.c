#include <reg52.h>
#include <stdlib.h>
#include "binary.h"
sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;


unsigned int i, cnt = 0;



// 一个简单的延迟函数
void delay(unsigned int x10us){
	unsigned int x,y;
	for(x=x10us;x>0;x--)
		for(y=11;y>0;y--);
}
// 在点阵LED屏上显示一个爱心
char P1_07_love[] = {
	~0x42, ~0xe7, ~0xff, ~0xff, ~0xff, ~0x7e, ~0x3c, ~0x18
};
// 在数码管上显示数字
char P1_8d_number[] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
	0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,
	0x7f, 0xff, B11001000, B10111111
};

char P1_8d_numbers[] = {
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

void show_P1_8d (void) {
	// 8 9 a b c d
	for (i = 8; i < 0xe; i ++) {
		P1 = i;
		P0 = P1_8d_number[P1_8d_numbers [i-8]];
		// P0 = P1_8e_numbers [i-8];
		delay (20);
	}
}
void turn2Numbers (int num) {
	/*if (num >= 1000000.0 || num < -100000.0) {
		// 下面这串数值代表了 n 这个字符
		P1_8d_numbers [5] = 0x12;
		P1_8d_numbers [4] = 0x0a;
		P1_8d_numbers [3] = 0x12;
		P1_8d_numbers [2] = 0x10;
		P1_8d_numbers [1] = 0x10;
		P1_8d_numbers [0] = 0x10;
	} else {
		unsigned char wei = 0, wei2 = 0;
		int tlow = 100000;
		if (num < 0.0) {
			P1_8d_numbers [5] = 0x13;
			num = -num;
			tlow = 10000;
		}
		while (num < tlow) {
			num *= 10;
			++ wei;
		}
		tlow = (int)num;
		while (num>0) {
			P1_8d_numbers [wei2]= tlow%10;
			++wei2;
		}
		P1_8d_numbers [wei] &= B01111111;
	}*/
	unsigned char wei=0;
	while (num>0){
		P1_8d_numbers [wei] = num % 10;
		num /= 10;
		++ wei;
	}
}
void main () {
	P1 = 0x00;
	LED = 0;
	
	// turn2Numbers (30);
	while (1) {
		if (cnt == 0) {
			for (i = 8; i < 0xe; i ++) {
				// P1_8e_numbers[i-8] = rand()&0xf;
				turn2Numbers (rand()%10000);
			}
		}
		
		++ cnt;
		if (cnt > 100) {
			cnt = 0;
		}
		show_P1_8d ();
	}
}