#ifndef __TBZ_LCD1602_H_
#define __TBZ_LCD1602_H_

// ��ŵĶ���
#ifdef __SDCC
#define LCD1602_DB  P0
#define LCD1602_RS  P1_0
#define LCD1602_RW  P1_1
#define LCD1602_E   P1_5
#define LCD1602_BLA P2_6
#else
#define LCD1602_DB  = P0
sbit LCD1602_RS  = P1^0;
sbit LCD1602_RW  = P1^1;
sbit LCD1602_E   = P1^5;
sbit LCD1602_BLA = P2^6;
#endif
/**
 * @brief ��ʼ��Һ�������ȴ�Һ��׼�����
 */
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
#ifdef __TBZ_ARGS_ENABLE_
/**
 * @brief �� LCD1602 д��һ���ֽ�����
 * @param cmd ��д��ֵ
 */
void lcdWriteCmd (unsigned char cmd, ...) {
	va_list p_args;
	va_start (p_args, cmd);
	unsigned char idx, val;
	FOR (idx,cmd) {
		lcdWaitReady ();
		LCD1602_RS = 0;
		LCD1602_RW = 0;
		LCD1602_DB = cmd;
		LCD1602_E = 1;
		LCD1602_E = 0;
	}
#else
/**
 * @brief �� LCD1602 д��һ���ֽ�����
 * @param cmd ��д��ֵ
 */
void lcdWriteCmd (unsigned char cmd) {
	lcdWaitReady ();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
#endif
}
/**
 * @brief �� LCD1602 ָ��λ��д��һ���ַ�
 * @param dat д����ֽ�����
 */
void lcdWriteChar (unsigned char dat) {
	lcdWaitReady ();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
/**
 * @brief ���õ�ǰ����
 * @param x �ڼ���
 * @param y �ڼ���
 */
void lcdSetCursor (unsigned char x, unsigned char y) {
	// unsigned char addr;
	// if (y) { // �� y �� 0 ʱ�����ڶ���д�� 
	// 	addr = 0x40 + x;
	// } else { // ���򣬵�һ��
	// 	addr = 0x00 + x;
	// }
	// addr = x + ((y&1) << 6);
	// ���� RAM ��ַ
	lcdWriteCmd ((x + ((y&1) << 6)) | 0x80);
}

/**
 * @brief �� LCD1602 ��������ֽ����޸�
 * @param x �ڼ���
 * @param y �ڼ���
 * @param str Ҫд����ַ���
 */
void lcdPrint (unsigned char x, unsigned y, unsigned char* str) {
	P1 = B00010010; // ���� P1 ��ֵ��ʹ P0 �������õ���������
	while (*str) {
		lcdSetCursor (x, y++);
		lcdWriteChar (*str++);
	}
}
/**
 * @brief ��ʼ�� LCD1602
 */
void initLCD1602 (void) {
#ifdef __TBZ_ARGS_ENABLE_
	lcdWriteCmd (0x38, 0x0c, 0x06, 0x01);
#else
	lcdWriteCmd (0x38);    // 16*2 ��ʾ, 5*7 ����8 λ���ݽӿ�
	lcdWriteCmd (0x0c);    // ��ʾ���������ر�
	lcdWriteCmd (0x06);    // ���ֲ�������ַ�Զ�+1
	lcdWriteCmd (0x01);    // ����
#endif
}

#undef LCD1602_DB
#endif