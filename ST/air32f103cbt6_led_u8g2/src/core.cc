#include "core.h"
#include "common.h"
// #include "sys.h"
#include <cstdio>

char strbuffer[100];

void core(void) {
	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();
	uint32_t sysclock = 0;
	sysclock = HAL_RCC_GetSysClockFreq();
	while (true) {
		HAL_Delay(1000);
		u8g2.clearBuffer();
		sprintf(strbuffer, "%d", sysclock);
		u8g2.drawStr(0, 12, strbuffer);
		u8g2.sendBuffer();
		flip(LED1);
		flip(LED2);
		// HAL_Delay(1000);
		flip(LED3);
		// HAL_Delay(1000);
	}

}



// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
// }