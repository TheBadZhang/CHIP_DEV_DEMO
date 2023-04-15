#include "../inc/i2c.h"

/**
 * @brief i2c ��ʼ�źţ�SDA SCL ��ʼ�ߣ������� SDA�������� SCL�����������ʼ�ź�
 */
void I2C_Start () {
	I2C_SDA = HIGH;
	I2C_SCL = HIGH; // SDA, SCL ��ʼ�ߵ�ƽ
	I2C_Delay ();
	I2C_SDA = LOW;  // ���� SDA
	I2C_Delay ();
	I2C_SCL = LOW;  // ���� SCL
}
/**
 * @brief i2c ��ֹ�źţ�SDA SCL ��ʼ�ͣ������� SCL�������� SDA�����������ֹ�ź�
 */
void I2C_Stop () {
	I2C_SCL = LOW;
	I2C_SDA = LOW;  // ����ȷ�� SDA��SCL ���ǵ͵�ƽ
	I2C_Delay ();
	I2C_SCL = HIGH; // ������ SCL
	I2C_Delay ();
	I2C_SDA = HIGH; // ������ SDA
	I2C_Delay ();
}


void I2C_NAK () {
	I2C_SDA = HIGH;        // 8 λ���ݷ���������� SDA�� ���ͷ�Ӧ���ź�
	I2C_Delay ();
	I2C_SCL = HIGH;        // ���� SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // ���� SCL ��ɷ�Ӧ��λ��������ס����
}
void I2C_ACK () {
	I2C_SDA = LOW;         // 8 λ���ݷ���������� SDA�� ���ͷ�Ӧ���ź�
	I2C_Delay ();
	I2C_SCL = HIGH;        // ���� SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // ���� SCL ��ɷ�Ӧ��λ��������ס����
}

void I2C_WaitAck() {
	I2C_SCL = HIGH ;
	I2C_SCL = LOW ;
}


/**
 * @brief I2C д��һ���ֽڵ�����
 * @param dat ��д�������
 * @return __bit��һ��λ��
 * @retval 1 ��ʾ��Ӧ��
 *         0 ��ʾ��Ӧ��
 */
__bit I2C_Write (unsigned char dat) {
	__bit ack;  // �ݴ�Ӧ��λ��ֵ
	unsigned char mask;  // ����̽���ֽ���ĳһλֵ���������

	for (mask = 0x80; mask != 0; mask >>= 1) {
						 // �Ӹ�λ����λ���ν���
		I2C_SDA = (mask&dat) != 0; // �Ѹ�λ��ֵ��ֵ�� SDA ��
		I2C_Delay ();
		I2C_SCL = HIGH;  // ���� SCL
		I2C_Delay ();
		I2C_SCL = LOW;   // ���� SCL�����һ��λ����
	}
	I2C_SDA = HIGH;      // 8 λ���ݷ�����������ͷ� SDA���Լ��ӻ�Ӧ��
	I2C_Delay ();
	I2C_SCL = LOW;       // ���� SCL
	I2C_Delay ();
	ack = I2C_SDA;       // ��ȡ��ʱ�Ĵӻ�Ӧ��ֵ
	I2C_Delay ();
	I2C_SCL = HIGH;      // ���� SCL ���Ӧ�𣬱�������

	return (!ack);       // ���ط����߼���Ӧ��ֵ
						 // 0: �����ڻ�æ��д��ʧ�ܣ�1: �����ҿ��л�ɹ�д��
}


/**
 * @brief ��
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_Read () {
	unsigned char i;
	unsigned char dat = 0;

	I2C_SDA = HIGH;         // �����ͷ� SDA
	// while (i--) {
	FOR (i, 8) {
		I2C_Delay ();
		I2C_SCL = HIGH;     // ���� SCL
		dat |= I2C_SDA << i;
		I2C_Delay ();
		I2C_SCL = LOW;     // ���� SCL����ʹ�ӻ����ͳ���һλ
	}

	return dat;          // ��������
}


/**
 * @brief Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadACK () {
	unsigned char dat = I2C_Read ();
	I2C_ACK ();
	return dat;          // ��������
}

/**
 * @brief ��Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadNAK () {
	unsigned char dat = I2C_Read ();
	I2C_NAK ();
	return dat;          // ��������
}


void I2C_WriteRegister (unsigned char addr, unsigned char register_addr, unsigned char dat) {
	I2C_Start ();
	I2C_Write (addr);
	I2C_WaitAck ();
	I2C_Write (register_addr);
	I2C_WaitAck ();
	I2C_Write (dat);
	I2C_WaitAck ();
	I2C_Stop ();
}
unsigned char I2C_ReadRegister (unsigned char addr, unsigned char register_addr) {
	I2C_Start ();
	I2C_Write (addr);
	I2C_Write (register_addr);
	I2C_Start ();
	I2C_Write (addr|0x01);
	unsigned char r = I2C_Read ();
	I2C_Stop ();
	return r;
}


/**
 * @brief I2C Ԫ����ַ��ѯ
 * @return __bit
 * @retval 0 ��ʾ������
 *         1 ��ʾ����
 */
__bit I2C_Addressing (unsigned char addr) {
	__bit ack;
	I2C_Start ();
	ack = I2C_Write (addr << 1);
	I2C_Stop ();

	return ack;
}