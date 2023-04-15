#ifndef __TBZ_LCMLCD4_H_
#define __TBZ_LCMLCD4_H_
#define __STC15W4K32S
#include "myheader.h"

#define LCD4_DATA P0
#define LCD4_COM1 P1_3
#define LCD4_COM2 P1_2
#define LCD4_COM3 P1_1
#define LCD4_COM4 P1_0




/*
error code list:

E000: out of range 数据超出显示范围

*/



/**
 * @brief 显示内容
 */
void lcmlcd4_show (void);
/**
 * @brief 将数字转换到缓存中
 * @param num 要显示的内容（暂不支持浮点数）[-999, 9999]
 */
void lcmlcd4_t2n (int num);



#endif