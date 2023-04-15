#include "../inc/i2c.h"

/**
 * @brief i2c 起始信号，SDA SCL 起始高，先拉低 SDA，再拉低 SCL，即可完成起始信号
 */
void I2C_Start () {
	I2C_SDA = HIGH;
	I2C_SCL = HIGH; // SDA, SCL 起始高电平
	I2C_Delay ();
	I2C_SDA = LOW;  // 拉低 SDA
	I2C_Delay ();
	I2C_SCL = LOW;  // 拉低 SCL
}
/**
 * @brief i2c 终止信号，SDA SCL 起始低，先拉高 SCL，再拉高 SDA，即可完成终止信号
 */
void I2C_Stop () {
	I2C_SCL = LOW;
	I2C_SDA = LOW;  // 首先确保 SDA、SCL 都是低电平
	I2C_Delay ();
	I2C_SCL = HIGH; // 先拉高 SCL
	I2C_Delay ();
	I2C_SDA = HIGH; // 再拉高 SDA
	I2C_Delay ();
}


void I2C_NAK () {
	I2C_SDA = HIGH;        // 8 位数据发送完后，拉高 SDA， 发送非应答信号
	I2C_Delay ();
	I2C_SCL = HIGH;        // 拉高 SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // 拉低 SCL 完成非应答位，并保持住总线
}
void I2C_ACK () {
	I2C_SDA = LOW;         // 8 位数据发送完后，拉高 SDA， 发送非应答信号
	I2C_Delay ();
	I2C_SCL = HIGH;        // 拉高 SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // 拉低 SCL 完成非应答位，并保持住总线
}

void I2C_WaitAck() {
	I2C_SCL = HIGH ;
	I2C_SCL = LOW ;
}


/**
 * @brief I2C 写入一个字节的数据
 * @param dat 欲写入的数据
 * @return __bit（一个位）
 * @retval 1 表示有应答
 *         0 表示无应答
 */
__bit I2C_Write (unsigned char dat) {
	__bit ack;  // 暂存应答位的值
	unsigned char mask;  // 用于探测字节内某一位值的掩码变量

	for (mask = 0x80; mask != 0; mask >>= 1) {
						 // 从高位到低位依次进行
		I2C_SDA = (mask&dat) != 0; // 把该位的值赋值到 SDA 上
		I2C_Delay ();
		I2C_SCL = HIGH;  // 拉高 SCL
		I2C_Delay ();
		I2C_SCL = LOW;   // 拉低 SCL，完成一个位周期
	}
	I2C_SDA = HIGH;      // 8 位数据发送完后，主机释放 SDA，以检测从机应答
	I2C_Delay ();
	I2C_SCL = LOW;       // 拉高 SCL
	I2C_Delay ();
	ack = I2C_SDA;       // 读取此时的从机应答值
	I2C_Delay ();
	I2C_SCL = HIGH;      // 拉低 SCL 完成应答，保持总线

	return (!ack);       // 返回符合逻辑的应答值
						 // 0: 不存在或忙活写入失败，1: 存在且空闲或成功写入
}


/**
 * @brief 读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_Read () {
	unsigned char i;
	unsigned char dat = 0;

	I2C_SDA = HIGH;         // 主机释放 SDA
	// while (i--) {
	FOR (i, 8) {
		I2C_Delay ();
		I2C_SCL = HIGH;     // 拉高 SCL
		dat |= I2C_SDA << i;
		I2C_Delay ();
		I2C_SCL = LOW;     // 拉低 SCL，以使从机发送出下一位
	}

	return dat;          // 返回数据
}


/**
 * @brief 应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadACK () {
	unsigned char dat = I2C_Read ();
	I2C_ACK ();
	return dat;          // 返回数据
}

/**
 * @brief 非应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadNAK () {
	unsigned char dat = I2C_Read ();
	I2C_NAK ();
	return dat;          // 返回数据
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
 * @brief I2C 元件地址查询
 * @return __bit
 * @retval 0 表示不存在
 *         1 表示存在
 */
__bit I2C_Addressing (unsigned char addr) {
	__bit ack;
	I2C_Start ();
	ack = I2C_Write (addr << 1);
	I2C_Stop ();

	return ack;
}