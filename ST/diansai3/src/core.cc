#include "core.h"
#include "common.h"

const int data_size = 600;
const int channels = 2;
const int c_size = channels*data_size;
uint16_t c[c_size] = {};
uint8_t sss[32] = "";
uint8_t uart1_rxbuf[60]="NO DATA NOW";
void core(void) {
	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
		u8g2.setFont(u8g2_font_DigitalDiscoThin_tf);
	u8g2.begin();
	// char str[32];
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_UART_Receive_IT(&huart1, uart1_rxbuf, 60);

	while(true) {
		// u8g2.drawBox(0,0,20,20);
		// u8g2.drawBox(20,20,20,20);
		// u8g2.sendBuffer();
		// u8g2.drawFrame(10,40,20,20);
		// u8g2.drawStr(10, 20, "123");
		u8g2.clear();
		u8g2.drawStr(0,10,(char*)(uart1_rxbuf+0));
		u8g2.drawStr(0,25,(char*)(uart1_rxbuf+15));
		u8g2.drawStr(0,40,(char*)(uart1_rxbuf+30));
		u8g2.drawStr(0,55,(char*)(uart1_rxbuf+45));
		u8g2.sendBuffer();
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(500);
	}

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
for (int j = 0; j < channels; j++) {
	HAL_UART_Transmit(&huart1, (uint8_t*)"start\n", 6, 100);
		// int len1 = sprintf ((char*)sss, "ch%d:%d", j, c[j]);
		// HAL_UART_Transmit(&huart1, sss, len1, 100);
		for (int i = 0; i < data_size; i++) {
			int len = sprintf((char*)sss, "%d,", c[channels*i+j]);
			if (len > 0) HAL_UART_Transmit(&huart1, sss, len, 100);
		}
		HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", 2, 100);
	}
	// HAL_UART_Transmit_DMA(&huart1, (uint8_t *)Senbuff, sizeof(Senbuff));
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim3)) {
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)c, c_size);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Transmit(&huart1, uart1_rxbuf, 60, 100);    // 把收到的字节原样发送出去
	uart1_rxbuf[14] = '\0';
	uart1_rxbuf[29] = '\0';
	uart1_rxbuf[44] = '\0';
	uart1_rxbuf[59] = '\0';
	HAL_UART_Receive_IT(&huart1, uart1_rxbuf, 60);       // 重新注册一次，要不然下次收不到了
}
