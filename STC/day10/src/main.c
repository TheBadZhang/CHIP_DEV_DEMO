#include "myheader.h"

#define UART_RXD P3_0
#define UART_TXD P3_1

__bit RxdOrTxd = 0;  // 当前的状态是接受还是发送
__bit RxdEnd   = 0;  // 接受结束标志
__bit TxdEnd   = 0;  // 发送结束标志

unsigned char RxdBuf = 0;  // 接收缓冲器
unsigned char TxdBuf = 0;  // 发送缓冲器

void ConfigUART (unsigned int baud);
void   StartTXD (unsigned char data);
void   StartRXD ();
void     RxdTxd () __interrupt 1;


void main () {
	EA = 1;             // 中断使能总开关
	ConfigUART (11520);  // 配置波特率为 9600

	while (1) {
		while (UART_RXD);     // 等待接收引脚出现低电平，即起始位
		// 这里有一点多线程的味道了，不过 这个版本的 c 并没有对多线程有多少支持
		StartRXD ();          // 启动接收
		while (!RxdEnd);      // 等待接收完成
		StartTXD (RxdBuf+1);  // 将接收到的数据发送回去
		while (!TxdEnd);      // 等待发送完成
	}
}

/* 串口配置函数，baud-通信波特率 */
void ConfigUART (unsigned int baud) {
	TMOD &= 0xF0;    // 清空 T0 的 TMOD 配置
	TMOD |= 0x02;    // 设置 T0 的 TMOD 为 0x02
	TH0 = 256 - (11059200/12)/baud;
	// 计算 T0 重载值，即两位数据的间隔
}
/* 启动串行接收 */
void StartRXD () {
	TL0 = 256 - ((256-TH0) >> 1);
	// （根据奈奎斯特定理）设置接收时 T0 为半个波特率周期
	ET0 = 1;    // T0 中断使能
	TR0 = 1;    // 启动 T0
	RxdEnd = 0; // 设置当前的状态为接收
	RxdOrTxd = 0; // 设置当前状态为接收
}
/* 启动串行发送，data-待发送字节数据 */
void StartTXD (unsigned char data) {
	TxdBuf = data;   // 待发送数据保存到发送缓冲器
	TL0 = TH0;       // T0 计数重载
	ET0 = 1;         // T0 中断使能
	TR0 = 1;         // 启动 T0
	UART_TXD = 0;    // 发送起始位
	TxdEnd = 0;      // 清零发送结束标志
	RxdOrTxd = 1;    // 设置当前的状态为发送
}
/* T0 中断服务函数，处理串行发送和接收 */
void RxdTxd () __interrupt 1 {
	static unsigned char cnt = 0;  // 位接收或发送计数

	if (RxdOrTxd) { // 串行发送处理
		++cnt;

		if (cnt <= 8) {
			UART_TXD = TxdBuf & 0x01;
			TxdBuf >>= 1;
		} else if (cnt == 9) {
			UART_TXD = 1; // 发送停止位
		} else {
			cnt = 0;      // 复位计数器
			TR0 = 0;      // 关闭 T0
			TxdEnd = 1;   // 配置发送结束标志
		}
	} else { // 串行接受处理
		if (cnt == 0) {
			if (!UART_RXD) {   // 起始位为 0 时，清空接收缓冲器，准备接收数据位
				RxdBuf = 0;
				++ cnt;
			} else {           // 起始位不为 0 时，终止接收
				TR0 = 0;       // 关闭 T0
			}
		} else if (cnt <= 8) { // 处理 8 位数据
			RxdBuf >>= 1;      // 低位在线，将之前接收的位 右移
			if (UART_RXD) {    // 接收脚为 1 时，缓冲器最高位置 1，
				RxdBuf |= 0x80;// 而为 0 时，不处理，即保持位移后的 0
			}
			++ cnt;
		} else {               // 停止位处理
			cnt = 0;           // 复位 bit 计数器
			TR0 = 0;           // 关闭 T0
			if (UART_RXD) {    // 停止位为 1 时，方能认为数据有效
				RxdEnd = 1;    // 置接收结束标志
			}
		}
	}
}
