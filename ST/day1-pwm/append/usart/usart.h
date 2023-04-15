#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  		64  	//�����������ֽ��� 64
#define EN_USART1_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         				//����״̬���	

 u8 UartCnt;	 //���ڽ��յ������ݳ���
 u8 FlagRec;   //�������ڽ��ձ�־λ
 u8 FlagGetOk; //���ڽ�����ɱ�־λ
extern u16 UartTime;

void uart_init(u32 bound);
#endif
