#define __TBZ_LED88_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
// #define __TBZ_RESET_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __SDCC
#include "myheader.h"

__pdata unsigned char animation [7][8] = {
	{
		B10000001,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B10000001
	}, {
		B11000011,
		B10000001,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B10000001,
		B11000011
	}, {
		B11100111,
		B11000011,
		B10000001,
		B00000000,
		B00000000,
		B10000001,
		B11000011,
		B11100111
	}, {
		B11111111,
		B11100111,
		B11000011,
		B10000001,
		B10000001,
		B11000011,
		B11100111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11100111,
		B11000011,
		B11000011,
		B11100111,
		B11111111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11111111,
		B11100111,
		B11100111,
		B11111111,
		B11111111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111
	}
};
int count = 0;
int chose = 0;
int number = 20;
int flag = 1;
char toUp = 1;
char toDown = 0;
char k;


void timer1 (void) __interrupt (3);
void timer2 (void) __interrupt (5);

void main () {
	//经过了计算，这个数值作为起点，
	// 能够得到一个较为准确的0.1秒计时
	P1_4 = 0;
	// TR0 = 1;
	EA = 1;      // 总中断使能
	ET1 = 1;     // timer1 中断使能
	ET2 = 1;
	TMOD = 0x01; // 高低位联合的计时器
	TR1 = 0;
	while (1) {
		turn2Numbers (number);  // 将数字转换成文本，存到对应的数组中
		show_P1_8d ();          // 显示数码管上的字
		P1 = 0xe;
		P0 = 0xff ^ (1 << chose) ^ (TR1 << 3);
		delay(1);
		P0 = 0xff;
		if (number < 0) {
			// if (flag) {
			// for (i = 0; i < 6; ++i) {
			// 	P1_8d_numbers [i] = 0x11;
			// }
			// 动画
			P1 = 0xe;
			for (i = 0; i < 8; ++i) {
				P0 = 1 << i;
				delay (1000);
			}
			for (i = 0; i < 8; ++i) {
				P0 = B10000000 >> i;
				delay (1000);
			}
			TR2 = 1;
			TH2 = 0xFC;
			TL2 = 0x67;
			for (j = 0; j < 7; ++j) {
				copy (P1_07, animation [j], 8);
				delay (10);
			}
			openBuzz (1808); 	// 蜂鸣器
			flag = 1;
			// TR2 = 0;     // 不再显示 LED88
		// } else {
		}
		/**********下面开始按键处理************/
		k = keystate();         // 返回第一个被扫描到的按键（没有采用书上的数据结构
		if (k == 0xff) {        // 如果什么也没有按下，表示当前为弹起状态
			toUp = 1;
		} else if (toUp == 1) { // 如果当前是弹起状态
			toUp = 0;           // 因为有按键被按下，所以标记当前为按下状态
			switch (k) {        // 使用 switch 处理当前按键
				case VK_ESC: {  // 当按下 ESC 键
					flag = 1;   // 忘记 flag 表示啥了
					chose = 0;  // 当前选择的位
					number = 20;// 初始化 number 为 20
					flag = 1;
					TR1 = 0;
					stopBuzz();
				} break;        //
				case VK_LEFT: { // 当按下 LEFT 键
					chose = (chose + 1) % 2;
								// 只有个位、十位可以选
				} break;
				case VK_RIGHT: {// 当按下 RIGHT 键
					chose = (chose + 1) % 2;
								// 只有个位、十位可以选
				} break;
				case VK_UP: {   // 当按下 UP 键
					if (chose) {// 根据当前所选择的位进行不同的操作
						number += 10;
					} else {    // 十位上 +10，个位上 +1
						number += 1;
					}
				} break;
				case VK_DOWN: { // 当按下 DOWN 键
					if (chose) {// 根据当前所选择的位进行不同的操作
						number -= 10;
					} else {    // 十位上 -10，个位上 -1
						number -= 1;
					}
				} break;
				case VK_ENTER: {// 当按下 ENTER 键
					TH1 = 0x26; // 开始计时
					TL1 = 0x00;
					TR1 = 1;
					flag = 0;
				}
			}
			if (number < 0) number = 0;  // 控制当前调整数字的范围
			else if (number > 99) number = 99;
		}
		// if (!flag) -- number;
	// }
	}
}



// 1 计时器的中断函数
void timer1 (void) __interrupt (3) {
	TR1 = 0;            // 暂停计时器
	if (count >= 100) { // 每一秒
		count = 0;      // 清空计数器
		-- number;      // 数码管上的数字 -1
	}
	++count;            // 计数器 +1

	TH1 = 0x26;         // 重新开始计时
	TL1 = 0x00;
	TR1 = 1;
}

void timer2 (void) __interrupt (5) {
	static unsigned char i = 0;   // 动态扫描的索引
	// static unsigned char index = 0
	TR2 = 0;
	P0 = 0xff;
	P1 = i;
	switch (i) {
		case 0: P0 = P1_07 [i]; break;
		case 1: P0 = P1_07 [i]; break;
		case 2: P0 = P1_07 [i]; break;
		case 3: P0 = P1_07 [i]; break;
		case 4: P0 = P1_07 [i]; break;
		case 5: P0 = P1_07 [i]; break;
		case 6: P0 = P1_07 [i]; break;
		case 7: P0 = P1_07 [i]; break;
	}
	delay(1);
	++ i;
	if (i > 7) {
		i = 0;
	}
	TH2 = 0xFC;
	TL2 = 0x67;
	TR2 = 1;
}
