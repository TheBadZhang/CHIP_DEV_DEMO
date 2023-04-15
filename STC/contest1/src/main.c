/**
 * @file I2C 读取 HDC1080 数据实例
 * @author 张乐辉
 */

// #define __TBZ_LED7SEG_ENABLE_

#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_HDC1080_ENABLE_
#define __TBZ_SMS0801_ENABLE_
#include "myheader.h"

// 看门狗

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
	/* timer 设置 */
	// EA = 1;      // 总中断使能
	// ET1 = 1;     // timer1 中断使能
	// TMOD = 0x01; // 高低位联合的计时器
	// TH1 = 0x26;
	// TL1 = 0x00;
	// TR1 = 1;
	/* 看门狗设置 */
	/*  */
	initHDC1080 ();
			WDT_CONTR = B00111000;
	while (1) {
		// if (tick) {
			SMS0801_t2n (HDC1080_Temperature ());
			transram ();
			WDT_CONTR = B00111010;
			// PCON |= PD;    // 进入掉电模式
			// tick = 0;
		// }
		// show_P1_8d ();
	}
}

// 1 计时器的中断函数
// void timer1 (void) __interrupt (3) {
// 	static char count = 0;
// 	TR1 = 0;            // 暂停计时器
// 	if (count >= 20) { // 每一秒
// 		count = 0;      // 清空计数器
// 		tick = 1;
// 	}
// 	++count;            // 计数器 +1

// 	TH1 = 0x26;         // 重新开始计时
// 	TL1 = 0x00;
// 	TR1 = 1;
// }
