#ifndef __TBZ_LCD12864_H_
#define __TBZ_LCD12864_H_

#include "myheader.h"

#define uchar unsigned char
#define uint unsigned int

uchar code num[]={"0123456789 e:.-"};

#define RS   P1_0     //����/����ѡ��
#define RW   P1_1     //��д��
#define E    P1_5     //ʹ�ܶ�
#define PSB  1        //����ѡ��, 1���У�0�����У���ɳ̲����������ֻ�в��У�

void lcd1864_delay(uint t) {
	uint i;
	while(t--)
		for(i=0;i<110;i++);
}

/**
 * @brief ���LCD��ǰ�Ƿ�æµ
 * @return ���ص�ǰ�Ƿ�æ
 * @retval 1 ����æ
 *         0 ��æ
 */
__bit busy() {
	__bit result;
	P0 = 0X00;
	RS = 0;			// ����/����ѡ��,Ϊ 0 ʱѡ������
	RW = 1;			// ��/дѡ��Ϊ 1 ʱѡ���
	E  = 1;			// ʹ��
	delay(1);
	result = (bit)(P0&0x80); //��æ��־λ���ȴ���־λΪ0������ʾд�����
	E = 0;			// �رն�д
	return (result);
}
/**
 * @brief ��lcdдһ����
 * @param cmd ��д�������
 */
void wcode(uchar cmd) {
	while(busy());                   //��æ
	RS = 0;							 //����/����ѡ��,Ϊ0ʱѡ������
	RW = 0;							 //��/дѡ��Ϊ0ʱѡ��д
	E  = 0;
	_nop_();
	_nop_();
	P0 = cmd;                //��������
	delay(1);                //�ȴ�
	E = 1;
	delay(1);
	E = 0;
}
/**
 * @brief ��LCDдһ����
 */
void wdata(uchar dat) {
	while(busy());
	RS = 1;            //HΪ����
	RW = 0;
	E  = 0;
	P0 = dat;
	delay(1);
	E = 1;
	delay(1);
	E = 0;
}
/**
 * @brief LCD��ʼ��
 */
void initlcd() {
	// PSB = 1;       //����Ϊ8BIT���ڹ���ģʽ  H���� L����
	delay(10);
	wcode(0x34);
	delay(5);
	wcode(0x30);   //ѡ�����ָ�
	delay(5);
	wcode(0x0c);   //����ʾ�����α�
	delay(5);
	wcode(0x01);   //�����ʾ�������趨��ַָ��Ϊ00H
	delay(5);
	wcode(0x06);   //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ
}
/**
 * @brief ����λ����ʾ�ַ���
 * @param x Ϊ������
 * @param y λ������
 * @param s ��ʾָ�룬Ϊ���ݵ��׵�ַ
 */
void dis(uchar x,uchar y,uchar code* s) {
	switch(y) { //ѡ��������
		case 0: wcode (0x80+x); break;  //��һ��
		case 1: wcode (0x90+x); break;  //�ڶ���
		case 2: wcode (0x88+x); break;  //������
		case 3: wcode (0x98+x); break;  //������
		default:break;
	}
	while(*s>0) {   //д�����ݣ�ֱ������Ϊ��
		wdata(*s);  //д����
		delay(10);  //��һ�ַ�
		s++;
	}
}
void showGB(uchar *HZ) { //��ʾ��������
   wdata(HZ[0]);         //д�뺺�ָ߰�λ����
   wdata(HZ[1]);         //д��Ͱ�λ
}

void wrnum(uchar s) {
	wdata(num[s]);
	delay(1);
}



#endif