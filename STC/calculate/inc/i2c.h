#ifndef __TBZ_I2C_H_
#define __TBZ_I2C_H_

#include "myheader.h"
/*

._________
/ sdlfkj  \
\_________/


*/

/**
 * @brief I2C ��ʱ����
 * @note ��Ϊ I2C �е��٣����٣���������ģʽ
 */
#define I2C_Delay() { _nop_(); _nop_(); _nop_(); _nop_(); }
// #define I2C_Delay I2C_WaitAck
// #define I2C_Delay()
// I2C SCL ����
#define I2C_SCL P1_1
// I2C SDA ����
#define I2C_SDA P1_0
/**
 * @brief i2c ��ʼ�źţ�SDA SCL ��ʼ�ߣ������� SDA�������� SCL�����������ʼ�ź�
 */
void I2C_Start ();
/**
 * @brief i2c ��ֹ�źţ�SDA SCL ��ʼ�ͣ������� SCL�������� SDA�����������ֹ�ź�
 */
void I2C_Stop ();
void I2C_NAK ();
void I2C_ACK ();
void I2C_WaitAck();

/**
 * @brief I2C д��һ���ֽڵ�����
 * @param dat ��д�������
 * @return __bit��һ��λ��
 * @retval 1 ��ʾ��Ӧ��
 *         0 ��ʾ��Ӧ��
 */
__bit I2C_Write (unsigned char dat);
/**
 * @brief ��
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_Read ();

/**
 * @brief Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadACK ();
/**
 * @brief ��Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadNAK ();
void I2C_WriteRegister (unsigned char addr, unsigned char register_addr, unsigned char dat);
unsigned char I2C_ReadRegister (unsigned char addr, unsigned char register_addr);


/**
 * @brief I2C Ԫ����ַ��ѯ
 * @return __bit
 * @retval 0 ��ʾ������
 *         1 ��ʾ����
 */
__bit I2C_Addressing (unsigned char addr);

#endif