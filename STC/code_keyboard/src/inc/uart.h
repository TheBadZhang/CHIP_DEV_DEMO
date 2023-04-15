#ifndef __TBZ_UART_H_
#define __TBZ_UART_H_

#include "myheader.h"

/**
 * @brief ��ʼ������
 */
void uart_init () {
    SCON = 0x50; //���ô��ڹ�����ʽ1
    TMOD = 0x20; //���ü�����������ʽ2
    PCON = 0x00; //��SMOD=1�������ʲ��ӱ�
	ASSIGNMENT16 (TH1, TL1, 0xFDFD); //��������ֵ����������9600,����Ϊ11.0592MHz
    ES   = 1;    //�򿪽����ж�
    EA   = 1;    //�����ж�
    TR1  = 1;    //�򿪶�ʱ��
}

/**
 * @brief ���ڷ���һ���ֽ�
 */
void uart_tx_byte(uchar ch) {
	SBUF = ch;
	while (!TI);
	TI = 0;
}
/**
 * @brief ���ڷ���һ���ַ���
 */
void uart_tx_string(uchar *str) {
	while (*str != '\0') {
		uart_tx_byte (*str++);
	}
}

/**
 * @brief ���ڽ���һ���ַ���
 */
uchar uart_rx_string( uchar* RxBuffer ) {
	uchar rxLength = 0;
	uint uartRxTimOut = 0x7FFF;
	while( uartRxTimOut-- ) {
		if( 0 != RI ) {
			RI = 0;
			*RxBuffer = SBUF;
			RxBuffer++;
			rxLength++;
			uartRxTimOut = 0x7FFF;
		}
	}
	return rxLength;
}
/**
 * @brief �����յ������ݴ��뵽 UartRxBuffer
 */
void UART_INT (void) __interrupt (4) {
	if(RI) {
		RI = 0;
		uart_func (SBUF);
	}
	if(TI) {
		TI = 0;
	}
}

#endif