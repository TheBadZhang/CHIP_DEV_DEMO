#ifndef __TBZ_LED7SEG_H_
#define __TBZ_LED7SEG_H_

#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"

// 查表在数码管上显示数字
unsigned char P1_8d_number[] = {
	// 0     1     2     3     4     5     6     7
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
	// 8     9     A     b     C     d     E     F
	0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,
	//.(10) (11)    n(12)     -(13)
	0x7f, 0xff, B11001000, B10111111// h
};

// 数码管对应位置上的数值
unsigned char P1_8d [6] = {
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

/**
 * @brief 往数码管上打印数字
 * @note 使用动态刷新的方式刷新数码管
 */
void show_P1_8d (void) {
	// P1 : 8 9 a b c d
	static char i = 8;
	P0 = 0xff;            // 每次调用这个函数都会刷新下一个数码管
	P1 = i;               // 需要保证两次调用这个函数并不会间隔太多
	                      // 否则会造成不可避免的闪烁
	P0 = P1_8d_number[P1_8d [i++ - 8]];
	if (i > 0xd) i = 8;
}

/**
 * @brief 将整数切割到数组中
 * @param num 整数
 */
void turn2Numbers (int num) {
	int j;
	memset (P1_8d, 6, 0x11);   // 清空当前数据
	if (num) for (j = 0; num > 0; ++ j){        // 将数据存到
		P1_8d [j] = num % 10;
		num /= 10;
	}
	else P1_8d [0] = 0;
}

#endif