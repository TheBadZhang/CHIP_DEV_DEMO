#ifndef __TBZ_BUZZ_H_
#define __TBZ_BUZZ_H_

#ifdef __TBZ_BUZZ_MUSIC_
int buzzzz [] = {
	544, 735, 992, 1339, 1808, 2440, 3294, 4447
};
#endif
// ��������������
#ifdef __SDCC
#define BUZZ P1_6
#else
sbit BUZZ = P1^6;
#endif
unsigned char T0RL = 0, T0RH = 0;

/**
 * @brief ��ָ��Ƶ������������
 * @param frequ ������������������Ƶ��
 * @return void
 */
void openBuzz (unsigned int frequ) {
	// ��������Ķ�ʱ������ֵ
	unsigned int reload;
	// �ɸ���Ƶ�ʼ��㶨ʱ������ֵ
	reload = 65536 - (11059200/12)/(frequ*2);
	// 16 λ����ֵ�ֽ�Ϊ�ߵ������ֽ�
	TMOD = 0x01;
	T0RH = (unsigned char)(reload >> 8);
	T0RL = (unsigned char)(reload);
	// ����һ����Ҫ����ĳ�ֵ��ʹ��ʱ�����Ͼ���Ͷ�빤��
	TH0 = 0xFF;
	TL0 = 0xFE;
	// ʹ�� T0 �ж�
	ET0 = 1;
	// ���� T0 ��ʱ��
	TR0 = 1;
}
/**
 * @brief ��ͣ������
 */
void stopBuzz (void) {
	ET0 = 0;     // ���� T0 �ж�
	TR0 = 0;     // ���� T0 ��ʱ��
}

/**
 * @brief �������õ��ļ�ʱ��
 */
void timer0 () __interrupt 1 {
	// ���¼�������ֵ
	TH0 = T0RH;
	TL0 = T0RL;
	// ��ת��������������
	BUZZ = !BUZZ;
}
#endif
