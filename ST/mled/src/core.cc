#include "core.h"
#include "common.h"


extern uint8_t mled_data[];
extern const uint32_t mled_data_size;

void core(void) {
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim11);
	HAL_TIM_Base_Start_IT(&htim2);
	while (true) {
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(1000);
	}

}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static uint32_t cnt = 0;
	static uint32_t sel = 0;
	static uint32_t sel2 = 0;
	static bool flag = true;
	if (htim == (&htim11)) {
		set(dig0);set(dig1);set(dig2);set(dig3);set(dig4);set(dig5);set(dig6);
		if (mled_data[sel+cnt]&0b00000001) clr(dig0);
		if (mled_data[sel+cnt]&0b00000010) clr (dig1);
		if (mled_data[sel+cnt]&0b00000100) clr (dig2);
		if (mled_data[sel+cnt]&0b00001000) clr (dig3);
		if (mled_data[sel+cnt]&0b00010000) clr (dig4);
		if (mled_data[sel+cnt]&0b00100000) clr (dig5);
		if (mled_data[sel+cnt]&0b01000000) clr (dig6);
		switch (cnt) {
			case 0: {
				set(seg0);clr(seg1);clr(seg2);clr(seg3);clr(seg4);cnt = 1;
			} break;
			case 1: {
				clr(seg0);set(seg1);clr(seg2);clr(seg3);clr(seg4);cnt = 2;
			} break;
			case 2: {
				clr(seg0);clr(seg1);set(seg2);clr(seg3);clr(seg4);cnt = 3;
			} break;
			case 3: {
				clr(seg0);clr(seg1);clr(seg2);set(seg3);clr(seg4);cnt = 4;
			} break;
			case 4: {
				clr(seg0);clr(seg1);clr(seg2);clr(seg3);set(seg4);cnt = 0;
			} break;
		}
		// if (count >= 1000) {
		// 	sel = (sel+1)%4;
		// }
	} else if (htim == &htim2) {
		if (flag) {
			sel = (sel+1)%(mled_data_size-5);
			if ((sel)%7 == 0) flag = false;
		} else {
			sel2 ++;
			if (sel2 == 10) {
				sel2 = 0;
				flag = true;
			}
		}
	}
	// } else if (htim == &htim10) {
	// 	flag = true;
	// }
}