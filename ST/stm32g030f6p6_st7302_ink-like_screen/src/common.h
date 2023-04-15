#ifndef __TBZ_COMMON_H__
#define __TBZ_COMMON_H__
#include "main.h"
// #include "oled.h"
#include "sys.h"
// #include "mpu6050.h"
// #include <cstdint>
// #include <cstdio>
// extern UART_HandleTypeDef huart2;
// extern I2C_HandleTypeDef hi2c2;
extern SPI_HandleTypeDef hspi1;
// extern UART_HandleTypeDef huart1;
// extern UART_HandleTypeDef huart2;
// extern I2C_HandleTypeDef hi2c1;
// extern I2C_HandleTypeDef hi2c2;
/**
 * @brief 简写的 for 循环
 * @param i 要被循环的变量
 * @param x 循环次数 [0,x)
 */

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET
// #define GPIO_Pin(name) GPIO_Port(name) ## , ## Pin(name)
// #define GPIO_Port(name) name##_GPIO_Port
// #define Pin(name) name##_Pin
// #define set(name) HAL_GPIO_WritePin(Pin(name), HIGH)
// #define clr(name) HAL_GPIO_WritePin(Pin(name), LOW)


#define set(io) HAL_GPIO_WritePin(io##_GPIO_Port, io##_Pin, GPIO_PIN_SET)
#define clr(io) HAL_GPIO_WritePin(io##_GPIO_Port, io##_Pin, GPIO_PIN_RESET)
#define toggle(io) HAL_GPIO_TogglePin(io##_GPIO_Port, io##_Pin)
#define FOR0(i,s,e) for (int i = s; i < e; ++i)
#define FOR(i,s,e) for (int i = s; i <= e; ++i)
#define ROF0(i,s,e) for(int i = s; i > e; --i)
#define ROF(i,s,e) for(int i = s; i >= e; --i)
#define DO  {
#define END }
#endif