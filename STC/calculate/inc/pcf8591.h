#ifndef __TBZ_PCF8591_H_
#define __TBZ_PCF8591_H_

#defin __TBZ_IIC_ENABLE_
#include "myheader.h"

#define PCF8591_ADDR B10010000
#define PCF8591_CMD B00000000
#define PCF8591_DA_ENABLE B01000000
#define PCF8591_SINGLE_ENDED B00010000
#define PCF8591_DIFFERENTIAL B00100000
#define PCF8591_AUTO_INCREASE B00000100
#define PCF8591_CHANNEL0 B00000000
#define PCF8591_CHANNEL1 B00000001
#define PCF8591_CHANNEL2 B00000010
#define PCF8591_CHANNEL3 B00000011

unsigned char code SinWave[] = { //���Ҳ�����
	127, 152, 176, 198, 217, 233, 245, 252,
	255, 252, 245, 233, 217, 198, 176, 152,
	127, 102, 78, 56, 37, 21, 9, 2,
	0, 2, 9, 21, 37, 56, 78, 102,
};
unsigned char code TriWave[] = { //���ǲ�����
	0, 16, 32, 48, 64, 80, 96, 112,
	128, 144, 160, 176, 192, 208, 224, 240,
	255, 240, 224, 208, 192, 176, 160, 144,
	128, 112, 96, 80, 64, 48, 32, 16,
};
unsigned char code SawWave[] = { //��ݲ���
	0, 8, 16, 24, 32, 40, 48, 56,
	64, 72, 80, 88, 96, 104, 112, 120,
	128, 136, 144, 152, 160, 168, 176, 184,
	192, 200, 208, 216, 224, 232, 240, 248,
};

/**
 * @brief �� PCF8591 д����
 * @param addr д��ĵ�ַ
 * @param data д�������
 */
void PCF8591_Read (unsigned char channel, unsigned char mode) {
	I2C_Start ();                  //��ʼ�ź�
	I2C_Write (PCF8519_ADDR);   //����HDC1080�豸��ַ+д�ź�
	I2C_Delay ();
	I2C_Write (PCF8591_CMD|channel|mode);               //�ڲ��Ĵ�����ַ
	I2C_Delay ();
	I2C_Stop ();                   //ֹͣ�ź�
}


unsigned int PCF8591_Write (unsigned char addr) {
	unsigned int r = 0;
	I2C_Start();   //��ʼ�ź�  
	I2C_Delay ();
	I2C_Write (HDC1080_I2C_ADDR);   //����HDC1080�豸��ַ+д�ź�
	I2C_Delay ();
	I2C_Write (addr);   //�ڲ��Ĵ�����ַ
	delay (100);     // �ȴ����ݲ������ڶ�ȡ֮ǰ�ȴ�
	I2C_Start ();   //��ʼ�ź�
	I2C_Write (HDC1080_I2C_ADDR|0x01);   //����HDC1080�豸��ַ+���ź�
	I2C_Delay ();


	// I2C_Stop ();
	r = I2C_ReadACK ();
	I2C_Stop();   //ֹͣ�ź�

	return r;
}


/**
 * @brief ����¶�����
 * @return �����¶�һ�ٱ�������
 * @retval ���� 10000 ʵ������ 100.00 ���϶�
 */
int HDC1080_Temperature (void) {
	return (int)((HDC1080_ReadReg (0x0000)/65536.0*165.0-40.0)*100); 
}


/**
 * @brief ��ʼ�� HDC1080
 */
void initHDC1080 () {
	HDC1080_WriteReg (configuration, heatFast);
}



#endif