#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  		64  	//定义最大接收字节数 64
#define EN_USART1_RX 			1			//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         				//接收状态标记	

 u8 UartCnt;	 //串口接收到的数据长度
 u8 FlagRec;   //串口正在接收标志位
 u8 FlagGetOk; //串口接收完成标志位
extern u16 UartTime;

void uart_init(u32 bound);
#endif
