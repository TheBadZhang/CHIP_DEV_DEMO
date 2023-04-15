#ifndef __TBZ_BUZZ_H_
#define __TBZ_BUZZ_H_

// 蜂鸣器控制引脚
sbit BUZZ = P1^6;
unsigned char T0RL = 0, T0RH = 0;
// 用指定频率启动蜂鸣器
void openBuzz (unsigned int frequ) {
	// 计算所需的定时器重载值
	unsigned int reload;
	// 由给定频率计算定时器重载值
	reload = 65536 - (11059200/12)/(frequ*2);
	// 16 位重载值分解为高低两个字节
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
// 暂停蜂鸣器
void stopBuzz (void) {
	// 禁用 T0 中断
	ET0 = 0;
	// 禁用 T0 计时器
	TR0 = 0;
}
void interruptTimer0 () {
	// 重新加载重载值
	TH0 = T0RH;
	TL0 = T0RL;
	// 反转蜂鸣器控制引脚
	BUZZ = ~BUZZ;
}
	
#endif
