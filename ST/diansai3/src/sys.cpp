#include "sys.h"


void delay_us(uint32_t time) {
	uint32_t i = 8 * time;
	while (i--)
		;
}
