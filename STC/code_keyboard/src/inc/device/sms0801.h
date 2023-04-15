#ifndef __TBZ_SMS0801_H_
#define __TBZ_SMS0801_H_

//-------------------------------------------------------------------------------
//SMS0801B产品引脚说明
//PIN1: VSS [电源地]
//PIN2: VSS [电源地]
//PIN3: CLK [串行移位脉冲输入]
//PIN4: VDD [电源正极]
//PIN5: VDD [电源正极]
//PIN6: DI  [串行数据输入]
//-------------------------------------------------------------------------------
#define CLK P1_2   // 负脉冲触发
#define  DI P1_5
#define SMS_DELAY() \
	_nop_();        \
	_nop_();
unsigned char num_ram [8] = {0};
unsigned char num_point = 0x04;   // 小数点的位置
//-------------------------------------------------------------------------------
//数码笔段定义:  8字的最上面一笔段为A笔段,顺时针方向依次为BCDEF笔段,中间的是G笔段
//数码笔段顺序:  D76543210
//               ABCDE GX
unsigned char NUMCODETAB[] = { 0xFC, 0x60, 0xDA, 0xF2,	 // 数字0,1,2,3
							   0x66, 0xB6, 0xBE, 0xE0,	 // 数字4,5,6,7
							   0xFE, 0xF6, 0x00, 0x02,	 // 数字8,9,字符空格,字符-
							   0x9C, 0xCE, 0x9E, 0x8E }; // 字符C,字符P,字符E,字符F
/**
 * @brief 将整数切割到数组中
 * @param num 整数
 */
void SMS0801_t2n (signed long num) { // long 范围为 -2147483648-2147483647

	memset (num_ram, sizeof (num_ram), 0xa);    // 清空当前数据
	if (num) for (j = 7; num > 0; -- j){        // 将数据存到
		num_ram [j] = num % 10;
		num /= 10;
	}
	else num_ram [7] = 0;
}
/**
 * @brief LCD液晶显示控制器子程序
 */ 
void transram(void) {
	unsigned char buf;
	unsigned char mask, i, j;

	for (mask = 0x80, i = 0; mask != 0x00; mask >>= 1, i++) {
		buf = 0x00;							  // 当前译码数据置初始值
											  // 需译码的BIT为ABCDEFGZ位
		buf |= NUMCODETAB[num_ram[i]] & 0xfe; // 第1个8字的ABCDEFG笔段译码
		if ((num_point & mask) != 0)		  // 第1个标志[H1]译码
			buf |= 0x01;
		for (j = 0; j < 8; j++) {             // 从低到高位送字节位数据到液晶显示控制器
			DI = (buf>>j) & 0x1;              // 先送数据到数据口线DI
			SMS_DELAY ();
			CLK = 1;                          // 再使时钟口线发一个负脉冲
			SMS_DELAY ();
			CLK = 0;
			SMS_DELAY ();
			CLK = 1;
		}
	}
}

#endif