#ifndef __TBZ_DMA_H_
#define __TBZ_DMA_H_

#include "dma_reg.h"
#include "binary.h"
#include "mytype.h"

typedef enum dma_uart_trans_int_flag_t {
	dma_uart_trans_int_enable = B10000000
} dma_uart_trans_int_flag_t;

typedef enum dma_uart_trans_int_priority_t {
	 dma_uart_trans_int_priority0 = B00000000,
	 dma_uart_trans_int_priority1 = B00000100,
	 dma_uart_trans_int_priority2 = B00001000,
	 dma_uart_trans_int_priority3 = B00001100
} dma_uart_trans_int_priority_t;

typedef enum dma_uart_trans_data_access_priority_t {
	dma_uart_trans_data_access_priority_priority0 = B00000000,
	dma_uart_trans_data_access_priority_priority1 = B00000001,
	dma_uart_trans_data_access_priority_priority2 = B00000010,
	dma_uart_trans_data_access_priority_priority3 = B00000011
} dma_uart_trans_data_access_priority_t;

// typedef struct dma_uart_int_t {
// 	dma_uart_int_flag_t enable;
// 	dma_uart_int_priority_t priority;
// 	dma_uart_data_access_priority_t access_priority;
// } dma_uart_int_t;

typedef enum dma_uart_trans_enable_flag_t {
	dma_uart_trans_enable = B10000000
} dma_uart_trans_enable_flag_t;

typedef enum dma_uart_trans_run_flag_t {
	dma_uart_trans_run  = B01000000
} dma_uart_trans_run_flag_t;

// typedef struct dma_uart_enable_t {
// 	dma_uart_enable_flag_t enable;
// 	dma_uart_run_flag_t run;
// } dma_uart_enable_t;

typedef enum dma_uart_recieve_int_flag_t {
	dma_uart_recieve_int_enable = B10000000
} dma_uart_recieve_int_flag_t;

typedef enum dma_uart_recieve_int_priority_t {
	 dma_uart_recieve_int_priority0 = B00000000,
	 dma_uart_recieve_int_priority1 = B00000100,
	 dma_uart_recieve_int_priority2 = B00001000,
	 dma_uart_recieve_int_priority3 = B00001100
} dma_uart_recieve_int_priority_t;

typedef enum dma_uart_recieve_data_access_priority_t {
	dma_uart_recieve_data_access_priority_priority0 = B00000000,
	dma_uart_recieve_data_access_priority_priority1 = B00000001,
	dma_uart_recieve_data_access_priority_priority2 = B00000010,
	dma_uart_recieve_data_access_priority_priority3 = B00000011
} dma_uart_recieve_data_access_priority_t;


typedef struct dma_uart_init_t {
	dma_uart_trans_int_flag_t trans_int_enable;
	dma_uart_trans_int_priority_t trans_priority;
	dma_uart_trans_data_access_priority_t trans_access_priority;
	dma_uart_trans_enable_flag_t trans_enable;
	dma_uart_trans_run_flag_t trans_run;
	void* data_address;
	u8 trans_bytes;    // 设置为 0 时传输 1 字节，设置 255 时，传输 256 字节
} dma_uart_init_t;

void dma_uart_init (dma_uart_init_t* dma_uart_init_struct);
void dma_uart_trans_int_resetflat (unsigned char volatile __xdata* uart);
void dma_uart_trans_errorWrite_resetflag (unsigned char volatile __xdata* uart);
void dma_uart_get_transed_bytes (unsigned char volatile __xdata* uart);
#endif