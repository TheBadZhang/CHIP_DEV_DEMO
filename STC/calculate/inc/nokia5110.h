#ifndef LCD_H
#define LCD_H

#include "myheader.h"

#define nokia5110_writeCmd(cmd)   nokia5110_writeByte(cmd, 0)   //写入指令
#define nokia5110_writeDat(dat)   nokia5110_writeByte(dat, 1)   //写入数据

#define nokia5110_showBlank()     nokia5110_writeCmd(0x08)      //显示空白
#define nokia5110_showNormal()    nokia5110_writeCmd(0x0c)      //正常显示
#define nokia5110_showBlack()     nokia5110_writeCmd(0x09)      //显示全黑
#define nokia5110_showReverse()   nokia5110_writeCmd(0x0d)      //反色显示

#define CLK P0_4     //串行时钟         //上升沿写入数据
#define DIN P0_3     //串行数据输入       //先高后低
#define DC  P0_2     //数据指令控制端  //高电平数据，低电平指令
#define CS  P0_1     //片选使能         //低电平有效
#define RST P0_0     //LCD复位端       //低电平复位
#define LED P1_5    //背光灯控制端      //高电平打开LED

extern void nokia5110_writeByte(unsigned char wByte, unsigned char datOrCmd);
extern void nokia5110_clear();//清屏
extern void nokia5110_moveTo(unsigned char x, unsigned char y);
extern void nokia5110_writeChar(unsigned char x, unsigned char y, unsigned char c);
extern void nokia5110_writeString(unsigned char x, unsigned char y, unsigned char *str);
extern void nokia5110_LCDInit(void);

#endif