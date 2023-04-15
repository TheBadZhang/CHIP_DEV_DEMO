#ifndef __TBZ_FONT_0x_
#define __TBZ_FONT_0x_

//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:12*6
/************************************6*8的点阵************************************/
extern const unsigned char __code font0608[][6];
/****************************************8*16的点阵************************************/
extern const unsigned char __code font0816[];
/*--------------------------------------------------------------*/
//    字体:   Fixedsys
//取码规则: 低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//查表方法: 要显示的ASCII码-32就可以得到字库码的指针
extern unsigned char __code font_Fixedsys[][16];

//汉字取模
extern unsigned char __code font_chinese[][32];
typedef struct typFNT_GBK16 {
       unsigned char index[2];
       char mask[32];
} typFNT_GBK16_t;
//宋体5号
//中文显示测试全动电子欢迎您因为专业所以注　
extern typFNT_GBK16_t __code hz16[];
#endif
