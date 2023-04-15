
// 引入 51 单片机中对针脚的定义
#ifdef __SDCC
	#include <8052.h>
	#define        sbit __sbit
	#define         bit __bit
	#define   interrupt __interrupt
	// #define  sfr
#else
	#include <reg52.h>
	#define      __sbit sbit
	#define       __bit bit
	#define __interrupt interrupt
#endif

// 特殊语法

#define _nop_() __asm nop __endasm
#define FOR(i,x) for (i = 0; i < x; ++i)
#define DO  {
#define END }

#define HIGH 1
#define LOW  0
#define set(v) v = HIGH
#define clr(v) v = LOW

#define true 1
#define True 1
#define TRUE 1
#define false 0
#define False 0
#define FALSE 0
#define bool __bit


#define u32 unsigned long
#define u16 unsigned short
#define u8  unsigned char
#define uc  unsigned char


/**
 * @brief 一个简单的延迟函数
 * @param x10us 延时的时间
 * 	延时时间相当于 参数*10 个微秒
 * @return void
 */
void delay(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}


#ifndef __TBZ_MATH_H_
#define __TBZ_MATH_H_

//m^n函数
u32 pow (u8 m,u8 n) {
	u32 result = 1;
	while (n--)
        result *= m;
	return result;
}


#endif


/**************************/
// 按键处理
#define VK_NULL  '\0'
#define VK_UP    0x26
#define VK_LEFT  0x25
#define VK_DOWN  0x28
#define VK_ESC   0x1b
#define VK_ENTER 0x0d
#define VK_RIGHT 0x27
/**
 * @brief 获取当前按键，从上到下扫描
 * @return 返回当前的按键值
 */
unsigned char keystate (void) {
	P2 = 0x7e;
	if (!P2_1) return VK_LEFT ;
	if (!P2_2) return VK_DOWN ;
	if (!P2_3) return VK_RIGHT;
	if (!P2_4) return VK_ESC  ;
	if (!P2_5) return VK_UP   ;
	if (!P2_6) return VK_ENTER;
	return VK_NULL;
}
char isUp = 1;   // 只响应一次
/******************************/

// signed char light_value [8] = { 0, 2, 6, 10, 12, 14,16, 20 };   // LED 灯的 占空比（百分数）
signed char light_value [8] = { 0 };   // LED 灯的 占空比（百分数）
unsigned int freq = 200;      // 频率（一秒中有多少个周期）
unsigned int timeDuration;    // 当前频率下定时器所需要的数值
unsigned int keyboard_timeDuration;
signed char duty_max = 20;  // 一周期定时器响应的次数（用于控制亮灭
                              // 否则应当手动计算当前所需的延时时长
							  // 但是因为要同时控制八盏灯的亮暗，只能做满 duty_max 次
char tick;
int ii, jj;   // FOR 循环所用变量
unsigned int calcCurrentDuration (unsigned int freq, unsigned int duty_max) {
                              // 用于计算当前的
	return 0xffff-(11059200/freq/duty_max);
}

#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);

void draw (void);        // 绘制界面，显示 OLED 内容
void keyboard (void);    // 按键输入，不包括旋转编码器的处理
void KEY_INPUT (void) __interrupt (1);     // 定时按键输入处理（？
void LED_SHOWUP (void) __interrupt (3);    // LED PWM 调光定时器函数
void main () {
	/**********初始化部分*************/
    // 在单片机上电后或者复位后调用一次
	TMOD = 0x00;         // 0、1 定时器都采用 16 位计时
	EXEN2 = 0x00;
	// PT2 = 0;
	IP = 0x0a;
	EA = 1;              // 总中断使能

	timeDuration = calcCurrentDuration (freq, duty_max);  // PWM 一周期对应的计时器数值
	keyboard_timeDuration = 10204;    // 每 5ms 处理一次按键
	ET0 = 1;        // 定时器0 中断使能
	ET1 = 1;        // 定时器1 中断使能
	ET2 = 1;        // 定时器2 中断使能

	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
	ASSIGNMENT16 (TH1, TL1, timeDuration);

	FOR(ii, 8) light_value[ii] = 1;


	TR0 = 1;        // 启动 定时器0
	TR1 = 1;        // 启动 定时器1


	while (1);      // 使程序不断运行


}

void KEY_INPUT (void) __interrupt (1) {
	unsigned char k = keystate();    // 返回第一个被扫描到的按键（没有采用书上的做法
	static unsigned int flag = 0;    // 0 代表当前是第一次读到这个按键，需要在下一次再进行处理
	static int fi = 20;
	flag ++;
	if (flag > 130) isUp = 1;
	if (k == VK_NULL) {              // 如果什么也没有按下，表示当前为弹起状态
		isUp = 1;
		flag = 0;
		fi = 20;
	} else if (isUp == 1) {          // 如果当前是弹起状态
		if (flag > 1) {
			if (flag > 130) {
				if (flag % fi) goto end;
				else fi--;
				if (fi < 1) fi = 1;
			}
			isUp = 0;                // 因为有按键被按下，所以标记当前为按下状态
			switch (k) {
				case VK_LEFT: {
					if (--freq < 1) freq = 1;
				} break;
				case VK_RIGHT: {
					if (++freq > 20000) freq = 20000;
				} break;
				case VK_UP: {
					if (++light_value[0] > duty_max)
						light_value[0] = duty_max;
				} break;
				case VK_DOWN: {
					if (--light_value[0] < 0)
						light_value[0] = 0;
				} break;
			}
			timeDuration = calcCurrentDuration(freq, duty_max);
		}
	}
end:
	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
}


void LED_SHOWUP (void) __interrupt (3) {
	static signed char count = 0;       // 占空比计数
	if (count >= duty_max) count = 0;   // 达到设定的次数后重新计数

	P0_0 = count >= light_value[0];     // 如果当前 小于设定值，灯亮，否则，灭
	// P0_1 = count >= light_value[1];
	// P0_2 = count >= light_value[2];
	// P0_3 = count >= light_value[3];
	// P0_4 = count >= light_value[4];
	// P0_5 = count >= light_value[5];
	// P0_6 = count >= light_value[6];
	// P0_7 = count >= light_value[7];
	count ++;
	ASSIGNMENT16 (TH1, TL1, timeDuration);
}
