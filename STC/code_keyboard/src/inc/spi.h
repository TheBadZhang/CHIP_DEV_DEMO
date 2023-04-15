#ifndef __TBZ_SPI_H_
#define __TBZ_SPI_H_
#define __TBZ_BINARY_ENABLE_
#include "myheader.h"

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
__sfr __at(0xcd) SPSTAT;  // SPI ״̬�Ĵ���
__sfr __at(0xce) SPCTL;   // SPI ���ƼĴ���
__sfr __at(0xcf) SPDAT;   // SPI ���ݻ���Ĵ���

/**
 * @brief SPI ��������
 **/
typedef enum SPI_MSType_t {
	SPI_Type_Master_Slave = B00000000,  // SPI ��Ϊ���ӻ�ģʽ
	SPI_Type_Master       = B01010000,  // SPI ����ģʽ
	SPI_Type_Slave        = B01000000,  // SPI �ӻ�ģʽ
} SPI_MSType_t;
/**
 * @brief SPI ʱ��Դѡ��
 **/
typedef enum SPI_ClockSource_t {
	SPI_SCLK_DIV_4  = B00000000,  // SPI ϵͳʱ��Դ  4 ��Ƶ
	SPI_SCLK_DIV_8  = B00000001,  // SPI ϵͳʱ��Դ  8 ��Ƶ
	SPI_SCLK_DIV_16 = B00000010,  // SPI ϵͳʱ��Դ 16 ��Ƶ
	SPI_SCLK_DIV_32 = B00000011   // SPI ϵͳʱ��Դ 32 ��Ƶ
} SPI_ClockSource_t;
/**
 * @brief SPI ��������
 **/
typedef enum SPI_DataOrder_t {
	SPI_Tran_MSB = B00000000,   // ��λ���ȴ���
	SPI_Tran_LSB = B00100000    // ��λ���ȴ���
} SPI_DataOrder_t;
/**
 * @brief     SPI ģʽ
 **/
typedef enum SPI_ClockType_t {
	SPI_Mode_0  = B00000000, // ǰʱ��Ϊ�����أ���ʱ��Ϊ�½��أ���ʱ���ظı����ݣ�ǰʱ���ػ�ȡ����
	SPI_Mode_1  = B00000100, // ǰʱ��Ϊ�½��أ���ʱ��Ϊ�����أ���ʱ���ظı����ݣ�ǰʱ���ػ�ȡ����
	SPI_Mode_2  = B00001000, // ǰʱ��Ϊ�����أ���ʱ��Ϊ�½��أ�ǰʱ���ظı����ݣ���ʱ���ػ�ȡ����
	SPI_Mode_3  = B00001100  // ǰʱ��Ϊ�½��أ���ʱ��Ϊ�����أ�ǰʱ���ظı����ݣ���ʱ���ػ�ȡ����
} SPI_ClockType_t;

typedef enum SPI_Run_t {
	SPI_Stop = B00000000,
	SPI_Run = B10000000
} SPI_Run_t;

/**
 * @brief   SPI ��ʼ��ö��
 **/
typedef struct SPI_Init_t {
	SPI_MSType_t      MSType;     // SPI ��������
	SPI_ClockSource_t ClkSrc;     // SPI ʱ��Դ
	SPI_DataOrder_t   Order;      // SPI ����ģʽ
	SPI_ClockType_t   CLType;     // SPI ��������
	SPI_Run_t         Run;        // SPI ���п���λ
} SPI_Init_t;


/**
 * @brief SPI ��ʼ��
 * @param spix SPI ��ʼ���ṹ��ָ��
 **/
void spi_init (const SPI_Init_t* spix);

/**
 * @brief SPI ����һ���ֽ�
 * @param dat Ҫ���͵�����
 **/
void spi_writeByte (uint8_t dat);
/**
 * @brief SPI ���������ֽ�
 * @param dat Ҫ���͵�����
 **/
void spi_writeWord (uint16_t dat);
/**
 * @brief SPI ����һ���ֽ�
 * @param dats Ҫ���͵�����
 * @param len ���ݳ���
 **/
void spi_writeBytes (uint8_t* dat, uint8_t len);

/**
 * @brief SPI ����һ���ֽ�
 * @return ���յ�������
 **/
uint8_t SPI_readByte (void);


#endif