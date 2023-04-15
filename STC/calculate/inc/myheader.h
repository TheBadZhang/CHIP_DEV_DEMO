#ifndef __TBZ_HEADER_H_
#define __TBZ_HEADER_H_

/**
 * @brief 关闭对于特殊关键词检查报错
 */
#include "lint.h"

#ifdef __TBZ_SPECIAL_
	#include <iso646.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <tinibios.h>
#endif

// 引入 51 单片机中对针脚的定义
#include "8052.h"
#define        sbit __sbit
#define         bit __bit
#define   interrupt __interrupt
// #define  sfr

#ifdef __STC15W4K32S
	__sfr __at(0xb3) P4M1;
	__sfr __at(0xb4) P4M0;
	__sfr __at(0xb1) P3M1;
	__sfr __at(0xb2) P3M0;
	__sfr __at(0x95) P2M1;
	__sfr __at(0x96) P2M0;
	__sfr __at(0x91) P1M1;
	__sfr __at(0x92) P1M0;
	__sfr __at(0x93) P0M1;
	__sfr __at(0x94) P0M0;
#endif

// 全局变量开始

// unsigned int i, j;

// 全局变量结束


// 特殊语法

/**
 * @brief 简写的 for 循环
 * @param i 要被循环的变量
 * @param x 循环次数 [0,x)
 */
#define FOR(i,x) for (i = 0; i < x; ++i)
#define DO  {
#define END }

#define HIGH 1
#define LOW  0

/**
 * @brief 设置一个引脚为高电位
 * @param v 要设置的引脚
 */
#define set(v) v = HIGH
/**
 * @brief 设置一个引脚为低电位
 * @param v 要设置的引脚
 */
#define clr(v) v = LOW


// 因为 c 语言不支持字面量二进制
// 为了方便书写，采用宏的方式定义二进制数
#define __TBZ_BINARY_ENABLE_
#ifdef __TBZ_BINARY_ENABLE_
	#include "binary.h"
#endif

#define INT0 0
#define TMR0 1
#define INT1 2
#define TMR1 3
#define TMR2 5

#include "mytype.h"

/**
 * @brief 逻辑与
 */
#define AND(a,b) ((a)&&(b))
/**
 * @brief 逻辑或
 */
#define OR(a,b) ((a)||(b))
/**
 * @brief 逻辑非
 */
#define NOT(x) (!(x))



/**
 * @brief 什么也不做的一条语句
 */
#define _nop_() __asm nop __endasm
/**
 * @brief 将一个int的数据赋值给高低两个字节
 * @param high 高字节
 * @param low 低字节
 * @param value 16-bit 的数据
 */
#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);
/**
 * @brief 将高低两个字节的数据合成为两个字节的int
 * @param high 高字节
 * @param low 低字节
 */
#define BIND2BYTE(high, low)\
	(high << 8) | low




// 软代码重载
#ifdef __TBZ_RESET_ENABLE_
	void reset (void){
		unsigned char code rst[] = {0xe4,0xc0,0xe0,0xc0,0xe0,0x32};
		(*((void (*)(void))(rst)))();
	}
#endif
// #define __TBZ_RANDOM_ENABLE_
#ifdef __TBZ_RANDOM_ENABLE_
	#include "random.h"
#endif
// 为 51 提供参数可变函数的扩展宏
#ifdef __TBZ_ARGS_ENABLE_
	#include "myargs.h"
#endif
// 文字处理与数据处理的函数
#ifdef __TBZ_EFFECT_ENABLE_
	#include "effect.h"
#endif
/**
 * @brief 一个简单的延迟函数
 * @param m 延时 m 个时钟
 * @return void
 */
void delay(unsigned int m);
/**
 * @brief 一个简单的延迟函数
 * @param x10us 延时的时间
 * 	延时时间相当于 参数*10 个微秒
 * @return void
 */
void delay10us(unsigned int x10us);
/**
 * @brief 一个简单的延迟函数
 * @param x1ms 延时的时间
 * 	延时时间相当于 参数个毫秒
 * @return void
 */
void delay1ms(unsigned int a);
// LED-7SEG（数码管） 的操作封装
#ifdef __TBZ_LED7SEG_ENABLE_
	#include "led7seg.h"
#endif
// LED-8x8 的操作封装
#ifdef __TBZ_LED88_ENABLE_
	#include "led88.h"
#endif
// 键盘操作封装
#ifdef __TBZ_KEYBOARD_ENABLE_
	#include "keyboard.h"
#endif
// 蜂鸣器操作封装
#ifdef __TBZ_BUZZ_ENABLE_
	#include "buzz.h"
#endif
// 步进电机操作封装
#ifdef __TBZ_MOTOR_ENABLE_
	#include "28byj-48.h"
#endif
/* 通讯协议类头文件 */
// uart 操作封装
#ifdef __TBZ_I2C_ENABLE_
	#include "uart.h"
#endif
// I2C 操作封装
#ifdef __TBZ_I2C_ENABLE_
	#include "i2c.h"
#endif
// 1-wire 操作
#ifdef __TBZ_1WIRE_ENABLE_
	#include "1wire.h"
#endif


// LCD1602 的操作封装
#ifdef __TBZ_LCD1602_ENABLE_
	#include "lcd1602.h"
#endif
// EEPROM 操作封装
#ifdef __TBZ_EEPROM_ENABLE_
	#include "eeprom.h"
#endif
// HDC1080 操作封装
#ifdef __TBZ_HDC1080_ENABLE_
	#include "hdc1080.h"
#endif
// SMS0801 操作封装
#ifdef __TBZ_SMS0801_ENABLE_
	#include "sms0801.h"
#endif
#ifdef __TBZ_HT1621_ENABLE_
	#include "ht1621.h"
#endif
#ifdef __TBZ_MAX7219_ENABLE_
	#include "max7219.h"
#endif
#ifdef __TBZ_SSD1306_ENABLE_
	#include "ssd1306.h"
#endif
#ifdef __TBZ_OLED12864_ENABLE_
	#include "oled12864.h"
#endif
#ifdef __TBZ_LCD12864_ENABLE_
	#include "lcd12864.h"
#endif

#endif