#ifndef __TBZ_COMMON_H__
#define __TBZ_COMMON_H__
#include "main.h"
// #include "oled.h"
#include "sys.h"
#include "trick.h"
#include <cstdint>
#include <cstdio>

// extern UART_HandleTypeDef huart2;
// extern I2C_HandleTypeDef hi2c2;
// extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim17;
// extern DMA_HandleTypeDef hdma_tim3_up;

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac3;
extern DMA_HandleTypeDef hdma_dac1_ch1;
extern DMA_HandleTypeDef hdma_dac3_ch2;

extern OPAMP_HandleTypeDef hopamp1;
extern OPAMP_HandleTypeDef hopamp3;
#endif