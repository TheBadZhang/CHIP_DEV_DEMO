#ifndef __TBZ_I2C_H_
#define __TBZ_I2C_H_

#include "myheader.h"
/*

._________
/ sdlfkj  \
\_________/


*/

/**
 * @brief I2C 延时函数
 * @note 因为 I2C 有低速，快速，高速三种模式
 */
#define I2C_Delay() { _nop_(); _nop_(); _nop_(); _nop_(); }
// #define I2C_Delay I2C_WaitAck
// #define I2C_Delay()
// I2C SCL 引脚
#define I2C_SCL P1_1
// I2C SDA 引脚
#define I2C_SDA P1_0
/**
 * @brief i2c 起始信号，SDA SCL 起始高，先拉低 SDA，再拉低 SCL，即可完成起始信号
 */
void I2C_Start ();
/**
 * @brief i2c 终止信号，SDA SCL 起始低，先拉高 SCL，再拉高 SDA，即可完成终止信号
 */
void I2C_Stop ();
void I2C_NAK ();
void I2C_ACK ();
void I2C_WaitAck();

/**
 * @brief I2C 写入一个字节的数据
 * @param dat 欲写入的数据
 * @return __bit（一个位）
 * @retval 1 表示有应答
 *         0 表示无应答
 */
__bit I2C_Write (unsigned char dat);
/**
 * @brief 读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_Read ();

/**
 * @brief 应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadACK ();
/**
 * @brief 非应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadNAK ();
void I2C_WriteRegister (unsigned char addr, unsigned char register_addr, unsigned char dat);
unsigned char I2C_ReadRegister (unsigned char addr, unsigned char register_addr);


/**
 * @brief I2C 元件地址查询
 * @return __bit
 * @retval 0 表示不存在
 *         1 表示存在
 */
__bit I2C_Addressing (unsigned char addr);

#endif