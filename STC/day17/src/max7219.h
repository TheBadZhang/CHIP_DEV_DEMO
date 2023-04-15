#ifndef __TBZ_MAX7219_H_
#define __TBZ_MAX7219_H_

//定义Max7219端口
#define max7219_CLK P0_2
#define max7219_CS  P0_1
#define max7219_DIN P0_0


extern uchar __code max7219_disp [38][8];
/**
 * @brief 向MAX7219(U3)写入字节
 * @param DATA 待写入的字节数据
 */
void max7219_WriteByte (uchar DATA);
/**
 * @brief 向MAX7219的寄存器写入数据
 * @param addr 寄存器地址
 * @param dat 待写入的数据
 */
#define max7219_Write(addr,dat) max7219_MultiWrite(0,addr,dat)
/**
 * @brief 向MAX7219的寄存器写入数据
 * @param piece 第几块芯片
 * @param addr 寄存器地址
 * @param dat 待写入的数据
 */
void max7219_MultiWrite (uchar piece, uchar addr, uchar dat);
/**
 * @brief 初始化
 */
void max7219_Init (void);


// demo
/*

max7219_Init ();
int i,j = 8, k;
while (1) {
	FOR (j, 38) {
		FOR (k, 4) FOR (i, 8)
			max7219_Write (i+1,max7219_disp[j][i]);
		delay1ms (5000);
	}
}

*/



#endif