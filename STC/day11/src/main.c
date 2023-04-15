#define __TBZ_LED88_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_EEPROM_ENABLE_
#include "myheader.h"

__pdata unsigned char animation [40] = {
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0,
	0xF8,0xFD,0xFD,0xFD,0xFD,0xFD,0xDD,0xC0,
	0xCC,0xED,0xED,0xE1,0xED,0xED,0xED,0xCC,
	0xE0,0xF6,0xF7,0xFB,0xFB,0xFD,0xED,0xE0
};
char scene = 0;
int number = 50;
char toUp = 1, toDown = 0;
char tick = 0;
char tick1 = 0;
char tick2 = 50;
char tick3 = 0;

int addr = 0;

void timer1 (void) __interrupt (3);
void workProcess ();
void keyProcess ();
void main () {
	/* timer ���� */
	EA = 1;      // ���ж�ʹ��
	ET1 = 1;     // timer1 �ж�ʹ��
	TMOD = 0x01; // �ߵ�λ���ϵļ�ʱ��
	TH1 = 0x26;
	TL1 = 0x00;
	TR1 = 1;
	/*  */
	scene = eeReadByte (0);
	tick1 = eeReadByte (1);
	tick2 = eeReadByte (2);
	tick3 = eeReadByte (3);
	number = eeReadByte (4);
	/*  ��ѭ��  */
	while (1) {
		P0 = 0xff;   // ����
		workProcess ();
		keyProcess ();  // ��������
	}
}

void workProcess () {
	switch (scene) {
		case VK_1: {
			switch (tick1) {  // ��ʾ��ˮ��
				case 0: P1 = 0xe; P0 = B01111110; break;
				case 1: P1 = 0xe; P0 = B10111101; break;
				case 2: P1 = 0xe; P0 = B11011011; break;
				case 3: P1 = 0xe; P0 = B11100111; break;
				case 4: P1 = 0xe; P0 = B11011011; break;
				case 5: P1 = 0xe; P0 = B10111101; break;
			}
			if (tick) {
				tick1 = (tick1+1)%6;
				tick = 0;
			}
		} break;
		case VK_2: {
			show_P1_8d ();
			P1_8d [3] = tick2/10;
			P1_8d [2] = tick2%10;
			if (tick) {
				tick2 ++;
				tick = 0;
				if (tick2 > 55) tick2 = 50;
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
		case VK_4: {
			show_P1_8d ();
			turn2Numbers (I2CAddressing (0x50));
		} break;
	}
	show_P1_8d ();
}

void keyProcess () {
	
	char k = keystate();         // ���ص�һ����ɨ�赽�İ�����û�в������ϵ�����
	if (k == 0xff) {        // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
		toUp = 1;
	} else if (toUp == 1) { // �����ǰ�ǵ���״̬
		toUp = 0;           // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
		switch (k) {
			case VK_UP: {
				addr ++;
			} break;
			case VK_DOWN: {
				addr --;
			} break;
			case VK_0: {
				scene = VK_3;
				eeWriteByte(0,  VK_3);
				eeWriteByte(1,  tick1);
				eeWriteByte(2,  tick2);
				eeWriteByte(3,  tick3);
				eeWriteByte(4, number);
			} break;
		}
		tick = 0;
		tick1 = 0;
		tick2 = 50;
		tick3 = 0;
		TH1 = 0x26;
		TL1 = 0x00;
		scene = k;
		memset (P1_8d, 6, 0x11);
		turn2Numbers (eeReadByte (0));
		I2CDelay ();
		eeWriteByte (0, k);
		switch (k) {
			case VK_UP: {
				addr ++;
			} break;
			case VK_DOWN: {
				addr --;
			} break;
			case VK_0: {
				scene = VK_3;
				eeWriteByte(0,  VK_3);
				eeWriteByte(1,  tick1);
				eeWriteByte(2,  tick2);
				eeWriteByte(3,  tick3);
				eeWriteByte(4, number);
			} break;
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
	}
	++count;            // ������ +1

	TH1 = 0x26;         // ���¿�ʼ��ʱ
	TL1 = 0x00;
	TR1 = 1;
}