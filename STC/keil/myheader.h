#ifndef __TBZ_HEADER_H_
#define __TBZ_HEADER_H_

#ifdef __TBZ_SPECIAL_
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tinibios.h>
#endif

// 引入 51 单片机中对针脚的定义
#ifndef __SDCC
#include <reg52.h>
#define __sbit sbit
#define __bit bit
#else
#include <8052.h>
#define sbit __sbit
#define bit __bit
#endif

// 全局变量开始

unsigned int i, j;

// 全局变量结束

#ifdef __TBZ_BINARY_ENABLE_
// 因为 c 语言不支持字面量二进制
// 为了方便书写，采用宏的方式定义二进制数
#include "binary.h"
#endif
#ifdef __TBZ_ARGS_ENABLE_
// 为 51 提供参数可变函数的扩展宏
#include "myargs.h"
#endif
#ifdef __TBZ_EFFECT_ENABLE_
// 文字处理与数据处理的函数
#include "effect.h"
#endif
#ifdef __TBZ_LED7SEG_ENABLE_
// LED-7SEG 的操作封装
#include "led7seg.h"
#endif
#ifdef __TBZ_LED88_ENABLE_
// LED-8x8 的操作封装
#include "led88.h"
#endif
#ifdef __TBZ_LCD1602_ENABLE_
// LCD1602 的操作封装
#include "lcd1602.h"
#endif
#ifdef __TBZ_KEYBOARD_ENABLE_
// 键盘操作封装
#include "keyboard.h"
#endif
#ifdef __TBZ_BUZZ_ENABLE_
// 蜂鸣器操作封装
#include "buzz.h"
#endif
#ifdef __TBZ_MOTOR_ENABLE_
// 步进电机操作封装
#include "motor.h"
#endif

#endif