#include "core.h"
#include "common.h"
#include "oled.h"

int32_t compareVal = 306;   //PWM占空比
int32_t voltagVal = 200;   //目标电压(mv)


void setCompare() {
	htim1.Instance->CCR1 = compareVal;
}


void core(void) {

	U8G2_PCD8544_84X48_NONAME_F u8g2(U8G2_R0);
	// u8g2.setFont(u8g2_font_nokiafc22_tf);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	char strbuf[20];

	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim4);
	setCompare();
	while (true) {
		flip(LED);
		u8g2.clearBuffer();
		sprintf(strbuf, "%04d/5000", (int)compareVal);
		u8g2.drawStr(0, 10, "CompareVal:");
		u8g2.drawStr(0, 20, strbuf);
		u8g2.drawStr(0, 30, "Target Voltage");
		sprintf(strbuf, "is %d.%03dV", (int)voltagVal/1000, (int)voltagVal%1000);
		u8g2.drawStr(0, 40, strbuf);
		u8g2.sendBuffer();
	}
}

void resolveKeyInput() {
	static uint16_t keys[3] = {0};
	static uint16_t key_count[3] = {0};
	if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) {
		keys[0] = (keys[0] << 1) | 1;
	} else {
		keys[0] = keys[0] << 1;
	}


	if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET) {
		keys[1] = (keys[1] << 1) | 1;
	} else {
		keys[1] = keys[1] << 1;
	}

	if (keys[0] == 0xffff) {
		if (key_count[0] == 0 || key_count[0] > 300) {
			voltagVal ++;
			// compareVal ++;
		} else if (key_count[0] > 1000) {
			voltagVal += 10;
		}
		if (voltagVal > 2000) {
			voltagVal = 2000;
		}
		key_count[0] ++;
	} else {
		key_count[0] = 0;
	}

	if (keys[1] == 0xffff) {
		if (key_count[1] == 0 || key_count[1] > 300) {
			voltagVal --;
			// compareVal --;
		} else if (key_count[1] > 1000) {
			voltagVal -= 10;
		}
		if (voltagVal < 0) {
			voltagVal = 0;
		}
		key_count[1] ++;
	} else {
		key_count[1] = 0;
	}

	if (keys[2] == 0xffff) {
		// HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
		// toggle status;
	}
}
#define func(a,b) ((a)*voltage+(b))/10000
uint16_t getCompareValueFromVoltage(uint16_t voltage) {
	if (voltage <= 500) {
		return func(15400, -20000);
	} else {
		return func(15326, 26670);
	}
	// return func(15300, 80000);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim4)) {
		// compareVal ++;
		// if (compareVal > 400) {
		// 	compareVal = 0;
		// }
		resolveKeyInput();
		compareVal = getCompareValueFromVoltage(voltagVal);
		setCompare();
	}
}