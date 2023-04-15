#include "core.h"
#include "common.h"
#include <cstdlib>
#include <cstring>

uint8_t uart1_rxbuf[2100];                // 用于存放接收到的数据
// char str[10][512];
#define BUFFER_SIZE 1024
int startpos[20] {0};
int ind = 0;
void core(void) {

	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	U8G2_UC1609_SLG19264_f_4W_SW_SPI u8g2(U8G2_R0);
	u8g2.setFont(u8g2_font_4x6_tf );
	u8g2.begin();
	// int fonty = 0;
	// __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);// 启用空闲中断
	// HAL_UART_Receive_DMA(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	// HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
	while (true) {

	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rxbuf, 1);
		// while(HAL_UART_Receive(&huart1, (uint8_t *)uart1_rxbuf, 1, 1) != HAL_OK);
		// HAL_UART_Transmit(&huart1,(uint8_t *)uart1_rxbuf,1,10);
		u8g2.clearBuffer();
		// for (long i = 0; i < 192; i++) {
		// 	for (long j = 0; j < 64; j++) {
		// 		// if ((i^j)%2 && (i < 64 || i > 64 || j < 20 || j > 44))
		// 		if ((i^j)&1)
		// 			// u8g2.setDrawColor(1);
		// 		// else
		// 			// u8g2.setDrawColor(0);
		// 		u8g2.drawPixel(i, j);
		// 	}
		// // 	// u8g2.drawLine(64, 20, 128, 20);
		// // 	// u8g2.drawLine(64, 20, 64, 44);
		// // 	// u8g2.drawLine(128,20, 128,44);
		// // 	// u8g2.drawLine(64,44,128,44);
		// }
		// u8g2.setDrawColor(0);
		// u8g2.drawBox(66, fonty-12,42, 13);
		// u8g2.setDrawColor(1);
		// u8g2.drawStr(66,fonty, "WARNING");
		// fonty+=3;
		// if (fonty >= 128) fonty = 0;
		// u8g2.sendBuffer();
	// 	const int len = 512;
	// 	// for (int i = 0; i < 20; i++) startpos[i] = 0;
	// 	// for (int i = 0; i < len; i++) str[i] = 0;
	// 	// HAL_UART_Receive(&huart1, (uint8_t*)str, len, 300);
	// 	// int j = 1;
	// 	// for (int i = 0; i < len; i++) {
	// 	// 	if (str[i] == '\r' && str[i+1] == '\n') {
	// 	// 		str[i] = str[i+1] = '\0';
	// 	// 		startpos[j++] = i+2;
	// 	// 	}
	// 	// }
	// 	// if (j > 2)
		for (int i = 0; i < ind; i ++) {
			// if (str[i][0] == '$')
			u8g2.drawStr(0, 6*(i+1), (const char*)(uart1_rxbuf+startpos[i]));
		}
	// 	// u8g2.drawStr(0, 10, str);
	// 	// u8g2.drawStr(0, 20, str+len/4+1);
	// 	// u8g2.drawStr(0, 30, str+len/2+1);
	// 	// u8g2.drawStr(0, 40, str+3*len/4+1);
	// 	// 	// u8g2.drawRBox()
	// 	// 	// u8g2.drawBox(64, 20, 64, 24);
	// 	// }
	// 	// u8g2.clearLine()
	// 	// u8g2.drawStr(10, 20, "Hello World");
		u8g2.sendBuffer();

	// // HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
		// HAL_UART_Transmit(&huart1, (uint8_t*)("still work"), 10, 100);
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(500);
	}

}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
	static int in = 0;

	// if (huart -> Instance == USART1) {
	// 	HAL_UART_Transmit(&huart1, uart1_rxbuf, size, 0xff);
	// 	HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rxbuf, 1024);
	// }
	if (huart -> Instance == USART1) {
		HAL_UART_Transmit(&huart1, uart1_rxbuf, size,0xff);
		ind = 0;
		in = 1;
		// startpos[0] = 0;
		for (int i = 0; i < size; i++) {
			if (uart1_rxbuf[i] == '\r' && uart1_rxbuf[i+1] == '\n') {
				uart1_rxbuf[i] = '\0';
				ind ++;
				startpos[in++] = i + 2;
				i ++;
			}
		}
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart1_rxbuf, 1024);
		// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
	}
}
/*
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart) {
    HAL_UART_DMAStop(&huart1);                                                     //停止本次DMA传输

    uint16_t data_length  = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //计算接收到的数据长度

    // printf("Receive Data(length = %d): ",data_length);
    HAL_UART_Transmit(&huart1,uart1_rxbuf,data_length,0x200);                     //测试函数：将接收到的数据打印出去
    // printf("\r\n");

    memset(uart1_rxbuf,0,data_length);                                            //清零接收缓冲区
    data_length = 0;
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)uart1_rxbuf, 1024);                    //重启开始DMA传输 每次255字节数据
}
void USER_UART_IRQHandler(UART_HandleTypeDef *huart) {
    if(USART1 == huart1.Instance) {                                  //判断是否是串口1（！此处应写(huart->Instance == USART1)
        if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE)) {  //判断是否是空闲中断
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                      //清除空闲中断标志（否则会一直不断进入中断）
            // printf("\r\nUART1 Idle IQR Detected\r\n");
            USAR_UART_IDLECallback(huart);                           //调用中断处理函数
        }
    }
}*/

/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static int in = 0;
	static bool cr = false;
	static int ind = 0;

	HAL_UART_Transmit(&huart1, uart1_rxbuf, 1, 100);
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rxbuf, 1);
	if (huart == &huart1) {
		if (uart1_rxbuf[0] == '$') {
			ind = 0;
		}
		str[in][ind] = uart1_rxbuf[0];
		// HAL_UART_Transmit(&huart1, (uint8_t*)&str[in][ind],1,100);
		if (uart1_rxbuf[0] == '\r') {
			str[in][ind] = '\0';
			cr = true;
		}
		if (cr && uart1_rxbuf[0] == '\n') {
			str[in][ind] = '\0';
			if (str[in][4] == 'G' && str[in][5] == 'A') {
				for (int i = 0; i < ind; i++) {
					str[0][i] = str[in][i];
				}
				in = 0;
				ind = 0;
			}
			cr = false;
			in ++;
			ind = 0;
		}
		ind ++;
		if (in >= 10) in = 0;
	}
}
*/
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