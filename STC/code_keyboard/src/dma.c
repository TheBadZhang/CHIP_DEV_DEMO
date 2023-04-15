#include "dma.h"


void dma_uart_init (dma_uart_init_t* dma_uart_init_struct) {

}

void dma_uart_trans_int_resetflat (unsigned char volatile __xdata* uart) {
	*(uart+0x02) &= B00000010;
}

