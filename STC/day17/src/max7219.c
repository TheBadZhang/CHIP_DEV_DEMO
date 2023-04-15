#include "myheader.h"
#include "max7219.h"


/*   MAX7219 寄存器地址与功能

寄存器名称      寄存器地址
-------------------------
不操作			0x00
digit[0-7]     0x01 - 0x08
解码模式        0x09
	不解码				B00000000    //* 选择哪位，就给哪位进行 BCD 解码
	为 digit0 解码		B00000001    //* 点阵屏无需 BCD 解码
	为 digit[0-3] 解码	B00001111    //* 译码器只对数据的低四位进行译码（D3-D0），D4-D6 为无效位
	为 digt [0-7] 解码  B11111111    //* D7 位用来设置小数点，不受译码器的控制且为高电平
显示亮度               0x0a     //* 总共有 16 级亮度，但是最亮不是最亮，最暗不是关掉
	亮度0				0x00
	亮度1				0x01
	亮度2				0x02
	亮度3				0x03
	亮度4				0x04
	亮度5				0x05
	亮度6				0x06
	亮度7				0x07
	亮度8				0x08
	亮度9				0x09
	亮度10				0x0a
	亮度11				0x0b
	亮度12				0x0c
	亮度13				0x0d
	亮度14				0x0e
	亮度15				0x0f
扫描限制               0x0b      //* 选择哪些 ditgit 会被显示
	digit0       		0x00
	digit0&1     		0x01
	digit0&1&2   		0x02
	....
	digit0&1&2&3&4&5&6&7 0x07
掉电模式（停机模式）	0x0c       //* 默认掉电模式是开启的
	掉电模式			0x00
	正常模式			0x01
屏幕测试               0x0f
	正常模式			0x00
	测试模式			0x01

*/


uchar __code max7219_disp [38][8]={
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
	{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
	{0x7E,0x02,0x02,0x7E,0x40,0x40,0x40,0x7E},//2
	{0x3E,0x02,0x02,0x3E,0x02,0x02,0x3E,0x00},//3
	{0x08,0x18,0x28,0x48,0xFE,0x08,0x08,0x08},//4
	{0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C,0x00},//5
	{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x00},//6
	{0x3E,0x22,0x04,0x08,0x08,0x08,0x08,0x08},//7
	{0x00,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
	{0x3E,0x22,0x22,0x3E,0x02,0x02,0x02,0x3E},//9
	{0x08,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
	{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x00},//B
	{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x00},//C
	{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x00},//D
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
	{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
	{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
	{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
	{0x3C,0x08,0x08,0x08,0x08,0x08,0x48,0x30},//J
	{0x00,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
	{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
	{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
	{0x00,0x42,0x62,0x52,0x4A,0x46,0x42,0x00},//N
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
	{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
	{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
	{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
	{0x00,0x1E,0x20,0x20,0x3E,0x02,0x02,0x3C},//S
	{0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08},//T
	{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
	{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
	{0x00,0x49,0x49,0x49,0x49,0x2A,0x1C,0x00},//W
	{0x00,0x41,0x22,0x14,0x08,0x14,0x22,0x41},//X
	{0x41,0x22,0x14,0x08,0x08,0x08,0x08,0x08},//Y
	{0x00,0x7F,0x02,0x04,0x08,0x10,0x20,0x7F},//Z
	{0x08,0x7F,0x49,0x49,0x7F,0x08,0x08,0x08},//中
	{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//国
};

/**
 * @brief 向MAX7219(U3)写入字节
 * @param DATA 待写入的字节数据
 */
void max7219_WriteByte (uchar DATA) {
	uchar i;
	max7219_CS = 0;
	FOR (i, 8) {
		max7219_CLK = 0;
		max7219_DIN = DATA&0x80;
		DATA <<= 1;
		max7219_CLK = 1;
	}
}

/**
 * @brief 向MAX7219的寄存器写入数据
 * @param piece 第几块芯片
 * @param addr 寄存器地址
 * @param dat 待写入的数据
 */
void max7219_MultiWrite (uchar piece, uchar addr, uchar dat) {
	uchar i;
	max7219_CS = 0;
	max7219_WriteByte (addr);     // 写入地址
	max7219_WriteByte (dat);      // 写入数据
	max7219_CLK = 1;
	FOR (i, piece) {                 // 级联时，NO-OP，操作是在这个地方写的，当片选变成1时，
		max7219_WriteByte (0x00);    // 级联的选片就失效了，一定是连续写入，不停止的那种
		max7219_WriteByte (0x00);
	}
	max7219_CS = 1;
}
// void max7219_Init (uchar mode, uchar intensity, uchar scan_limit) {
/**
 * @brief 初始化
 */
void max7219_Init (void) {
	max7219_Write(0x09, 0x00);       // 译码方式：不译码
	max7219_Write(0x0a, 0x00);       // 亮度3
	max7219_Write(0x0b, 0x07);       // 扫描界限；8个数码管显示
	max7219_Write(0x0c, 0x01);       // 掉电模式：0，普通模式：1
	max7219_Write(0x0f, 0x00);       // 显示测试：1；测试结束，正常显示：0
}
