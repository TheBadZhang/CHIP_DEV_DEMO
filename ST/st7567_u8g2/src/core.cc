#include "core.h"
#include "common.h"

void core(void) {


	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
	u8g2.begin();
	char str[32];
	u8g2.setFont(u8g2_font_DigitalDiscoThin_tf);

	while (true) {

		u8g2.clearBuffer();
		u8g2.drawBox(0,0,20,20);
		u8g2.drawBox(20,20,20,20);
		u8g2.drawFrame(10,40,20,20);
		u8g2.drawStr(50, 40, "Hello World");
		u8g2.sendBuffer();


		HAL_Delay(1000);
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