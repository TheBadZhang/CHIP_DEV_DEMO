#include "../inc/lcmlcd4.h"


/**
 * @brief 用于描述显示的内容
 */
uchar lcmlcd4_numcode [] = {
	~B01101011, ~B00010001, ~B01100111,  // 0 1 2
	~B01010111, ~B00011101, ~B01011110,  // 3 4 5
	~B01111110, ~B00010011, ~B01111111,  // 6 7 8
	~B00011111, ~B00111111, ~B01111100,  // 9 A b
	~B01101010, ~B01110101, ~B01101110,  // C d E
	~B00101110, ~B00000100, ~B00000000   // F -
};


/**
 * @brief 缓存当前显示的内容，因为一个液晶使用多个com进行显示，所以需要这个来缓存
 */
uchar lcmlcd4_numbuf [] = {
	~B0001, ~B0000, ~B0000, ~B0000
};


/**
 * @brief 显示内容
 */
void lcmlcd4_show (void) {
	static uchar i = 0;
	switch (i) {
		case 0: /*P1M1=0xff; P1M0=0x00; P1M1&=B11110111; P1M0|=~B11110111;*/ LCD4_COM4 = 1; LCD4_DATA = lcmlcd4_numbuf [0]; LCD4_COM1 = 1; i = 1; break;
		case 1: /*P1M1=0xff; P1M0=0x00; P1M1&=B11111011; P1M0|=~B11111011;*/ LCD4_COM1 = 1; LCD4_DATA = lcmlcd4_numbuf [1]; LCD4_COM2 = 1; i = 2; break;
		case 2: /*P1M1=0xff; P1M0=0x00; P1M1&=B11111101; P1M0|=~B11111101;*/ LCD4_COM2 = 1; LCD4_DATA = lcmlcd4_numbuf [2]; LCD4_COM3 = 1; i = 3; break;
		case 3: /*P1M1=0xff; P1M0=0x00; P1M1&=B11111110; P1M0|=~B11111110;*/ LCD4_COM3 = 1; LCD4_DATA = lcmlcd4_numbuf [3]; LCD4_COM4 = 1; i = 0; break;
	}
}


#define sub(buf,x) (buf[0]>>x)&0x3 | ((buf[1]>>x)&0x3)<<2 | ((buf[2]>>x)&0x3)<<4 | ((buf[3]>>x)&0x3)<<6

/**
 * @brief 将数字转换到缓存中
 * @param num 要显示的内容（暂不支持浮点数）[-999, 9999]
 */
void lcmlcd4_t2n (int num) {
	uchar i = 0;
	if (num < -999 || num > 9999) {
		lcmlcd4_numbuf [0] = lcmlcd4_numcode [0xE];
		lcmlcd4_numbuf [1] = lcmlcd4_numcode [0x0];
		lcmlcd4_numbuf [2] = lcmlcd4_numcode [0x0];
		lcmlcd4_numbuf [3] = lcmlcd4_numcode [0x0];
	} else {
		lcmlcd4_numbuf [0] = lcmlcd4_numcode [num % 10];
		lcmlcd4_numbuf [1] = lcmlcd4_numcode [(num/10)%10];
		lcmlcd4_numbuf [2] = lcmlcd4_numcode [(num/100)%10];
		if (num < 0) {
			lcmlcd4_numbuf [3] = lcmlcd4_numcode [0x10];
		} else {
			lcmlcd4_numbuf [3] = lcmlcd4_numcode [(num/1000)%10];
		}
	}
	uchar numbuf_copy [] = {
		lcmlcd4_numbuf [0], lcmlcd4_numbuf [1], lcmlcd4_numbuf [2], lcmlcd4_numbuf [3]
	};
	lcmlcd4_numbuf [0] = sub (numbuf_copy,0);
	lcmlcd4_numbuf [0] = sub (numbuf_copy,2);
	lcmlcd4_numbuf [0] = sub (numbuf_copy,4);
	lcmlcd4_numbuf [0] = sub (numbuf_copy,6);
}

#undef sub