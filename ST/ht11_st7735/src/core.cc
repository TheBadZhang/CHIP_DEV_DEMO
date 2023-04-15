#include "core.h"
#include <cstdint>
#include <cstdio>
// #include "st7789.h"
#include "st7735.h"
#include "fonts.h"
#include "testimg.h"

void loop();
DHT11_Data_TypeDef DHT11_Data;
char str[128];

void core(void) {

	HAL_Delay(100);
	ST7735_Init();
	// ST7735_InvertColors(false);
	HAL_Delay(1000);
	while(true) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		// sprintf(str, "wetness:%d.%d %%RH,temp:%d.%d%%",DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		// DHT11_ReadData(&DHT11_Data);
		// ST7735_WriteString(0, 0, str, Font_7x10, ST7735_WHITE, ST7735_BLACK);
		loop();
		HAL_Delay(1000);
	}

}


void loop() {
    // Check border
    ST7735_FillScreenFast(ST7735_RED);

    for(int x = 0; x < ST7735_WIDTH; x++) {
        ST7735_DrawPixel(x, 0, ST7735_RED);
        ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
    }

    for(int y = 0; y < ST7735_HEIGHT; y++) {
        ST7735_DrawPixel(0, y, ST7735_RED);
        ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
    }

    HAL_Delay(300);

    // Check fonts
    ST7735_FillScreenFast(ST7735_BLACK);
    ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
    ST7735_WriteString(0, 3*10, "Font_11x18, green, lorem ipsum", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    ST7735_WriteString(0, 3*10+3*18, "Font_16x26", Font_16x26, ST7735_BLUE, ST7735_BLACK);
    HAL_Delay(2000);

    // Check colors
    ST7735_FillScreenFast(ST7735_BLACK);
    ST7735_WriteString(0, 0, "BLACK", Font_11x18, ST7735_WHITE, ST7735_BLACK);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_BLUE);
    ST7735_WriteString(0, 0, "BLUE", Font_11x18, ST7735_BLACK, ST7735_BLUE);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_RED);
    ST7735_WriteString(0, 0, "RED", Font_11x18, ST7735_BLACK, ST7735_RED);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_GREEN);
    ST7735_WriteString(0, 0, "GREEN", Font_11x18, ST7735_BLACK, ST7735_GREEN);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_CYAN);
    ST7735_WriteString(0, 0, "CYAN", Font_11x18, ST7735_BLACK, ST7735_CYAN);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_MAGENTA);
    ST7735_WriteString(0, 0, "MAGENTA", Font_11x18, ST7735_BLACK, ST7735_MAGENTA);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_YELLOW);
    ST7735_WriteString(0, 0, "YELLOW", Font_11x18, ST7735_BLACK, ST7735_YELLOW);
    HAL_Delay(500);

    ST7735_FillScreenFast(ST7735_WHITE);
    ST7735_WriteString(0, 0, "WHITE", Font_11x18, ST7735_BLACK, ST7735_WHITE);
    HAL_Delay(500);

// #ifdef ST7735_IS_128X128
    // Display test image 128x128
    ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, (uint16_t*)test_img_128x128);


    // Display test image 128x128 pixel by pixel
    for(int x = 0; x < ST7735_WIDTH; x++) {
        for(int y = 0; y < ST7735_HEIGHT; y++) {
            uint16_t color565 = test_img_128x128[y][x];
            // fix endiness
            color565 = ((color565 & 0xFF00) >> 8) | ((color565 & 0xFF) << 8);
            ST7735_DrawPixel(x, y, color565);
        }
    }

    HAL_Delay(15000);
// #endif // ST7735_IS_128X128

}
uint32_t fac_us;

void delay_us(uint32_t udelay) {
	uint32_t startval,tickn,delays,wait;

	startval = SysTick->VAL;
	tickn = HAL_GetTick();
	//sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
	delays =udelay * 84; //sysc / 1000 * udelay;
	if(delays > startval) {
		while(HAL_GetTick() == tickn);
		wait = 84000 + startval - delays;
		while(wait < SysTick->VAL);
	} else {
		wait = startval - delays;
		while(wait < SysTick->VAL && HAL_GetTick() == tickn);
	}
}