#ifndef __TBZ_LED7SEG_H_
#define __TBZ_LED7SEG_H_
// 在数码管上显示数字
char P1_8d_number[] = {
	// 0     1     2     3     4     5     6     7
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
	// 8     9     A     b     C     d     E     F
	0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,
	// .           n           -
	0x7f, 0xff, B11001000, B10111111
};

// 数码管对应位置上的数值
char P1_8d_numbers[] = {
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

// 往数码管上打印数字
void show_P1_8d (void) {
	// 8 9 a b c d
	for (i = 8; i < 0xe; i ++) {
		P0 = 0xff;
		P1 = i;
		P0 = P1_8d_number[P1_8d_numbers [i-8]];
		// P0 = P1_8e_numbers [i-8];
		delay (1);
	}
}

// 将整数切割到数组中
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
	j = 0;
	while (num>0){
		P1_8d_numbers [j] = num % 10;
		num /= 10;
		++ j;
	}
}

#endif