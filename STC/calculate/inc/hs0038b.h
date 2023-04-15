#ifndef __TBZ_HS0038B_H_
#define __TBZ_HS0038B_H_

#include "myheader.h"


#define IR_INPUT P3_3      //�����������
__bit irflag = 0;          //������ձ�־���յ�һ֡��ȷ���ݺ��� 1
unsigned char ircode[4];   //���������ջ�����
/**
 * @brief ��ʼ��������չ���
 */
void InitInfrared() {
	IR_INPUT = 1;          //ȷ������������ű��ͷ�
	TMOD &= 0x0F;          //���� T1 �Ŀ���λ
	TMOD |= 0x10;          //���� T1 Ϊģʽ 1
	TR1 = 0;               //ֹͣ T1 ����
	ET1 = 0;               //��ֹ T1 �ж�
	IT1 = 1;               //���� INT1 Ϊ�����ش���
	EX1 = 1;               //ʹ�� INT1 �ж�
}
/**
 * @brief ��ȡ��ǰ�ߵ͵�ƽ�ĳ���ʱ��
 */
unsigned int GetVoltageTime(unsigned char voltage) {
	TH1 = 0;         //���� T1 ������ֵ
	TL1 = 0;
	TR1 = 1;         //���� T1 ����
	while (IR_INPUT == voltage) {//������������Ϊ 1 ʱѭ�����ȴ�����Ϊ 0 ʱ�������ѭ��
		if (TH1 >= 0x40) {
		           //�� T1 ����ֵ���� 0x4000�����ߵ�ƽ����ʱ�䳬��Լ 18ms ʱ��
			break; //ǿ���˳�ѭ������Ϊ�˱����ź��쳣ʱ��������������
		}
	}
	TR1 = 0;                  //ֹͣ T1 ����
	return BIND2BYTE (TH1,TL1); //T1 ����ֵ�ϳ�Ϊ 16bit �������������ظ���
}

/**
 * @brief �ж�һ�������Ƿ��� [a,b] �ķ�Χ��
 * @param _times ����
 * @param _left ��߽�
 * @param _right �ұ߽�
 */
#define IN_RANGE(_times, _left, _right) \
	_left <= _times && _times <= _right

/**
 * @brief �ж�ʱ���Ƿ��� [a,b] �ķ�Χ�ڣ��������˳�����
 * @param _times ʱ��
 * @param _left ��߽�
 * @param _right �ұ߽�
 */
#define TIME_NOT_IN_RANGE(_time, _left, _right) \
	if (NOT(IN_RANGE(_time,_left,_right))) {    \
		    /*�����˷�Χ��˵��Ϊ���룬ֱ���˳�*/   \
		IE1 = 0;   /*�˳�ǰ���� INT1 �жϱ�־*/   \
		return ;                                \
	}
/**
 * @brief �ж�ĳ����λ��ʱ���Ƿ��� [a,b] �ķ�Χ��
 */
#define VOLTAGE_TIME_NOT_IN_RANGE(_voltage, _left, _right) \
	TIME_NOT_IN_RANGE(GetVoltageTime(_voltage),_left,_right);
/**
 * @brief INT1 �жϷ�������ִ�к�����ռ�����
 */
void HS0038B_INT () __interrupt INT1 {

	unsigned char i, j;
	unsigned char byt;
	unsigned int time;
	//���ղ��ж�������� 9ms   �͵�ƽ
	VOLTAGE_TIME_NOT_IN_RANGE (LOW, 7833, 8755);  //ʱ���ж���ΧΪ 8.5��9.5ms��
	//���ղ��ж�������� 4.5ms �ߵ�ƽ
	VOLTAGE_TIME_NOT_IN_RANGE (HIGH, 3686, 4608);  //ʱ���ж���ΧΪ 4.0��5.0ms��
	//���ղ��ж������� 4 �ֽ�����
	FOR (i, 4) {//ѭ������ 4 ���ֽ�
		FOR (j, 8) {//ѭ�������ж�ÿ�ֽڵ� 8 �� bit
			//�����ж�ÿ bit �� 560us �͵�ƽ
			VOLTAGE_TIME_NOT_IN_RANGE (LOW, 313, 718);  //ʱ���ж���ΧΪ 340��780us��
			//����ÿ bit �ߵ�ƽʱ�䣬�ж��� bit ��ֵ
			time = GetVoltageTime(HIGH);
			if (NOT(IN_RANGE(time,313,718))) {    //ʱ���ж���ΧΪ 340��780us��
				                                  //�ڴ˷�Χ��˵���� bit ֵΪ 0
				byt >>= 1;                        //���λ���ȣ������������ƣ���λΪ 0
			} else if (IN_RANGE(time,1345,1751)) {//ʱ���ж���ΧΪ 1460��1900us��
			                                      //�ڴ˷�Χ��˵���� bit ֵΪ 1
				byt >>= 1;                        //���λ���ȣ������������ƣ�
				byt |= 0x80;                      //��λ�� 1
			} else {//����������Χ����˵��Ϊ���룬ֱ���˳�
				IE1 = 0;
				return;
			}
		}
		ircode[i] = byt; //������һ���ֽں󱣴浽������
	}
	irflag = 1; //������Ϻ����ñ�־
	IE1 = 0;    //�˳�ǰ���� INT1 �жϱ�־
}

#endif
