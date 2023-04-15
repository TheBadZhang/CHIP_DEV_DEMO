#ifndef __TBZ_LCD1602_H_
#define __TBZ_LCD1602_H_

// ��ŵĶ���
#ifndef __SDCC
#define LCD1602_DB  = P0
sbit LCD1602_RS  = P1^0;
sbit LCD1602_RW  = P1^1;
sbit LCD1602_E   = P1^5;
sbit LCD1602_BLA = P2^6;
#else
#define LCD1602_DB  P0
#define LCD1602_RS  P1_0
#define LCD1602_RW  P1_1
#define LCD1602_E   P1_5
#define LCD1602_BLA P2_6
#endif
// ��ʼ��Һ�������ȴ�Һ��׼�����
void lcdWaitReady () {
	unsigned char sta;
	LCD1602_DB = 0xff;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do {
		LCD1602_E = 1;
		sta = LCD1602_DB;
		LCD1602_E = 0;
	} while (sta & 0x80);
}
// �� LCD1602 д��һ���ֽ����cmd Ϊ��д��ֵ
#ifdef __TBZ_ARGS_ENABLE_
void lcdWriteCmd (unsigned char cmd, ...) {
	va_list p_args;
	va_start (p_args, cmd);
	unsigned char idx, val;
	for (idx = 0; idx < cmd; ++idx) {
#else
// �� LCD1602 д��һ���ֽ����cmd Ϊ��д��ֵ
void lcdWriteCmd (unsigned char cmd) {
#endif
	lcdWaitReady ();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
// �� LCD1602 ָ��λ��д��һ���ַ�
void lcdWriteChar (unsigned char dat) {
	lcdWaitReady ();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
// ���õ�ǰ����
void lcdSetCursor (unsigned char x, unsigned char y) {
	unsigned char addr;
	if (y) { // �� y �� 0 ʱ�����ڶ���д�� 
		addr = 0x40 + x;
	} else { // ���򣬵�һ��
		addr = 0x00 + x;
	}
	// ���� RAM ��ַ
	lcdWriteCmd (addr | 0x80);
}

// �� LCD1602 ��������ֽ����޸�
void lcdPrint (unsigned char x, unsigned y, unsigned char *str) {
	P1 = B00010010; // ���� P1 ��ֵ��ʹ P0 �������õ���������
	lcdSetCursor (x, y);
	while (*str) {
		lcdWriteChar (*str++);
	}
}
// ��ʼ�� LCD1602
void initLCD1602 (void) {
	lcdWriteCmd (0x38);    // 16*2 ��ʾ, 5*7 ����8 λ���ݽӿ�
	lcdWriteCmd (0x0c);    // ��ʾ���������ر�
	lcdWriteCmd (0x06);    // ���ֲ�������ַ�Զ�+1
	lcdWriteCmd (0x01);    // ����
}

#undef LCD1602_DB
#endif