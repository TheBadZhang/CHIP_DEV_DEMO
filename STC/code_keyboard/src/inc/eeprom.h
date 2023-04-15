#ifndef __TBZ_EEPROM_H_
#define __TBZ_EEPROM_H_E


#define EEPROM_ADDR B10100000            // 根据具体的地址进行设置

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
unsigned char eeReadByte (unsigned char addr);
/**
 * @brief 向 eeprom addr 位置写入一个字节数据
 * @param addr 欲写入 eeprom 的地址
 * @param dat 欲写入 eeprom 的数据
 * @return void
 */
void eeWriteByte (unsigned char addr, unsigned char dat);


#endif