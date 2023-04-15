#include "myheader.h"

#define UART_RXD P3_0
#define UART_TXD P3_1

__bit RxdOrTxd = 0;  // ��ǰ��״̬�ǽ��ܻ��Ƿ���
__bit RxdEnd   = 0;  // ���ܽ�����־
__bit TxdEnd   = 0;  // ���ͽ�����־

unsigned char RxdBuf = 0;  // ���ջ�����
unsigned char TxdBuf = 0;  // ���ͻ�����

void ConfigUART (unsigned int baud);
void   StartTXD (unsigned char data);
void   StartRXD ();
void     RxdTxd () __interrupt 1;


void main () {
	EA = 1;             // �ж�ʹ���ܿ���
	ConfigUART (11520);  // ���ò�����Ϊ 9600

	while (1) {
		while (UART_RXD);     // �ȴ��������ų��ֵ͵�ƽ������ʼλ
		// ������һ����̵߳�ζ���ˣ����� ����汾�� c ��û�жԶ��߳��ж���֧��
		StartRXD ();          // ��������
		while (!RxdEnd);      // �ȴ��������
		StartTXD (RxdBuf+1);  // �����յ������ݷ��ͻ�ȥ
		while (!TxdEnd);      // �ȴ��������
	}
}

/* �������ú�����baud-ͨ�Ų����� */
void ConfigUART (unsigned int baud) {
	TMOD &= 0xF0;    // ��� T0 �� TMOD ����
	TMOD |= 0x02;    // ���� T0 �� TMOD Ϊ 0x02
	TH0 = 256 - (11059200/12)/baud;
	// ���� T0 ����ֵ������λ���ݵļ��
}
/* �������н��� */
void StartRXD () {
	TL0 = 256 - ((256-TH0) >> 1);
	// �������ο�˹�ض������ý���ʱ T0 Ϊ�������������
	ET0 = 1;    // T0 �ж�ʹ��
	TR0 = 1;    // ���� T0
	RxdEnd = 0; // ���õ�ǰ��״̬Ϊ����
	RxdOrTxd = 0; // ���õ�ǰ״̬Ϊ����
}
/* �������з��ͣ�data-�������ֽ����� */
void StartTXD (unsigned char data) {
	TxdBuf = data;   // ���������ݱ��浽���ͻ�����
	TL0 = TH0;       // T0 ��������
	ET0 = 1;         // T0 �ж�ʹ��
	TR0 = 1;         // ���� T0
	UART_TXD = 0;    // ������ʼλ
	TxdEnd = 0;      // ���㷢�ͽ�����־
	RxdOrTxd = 1;    // ���õ�ǰ��״̬Ϊ����
}
/* T0 �жϷ������������з��ͺͽ��� */
void RxdTxd () __interrupt 1 {
	static unsigned char cnt = 0;  // λ���ջ��ͼ���

	if (RxdOrTxd) { // ���з��ʹ���
		++cnt;

		if (cnt <= 8) {
			UART_TXD = TxdBuf & 0x01;
			TxdBuf >>= 1;
		} else if (cnt == 9) {
			UART_TXD = 1; // ����ֹͣλ
		} else {
			cnt = 0;      // ��λ������
			TR0 = 0;      // �ر� T0
			TxdEnd = 1;   // ���÷��ͽ�����־
		}
	} else { // ���н��ܴ���
		if (cnt == 0) {
			if (!UART_RXD) {   // ��ʼλΪ 0 ʱ����ս��ջ�������׼����������λ
				RxdBuf = 0;
				++ cnt;
			} else {           // ��ʼλ��Ϊ 0 ʱ����ֹ����
				TR0 = 0;       // �ر� T0
			}
		} else if (cnt <= 8) { // ���� 8 λ����
			RxdBuf >>= 1;      // ��λ���ߣ���֮ǰ���յ�λ ����
			if (UART_RXD) {    // ���ս�Ϊ 1 ʱ�����������λ�� 1��
				RxdBuf |= 0x80;// ��Ϊ 0 ʱ��������������λ�ƺ�� 0
			}
			++ cnt;
		} else {               // ֹͣλ����
			cnt = 0;           // ��λ bit ������
			TR0 = 0;           // �ر� T0
			if (UART_RXD) {    // ֹͣλΪ 1 ʱ��������Ϊ������Ч
				RxdEnd = 1;    // �ý��ս�����־
			}
		}
	}
}
