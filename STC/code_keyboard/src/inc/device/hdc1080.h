#ifndef __TBZ_HDC1080_H_
#define __TBZ_HDC1080_H_

#ifdef __TBZ_BINARY_H_
#include "binary.h"
#endif
#ifdef __TBZ_I2C_H_
#include "i2c.h"
#endif

// �Ĵ�����ַ
#define HDC1080_I2C_ADDR   0x80   // HDC1080 �� IIC ��ַΪ 1000000��7λ��ַ��+ ��(1)��д(0)����λ
#define temperature        0x00   // �¶ȼĴ�������λֵΪ 0x0000 
#define humidity           0x01   // ʪ�ȼĴ�������λֵΪ 0x0000 
#define configuration      0x02   // ���üĴ�������λֵΪ 0x1000 
#define manufacturerID     0xFE   // ������ID�Ĵ�����0x5449
#define deviceID           0xFF   // �豸ID�Ĵ�����0x1050 

// �Ĵ���ֵ
#define manufacturerID_value   0x5449   // ������ ID ֵ
#define deviceID_value         0x1050   // �豸 ID ֵ
// �ر� Heater��ͬʱ�ɼ��¶Ⱥ�ʪ��(�¶���ǰ)���¶ȷֱ���Ϊ 14 λ��ʪ�ȷֱ���Ϊ 14 λ
#define configHeaterOff        0x1000
// ���� Heater��ͬʱ�ɼ��¶Ⱥ�ʪ��(�¶���ǰ)���¶ȷֱ���Ϊ 14 λ��ʪ�ȷֱ���Ϊ 14 λ
#define configHeaterOn         0x3000
#define heatFast           0x0600


/*

! HDC1080 ���ϵ����Ҫ�ȴ���� 15ms ������������
* ��ʱ���ص�ֵ�Ǵ� 0xFB �� 0xFF ��ֵ
* ���е����ݶ��� MSB �ȴ����
*/

/**
 * @brief �� HDC1080 д����
 * @param addr д��ĵ�ַ
 * @param data д�������
 */
void HDC1080_WriteReg (unsigned char addr, unsigned int data) {
	I2C_Start ();                  //��ʼ�ź�
	I2C_Write (HDC1080_I2C_ADDR);   //����HDC1080�豸��ַ+д�ź�
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write (addr);               //�ڲ��Ĵ�����ַ
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write ((unsigned char)((data & 0xFF00) >> 8));   //д���ڲ��Ĵ�������
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write ((unsigned char)(data & 0x00FF));          //д���ڲ��Ĵ�������
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Stop ();                   //ֹͣ�ź�
}


unsigned int HDC1080_ReadReg(unsigned char addr) {
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
	r = (I2C_ReadACK () << 8) & 0xff00;
	I2C_Delay ();
	r |= I2C_ReadNAK () & 0x00ff;
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