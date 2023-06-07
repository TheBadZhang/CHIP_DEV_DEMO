#include "core.h"
#include "common.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "effect.h"
#include "random.h"
#include "st7789.h"
// #include "oled.h"
// #include "ws2812.h"
// uint8_t uart1_rxbuf[10];                // 用于存放接收到的数据
// char str[3][60];
// #define A(a) ((int)a)/100
// #define B(b) ((int)b)%100

#include "LCD_Init.h"
#include "lcd.h"
#include "pic.h"

#define WS_BIT_1            0b01111100
#define WS_BIT_0            0b01110000
#define WS_RESET            0b00000000

uint8_t buffer [140] = {};
// uint32_t colors[8] = {0x010101};
uint32_t colors [8] = {0x110011, 0x001100, 0x000011, 0x110000, 0x001100, 0x000011, 0x110000, 0x001100};
void ws2812_convert (uint32_t* color, int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		uint32_t c = color[i];
		for (int j = 0; j < 24; j++) {
			if (c & 0x800000) {
				buffer[count++] = WS_BIT_1;
			} else {
				buffer[count++] = WS_BIT_0;
			}
			c <<= 1;
		}
	}
}

void ws2812_display(void) {
	// HAL_SPI_Transmit_DMA(&hspi2, buffer, 8*3*8);
	HAL_SPI_Transmit(&hspi2, buffer, 8*3*8, 100);
}

void core(void) {

	tbz::srand(20);
	clr(CS);
	float t = 0.0;
	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	lcd_initial();
	uint16_t c[]={
		RED    ,GREEN  ,BLUE   ,WHITE  ,BLACK  ,YELLOW ,GRAY0  ,GRAY1  ,GRAY2
	};
	int i =0;
	char str[32];
	HAL_TIM_Base_Start_IT(&htim14);

	// LL_SPI_Enable(SPI1);
	while (true) {
		// loop();
		// lcd_clear(c[i++]);

		LCD_Fill(0,0,LCD_W,LCD_H,c[i++]);
		i %= sizeof(c)/sizeof(c[0]);
		// LCD_ShowChinese(40,0,(u8*)"中景园电子",RED,WHITE,32,0);
		// LCD_ShowString(10,33,(u8*)"LCD_W:",RED,WHITE,32,0);
		// LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);
		// LCD_ShowString(10,66,(u8*)"LCD_H:",RED,WHITE,32,0);
		// LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);
		// LCD_ShowFloatNum1(10,99,t,4,RED,WHITE,32);
		// t+=0.11;
		// LCD_ShowPicture(160,95,40,40,gImage_1);
		// array2left(colors, sizeof(colors)/sizeof(uint16_t));

		// HAL_Delay(500);
		// HAL_SPI_Transmit(&hspi1, (uint8_t*)"hello12345", 10, 1000);
		HAL_Delay(100);
	}

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	// HAL_SPI_Transmit(&hspi2, (uint8_t*)"hello12345", 10, 1000);
	// HAL_UART_Transmit(&huart1, (uint8_t*)"hello12345", 10, 1000);
// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	uint32_t color = colors[0];
	for(int i = 0; i < sizeof(colors)/sizeof(uint32_t)-1; i++) {
		// colors[i] = tbz::rand();
		colors[i] = colors[i+1];
	}
	colors[sizeof(colors)/sizeof(uint32_t)-1] = color;
	ws2812_convert (colors, sizeof(colors)/sizeof(uint32_t));
	ws2812_display();

	flip(LED);
}