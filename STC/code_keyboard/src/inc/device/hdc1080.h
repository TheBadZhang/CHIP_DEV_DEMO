#ifndef __TBZ_HDC1080_H_
#define __TBZ_HDC1080_H_

#ifdef __TBZ_BINARY_H_
#include "binary.h"
#endif
#ifdef __TBZ_I2C_H_
#include "i2c.h"
#endif

// 寄存器地址
#define HDC1080_I2C_ADDR   0x80   // HDC1080 的 IIC 地址为 1000000（7位地址）+ 读(1)或写(0)方向位
#define temperature        0x00   // 温度寄存器，复位值为 0x0000 
#define humidity           0x01   // 湿度寄存器，复位值为 0x0000 
#define configuration      0x02   // 配置寄存器，复位值为 0x1000 
#define manufacturerID     0xFE   // 制造商ID寄存器，0x5449
#define deviceID           0xFF   // 设备ID寄存器，0x1050 

// 寄存器值
#define manufacturerID_value   0x5449   // 制造商 ID 值
#define deviceID_value         0x1050   // 设备 ID 值
// 关闭 Heater，同时采集温度和湿度(温度在前)，温度分辨率为 14 位，湿度分辨率为 14 位
#define configHeaterOff        0x1000
// 开启 Heater，同时采集温度和湿度(温度在前)，温度分辨率为 14 位，湿度分辨率为 14 位
#define configHeaterOn         0x3000
#define heatFast           0x0600


/*

! HDC1080 在上电后需要等待最多 15ms 才能正常工作
* 此时返回的值是从 0xFB 到 0xFF 的值
* 所有的数据都是 MSB 先传输的
*/

/**
 * @brief 向 HDC1080 写入令
 * @param addr 写入的地址
 * @param data 写入的数据
 */
void HDC1080_WriteReg (unsigned char addr, unsigned int data) {
	I2C_Start ();                  //起始信号
	I2C_Write (HDC1080_I2C_ADDR);   //发送HDC1080设备地址+写信号
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write (addr);               //内部寄存器地址
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write ((unsigned char)((data & 0xFF00) >> 8));   //写入内部寄存器数据
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Write ((unsigned char)(data & 0x00FF));          //写入内部寄存器数据
	// I2C_WaitAck ();
	I2C_Delay ();
	I2C_Stop ();                   //停止信号
}


unsigned int HDC1080_ReadReg(unsigned char addr) {
	unsigned int r = 0;
	I2C_Start();   //起始信号  
	I2C_Delay ();
	I2C_Write (HDC1080_I2C_ADDR);   //发送HDC1080设备地址+写信号
	I2C_Delay ();
	I2C_Write (addr);   //内部寄存器地址
	delay (100);     // 等待数据测量是在读取之前等待
	I2C_Start ();   //起始信号
	I2C_Write (HDC1080_I2C_ADDR|0x01);   //发送HDC1080设备地址+读信号
	I2C_Delay ();


	// I2C_Stop ();
	r = (I2C_ReadACK () << 8) & 0xff00;
	I2C_Delay ();
	r |= I2C_ReadNAK () & 0x00ff;
	I2C_Stop();   //停止信号

	return r;
}


/**
 * @brief 获得温度数据
 * @return 代表温度一百倍的整数
 * @retval 比如 10000 实际上是 100.00 摄氏度
 */
int HDC1080_Temperature (void) {
	return (int)((HDC1080_ReadReg (0x0000)/65536.0*165.0-40.0)*100); 
}


/**
 * @brief 初始化 HDC1080
 */
void initHDC1080 () {
	HDC1080_WriteReg (configuration, heatFast);
}


#endif