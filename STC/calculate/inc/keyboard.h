#ifndef __TBZ_KEYBOARD_H_
#define __TBZ_KEYBOARD_H_
#include "keyboard_vk.h"

// 但是这里一直有的问题是，书上写得都是各种使用 switch
// 用那种方式营造了一种 伪 并行 的程序,每一次按键读取都不会要很久
// 但是至多会需要四次进入中断函数才可以正确地读出一个按键
// 好处是对程序别的部分影响较小
#ifdef __SDCC
/**
 * @brief 获取当前按键，从上到下扫描
 * @return 返回当前的按键值
 */
unsigned char keystate (void) {
	P2 = 0xff;
	P2_3 = 0; 
	if (!P2_4) return VK_1;   // 这个地方好淦，我写了 VK0，结果找 bug 找了半天……
	if (!P2_5) return VK_2;
	if (!P2_6) return VK_3;
	if (!P2_7) return VK_UP;
	P2_3 = 1;
	P2_2 = 0;
	if (!P2_4) return VK_4   ;
	if (!P2_5) return VK_5   ;
	if (!P2_6) return VK_6   ;
	if (!P2_7) return VK_LEFT;
	P2_2 = 1;
	P2_1 = 0;
	if (!P2_4) return VK_7   ;
	if (!P2_5) return VK_8   ;
	if (!P2_6) return VK_9   ;
	if (!P2_7) return VK_DOWN;
	P2_1 = 1;
	P2_0 = 0;
	if (!P2_4) return VK_0    ;
	if (!P2_5) return VK_ESC  ;
	if (!P2_6) return VK_ENTER;
	if (!P2_7) return VK_RIGHT;
	P2_0 = 1;
	return 0xff;
}
#else
/**
 * @brief 获取当前按键，从上到下扫描
 * @return 返回当前的按键值
 */
unsigned char keystate (void) {
	P2 = 0xff;
	P2^3 = 0; 
	if (!P2^4) return VK_1;   // 这个地方好淦，我写了 VK0，结果找 bug 找了半天……
	if (!P2^5) return VK_2;
	if (!P2^6) return VK_3;
	if (!P2^7) return VK_UP;
	P2^3 = 1;
	P2^2 = 0;
	if (!P2^4) return VK_4   ;
	if (!P2^5) return VK_5   ;
	if (!P2^6) return VK_6   ;
	if (!P2^7) return VK_LEFT;
	P2^2 = 1;
	P2^1 = 0;
	if (!P2^4) return VK_7   ;
	if (!P2^5) return VK_8   ;
	if (!P2^6) return VK_9   ;
	if (!P2^7) return VK_DOWN;
	P2^1 = 1;
	P2^0 = 0;
	if (!P2^4) return VK_0    ;
	if (!P2^5) return VK_ESC  ;
	if (!P2^6) return VK_ENTER;
	if (!P2^7) return VK_RIGHT;
	P2^0 = 1;
	return 0xff;
}
#endif


#endif