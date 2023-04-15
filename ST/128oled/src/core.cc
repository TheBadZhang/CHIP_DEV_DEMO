#include "core.h"
#include "oled.h"
#include <cstdio>
#include "st7789.h"

void core(void) {

	HAL_Delay(1000);
	U8G2_SSD1327_128X128_NONAME_F u8g2(U8G2_R0);
	u8g2.begin();
	HAL_Delay(100);
	char str[32];
	while(true) {

		u8g2.sendBuffer();
		u8g2.drawBox(0,0,20,20);
		u8g2.drawBox(20,20,20,20);
		u8g2.sendBuffer();
		u8g2.drawFrame(10,40,20,20);
		u8g2.sendBuffer();
		u8g2.setFont(u8g2_font_DigitalDiscoThin_tf);
		sprintf(str,"%d",114514);
		u8g2.sendBuffer();


		HAL_Delay(1000);
	}

}
