#ifndef __TBZ_TTP229_H_
#define __TBZ_TTP229_H_

#include "myheader.h"
#include "keyboard_vk.h"
#include "ttp229_vk.h"

#define SDA P1_0
#define SCL P1_1

/**
 * @brief 获取触控键盘的数据
 * @return 返回获取到的按键数据
 * @retval 十六位整形，一个位对应一个按键
 */
uint TTP229B_get (void);

#endif