#include "core.h"
#include <cstdio>
#include "st7789.h"

void core(void) {

	HAL_Delay(100);
	lcd_initial();
	uint16_t c[]={
		RED    ,GREEN  ,BLUE   ,WHITE  ,BLACK  ,YELLOW ,GRAY0  ,GRAY1  ,GRAY2
	};
	int i =0;
	char str[32];
	while(true) {
		lcd_clear(c[i++]);
		i %= sizeof(c)/sizeof(c[0]);
		HAL_Delay(1000);
	}

}
