#ifndef __TBZ_EEPROM_H_
#define __TBZ_EEPROM_H_E

#include "../inc/i2c.h"
#include "../inc/eeprom.h"

#define EEPROM_ADDR B10100000            // KST51 上 EEPROM 的地址

/*

! EEPROM 写完后不能在短时间读，否则会影响程序的正常运行
* 把读写在写的前面，就可以规避绝大部分的问题，我因为错误的安排了程序
* 导致了程序运行结果一直不准确，我想要用 EEPROM 报错我程序运行的状态
*/



/**
 * @brief 从 eeprom addr 位置读取一个字节的数据
 * @param addr 从 eeprom 中读取数据的地址
 * @return 返回读取到的字节数据
 * @retval
 */
unsigned char eeReadByte (unsigned char addr) {

	unsigned char dat;                 // 存储返回数据

	I2C_Start ();                       // I2C 起始信号
	I2C_Write (EEPROM_ADDR);            // 寻址器件，后续操作为 写
	I2C_Write (addr);                   // 写入要查询的地址
	I2C_Stop ();                        // 结束信号传输

	I2C_Start ();                       // I2C 起始信号
	I2C_Write ((EEPROM_ADDR) | 0x1);    // 寻址器件，后续操作为 读

	dat = I2C_ReadNAK ();               // 读取一个字节的数据，然后结束（NAK）
	I2C_Stop ();                        // 结束信号传输

	return dat;
}
/**
 * @brief 向 eeprom addr 位置写入一个字节数据
 * @param addr 欲写入 eeprom 的地址
 * @param dat 欲写入 eeprom 的数据
 * @return void
 */
void eeWriteByte (unsigned char addr, unsigned char dat) {
	I2C_Start ();             // I2C 起始信号
	I2C_Write (EEPROM_ADDR);  // EEPROM 器件寻址
	I2C_Write (addr);         // 发送写入地址
	I2C_Write (dat);          // 向 addr 写入一个字节的数据
	I2C_Stop ();              // I2C 结束信号
}


#endif