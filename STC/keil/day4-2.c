#include <reg52.h>

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

char P1_18_love[] = {
	~0x42, ~0xe7, ~0xff, ~0xff, ~0xff, ~0x7e, ~0x3c, ~0x18
};
/*
void delay (int us) {
	// 一个机器周期时长为 1.08507e-6 s
	// 即 1.08507us
	// 延迟之前进行换算即可
	// 但是因为是软浮点运算
	// 所以计算的时长也需要考虑
	static unsigned int THH0, T0;
	THH0 = 0;
	T0 = 0;
	TMOD  = 0x01;
	TR0   = 1;
	TF0   = 0;
	TH0 = 0;
	TL0 = 0;
	while (T0 < us) {
		if (TF0 == 1) {
			TF0 = 0;
			++THH0;
			TH0 = 0x00;
			TL0 = 0x00;
		}
		T0 = (THH0<<8)|(TH0<<4)|TL0;
	}
}*/
void delay(unsigned int x10us){
	unsigned int x,y;
	for(x=x10us;x>0;x--)
		for(y=11;y>0;y--);
}

void main () {
	unsigned int i = 0;
	unsigned char cnt = 0;
	int dir = 1;
	P1 = 0x00;
	LED = 0;
	while (1) {
		for (i = 0; i < 8; ++i) {
			P1 = i;
			P0 = P1_18_love [i];
			delay (620);
		}
		// 爱心
		/*
		for (P1=0;P1<0xf;++P1) {
			P0 = 0x00;
		}
		*/
		// 点亮全部
	}
}