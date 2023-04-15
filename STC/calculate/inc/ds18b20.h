#ifndef __TBZ_DS18B20_H_
#define __TBZ_DS18B20_H_

#include "myheader.h"


#define IO_18B20 P3_2
/* ��λ���ߣ���ȡ�������壬������һ�ζ�д���� */
__bit Get18B20Ack() {
	__bit ack;
	EA = 0;		  //��ֹ���ж�
	IO_18B20 = 0; //���� 500us ��λ����
	delay(50);
	IO_18B20 = 1;
	delay(6);	//��ʱ 60us
	ack = IO_18B20; //��ȡ��������
	while (!IO_18B20)
		;	//�ȴ������������
	EA = 1; //����ʹ�����ж�
	return ack;
}
/* �� DS18B20 д��һ���ֽڣ�dat-��д���ֽ� */
void Write18B20(unsigned char dat) {
	unsigned char mask;
	EA = 0;									 //��ֹ���ж�
	for (mask = 0x01; mask != 0; mask <<= 1) {//��λ���ȣ������Ƴ� 8 �� bit
		IO_18B20 = 0; //���� 2us �͵�ƽ����
		_nop_();
		_nop_();
		if ((mask & dat) == 0) //����� bit ֵ
			IO_18B20 = 0;
		else
			IO_18B20 = 1;
		delay(6); //��ʱ 60us
		IO_18B20 = 1;  //����ͨ������
	}
	EA = 1; //����ʹ�����ж�
}
/* �� DS18B20 ��ȡһ���ֽڣ�����ֵ-�������ֽ� */
unsigned char Read18B20() {
	unsigned char dat;
	unsigned char mask;
	EA = 0;									 //��ֹ���ж�
	for (mask = 0x01; mask != 0; mask <<= 1) {//��λ���ȣ����βɼ� 8 �� bit
		IO_18B20 = 0; //���� 2us �͵�ƽ����
		_nop_();
		_nop_();
		IO_18B20 = 1; //�����͵�ƽ���壬�ȴ� 18B20 �������
		_nop_();	  //��ʱ 2us
		_nop_();
		if (!IO_18B20) //��ȡͨ�������ϵ�ֵ
			dat &= ~mask;
		else
			dat |= mask;
		delay(6); //����ʱ 60us
	}
	EA = 1; //����ʹ�����ж�
	return dat;
}
/* ����һ�� 18B20 �¶�ת��������ֵ-��ʾ�Ƿ������ɹ� */
__bit Start18B20() {
	bit ack;
	ack = Get18B20Ack(); //ִ�����߸�λ������ȡ 18B20 Ӧ��
	if (ack == 0) {      //�� 18B20 ��ȷӦ��������һ��ת��
		Write18B20(0xCC); //���� ROM ����
		Write18B20(0x44); //����һ���¶�ת��
	}
	return ~ack; //ack==0 ��ʾ�����ɹ������Է���ֵ����ȡ��
}
/* ��ȡ DS18B20 ת�����¶�ֵ������ֵ-��ʾ�Ƿ��ȡ�ɹ� */
__bit Get18B20Temp(int *temp) {
	__bit ack;
	unsigned char LSB, MSB; //16bit �¶�ֵ�ĵ��ֽں͸��ֽ�
	ack = Get18B20Ack();    //ִ�����߸�λ������ȡ 18B20 Ӧ��
	if (ack == 0){          //�� 18B20 ��ȷӦ�����ȡ�¶�ֵ
		Write18B20(0xCC);              //���� ROM ����
		Write18B20(0xBE);              //���Ͷ�����
		LSB = Read18B20();             //���¶�ֵ�ĵ��ֽ�
		MSB = Read18B20();             //���¶�ֵ�ĸ��ֽ�
		*temp = BIND2BYTE(MSB,LSB); //�ϳ�Ϊ 16bit ������
	}
	return ~ack; //ack==0 ��ʾ����Ӧ�����Է���ֵΪ��ȡ��ֵ
}
#endif