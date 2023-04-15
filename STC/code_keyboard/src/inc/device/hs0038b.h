#ifndef __TBZ_HS0038B_H_
#define __TBZ_HS0038B_H_

#include "myheader.h"


#define IR_INPUT P3_3      //红外接收引脚
__bit irflag = 0;          //红外接收标志，收到一帧正确数据后置 1
unsigned char ircode[4];   //红外代码接收缓冲区
/**
 * @brief 初始化红外接收功能
 */
void InitInfrared() {
	IR_INPUT = 1;          //确保红外接收引脚被释放
	TMOD &= 0x0F;          //清零 T1 的控制位
	TMOD |= 0x10;          //配置 T1 为模式 1
	TR1 = 0;               //停止 T1 计数
	ET1 = 0;               //禁止 T1 中断
	IT1 = 1;               //设置 INT1 为负边沿触发
	EX1 = 1;               //使能 INT1 中断
}
/**
 * @brief 获取当前高低电平的持续时间
 */
unsigned int GetVoltageTime(unsigned char voltage) {
	TH1 = 0;         //清零 T1 计数初值
	TL1 = 0;
	TR1 = 1;         //启动 T1 计数
	while (IR_INPUT == voltage) {//红外输入引脚为 1 时循环检测等待，变为 0 时则结束本循环
		if (TH1 >= 0x40) {
		           //当 T1 计数值大于 0x4000，即高电平持续时间超过约 18ms 时，
			break; //强制退出循环，是为了避免信号异常时，程序假死在这里。
		}
	}
	TR1 = 0;                  //停止 T1 计数
	return BIND2BYTE (TH1,TL1); //T1 计数值合成为 16bit 整型数，并返回该数
}

/**
 * @brief 判断一个数字是否在 [a,b] 的范围内
 * @param _times 数字
 * @param _left 左边界
 * @param _right 右边界
 */
#define IN_RANGE(_times, _left, _right) \
	_left <= _times && _times <= _right

/**
 * @brief 判断时间是否在 [a,b] 的范围内，不是则退出函数
 * @param _times 时间
 * @param _left 左边界
 * @param _right 右边界
 */
#define TIME_NOT_IN_RANGE(_time, _left, _right) \
	if (NOT(IN_RANGE(_time,_left,_right))) {    \
		    /*超过此范围则说明为误码，直接退出*/   \
		IE1 = 0;   /*退出前清零 INT1 中断标志*/   \
		return ;                                \
	}
/**
 * @brief 判断某个电位的时间是否在 [a,b] 的范围内
 */
#define VOLTAGE_TIME_NOT_IN_RANGE(_voltage, _left, _right) \
	TIME_NOT_IN_RANGE(GetVoltageTime(_voltage),_left,_right);
/**
 * @brief INT1 中断服务函数，执行红外接收及解码
 */
void HS0038B_INT () __interrupt INT1 {

	unsigned char i, j;
	unsigned char byt;
	unsigned int time;
	//接收并判定引导码的 9ms   低电平
	VOLTAGE_TIME_NOT_IN_RANGE (LOW, 7833, 8755);  //时间判定范围为 8.5～9.5ms，
	//接收并判定引导码的 4.5ms 高电平
	VOLTAGE_TIME_NOT_IN_RANGE (HIGH, 3686, 4608);  //时间判定范围为 4.0～5.0ms，
	//接收并判定后续的 4 字节数据
	FOR (i, 4) {//循环接收 4 个字节
		FOR (j, 8) {//循环接收判定每字节的 8 个 bit
			//接收判定每 bit 的 560us 低电平
			VOLTAGE_TIME_NOT_IN_RANGE (LOW, 313, 718);  //时间判定范围为 340～780us，
			//接收每 bit 高电平时间，判定该 bit 的值
			time = GetVoltageTime(HIGH);
			if (NOT(IN_RANGE(time,313,718))) {    //时间判定范围为 340～780us，
				                                  //在此范围内说明该 bit 值为 0
				byt >>= 1;                        //因低位在先，所以数据右移，高位为 0
			} else if (IN_RANGE(time,1345,1751)) {//时间判定范围为 1460～1900us，
			                                      //在此范围内说明该 bit 值为 1
				byt >>= 1;                        //因低位在先，所以数据右移，
				byt |= 0x80;                      //高位置 1
			} else {//不在上述范围内则说明为误码，直接退出
				IE1 = 0;
				return;
			}
		}
		ircode[i] = byt; //接收完一个字节后保存到缓冲区
	}
	irflag = 1; //接收完毕后设置标志
	IE1 = 0;    //退出前清零 INT1 中断标志
}

#endif
