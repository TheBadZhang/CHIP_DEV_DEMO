#ifndef __TBZ_HT1621_H_
#define __TBZ_HT1621_H_

#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"

#define sbi(x,y)  (x |= (1 << y))   /*置位寄器x的第y位*/
#define cbi(x,y)  (x &= ~(1 <<y ))  /*清零寄器x的第y位*/

// 高电位点亮，低点位熄灭

//定义HT1621的命令
#define  ComMode    0x52  // 4COM,1/3bias  1000    010 1001  0
#define  RCosc      0x30  // 内部 RC 振荡器(上电默认)1000 0011 0000
#define  LCD_on     0x06  // 打开 LCD 偏压发生器1000     0000 0 11 0
#define  LCD_off    0x04  // 关闭 LCD显示
#define  Sys_en     0x02  // 系统振荡器开 1000   0000 0010
#define  CTRl_cmd   0x80  // 写控制命令
#define  Data_cmd   0xa0  // 写数据命令

//定义端口HT1621数据端口
#define DATA P0_7
#define WR   P0_6   // 上升沿触发
#define CS   P0_5   // 低电平选中

#define write_data_begin WR=0
#define write_data_end   WR=1
#define choose_ht1621    CS=0
#define unchose_ht1621   CS=1

const char ht1621_num [] = {
	0x7D, 0x60, 0x3E, 0x7A, // 0, 1, 2, 3
	0x63, 0x5B, 0x5F, 0x70, // 4, 5, 6, 7
	0x7F, 0x7B, 0x77, 0x4F, // 8, 9, A, b
	0x1D, 0x0E, 0x6E, 0x1F, // C, c, d, E
	0x17, 0x67, 0x47, 0x0D, // F, H, h, L
	0x46, 0x75, 0x37, 0x06, // n, N, o, P
	0x0F, 0x6D, 0x02, 0x00  // r, t, U, -,
};
char ht1621_numbuf [6] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06
};


// sbi(ht1621_numbuf[5],7);   //显示电池图标顶部
// cbi(dispnum[5],7); //清除电池图标顶部
// sbi(ht1621_numbuf[4],7);   //显示电池图标中部
// cbi(dispnum[4],7); //清除电池图标中部
// sbi(ht1621_numbuf[3],7);   //显示电池图标底部
// cbi(dispnum[3],7); //清除电池图标底部


//延时约1ms
void ht1621_delay(uint a) {
	uint i;
	while (--a!=0) for(i=600;i>0;i--);   //1T单片机i=600，若是12T单片机i=125
}

/**
 * @brief 向ht1621发送数据
 * @param sdata 数据的高位先写入HT1621，高位在前
 * @param cnt 数据写入的位长度
 */
void ht1621_writeBits (uchar sdata,uchar cnt) {
	uchar i;
	FOR (i, cnt) {
		write_data_begin;
		DATA = sdata&0x80;
		write_data_end;
		sdata<<=1;
	}
}
//送命令
void ht1621_sendCMD (uchar command) {
	choose_ht1621;
	ht1621_writeBits (0x80, 4);    //写入标志码“100”和9 位command 命令，由于
	ht1621_writeBits (command, 8); //没有使有到更改时钟输出等命令，为了编程方便
	unchose_ht1621;               //直接将command 的最高位写“0”
}
//送数据和命令程序
void ht1621_write (uchar addr,uchar sdata) {
	addr <<= 2;
	choose_ht1621;
	ht1621_writeBits (0xa0, 3);     // 写入标志码“101”
	ht1621_writeBits (addr, 6);     // 写入addr 的高6位
	ht1621_writeBits (sdata, 8);    // 写入data 的8位
	unchose_ht1621;
}
/**
 * @brief ht1621 memeset
 */
void ht1621_all (uchar disp) {
	uchar i;
	FOR (i, 16) ht1621_write (2*i, disp);
}

//初始化1621
void ht1621_init (void) {
	ht1621_sendCMD (Sys_en);
	ht1621_sendCMD (RCosc);
	ht1621_sendCMD (ComMode);
	ht1621_sendCMD (LCD_on);
}
 //显示数组数据p为小数点位置
void ht1621_setpoint (int p) {
	sbi(ht1621_numbuf[p],7);
}

void ht1621_show (void) {
	uchar i;
	FOR (i, 6) {
		ht1621_write (i*2, ht1621_num[ht1621_numbuf[i]]);
	}
}

/**
 * @brief 将整数切割到数组中
 * @param num 整数
 */
void ht1621_t2n (signed long num) { // long 范围为 -2147483648-2147483647
	uchar i;
	memset (ht1621_numbuf, sizeof (ht1621_numbuf), 27);    // 清空当前数据
	if (num) FOR (i,6) {        // 将数据存到
		ht1621_numbuf [i] = num % 10;
		num /= 10;
	} else ht1621_numbuf [0] = 0;
}
#undef write_data_begin
#undef write_data_end
#undef choose_ht1621
#undef unchose_ht1621
//定义HT1621的命令
#undef ComMode
#undef RCosc
#undef LCD_on
#undef LCD_off
#undef Sys_en
#undef CTRl_cmd
#undef Data_cmd

#undef DATA
#undef WR
#undef CS

#endif

// https://blog.csdn.net/qq_43188920/article/details/82773994

/** 样例程序
#define __TBZ_KEYBOARD_ENABLE_
#define __STC15W4K32S
#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"
#include "ht1621.h"

void main() {
	P0M1 = 0x00;
	P0M0 = 0x00;

	ht1621_delay(1);
	ht1621_init ();
	ht1621_all (0xff); //全部点亮1621
	ht1621_delay (1000);
	ht1621_all (0x00); //全部熄灭1621
	ht1621_show ();
	int num = 0;
	while(1) {
		ht1621_t2n (num++);
		ht1621_delay (100);
		ht1621_show ();
	}
}

*/

