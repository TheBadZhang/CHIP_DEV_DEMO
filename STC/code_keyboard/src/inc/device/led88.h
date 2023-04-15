#ifndef __TBZ_LED88_H_
#define __TBZ_LED88_H_

#include "myheader.h"

#define __TBZ_TEST_
// 如果处于 DEBUG 阶段，则下面这些图形会被写入程序
#ifdef __TBZ_TEST_
	// 在点阵LED屏上显示一个爱心
	char P1_07_love[] = {
	#ifdef __TBZ_BINARY_H_
		B10111101, //    0         0
		B00011000, //  0 0 0     0 0 0
		B00000000, //  0 0 0 0 0 0 0 0
		B00000000, //  0 0 0 0 0 0 0 0
		B00000000, //  0 0 0 0 0 0 0 0
		B10000001, //    0 0 0 0 0 0
		B11000011, //      0 0 0 0
		B11100111  //        0 0
	#else
		~0x42, ~0xe7, ~0xff, ~0xff, ~0xff, ~0x7e, ~0x3c, ~0x18
	#endif
	};
	// 星星的数据
	char P1_07_star[] = {
	#ifdef __TBZ_BINARY_H_
		B11101111,
		B11100111,
		B11000011,
		B00000000,
		B11000011,
		B11000011,
		B10010011,
		B10111011
	#else
		0xef, 0xe7, 0xc3, 0x00, 0xc3, 0xc3, 0x93, 0xbb
	#endif
	};
#endif
// 在这修改显示的内容
unsigned char P1_07 [] = {
	0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff
};

/**
 * @brief 动态刷新显示 8*8
 */
void show_P1_07 (void) {
	static char i = 0;
	P0 = 0xff;
	P1 = i;
	P0 = P1_07 [i];
	i = (i+1) % 8;
}

#endif