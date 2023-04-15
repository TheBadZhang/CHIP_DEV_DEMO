#include "spi.h"

#define SPIF B10000000
#define WCOL B01000000

/**
 * @brief SPI 初始化
 * @param spix SPI 初始化结构体指针
 **/
void spi_init (const SPI_Init_t* spix) {
	SPDAT = 0;
	SPSTAT = SPIF | WCOL;
	SPCTL = spix -> MSType | spix -> ClkSrc |
		spix -> Order | spix -> CLType | spix -> Run;
}

/**
 * @brief SPI 发送一个字节
 * @param dat 要发送的数据
 **/
void spi_writeByte (uint8_t dat) {
	SPDAT = dat;			   // 设置待发送的数据
	while (!(SPSTAT & 0x80));  // SPI 忙查
	SPSTAT = B11000000;        // 清除 SPI 中断
}

/**
 * @brief SPI 发送两个字节
 * @param dat 要发送的数据
 **/
void spi_writeWord (uint16_t dat) {
	spi_writeByte (dat >> 8); //写入高8位数据
	spi_writeByte (dat);	  //写入低8位数据
}
/**
 * @brief SPI 发送一串字节
 * @param dats 要发送的数据
 * @param len 数据长度
 **/
void spi_writeBytes (uint8_t* dat, uint8_t len) {
	uint8_t i;
	FOR (i, len) {
		spi_writeByte (dat[i]);
	}
}

/**
 * @brief SPI 接收一个字节
 * @return 接收到的数据
 **/
uint8_t SPI_readByte (void) {
	while (!(SPSTAT & 0x80));  // SPI 忙查
	SPSTAT = B11000000;        // 清除 SPI 中断
	return SPDAT;              // 返回接收到的字节数据
}

