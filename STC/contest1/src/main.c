/**
 * @file I2C ��ȡ HDC1080 ����ʵ��
 * @author ���ֻ�
 */

// #define __TBZ_LED7SEG_ENABLE_

#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_HDC1080_ENABLE_
#define __TBZ_SMS0801_ENABLE_
#include "myheader.h"

// ���Ź�

__sbit __at (0xE1) WDT_CONTR ;
__sbit __at (0xE1) PS0       ;
__sbit __at (0xE2) PS1       ;
__sbit __at (0xE1) PS2       ;
__sbit __at (0xE2) IDLE_WDT  ;
__sbit __at (0xE1) CLR_WDT   ;
__sbit __at (0xE2) EN_WDT    ;


// char tick = 0;


// void timer1 (void) __interrupt (3);

void main () {
	/* timer ���� */
	// EA = 1;      // ���ж�ʹ��
	// ET1 = 1;     // timer1 �ж�ʹ��
	// TMOD = 0x01; // �ߵ�λ���ϵļ�ʱ��
	// TH1 = 0x26;
	// TL1 = 0x00;
	// TR1 = 1;
	/* ���Ź����� */
	/*  */
	initHDC1080 ();
			WDT_CONTR = B00111000;
	while (1) {
		// if (tick) {
			SMS0801_t2n (HDC1080_Temperature ());
			transram ();
			WDT_CONTR = B00111010;
			// PCON |= PD;    // �������ģʽ
			// tick = 0;
		// }
		// show_P1_8d ();
	}
}

// 1 ��ʱ�����жϺ���
// void timer1 (void) __interrupt (3) {
// 	static char count = 0;
// 	TR1 = 0;            // ��ͣ��ʱ��
// 	if (count >= 20) { // ÿһ��
// 		count = 0;      // ��ռ�����
// 		tick = 1;
// 	}
// 	++count;            // ������ +1

// 	TH1 = 0x26;         // ���¿�ʼ��ʱ
// 	TL1 = 0x00;
// 	TR1 = 1;
// }
