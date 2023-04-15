#define __TBZ_LED88_ENABLE_
#define __TBZ_BINARY_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
// #define __TBZ_RESET_ENABLE_
#define __TBZ_BUZZ_ENABLE_
#define __SDCC
#include "myheader.h"

__pdata unsigned char animation [7][8] = {
	{
		B10000001,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B10000001
	}, {
		B11000011,
		B10000001,
		B00000000,
		B00000000,
		B00000000,
		B00000000,
		B10000001,
		B11000011
	}, {
		B11100111,
		B11000011,
		B10000001,
		B00000000,
		B00000000,
		B10000001,
		B11000011,
		B11100111
	}, {
		B11111111,
		B11100111,
		B11000011,
		B10000001,
		B10000001,
		B11000011,
		B11100111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11100111,
		B11000011,
		B11000011,
		B11100111,
		B11111111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11111111,
		B11100111,
		B11100111,
		B11111111,
		B11111111,
		B11111111
	}, {
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111,
		B11111111
	}
};
int count = 0;
int chose = 0;
int number = 20;
int flag = 1;
char toUp = 1;
char toDown = 0;
char k;


void timer1 (void) __interrupt (3);
void timer2 (void) __interrupt (5);

void main () {
	//�����˼��㣬�����ֵ��Ϊ��㣬
	// �ܹ��õ�һ����Ϊ׼ȷ��0.1���ʱ
	P1_4 = 0;
	// TR0 = 1;
	EA = 1;      // ���ж�ʹ��
	ET1 = 1;     // timer1 �ж�ʹ��
	ET2 = 1;
	TMOD = 0x01; // �ߵ�λ���ϵļ�ʱ��
	TR1 = 0;
	while (1) {
		turn2Numbers (number);  // ������ת�����ı����浽��Ӧ��������
		show_P1_8d ();          // ��ʾ������ϵ���
		P1 = 0xe;
		P0 = 0xff ^ (1 << chose) ^ (TR1 << 3);
		delay(1);
		P0 = 0xff;
		if (number < 0) {
			// if (flag) {
			// for (i = 0; i < 6; ++i) {
			// 	P1_8d_numbers [i] = 0x11;
			// }
			// ����
			P1 = 0xe;
			for (i = 0; i < 8; ++i) {
				P0 = 1 << i;
				delay (1000);
			}
			for (i = 0; i < 8; ++i) {
				P0 = B10000000 >> i;
				delay (1000);
			}
			TR2 = 1;
			TH2 = 0xFC;
			TL2 = 0x67;
			for (j = 0; j < 7; ++j) {
				copy (P1_07, animation [j], 8);
				delay (10);
			}
			openBuzz (1808); 	// ������
			flag = 1;
			// TR2 = 0;     // ������ʾ LED88
		// } else {
		}
		/**********���濪ʼ��������************/
		k = keystate();         // ���ص�һ����ɨ�赽�İ�����û�в������ϵ����ݽṹ
		if (k == 0xff) {        // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
			toUp = 1;
		} else if (toUp == 1) { // �����ǰ�ǵ���״̬
			toUp = 0;           // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
			switch (k) {        // ʹ�� switch ����ǰ����
				case VK_ESC: {  // ������ ESC ��
					flag = 1;   // ���� flag ��ʾɶ��
					chose = 0;  // ��ǰѡ���λ
					number = 20;// ��ʼ�� number Ϊ 20
					flag = 1;
					TR1 = 0;
					stopBuzz();
				} break;        //
				case VK_LEFT: { // ������ LEFT ��
					chose = (chose + 1) % 2;
								// ֻ�и�λ��ʮλ����ѡ
				} break;
				case VK_RIGHT: {// ������ RIGHT ��
					chose = (chose + 1) % 2;
								// ֻ�и�λ��ʮλ����ѡ
				} break;
				case VK_UP: {   // ������ UP ��
					if (chose) {// ���ݵ�ǰ��ѡ���λ���в�ͬ�Ĳ���
						number += 10;
					} else {    // ʮλ�� +10����λ�� +1
						number += 1;
					}
				} break;
				case VK_DOWN: { // ������ DOWN ��
					if (chose) {// ���ݵ�ǰ��ѡ���λ���в�ͬ�Ĳ���
						number -= 10;
					} else {    // ʮλ�� -10����λ�� -1
						number -= 1;
					}
				} break;
				case VK_ENTER: {// ������ ENTER ��
					TH1 = 0x26; // ��ʼ��ʱ
					TL1 = 0x00;
					TR1 = 1;
					flag = 0;
				}
			}
			if (number < 0) number = 0;  // ���Ƶ�ǰ�������ֵķ�Χ
			else if (number > 99) number = 99;
		}
		// if (!flag) -- number;
	// }
	}
}



// 1 ��ʱ�����жϺ���
void timer1 (void) __interrupt (3) {
	TR1 = 0;            // ��ͣ��ʱ��
	if (count >= 100) { // ÿһ��
		count = 0;      // ��ռ�����
		-- number;      // ������ϵ����� -1
	}
	++count;            // ������ +1

	TH1 = 0x26;         // ���¿�ʼ��ʱ
	TL1 = 0x00;
	TR1 = 1;
}

void timer2 (void) __interrupt (5) {
	static unsigned char i = 0;   // ��̬ɨ�������
	// static unsigned char index = 0
	TR2 = 0;
	P0 = 0xff;
	P1 = i;
	switch (i) {
		case 0: P0 = P1_07 [i]; break;
		case 1: P0 = P1_07 [i]; break;
		case 2: P0 = P1_07 [i]; break;
		case 3: P0 = P1_07 [i]; break;
		case 4: P0 = P1_07 [i]; break;
		case 5: P0 = P1_07 [i]; break;
		case 6: P0 = P1_07 [i]; break;
		case 7: P0 = P1_07 [i]; break;
	}
	delay(1);
	++ i;
	if (i > 7) {
		i = 0;
	}
	TH2 = 0xFC;
	TL2 = 0x67;
	TR2 = 1;
}
