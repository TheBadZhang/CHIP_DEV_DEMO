#ifndef __TBZ_BUZZ_H_
#define __TBZ_BUZZ_H_

// ��������������
sbit BUZZ = P1^6;
unsigned char T0RL = 0, T0RH = 0;
// ��ָ��Ƶ������������
void openBuzz (unsigned int frequ) {
	// ��������Ķ�ʱ������ֵ
	unsigned int reload;
	// �ɸ���Ƶ�ʼ��㶨ʱ������ֵ
	reload = 65536 - (11059200/12)/(frequ*2);
	// 16 λ����ֵ�ֽ�Ϊ�ߵ������ֽ�
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
// ��ͣ������
void stopBuzz (void) {
	// ���� T0 �ж�
	ET0 = 0;
	// ���� T0 ��ʱ��
	TR0 = 0;
}
void interruptTimer0 () {
	// ���¼�������ֵ
	TH0 = T0RH;
	TL0 = T0RL;
	// ��ת��������������
	BUZZ = ~BUZZ;
}
	
#endif
