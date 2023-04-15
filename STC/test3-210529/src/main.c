#define __TBZ_LED88_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
// #define __TBZ_RESET_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#include "myheader.h"

__pdata unsigned char animation [40] = {
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0,
	0xF8,0xFD,0xFD,0xFD,0xFD,0xFD,0xDD,0xC0,
	0xCC,0xED,0xED,0xE1,0xED,0xED,0xED,0xCC,
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0
};
int scene = VK_0;
int number = 50;
char toUp = 1, toDown = 0;
char tick = 0;
char tick1 = 0;
int tick2 = 5;
char tick3 = 0;
char vk2 = 0;

void timer1 (void) __interrupt (3);

void main () {
	/* timer ���� */
	EA = 1;      // ���ж�ʹ��
	ET1 = 1;     // timer1 �ж�ʹ��
	TMOD = 0x01; // �ߵ�λ���ϵļ�ʱ��
	TH1 = 0x26;
	TL1 = 0x00;
	TR1 = 1;


	P1_8d [5] = 11;
	P1_8d [4] = 8;
	P1_8d [3] = 0;
	P1_8d [2] = 5;
	/*  ��ѭ��  */
	while (1) {
		P0 = 0xff;   // ����
		switch (scene) {
			case VK_0: {
				show_P1_8d ();
			} break;
			case VK_1: {
				switch (tick1) {  // ��ʾ��ˮ��
					case 0: P1 = 0xe; P0 = B01111111; break;
					case 1: P1 = 0xe; P0 = B11111110; break;
					case 2: P1 = 0xe; P0 = B11011111; break;
					case 3: P1 = 0xe; P0 = B11111011; break;
					case 4: P1 = 0xe; P0 = B11101111; break;
					case 5: P1 = 0xe; P0 = B11110111; break;
				}
				if (tick) {
					tick1 = (tick1+1)%6;
					tick = 0;
				}
			} break;
			case VK_2: {
				show_P1_8d ();
				if (tick2 < 0) tick2 = 99;
				if (tick2 > 99) tick2 = 0;
				P1_8d [5] = tick2/10;
				P1_8d [4] = tick2%10;
				if (tick && vk2) {
					tick2 --;
					tick = 0;
				}
			} break;
			case VK_3: {
				show_P1_07 ();
				if (tick) {
					tick = 0;
					int i = 0;
					for (i = tick3; i < tick3+8; i++) {
						P1_07 [i-tick3] = animation [i];
					}
					tick3 = (tick3+1) % 24;
				}
			} break;
		}
		/**********���濪ʼ��������************/
		char k = keystate();         // ���ص�һ����ɨ�赽�İ�����û�в������ϵ�����
		if (k == 0xff) {        // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
			toUp = 1;
		} else if (toUp == 1) { // �����ǰ�ǵ���״̬
			toUp = 0;           // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
			tick = 0;
			tick1 = 0;
			// tick2 = 50;
			tick3 = 0;
			TH1 = 0x26;
			TL1 = 0x00;
			memset (P1_8d, 6,0x11);
			scene = k;
			switch (k) {
				case VK_UP: {
					tick2 ++;
					scene = VK_2;
				} break;
				case VK_DOWN: {
					tick2 --;
					scene = VK_2;
				} break;
				case VK_ENTER: {
					vk2 = !vk2;
					scene = VK_2;
				} break;
				default: {
					vk2 = 0;
				} break;
			}
		}
	}
}



// 1 ��ʱ�����жϺ���
void timer1 (void) __interrupt (3) {
	static char count = 0;
	TR1 = 0;            // ��ͣ��ʱ��
	if (count >= 100) { // ÿһ��
		count = 0;      // ��ռ�����
		tick = 1;
		-- number;      // ������ϵ����� -1
	}
	++count;            // ������ +1

	TH1 = 0x26;         // ���¿�ʼ��ʱ
	TL1 = 0x00;
	TR1 = 1;
}
