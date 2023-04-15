#ifndef __TBZ_DS1302_H_
#define __TBZ_DS1302_H_

#include "myheader.h"

#define DS1302_CK P3_5
#define DS1302_IO P3_4
#define DS1302_CE P1_7

struct sTime { //日期时间结构体定义
	unsigned int year; //年
	unsigned char mon; //月
	unsigned char day; //日
	unsigned char hour; //时
	unsigned char min; //分
	unsigned char sec; //秒
	unsigned char week; //星期
};


/**
 * @brief 发送一个字节到 DS1302 通信总线上
*/
void DS1302ByteWrite(unsigned char dat) {
	for (; dat!=0; dat>>=1) {//低位在前，逐位移出
		if ((dat&0x01) != 0) //首先输出该位数据
			DS1302_IO = 1;
		else
			DS1302_IO = 0;
			DS1302_CK = 1; //然后拉高时钟
			DS1302_CK = 0; //再拉低时钟，完成一个位的操作
	}
	DS1302_IO = 1; //最后确保释放 IO 引脚
}

/**
 * @brief 由 DS1302 通信总线上读取一个字节
*/
unsigned char DS1302ByteRead() {
	unsigned char mask;
	unsigned char dat = 0;
	for (mask=0x01; mask!=0; mask<<=1) {//低位在前，逐位读取
		if (DS1302_IO != 0) {//首先读取此时的 IO 引脚，并设置 dat 中的对应位
			dat |= mask;
		}
		DS1302_CK = 1; //然后拉高时钟
		DS1302_CK = 0; //再拉低时钟，完成一个位的操作
	}
	return dat; //最后返回读到的字节数据
}

/**
 * @brief 用单次写操作向某一寄存器写入一个字节
 * @param reg 寄存器地址
 * @param dat 数据
*/
void DS1302SingleWrite (unsigned char reg, unsigned char dat) {
	DS1302_CE = 1;      // 使能片选
	DS1302ByteWrite ((reg<<1) | 0x80);  // 发送写寄存器指令
	DS1302ByteWrite (dat);    // 写入字节数据
	DS1302_CE = 0;            // 处能片选信号
}
/**
 * @brief 用单次读操作从某一寄存器读取一个字节
 * @param reg 寄存器地址
 * @return 读到的字节
*/
unsigned char DS1302SingleRead(unsigned char reg) {
	unsigned char dat;
	DS1302_CE = 1;                  //使能片选信号
	DS1302ByteWrite((reg<<1)|0x81); //发送读寄存器指令
	dat = DS1302ByteRead();         //读取字节数据
	DS1302_CE = 0;                  //除能片选信号
	return dat;
}

/**
 * @brief 用突发模式连续写入 8 个寄存器数据
 * @param dat 待写入数据指针
*/
void DS1302BurstWrite(unsigned char *dat) {
	unsigned char i;
	DS1302_CE = 1;
	DS1302ByteWrite(0xBE); //发送突发写寄存器指令
	for (i=0; i<8; i++) {//连续写入 8 字节数据
		DS1302ByteWrite(dat[i]);
	}
	DS1302_CE = 0;
}

/**
 * @brief 用突发模式连续读取 8 个寄存器的数据
 * @param dat 读取数据的接收指针
*/
void DS1302BurstRead(unsigned char* dat) {
	unsigned char i;
	DS1302_CE = 1;
	DS1302ByteWrite(0xBF); //发送突发读寄存器指令
	for (i=0; i<8; i++) {//连续读取 8 个字节
		dat[i] = DS1302ByteRead();
	}
	DS1302_CE = 0;
}
/**
 * @brief 获取实时时间，即读取 DS1302 当前时间并转换为时间结构体格式
*/
void GetRealTime(struct sTime *time) {
	unsigned char buf[8];
	DS1302BurstRead(buf);
	time->year = buf[6] + 0x2000;
	time->mon  = buf[4];
	time->day  = buf[3];
	time->hour = buf[2];
	time->min  = buf[1];
	time->sec  = buf[0];
	time->week = buf[5];
}
/**
 * @brief 设定实时时间，时间结构体格式的设定时间转换为数组并写入 DS1302
*/
void SetRealTime(struct sTime *time) {
	unsigned char buf[8];
	buf[7] = 0;
	buf[6] = time->year;
	buf[5] = time->week;
	buf[4] = time->mon;
	buf[3] = time->day;
	buf[2] = time->hour;
	buf[1] = time->min;
	buf[0] = time->sec;
	DS1302BurstWrite(buf);
}
/**
 * @brief DS1302 初始化，如发生掉电则重新设置初始时间
*/
void InitDS1302() {
	unsigned char i;
	unsigned char InitTime[] = {
		//2013 年 10 月 8 日 星期二 12:30:00
		0x00,0x30,0x12, 0x08, 0x10, 0x02, 0x13
	};
	DS1302_CE = 0;                //初始化 DS1302 通信引脚
	DS1302_CK = 0;
	i = DS1302SingleRead(0);      //读取秒寄存器
	if ((i & 0x80) != 0) {        //由秒寄存器最高位 CH 的值判断 DS1302 是否已停止
		DS1302SingleWrite(7, 0x00);   //撤销写保护以允许写入数据
		for (i=0; i<7; i++) {         //设置 DS1302 为默认的初始时间
			DS1302SingleWrite(i, InitTime[i]);
		}
	}
}



#endif