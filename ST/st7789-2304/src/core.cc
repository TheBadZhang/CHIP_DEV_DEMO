#include "core.h"
#include "common.h"
#include <cstring>
#include "st7789.h"

// uint8_t uart1_rxbuf[10];                // 用于存放接收到的数据
char str[3][60];
#define A(a) ((int)a)/100
#define B(b) ((int)b)%100
void core(void) {
	clr(RST);
	HAL_Delay(100);
	set(RST);
	lcd_initial();
	uint16_t c[]={
		RED    ,GREEN  ,BLUE   ,WHITE  ,BLACK  ,YELLOW ,GRAY0  ,GRAY1  ,GRAY2
	};
	int i =0;
	while (true) {
		lcd_clear(c[i++]);
		i %= sizeof(c)/sizeof(c[0]);
		flip(LED);
		HAL_Delay(500);
	}

}
