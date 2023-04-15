#ifndef __TBZ_LCD1602_H_
#define __TBZ_LCD1602_H_

// 针脚的定义
#ifdef __SDCC
#define LCD1602_DB  P0
#define LCD1602_RS  P1_0
#define LCD1602_RW  P1_1
#define LCD1602_E   P1_5
#define LCD1602_BLA P2_6
#else
#define LCD1602_DB  = P0
sbit LCD1602_RS  = P1^0;
sbit LCD1602_RW  = P1^1;
sbit LCD1602_E   = P1^5;
sbit LCD1602_BLA = P2^6;
#endif
/**
 * @brief 初始化液晶，并等待液晶准备完成
 */
void lcdWaitReady () {
	unsigned char sta;
	LCD1602_DB = 0xff;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do {
		LCD1602_E = 1;
		sta = LCD1602_DB;
		LCD1602_E = 0;
	} while (sta & 0x80);
}
#ifdef __TBZ_ARGS_ENABLE_
/**
 * @brief 向 LCD1602 写入一个字节命令
 * @param cmd 待写入值
 */
void lcdWriteCmd (unsigned char cmd, ...) {
	va_list p_args;
	va_start (p_args, cmd);
	unsigned char idx, val;
	FOR (idx,cmd) {
		lcdWaitReady ();
		LCD1602_RS = 0;
		LCD1602_RW = 0;
		LCD1602_DB = cmd;
		LCD1602_E = 1;
		LCD1602_E = 0;
	}
#else
/**
 * @brief 向 LCD1602 写入一个字节命令
 * @param cmd 待写入值
 */
void lcdWriteCmd (unsigned char cmd) {
	lcdWaitReady ();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
#endif
}
/**
 * @brief 向 LCD1602 指定位置写入一个字符
 * @param dat 写入的字节数据
 */
void lcdWriteChar (unsigned char dat) {
	lcdWaitReady ();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}
/**
 * @brief 设置当前坐标
 * @param x 第几列
 * @param y 第几行
 */
void lcdSetCursor (unsigned char x, unsigned char y) {
	// unsigned char addr;
	// if (y) { // 当 y 非 0 时，往第二排写入 
	// 	addr = 0x40 + x;
	// } else { // 否则，第一排
	// 	addr = 0x00 + x;
	// }
	// addr = x + ((y&1) << 6);
	// 设置 RAM 地址
	lcdWriteCmd ((x + ((y&1) << 6)) | 0x80);
}

/**
 * @brief 对 LCD1602 上面的文字进行修改
 * @param x 第几列
 * @param y 第几行
 * @param str 要写入的字符串
 */
void lcdPrint (unsigned char x, unsigned y, unsigned char* str) {
	P1 = B00010010; // 设置 P1 的值，使 P0 不会作用到其他灯上
	while (*str) {
		lcdSetCursor (x, y++);
		lcdWriteChar (*str++);
	}
}
/**
 * @brief 初始化 LCD1602
 */
void initLCD1602 (void) {
#ifdef __TBZ_ARGS_ENABLE_
	lcdWriteCmd (0x38, 0x0c, 0x06, 0x01);
#else
	lcdWriteCmd (0x38);    // 16*2 显示, 5*7 点阵，8 位数据接口
	lcdWriteCmd (0x0c);    // 显示器开，光标关闭
	lcdWriteCmd (0x06);    // 文字不动，地址自动+1
	lcdWriteCmd (0x01);    // 清屏
#endif
}

#undef LCD1602_DB
#endif