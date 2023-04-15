#ifndef __TBZ_HEADER_H_
#define __TBZ_HEADER_H_

/**
 * @brief �رն�������ؼ��ʼ�鱨��
 */
#include "lint.h"

#ifdef __TBZ_SPECIAL_
	#include <iso646.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <tinibios.h>
#endif

// ���� 51 ��Ƭ���ж���ŵĶ���
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

// ȫ�ֱ�����ʼ

// unsigned int i, j;

// ȫ�ֱ�������

#include "trick.h"


// ���������
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
// Ϊ 51 �ṩ�����ɱ亯������չ��
#ifdef __TBZ_ARGS_ENABLE_
	#include "myargs.h"
#endif
// ���ִ��������ݴ���ĺ���
#ifdef __TBZ_EFFECT_ENABLE_
	#include "effect.h"
#endif
/**
 * @brief һ���򵥵��ӳٺ���
 * @param m ��ʱ m ��ʱ��
 * @return void
 */
void delay(unsigned int m);
/**
 * @brief һ���򵥵��ӳٺ���
 * @param x10us ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����*10 ��΢��
 * @return void
 */
void delay10us(unsigned int x10us);
/**
 * @brief һ���򵥵��ӳٺ���
 * @param x1ms ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����������
 * @return void
 */
void delay1ms(unsigned int a);
// LED-7SEG������ܣ� �Ĳ�����װ
#ifdef __TBZ_LED7SEG_ENABLE_
	#include "./device/led7seg.h"
#endif
// LED-8x8 �Ĳ�����װ
#ifdef __TBZ_LED88_ENABLE_
	#include "./device/led88.h"
#endif
// ���̲�����װ
#ifdef __TBZ_KEYBOARD_ENABLE_
	#include "./device/keyboard.h"
#endif
// ������������װ
#ifdef __TBZ_BUZZ_ENABLE_
	#include "buzz.h"
#endif
// �������������װ
#ifdef __TBZ_MOTOR_ENABLE_
	#include "./device/28byj-48.h"
#endif
/* ͨѶЭ����ͷ�ļ� */
// uart ������װ
#ifdef __TBZ_I2C_ENABLE_
	#include "uart.h"
#endif
// I2C ������װ
#ifdef __TBZ_I2C_ENABLE_
	#include "i2c.h"
#endif
#ifdef __TBZ_SPI_ENABLE_
	#include "spi.h"
#endif
// 1-wire ����
#ifdef __TBZ_1WIRE_ENABLE_
	#include "1wire.h"
#endif


// LCD1602 �Ĳ�����װ
#ifdef __TBZ_LCD1602_ENABLE_
	#include "./device/lcd1602.h"
#endif
// EEPROM ������װ
#ifdef __TBZ_EEPROM_ENABLE_
	#include "eeprom.h"
#endif
// HDC1080 ������װ
#ifdef __TBZ_HDC1080_ENABLE_
	#include "./device/hdc1080.h"
#endif
// SMS0801 ������װ
#ifdef __TBZ_SMS0801_ENABLE_
	#include "device/sms0801.h"
#endif
#ifdef __TBZ_HT1621_ENABLE_
	#include "device/ht1621.h"
#endif
#ifdef __TBZ_MAX7219_ENABLE_
	#include "device/max7219.h"
#endif
#ifdef __TBZ_SSD1306_ENABLE_
	#include "device/ssd1306.h"
#endif
#ifdef __TBZ_OLED12864_ENABLE_
	#include "device/oled12864.h"
#endif
#ifdef __TBZ_LCD12864_ENABLE_
	#include "device/lcd12864.h"
#endif

#endif