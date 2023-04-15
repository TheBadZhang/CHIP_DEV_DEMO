#ifndef __TBZ_SPI_H_
#define __TBZ_SPI_H_
#define __TBZ_BINARY_ENABLE_
#include "myheader.h"

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
__sfr __at(0xcd) SPSTAT;  // SPI 状态寄存器
__sfr __at(0xce) SPCTL;   // SPI 控制寄存器
__sfr __at(0xcf) SPDAT;   // SPI 数据缓冲寄存器

/**
 * @brief SPI 工作类型
 **/
typedef enum SPI_MSType_t {
	SPI_Type_Master_Slave = B00000000,  // SPI 互为主从机模式
	SPI_Type_Master       = B01010000,  // SPI 主机模式
	SPI_Type_Slave        = B01000000,  // SPI 从机模式
} SPI_MSType_t;
/**
 * @brief SPI 时钟源选择
 **/
typedef enum SPI_ClockSource_t {
	SPI_SCLK_DIV_4  = B00000000,  // SPI 系统时钟源  4 分频
	SPI_SCLK_DIV_8  = B00000001,  // SPI 系统时钟源  8 分频
	SPI_SCLK_DIV_16 = B00000010,  // SPI 系统时钟源 16 分频
	SPI_SCLK_DIV_32 = B00000011   // SPI 系统时钟源 32 分频
} SPI_ClockSource_t;
/**
 * @brief SPI 传输类型
 **/
typedef enum SPI_DataOrder_t {
	SPI_Tran_MSB = B00000000,   // 高位优先传输
	SPI_Tran_LSB = B00100000    // 低位优先传输
} SPI_DataOrder_t;
/**
 * @brief     SPI 模式
 **/
typedef enum SPI_ClockType_t {
	SPI_Mode_0  = B00000000, // 前时钟为上升沿，后时钟为下降沿，后时钟沿改变数据，前时钟沿获取数据
	SPI_Mode_1  = B00000100, // 前时钟为下降沿，后时钟为上升沿，后时钟沿改变数据，前时钟沿获取数据
	SPI_Mode_2  = B00001000, // 前时钟为上升沿，后时钟为下降沿，前时钟沿改变数据，后时钟沿获取数据
	SPI_Mode_3  = B00001100  // 前时钟为下降沿，后时钟为上升沿，前时钟沿改变数据，后时钟沿获取数据
} SPI_ClockType_t;

typedef enum SPI_Run_t {
	SPI_Stop = B00000000,
	SPI_Run = B10000000
} SPI_Run_t;

/**
 * @brief   SPI 初始化枚举
 **/
typedef struct SPI_Init_t {
	SPI_MSType_t      MSType;     // SPI 工作类型
	SPI_ClockSource_t ClkSrc;     // SPI 时钟源
	SPI_DataOrder_t   Order;      // SPI 工作模式
	SPI_ClockType_t   CLType;     // SPI 传输类型
	SPI_Run_t         Run;        // SPI 运行控制位
} SPI_Init_t;


/**
 * @brief SPI 初始化
 * @param spix SPI 初始化结构体指针
 **/
void spi_init (const SPI_Init_t* spix);

/**
 * @brief SPI 发送一个字节
 * @param dat 要发送的数据
 **/
void spi_writeByte (uint8_t dat);
/**
 * @brief SPI 发送两个字节
 * @param dat 要发送的数据
 **/
void spi_writeWord (uint16_t dat);
/**
 * @brief SPI 发送一串字节
 * @param dats 要发送的数据
 * @param len 数据长度
 **/
void spi_writeBytes (uint8_t* dat, uint8_t len);

/**
 * @brief SPI 接收一个字节
 * @return 接收到的数据
 **/
uint8_t SPI_readByte (void);


#endif