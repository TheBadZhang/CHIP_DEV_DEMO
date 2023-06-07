#include "core.h"
#include "common.h"
#include <cstring>
#include "oled.h"
// #include "tinyexpr.h"
#include "ssd1315.h"
#include <cstdio>


unsigned char BMP1[] = {
	#include "frame_data2.dat"
};

extern unsigned char ASCII_5x7[][5];
unsigned char NUM_1x2_5x7[][5] = {
	#include "num_1x2_5x7.dat"
};
unsigned char lcd1602_ram [2][16] = {};

char lcd1602_string[32];
uint32_t clock = 0;
U8G2_SSD1306_96X16_ER_1_HW_I2C* pu8g2;

void lcd1602_demo () {
	static unsigned char i = 0;
	i++;
	i%=128;
	int ii = i;
	for (int ij = 0; ij < 2; ij++) {
		for (int ik = 0; ik < 16; ik ++) {
			lcd1602_ram[ij][ik] = ii--;
			if (ii < 0) {
				ii = 127;
			}
		}
	}
}
// template<int n>
void lcd1602_display(const unsigned char (&font)[][5] = ASCII_5x7, const unsigned char nums = 0) {
	(*pu8g2).clearBuffer();
	for (int i = 0 ; i < 2; i++) {
		for (int j = 0; j < 16; j++) {
			(*pu8g2).drawXBM((1-i)*8, j*6, 8, 5, font[lcd1602_ram[i*(nums==0)][j]+i*nums]);
		}
	}
	(*pu8g2).sendBuffer();
}
void lcd1602_clear(const unsigned char clear_char = ' ') {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 16; j++) {
			lcd1602_ram[i][j] = clear_char;
		}
	}
}
void lcd1602_print(const char* str) {
	lcd1602_clear();
	int k = -1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 16; j++) {
			k++;
			if (str[k] == '\n') {
				j = 16;
				continue;
			} else if (str[k] == '\0') return;
			lcd1602_ram[i][j] = str[k];
		}
	}
}

void core(void) {
	// delay_init();
	// OLED_Init();
	// LED_ON;
	U8G2_SSD1306_96X16_ER_1_HW_I2C u8g2(U8G2_R3);
	u8g2.setFont(u8g2_font_ncenB08_tr);
	u8g2.begin();
	pu8g2 = &u8g2;

	clock = 23*3600+43*60+52;
	HAL_TIM_Base_Start_IT(&htim16);
	HAL_TIM_Base_Start_IT(&htim14);

	while (true) {
		// lcd1602_demo();
		// sprintf(lcd1602_string, "1+1=%d\b2+2=%d", te_interp("1+1",0), te_interp("2+2",0));
		// lcd1602_print(lcd1602_string);
		// lcd1602_print("1+1=2\n2+2=4");
		flip(LED);
		HAL_Delay(500);
	}

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim16)) {
		clock++;  // increased every second
	} else if (htim == (&htim14)) {
		lcd1602_ram[0][0+4] = clock/3600/10;
		lcd1602_ram[0][1+4] = clock/3600%10;
		lcd1602_ram[0][2+4] = 10;
		lcd1602_ram[0][3+4] = clock/60%60/10;
		lcd1602_ram[0][4+4] = clock/60%10;
		lcd1602_ram[0][5+4] = 10;
		lcd1602_ram[0][6+4] = clock%60/10;
		lcd1602_ram[0][7+4] = clock%10;
		lcd1602_display(NUM_1x2_5x7,12);
		lcd1602_clear(11);
	}
}

