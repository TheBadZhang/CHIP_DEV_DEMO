#include "../inc/myheader.h"


/**
 * @brief 一个简单的延迟函数
 * @param m 延时 m 个时钟
 * @return void
 */
void delay(unsigned int m) {
	while (m--);
}
/**
 * @brief 一个简单的延迟函数
 * @param x10us 延时的时间
 * 	延时时间相当于 参数*10 个微秒
 * @return void
 */
void delay10us(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}
/**
 * @brief 一个简单的延迟函数
 * @param x1ms 延时的时间
 * 	延时时间相当于 参数个毫秒
 * @return void
 */
void delay1ms(unsigned int a){
	uint i;
	while (--a!=0) for(i=1200;i>0;i--);   //1T单片机i=600，若是12T单片机i=125
}