#include "common.h"
void spi_send(u8 dat) {

	// HAL_SPI_Transmit_DMA(&hspi1, &dat, 1);
	// while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	// HAL_SPI_Transmit(&hspi1, &dat, 1, 100);
	for(char i=0;i<8;i++) {
		clr(SCK);
		if(dat&0x80) {
			set(MOSI);
		} else {
			clr(MOSI);
		}
		set(SCK);
		dat<<=1;
	}
}