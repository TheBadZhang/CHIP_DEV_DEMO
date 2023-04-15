#include "core.h"
#include "common.h"

void core(void) {

	U8G2_SSD1327_MIDAS_128X128_F_3W_HW_SPI u8g2(U8G2_R0);
	u8g2.setFont(u8g2_font_6x10_mf);
	u8g2.begin();


	while (true) {

		u8g2.clearBuffer();
		for (int i = 0; i < 128; i++) {
			for (int j = 0; j < 128; j++) {
				if ((i^j)%2 && (i < 10 || i > 90 || j < 9|| j > 40)) u8g2.drawPixel(i, j);
			}
		}
		// u8g2.
		// u8g2.drawBox(0,0,128,128);
		// u8g2.drawLine(64, 20, 128, 20);
		// u8g2.drawLine(64, 20, 64, 44);
		// u8g2.drawLine(128,20, 128,44);
		// u8g2.drawLine(64,44,128,44);
		u8g2.drawStr(33,38, "WARNING");
		// u8g2.drawRBox()
		// u8g2.drawBox(64, 20, 64, 24);
		// u8g2.clearLine()
		u8g2.drawStr(10, 20, "Hello World");
		u8g2.sendBuffer();

	// HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(500);
	}

}



// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
// 	static int adc_read_counter = 0;
// 	static double adc_sum = 0.0;
// 	uint16_t ADC_Value = 0;
// 	static int dac_index = 0;
// 	// static uint32_t last_pwm_counter_capture = 0;
// 	if (htim == (&htim6)) {
// 		for (int ii = 0; ii < sizeof(c0); ii++) {
// 			HAL_ADC_Start(&hadc1);
// 			HAL_ADC_PollForConversion(&hadc1, 50);
// 			if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
// 				c0[c0i ++] = HAL_ADC_GetValue(&hadc1);
// 			}
// 			HAL_ADC_Start(&hadc1);
// 			HAL_ADC_PollForConversion(&hadc1, 50);
// 			if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
// 				c1[c1i ++] = HAL_ADC_GetValue(&hadc1);
// 			}
// 		}
// 		adc_is_compelete = true;
// 	}
// }