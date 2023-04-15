#include "ttp229.h"


/**
 * @brief 获取触控键盘的数据
 * @return 返回获取到的按键数据
 * @retval 十六位整形，一个位对应一个按键
 */
unsigned int TTP229B_get (void) {
	uchar i;
	uint key = 0x0000;

	SDA = 1;            // 拉高 SDA 准备接收数据
	delay1ms (100);     // 等待一百毫秒

	FOR (i, 16) {
		SCL = 1;
		delay (10);
		SCL = 0;
		delay(10);
		key |= (SDA<<i);
	}
	key = ~key;
	delay1ms(32);

	switch (key) {
		case 0x0001: return VK_1;
		case 0x0002: return VK_2;
		case 0x0004: return VK_3;
		case 0x0008: return VK_A;

		case 0x0010: return VK_4;
		case 0x0020: return VK_5;
		case 0x0040: return VK_6;
		case 0x0080: return VK_B;

		case 0x0100: return VK_7;
		case 0x0200: return VK_8;
		case 0x0400: return VK_9;
		case 0x0800: return VK_C;

		case 0x1000: return VK_STAR;
		case 0x2000: return VK_0;
		case 0x4000: return VK_SHARP;
		case 0x8000: return VK_D;
	}
	return key;
}