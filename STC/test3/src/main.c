
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

// �����﷨

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
 * @brief һ���򵥵��ӳٺ���
 * @param x10us ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����*10 ��΢��
 * @return void
 */
void delay(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}


#ifndef __TBZ_MATH_H_
#define __TBZ_MATH_H_

//m^n����
u32 pow (u8 m,u8 n) {
	u32 result = 1;
	while (n--)
        result *= m;
	return result;
}


#endif


/**************************/
// ��������
#define VK_NULL  '\0'
#define VK_UP    0x26
#define VK_LEFT  0x25
#define VK_DOWN  0x28
#define VK_ESC   0x1b
#define VK_ENTER 0x0d
#define VK_RIGHT 0x27
/**
 * @brief ��ȡ��ǰ���������ϵ���ɨ��
 * @return ���ص�ǰ�İ���ֵ
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
char isUp = 1;   // ֻ��Ӧһ��
/******************************/

// signed char light_value [8] = { 0, 2, 6, 10, 12, 14,16, 20 };   // LED �Ƶ� ռ�ձȣ��ٷ�����
signed char light_value [8] = { 0 };   // LED �Ƶ� ռ�ձȣ��ٷ�����
unsigned int freq = 200;      // Ƶ�ʣ�һ�����ж��ٸ����ڣ�
unsigned int timeDuration;    // ��ǰƵ���¶�ʱ������Ҫ����ֵ
unsigned int keyboard_timeDuration;
signed char duty_max = 20;  // һ���ڶ�ʱ����Ӧ�Ĵ��������ڿ�������
                              // ����Ӧ���ֶ����㵱ǰ�������ʱʱ��
							  // ������ΪҪͬʱ���ư�յ�Ƶ�������ֻ������ duty_max ��
char tick;
int ii, jj;   // FOR ѭ�����ñ���
unsigned int calcCurrentDuration (unsigned int freq, unsigned int duty_max) {
                              // ���ڼ��㵱ǰ��
	return 0xffff-(11059200/freq/duty_max);
}

#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);

void draw (void);        // ���ƽ��棬��ʾ OLED ����
void keyboard (void);    // �������룬��������ת�������Ĵ���
void KEY_INPUT (void) __interrupt (1);     // ��ʱ�������봦����
void LED_SHOWUP (void) __interrupt (3);    // LED PWM ���ⶨʱ������
void main () {
	/**********��ʼ������*************/
    // �ڵ�Ƭ���ϵ����߸�λ�����һ��
	TMOD = 0x00;         // 0��1 ��ʱ�������� 16 λ��ʱ
	EXEN2 = 0x00;
	// PT2 = 0;
	IP = 0x0a;
	EA = 1;              // ���ж�ʹ��

	timeDuration = calcCurrentDuration (freq, duty_max);  // PWM һ���ڶ�Ӧ�ļ�ʱ����ֵ
	keyboard_timeDuration = 10204;    // ÿ 5ms ����һ�ΰ���
	ET0 = 1;        // ��ʱ��0 �ж�ʹ��
	ET1 = 1;        // ��ʱ��1 �ж�ʹ��
	ET2 = 1;        // ��ʱ��2 �ж�ʹ��

	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
	ASSIGNMENT16 (TH1, TL1, timeDuration);

	FOR(ii, 8) light_value[ii] = 1;


	TR0 = 1;        // ���� ��ʱ��0
	TR1 = 1;        // ���� ��ʱ��1


	while (1);      // ʹ���򲻶�����


}

void KEY_INPUT (void) __interrupt (1) {
	unsigned char k = keystate();    // ���ص�һ����ɨ�赽�İ�����û�в������ϵ�����
	static unsigned int flag = 0;    // 0 ����ǰ�ǵ�һ�ζ��������������Ҫ����һ���ٽ��д���
	static int fi = 20;
	flag ++;
	if (flag > 130) isUp = 1;
	if (k == VK_NULL) {              // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
		isUp = 1;
		flag = 0;
		fi = 20;
	} else if (isUp == 1) {          // �����ǰ�ǵ���״̬
		if (flag > 1) {
			if (flag > 130) {
				if (flag % fi) goto end;
				else fi--;
				if (fi < 1) fi = 1;
			}
			isUp = 0;                // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
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
	static signed char count = 0;       // ռ�ձȼ���
	if (count >= duty_max) count = 0;   // �ﵽ�趨�Ĵ��������¼���

	P0_0 = count >= light_value[0];     // �����ǰ С���趨ֵ��������������
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
