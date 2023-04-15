#ifndef __TBZ_EEPROM_H_
#define __TBZ_EEPROM_H_E

#include "../inc/i2c.h"
#include "../inc/eeprom.h"

#define EEPROM_ADDR B10100000            // KST51 �� EEPROM �ĵ�ַ

/*

! EEPROM д������ڶ�ʱ����������Ӱ��������������
* �Ѷ�д��д��ǰ�棬�Ϳ��Թ�ܾ��󲿷ֵ����⣬����Ϊ����İ����˳���
* �����˳������н��һֱ��׼ȷ������Ҫ�� EEPROM �����ҳ������е�״̬
*/



/**
 * @brief �� eeprom addr λ�ö�ȡһ���ֽڵ�����
 * @param addr �� eeprom �ж�ȡ���ݵĵ�ַ
 * @return ���ض�ȡ�����ֽ�����
 * @retval
 */
unsigned char eeReadByte (unsigned char addr) {

	unsigned char dat;                 // �洢��������

	I2C_Start ();                       // I2C ��ʼ�ź�
	I2C_Write (EEPROM_ADDR);            // Ѱַ��������������Ϊ д
	I2C_Write (addr);                   // д��Ҫ��ѯ�ĵ�ַ
	I2C_Stop ();                        // �����źŴ���

	I2C_Start ();                       // I2C ��ʼ�ź�
	I2C_Write ((EEPROM_ADDR) | 0x1);    // Ѱַ��������������Ϊ ��

	dat = I2C_ReadNAK ();               // ��ȡһ���ֽڵ����ݣ�Ȼ�������NAK��
	I2C_Stop ();                        // �����źŴ���

	return dat;
}
/**
 * @brief �� eeprom addr λ��д��һ���ֽ�����
 * @param addr ��д�� eeprom �ĵ�ַ
 * @param dat ��д�� eeprom ������
 * @return void
 */
void eeWriteByte (unsigned char addr, unsigned char dat) {
	I2C_Start ();             // I2C ��ʼ�ź�
	I2C_Write (EEPROM_ADDR);  // EEPROM ����Ѱַ
	I2C_Write (addr);         // ����д���ַ
	I2C_Write (dat);          // �� addr д��һ���ֽڵ�����
	I2C_Stop ();              // I2C �����ź�
}


#endif