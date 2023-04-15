#include "spi.h"

#define SPIF B10000000
#define WCOL B01000000

/**
 * @brief SPI ��ʼ��
 * @param spix SPI ��ʼ���ṹ��ָ��
 **/
void spi_Init (const SPI_Init_t* spix) {
	SPDAT = 0;
	SPSTAT = SPIF | WCOL;
	SPCTL = spix -> MSType | spix -> ClkSrc |
		spix -> Order | spix -> CLType | spix -> Run;
}

/**
 * @brief SPI ����һ���ֽ�
 * @param dat Ҫ���͵�����
 **/
void spi_writeByte (uint8_t dat) {
	SPDAT = dat;			   // ���ô����͵�����
	while (!(SPSTAT & 0x80));  // SPI æ��
	SPSTAT = B11000000;        // ��� SPI �ж�
}

/**
 * @brief SPI ����һ���ֽ�
 * @param dats Ҫ���͵�����
 * @param len ���ݳ���
 **/
void spi_writeBytes (uint8_t* dat, uint8_t len) {
	uint8_t i;
			P1_2 = 0;
	FOR (i, len) {
		spi_writeByte (dat[i]);
	}
			P1_2 = 1;
}

/**
 * @brief SPI ����һ���ֽ�
 * @return ���յ�������
 **/
uint8_t SPI_readByte (void) {
	while (!(SPSTAT & 0x80));  // SPI æ��
	SPSTAT = B11000000;        // ��� SPI �ж�
	return SPDAT;              // ���ؽ��յ����ֽ�����
}

