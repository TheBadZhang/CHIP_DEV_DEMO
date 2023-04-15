#ifndef __TBZ_BUZZ_H_
#define __TBZ_BUZZ_H_

#ifdef __TBZ_BUZZ_MUSIC_
int buzzzz [] = {
	544, 735, 992, 1339, 1808, 2440, 3294, 4447
};
#endif
// 蜂鸣器控制引脚
#ifdef __SDCC
#define BUZZ P1_6
#else
sbit BUZZ = P1^6;
#endif
unsigned char T0RL = 0, T0RH = 0;

/**
 * @brief 用指定频率启动蜂鸣器
 * @param frequ 蜂鸣器产生的声音的频率
 * @return void
 */
void openBuzz (unsigned int frequ) {
	// 计算所需的定时器重载值
	unsigned int reload;
	// 由给定频率计算定时器重载值
	reload = 65536 - (11059200/12)/(frequ*2);
	// 16 位重载值分解为高低两个字节
	TMOD = 0x01;
	T0RH = (unsigned char)(reload >> 8);
	T0RL = (unsigned char)(reload);
	// 设置一个快要溢出的初值，使定时器马上就能投入工作
	TH0 = 0xFF;
	TL0 = 0xFE;
	// 使能 T0 中断
	ET0 = 1;
	// 启动 T0 计时器
	TR0 = 1;
}
/**
 * @brief 暂停蜂鸣器
 */
void stopBuzz (void) {
	ET0 = 0;     // 禁用 T0 中断
	TR0 = 0;     // 禁用 T0 计时器
}

/**
 * @brief 蜂鸣器用到的计时器
 */
void timer0 () __interrupt 1 {
	// 重新加载重载值
	TH0 = T0RH;
	TL0 = T0RL;
	// 反转蜂鸣器控制引脚
	BUZZ = !BUZZ;
}
#endif
