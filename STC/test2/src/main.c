#define __TBZ_LED88_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
// #define __TBZ_RESET_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#include "myheader.h"

__pdata unsigned char animation [40] = {
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0,
	0xF8,0xFD,0xFD,0xFD,0xFD,0xFD,0xDD,0xC0,
	0xCC,0xED,0xED,0xE1,0xED,0xED,0xED,0xCC,
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0
};
int scene = 0;
int number = 50;
char toUp = 1, toDown = 0;
char tick = 0;
char tick1 = 0;
char tick2 = 50;
char tick3 = 0;

void timer1 (void) __interrupt (3);

void main () {
	/* timer 设置 */
	EA = 1;      // 总中断使能
	ET1 = 1;     // timer1 中断使能
	TMOD = 0x01; // 高低位联合的计时器
	TH1 = 0x26;
	TL1 = 0x00;
	TR1 = 1;
	/*  主循环  */
	while (1) {
		P0 = 0xff;   // 消隐
		switch (scene) {
			case 1: {
				switch (tick1) {  // 显示流水灯
					case 0: P1 = 0xe; P0 = B01111110; break;
					case 1: P1 = 0xe; P0 = B10111101; break;
					case 2: P1 = 0xe; P0 = B11011011; break;
					case 3: P1 = 0xe; P0 = B11100111; break;
					case 4: P1 = 0xe; P0 = B11011011; break;
					case 5: P1 = 0xe; P0 = B10111101; break;
				}
				if (tick) {
					tick1 = (tick1+1)%6;
					tick = 0;
				}
			} break;
			case 2: {
				show_P1_8d ();
				P1_8d_numbers [3] = tick2/10;
				P1_8d_numbers [2] = tick2%10;
				if (tick) {
					tick2 ++;
					tick = 0;
					if (tick2 > 55) tick2 = 50;
				}
			} break;
			case 3: {
				show_P1_07 ();
				if (tick) {
					tick = 0;
					int i = 0;
					for (i = tick3; i < tick3+8; i++) {
						P1_07 [i-tick3] = animation [i];
					}
					tick3 = (tick3+1) % 24;
				}
			} break;
		}
		/**********下面开始按键处理************/
		char k = keystate();         // 返回第一个被扫描到的按键（没有采用书上的做法
		if (k == 0xff) {        // 如果什么也没有按下，表示当前为弹起状态
			toUp = 1;
		} else if (toUp == 1) { // 如果当前是弹起状态
			toUp = 0;           // 因为有按键被按下，所以标记当前为按下状态
			tick = 0;
			tick1 = 0;
			tick2 = 50;
			tick3 = 0;
			TH1 = 0x26;
			TL1 = 0x00;
			P1_8d_numbers [2] = 0x11;
			P1_8d_numbers [3] = 0x11;
			switch (k) {        // 使用 switch 处理当前按键
				case VK_1: {  // 当按下 1 键
					scene = 1;
				} break;
				case VK_2: {  // 当按下 2 键
					scene = 2;
				} break;
				case VK_3: {  // 当按下 3 键
					scene = 3;
				} break;
			}
		}
	}
}



// 1 计时器的中断函数
void timer1 (void) __interrupt (3) {
	static char count = 0;
	TR1 = 0;            // 暂停计时器
	if (count >= 100) { // 每一秒
		count = 0;      // 清空计数器
		tick = 1;
		-- number;      // 数码管上的数字 -1
	}
	++count;            // 计数器 +1

	TH1 = 0x26;         // 重新开始计时
	TL1 = 0x00;
	TR1 = 1;
}
