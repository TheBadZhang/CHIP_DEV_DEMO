/**
 * @file I2C 读取 HDC1080 数据实例
 * @author 张乐辉
 */

#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_HDC1080_ENABLE_
#define __TBZ_EEPROM_ENABLE_
#define __TBZ_SMS0801_ENABLE_
#include "myheader.h"

char scene = 0;
int number = 50;
char toUp = 1, toDown = 0;
char tick = 0;
char tick1 = 0;

int addr = 0;

void timer1 (void) __interrupt (3);
void workProcess ();
void keyProcess ();

void main () {
	/* timer 设置 */
	EA = 1;      // 总中断使能
	ET1 = 1;     // timer1 中断使能
	TMOD = 0x01; // 高低位联合的计时器
	TH1 = 0x26;
	TL1 = 0x00;
	TR1 = 1;
	/*  */
	initHDC1080 ();
	scene = VK_1;
	memset (num_ram, 8, 0x10);
	delay (1500);
	/*  主循环  */
	while (1) {
		P0 = 0xff;   // 消隐
		// workProcess ();
		// keyProcess ();  // 按键处理
	}
}

/**
 * @brief 根据 scene 的值，不断执行其中的操作
 * @note 因为是不断执行的，所以是反复，如果是希望一次响应，可以在 keyProcess 中处理
 */
void workProcess () {
	switch (scene) {
		case VK_1: {
			if (tick) {
				turn2Numbers (HDC1080_Temperature ());
				tick = 0;
			}
		} break;
		case VK_2: {
			if (tick) {
				turn2Numbers (eeReadByte (0));
				// turn2Numbers (I2C_Addressing (EEPROM_ADDR>>1));
				tick = 0;
			}
		} break;
		case VK_3: {
			if (tick) {
				turn2Numbers (I2C_Addressing (HDC1080_I2C_ADDR>>1));
				tick = 0;
			}
		} break;
		case VK_4: {
			if (tick) {
				SMS0801_t2n (HDC1080_Temperature ());
				transram ();
				tick = 0;
			}
		}
	}
	show_P1_8d ();
}

/**
 * @brief 按键处理函数
 */
void keyProcess () {
	
	unsigned char k = keystate();    // 返回第一个被扫描到的按键（没有采用书上的做法
	if (k == 0xff) {        // 如果什么也没有按下，表示当前为弹起状态
		toUp = 1;
	} else if (toUp == 1) { // 如果当前是弹起状态
		toUp = 0;           // 因为有按键被按下，所以标记当前为按下状态
		tick = 0;
		TH1 = 0x26;
		TL1 = 0x00;
		scene = k;
		memset (P1_8d, 6, 0x11);
		switch (k) {
			case VK_UP: {
				addr ++;
			} break;
			case VK_DOWN: {
				addr --;
			} break;
		}
	}
}
// 1 计时器的中断函数
void timer1 (void) __interrupt (3) {
	static char count = 0;
	TR1 = 0;            // 暂停计时器
	if (count >= 200) { // 每一秒
		count = 0;      // 清空计数器
		tick = 1;
	}
	++count;            // 计数器 +1

	TH1 = 0x26;         // 重新开始计时
	TL1 = 0x00;
	TR1 = 1;
}
