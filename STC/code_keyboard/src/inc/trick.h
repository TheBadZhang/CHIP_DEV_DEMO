#ifndef __TBZ_TRICK_H_
#define __TBZ_TRICK_H_
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

#endif