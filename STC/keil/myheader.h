#ifndef __TBZ_HEADER_H_
#define __TBZ_HEADER_H_

#ifdef __TBZ_SPECIAL_
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tinibios.h>
#endif

// ���� 51 ��Ƭ���ж���ŵĶ���
#ifndef __SDCC
#include <reg52.h>
#define __sbit sbit
#define __bit bit
#else
#include <8052.h>
#define sbit __sbit
#define bit __bit
#endif

// ȫ�ֱ�����ʼ

unsigned int i, j;

// ȫ�ֱ�������

#ifdef __TBZ_BINARY_ENABLE_
// ��Ϊ c ���Բ�֧��������������
// Ϊ�˷�����д�����ú�ķ�ʽ�����������
#include "binary.h"
#endif
#ifdef __TBZ_ARGS_ENABLE_
// Ϊ 51 �ṩ�����ɱ亯������չ��
#include "myargs.h"
#endif
#ifdef __TBZ_EFFECT_ENABLE_
// ���ִ��������ݴ���ĺ���
#include "effect.h"
#endif
#ifdef __TBZ_LED7SEG_ENABLE_
// LED-7SEG �Ĳ�����װ
#include "led7seg.h"
#endif
#ifdef __TBZ_LED88_ENABLE_
// LED-8x8 �Ĳ�����װ
#include "led88.h"
#endif
#ifdef __TBZ_LCD1602_ENABLE_
// LCD1602 �Ĳ�����װ
#include "lcd1602.h"
#endif
#ifdef __TBZ_KEYBOARD_ENABLE_
// ���̲�����װ
#include "keyboard.h"
#endif
#ifdef __TBZ_BUZZ_ENABLE_
// ������������װ
#include "buzz.h"
#endif
#ifdef __TBZ_MOTOR_ENABLE_
// �������������װ
#include "motor.h"
#endif

#endif