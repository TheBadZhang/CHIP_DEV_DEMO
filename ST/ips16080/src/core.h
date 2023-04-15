#ifndef __TBZ_CORE_H_
#define __TBZ_CORE_H_
#include "main.h"
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
/**
 * @brief 简写的 for 循环
 * @param i 要被循环的变量
 * @param x 循环次数 [0,x)
 */

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET
#define GPIO_Pin(name) GPIO_Port(name)##,##Pin(name)
#define GPIO_Port(name) name##_GPIO_Port
#define Pin(name) name##_Pin
#define set(name) HAL_GPIO_WritePin(Pin(name), HIGH)
#define clr(name) HAL_GPIO_WritePin(Pin(name), LOW)
#define FOR0(i,s,e) for (int i = s; i < e; ++i)
#define FOR(i,s,e) for (int i = s; i <= e; ++i)
#define ROF0(i,s,e) for(int i = s; i > e; --i)
#define ROF(i,s,e) for(int i = s; i >= e; --i)
#define DO  {
#define END }
#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint8_t uchar;
typedef uint32_t uint;
void delay_us(uint32_t time);
void core(void);

#ifdef __cplusplus
}
#endif
#endif
