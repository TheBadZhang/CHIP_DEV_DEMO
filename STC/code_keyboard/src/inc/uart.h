#ifndef __TBZ_UART_H_
#define __TBZ_UART_H_

#include "myheader.h"

/**
 * @brief 初始化串口
 */
void uart_init () {
    SCON = 0x50; //设置串口工作方式1
    TMOD = 0x20; //设置计数器工作方式2
    PCON = 0x00; //即SMOD=1，波特率不加倍
	ASSIGNMENT16 (TH1, TL1, 0xFDFD); //计数器初值，波特率是9600,晶振为11.0592MHz
    ES   = 1;    //打开接收中断
    EA   = 1;    //打开总中断
    TR1  = 1;    //打开定时器
}

/**
 * @brief 串口发送一个字节
 */
void uart_tx_byte(uchar ch) {
	SBUF = ch;
	while (!TI);
	TI = 0;
}
/**
 * @brief 串口发送一个字符串
 */
void uart_tx_string(uchar *str) {
	while (*str != '\0') {
		uart_tx_byte (*str++);
	}
}

/**
 * @brief 串口接收一个字符串
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
 * @brief 将接收到的数据存入到 UartRxBuffer
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