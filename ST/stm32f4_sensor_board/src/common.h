#ifndef __TBZ_COMMON_H__
#define __TBZ_COMMON_H__
#include "main.h"
#include "trick.h"
#include "sys.h"
// #include "mpu6050.h"
#include <cstdint>
#include <cstdio>

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_tx;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

#endif