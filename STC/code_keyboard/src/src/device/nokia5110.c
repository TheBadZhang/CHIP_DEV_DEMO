#include "device/nokia5110.h"
#include "device/font.h"
#include "binary.h"


#define HEIGHT 6
#define WIDTH 84

// 当 D/C 为 0（命令） //
/*************************************************/
#define FUNCTION_SET B00100000  // 掉电模式/进入模式/扩展指令设置（H）
				   // 00100PVH
#define P   B00000100    // 0 芯片是活动的 1 芯片处于掉电状态
#define V   B00000010    // 0 水平寻址 1 垂直寻址
#define H   B00000001    // 0 使用基本指令集 1 使用扩展指令集
/*************************************************/
// when not H  //
/*************************************************/
#define DISPLAY_SET B00001000   // 设置显示配置
				//   00001D0E
#define DE_BLANK B00000000    // 显示空白
#define DE_NORMAL B00000100   // 普通模式
#define DE_ALL B00000001      // 开所有显示段
#define DE_INVERT B00000101   // 反转映像模式
/*************************************************/
#define RAM_Y B01000000  // 设置 RAM 的 Y 地址 [0,5]
			// 01000YYY
#define RAM_X B10000000  // 设置 RAM 的 X 地址 [0,83]
			// 1XXXXXXX
/*************************************************/
// when H //
/*************************************************/
#define TEMP_K B00000100
#define TC0 B00000000
#define TC1 B00000001
#define TC2 B00000010
#define TC3 B00000011
/*************************************************/
#define BIAS B00010000     // 设置液晶偏振
#define BS0  B00010000
#define BS1  B00010001
#define BS2  B00010010
#define BS3  B00010011
#define BS4  B00010100
#define BS5  B00010101
#define BS6  B00010110
#define BS7  B00010111
/*************************************************/
// 当 D/C 为 1（数据）

/**
 * @brief 写入一个字节(数据或指令)
 * @param wByte 待写入的数据
 * @param datOrCmd
 *           1-数据
 *           0-指令
 */
void nokia5110_writeByte(uchar wByte, uchar datOrCmd) {
	unsigned char i = 8;

	CS = 0;         // 选片
	DC = datOrCmd;  // 1-数据  //0-指令
	while (i) {     // 8位数据, 先高后低
		--i;
		DIN = (wByte >> i) & 0x01;
		CLK = 0;
		delay (1);
		CLK = 1;    //上升沿写入
	}
	CS = 1;         // 禁止
}

/**
 * @brief 清空屏幕上所有的内容（设为0）
 */
void nokia5110_clear() {
	unsigned int i;               // 需要为基本指令集时
	nokia5110_moveTo (0, 0);
	FOR (i, WIDTH*HEIGHT)         // 遍历 5110 中每一个字节
		nokia5110_writeDat(0x00);           // 将所有RAM写0

}

/**
 * @brief 设置写数据位置
 * @param x [0,83]
 * @param y [0, 5]
 */
void nokia5110_moveTo(uchar x, uchar y) {
	nokia5110_writeCmd(RAM_X|x);         // 设置 Y 坐标
	nokia5110_writeCmd(RAM_Y|y);         // 设置 X 坐标
}

/**
 * @brief 写一个字符
 * @param x [0,9]
 * @param y [0,2]
 */
void nokia5110_writeChar(uchar x, uchar y, uchar c) {

	unsigned char i, j;
	c -= 32;
	x <<= 3;
	y <<= 1;
	FOR (j, 2) {
		nokia5110_moveTo(x, (y + j));
		FOR (i, 8) nokia5110_writeDat(font_Fixedsys[c][8 * j + i]);
	}
}

/**
 * @brief 写一个字符串
 * @param x [0,9]
 * @param y [0,2]
 */
void nokia5110_writeString(uchar x, uchar y, uchar *str) {
	while(*str && x < 10) {
		nokia5110_writeChar(x++, y, *str++);
	}
}

void nokia5110_LCDInit(void) {
	RST = 0;
	RST = 1;           //硬件复位

	nokia5110_writeCmd (FUNCTION_SET|H);        // 工作模式, 水平寻址, 扩展指令
	nokia5110_writeCmd (TEMP_K|TC0);            // VLCD 温度系数,设置0x04~0x07,越小越黑
	nokia5110_writeCmd (BIAS|BS3);              // 设置偏置系统(BSx) 1:48,设置为0x10~0x17
	nokia5110_writeCmd (128+65);                // 设置电压VLCD = 3.06 + 0.06*Vop, 对比度调整,设置为0x80~0xff;128+(0~127)

	nokia5110_writeCmd (FUNCTION_SET);          // 工作模式, 水平寻址, 常规指令
	nokia5110_writeCmd (DISPLAY_SET|DE_NORMAL); // 普通模式

	nokia5110_moveTo (0, 0);
	nokia5110_clear ();                         // 清全屏
}

