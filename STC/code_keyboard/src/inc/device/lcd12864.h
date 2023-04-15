#ifndef __TBZ_LCD12864_H_
#define __TBZ_LCD12864_H_

#include "myheader.h"

#define uchar unsigned char
#define uint unsigned int

uchar code num[]={"0123456789 e:.-"};

#define RS   P1_0     //命令/数据选择
#define RW   P1_1     //读写口
#define E    P1_5     //使能端
#define PSB  1        //串并选择, 1并行，0，串行（金沙滩这里锁死了只有并行）

void lcd1864_delay(uint t) {
	uint i;
	while(t--)
		for(i=0;i<110;i++);
}

/**
 * @brief 检查LCD当前是否忙碌
 * @return 返回当前是否繁忙
 * @retval 1 不繁忙
 *         0 繁忙
 */
__bit busy() {
	__bit result;
	P0 = 0X00;
	RS = 0;			// 命令/数据选择,为 0 时选择命令
	RW = 1;			// 读/写选择，为 1 时选择读
	E  = 1;			// 使能
	delay(1);
	result = (bit)(P0&0x80); //查忙标志位，等待标志位为0，即表示写入完毕
	E = 0;			// 关闭读写
	return (result);
}
/**
 * @brief 向lcd写一命令
 * @param cmd 待写入的命令
 */
void wcode(uchar cmd) {
	while(busy());                   //查忙
	RS = 0;							 //命令/数据选择,为0时选择命令
	RW = 0;							 //读/写选择，为0时选择写
	E  = 0;
	_nop_();
	_nop_();
	P0 = cmd;                //送入命令
	delay(1);                //等待
	E = 1;
	delay(1);
	E = 0;
}
/**
 * @brief 向LCD写一数据
 */
void wdata(uchar dat) {
	while(busy());
	RS = 1;            //H为数据
	RW = 0;
	E  = 0;
	P0 = dat;
	delay(1);
	E = 1;
	delay(1);
	E = 0;
}
/**
 * @brief LCD初始化
 */
void initlcd() {
	// PSB = 1;       //设置为8BIT并口工作模式  H并行 L串行
	delay(10);
	wcode(0x34);
	delay(5);
	wcode(0x30);   //选择基本指令集
	delay(5);
	wcode(0x0c);   //开显示，无游标
	delay(5);
	wcode(0x01);   //清除显示，并且设定地址指针为00H
	delay(5);
	wcode(0x06);   //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位
}
/**
 * @brief 任意位置显示字符串
 * @param x 为横坐标
 * @param y 位纵坐标
 * @param s 表示指针，为数据的首地址
 */
void dis(uchar x,uchar y,uchar code* s) {
	switch(y) { //选择纵坐标
		case 0: wcode (0x80+x); break;  //第一行
		case 1: wcode (0x90+x); break;  //第二行
		case 2: wcode (0x88+x); break;  //第三行
		case 3: wcode (0x98+x); break;  //第四行
		default:break;
	}
	while(*s>0) {   //写入数据，直到数据为空
		wdata(*s);  //写数据
		delay(10);  //下一字符
		s++;
	}
}
void showGB(uchar *HZ) { //显示单个汉字
   wdata(HZ[0]);         //写入汉字高八位数据
   wdata(HZ[1]);         //写入低八位
}

void wrnum(uchar s) {
	wdata(num[s]);
	delay(1);
}



#endif