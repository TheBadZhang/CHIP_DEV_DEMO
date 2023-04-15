#include "core.h"
#include "oled.h"
#include <cstdio>

void start () {


	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
	u8g2.begin();
	char str[32];

	while (true) {

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
