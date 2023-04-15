#include <reg52.h>

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;


void main () {
	unsigned int i = 0;
	unsigned char cnt = 0;
	int dir = 1;
	unsigned int count = 0;
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	LED = 0;
	TR0 = 1;
	while (1) {
		// P0 = ~(0x01 << cnt);
		P0 = cnt;
						   
		// while (TH0!=0xff);
		while (count <= 0xfffffff) {
			if (TH0 == 0xff) count ++;
		}
		count = 0;
		cnt += dir;
		dir ++;
		// cnt = cnt + dir;
		if (cnt >= 7 && dir == 1) {
			dir = -1;
		}
		if (cnt <= 0 && dir == -1) {
			dir = 1;
		}
			
	}
}