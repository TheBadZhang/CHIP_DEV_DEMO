#ifndef __TBZ_1WIRE_H_
#define __TBZ_1WIRE_H_
#include "myheader.h"

// 开始的 8 位是产品类型编码（DS18B20 是 0x10），接着的 48 位是每个器件
// 唯一的序号，最后的 8 位是 CRC 校验码
// Skip ROM（跳过 ROM）：0xCC。当总线上只有一个器件的时候，可以跳过 ROM，不进行 ROM 检测。
// Read Scratchpad（读暂存寄存器）：0xBE
// 这里要注意的是，DS18B20 的温度数据是 2 个字节，我们读取数据的时候，先读取到的
// 是低字节的低位，读完了第一个字节后，再读高字节的低位，直到两个字节全部读取完毕。
// Convert Temperature（启动温度转换）：0x44
// 当我们发送一个启动温度转换的指令后，DS18B20
#define WIRE1 


/**
 * @brief 检测是否存在对应设备
 */
__bit GET_1WIRE_ACK() {
	__bit ack;
	EA = 0;		  //禁止总中断
	WIRE1 = 0; //产生 500us 复位脉冲
	delay(50);   // 这个时长设置需要参考元器件的数据手册
	WIRE1 = 1;
	delay(6);	//延时 60us
	ack = WIRE1; //读取存在脉冲
	while (!WIRE1)
		;	//等待存在脉冲结束
	EA = 1; //重新使能总中断
	return ack;
}

#endif