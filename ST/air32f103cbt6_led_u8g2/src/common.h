#ifndef __TBZ_COMMON_H__
#define __TBZ_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
// #include "sys.h"
#include "oled.h"
#include <stdint.h>
// #include <cstdint>
// #include <cstdio>
extern I2C_HandleTypeDef hi2c1;
// extern SPI_HandleTypeDef hspi1;
/**
 * @brief 简写的 for 循环
 * @param i 要被循环的变量
 * @param x 循环次数 [0,x)
 */

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET
// #define GPIO_Pin(name) GPIO_Port(name) ## , ## Pin(name)
#define GPIO_Port(name) name##_GPIO_Port
#define Pin(name) name##_Pin
#define set(name) HAL_GPIO_WritePin(GPIO_Port(name), Pin(name), HIGH)
#define clr(name) HAL_GPIO_WritePin(GPIO_Port(name), Pin(name), LOW)
#define flip(name) HAL_GPIO_TogglePin(GPIO_Port(name), Pin(name))
#define FOR0(i,s,e) for (int i = s; i < e; ++i)
#define FOR(i,s,e) for (int i = s; i <= e; ++i)
#define ROF0(i,s,e) for(int i = s; i > e; --i)
#define ROF(i,s,e) for(int i = s; i >= e; --i)
#define DO  {
#define END }

#ifdef __cplusplus
}
#endif


#endif
