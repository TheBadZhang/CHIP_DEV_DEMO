/**
 * @file I2C ��ȡ HDC1080 ����ʵ��
 * @author ���ֻ�
 */

#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_HDC1080_ENABLE_
#define __TBZ_EEPROM_ENABLE_
#define __TBZ_SMS0801_ENABLE_
#include "myheader.h"

char scene = 0;
int number = 50;
char toUp = 1, toDown = 0;
char tick = 0;
char tick1 = 0;

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
	initHDC1080 ();
	scene = VK_1;
	memset (num_ram, 8, 0x10);
	delay (1500);
	/*  ��ѭ��  */
	while (1) {
		P0 = 0xff;   // ����
		// workProcess ();
		// keyProcess ();  // ��������
	}
}

/**
 * @brief ���� scene ��ֵ������ִ�����еĲ���
 * @note ��Ϊ�ǲ���ִ�еģ������Ƿ����������ϣ��һ����Ӧ�������� keyProcess �д���
 */
void workProcess () {
	switch (scene) {
		case VK_1: {
			if (tick) {
				turn2Numbers (HDC1080_Temperature ());
				tick = 0;
			}
		} break;
		case VK_2: {
			if (tick) {
				turn2Numbers (eeReadByte (0));
				// turn2Numbers (I2C_Addressing (EEPROM_ADDR>>1));
				tick = 0;
			}
		} break;
		case VK_3: {
			if (tick) {
				turn2Numbers (I2C_Addressing (HDC1080_I2C_ADDR>>1));
				tick = 0;
			}
		} break;
		case VK_4: {
			if (tick) {
				SMS0801_t2n (HDC1080_Temperature ());
				transram ();
				tick = 0;
			}
		}
	}
	show_P1_8d ();
}

/**
 * @brief ����������
 */
void keyProcess () {
	
	unsigned char k = keystate();    // ���ص�һ����ɨ�赽�İ�����û�в������ϵ�����
	if (k == 0xff) {        // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
		toUp = 1;
	} else if (toUp == 1) { // �����ǰ�ǵ���״̬
		toUp = 0;           // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
		tick = 0;
		TH1 = 0x26;
		TL1 = 0x00;
		scene = k;
		memset (P1_8d, 6, 0x11);
		switch (k) {
			case VK_UP: {
				addr ++;
			} break;
			case VK_DOWN: {
				addr --;
			} break;
		}
	}
}
// 1 ��ʱ�����жϺ���
void timer1 (void) __interrupt (3) {
	static char count = 0;
	TR1 = 0;            // ��ͣ��ʱ��
	if (count >= 200) { // ÿһ��
		count = 0;      // ��ռ�����
		tick = 1;
	}
	++count;            // ������ +1

	TH1 = 0x26;         // ���¿�ʼ��ʱ
	TL1 = 0x00;
	TR1 = 1;
}
