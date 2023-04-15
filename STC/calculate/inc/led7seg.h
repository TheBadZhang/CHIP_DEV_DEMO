#ifndef __TBZ_LED7SEG_H_
#define __TBZ_LED7SEG_H_

#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"

// ��������������ʾ����
unsigned char P1_8d_number[] = {
	// 0     1     2     3     4     5     6     7
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
	// 8     9     A     b     C     d     E     F
	0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,
	//.(10) (11)    n(12)     -(13)
	0x7f, 0xff, B11001000, B10111111// h
};

// ����ܶ�Ӧλ���ϵ���ֵ
unsigned char P1_8d [6] = {
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

/**
 * @brief ��������ϴ�ӡ����
 * @note ʹ�ö�̬ˢ�µķ�ʽˢ�������
 */
void show_P1_8d (void) {
	// P1 : 8 9 a b c d
	static char i = 8;
	P0 = 0xff;            // ÿ�ε��������������ˢ����һ�������
	P1 = i;               // ��Ҫ��֤���ε������������������̫��
	                      // �������ɲ��ɱ������˸
	P0 = P1_8d_number[P1_8d [i++ - 8]];
	if (i > 0xd) i = 8;
}

/**
 * @brief �������и������
 * @param num ����
 */
void turn2Numbers (int num) {
	int j;
	memset (P1_8d, 6, 0x11);   // ��յ�ǰ����
	if (num) for (j = 0; num > 0; ++ j){        // �����ݴ浽
		P1_8d [j] = num % 10;
		num /= 10;
	}
	else P1_8d [0] = 0;
}

#endif