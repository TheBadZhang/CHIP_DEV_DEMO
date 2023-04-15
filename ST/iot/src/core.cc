#include "core.h"
#include "common.h"
#include <cstring>

// uint8_t uart1_rxbuf[10];                // 用于存放接收到的数据
char str[3][60];
#define A(a) ((int)a)/100
#define B(b) ((int)b)%100
void core(void) {

	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	// U8G2_SSD1327_MIDAS_128X128_f_4W_HW_SPI u8g22(U8G2_R0);
	// u8g22.setFont(u8g2_font_6x13_tf);
	// u8g22.begin();
	// HAL_Delay(1000);
	U8G2_SH1107_64X128_1_HW_I2C u8g2(U8G2_R1);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	MPU6050_Init();
	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	while (true) {

		u8g2_SetContrast(&u8g2, 255);
		u8g2.clearBuffer();
		// for (int i = 0; i < 64; i++) {
		// 	for (int j = 0; j < 128; j++) {
		// 		if ((i^j)%2)
		// 			u8g2.drawPixel(i, j);
		// 	}
		// }
		MPU6050_Read_Accel();
		MPU6050_Read_Gyro();
		MPU6050_Read_Temp();
		sprintf(str[0],"Ax=%d.%d,Ay=%d.%d,Az=%d.%d\r\n",A(Ax), B(Ax), A(Ay), B(Ay), A(Az), B(Az));
		sprintf(str[1],"Gx=%d.%d,Gy=%d.%d,Gz=%d.%d\r\n",A(Gx), B(Gx), A(Gy), B(Gy), A(Gz), B(Gz));
		sprintf (str[2],"Temperature=%d.%d,\r\n",A(Temp), B(Temp));
		u8g2.drawStr(0,10,str[0]);
		u8g2.drawStr(0,20,str[1]);
		u8g2.drawStr(0,30,(str[1]+20));
		u8g2.drawStr(0,40,str[2]);
		HAL_UART_Transmit(&huart2, (uint8_t*)str[0], strlen(str[0]),1000);
		HAL_UART_Transmit(&huart2, (uint8_t*)str[1], strlen(str[1]),1000);
		HAL_UART_Transmit(&huart2, (uint8_t*)str[2], strlen(str[2]),1000);
		// u8g2_SetContrast(&u8g22, 255);
		// u8g22.clearBuffer();
		// for (int i = 0; i < 128; i++) {
		// 	for (int j = 0; j < 128; j++) {
		// 		if ((i^j)%2)
		// 			u8g22.drawPixel(i, j);
		// 	}
		// }
		// 	// u8g2.drawLine(64, 20, 128, 20);
		// 	// u8g2.drawLine(64, 20, 64, 44);
		// 	// u8g2.drawLine(128,20, 128,44);
		// 	// u8g2.drawLine(64,44,128,44);
		// 	u8g2.drawStr(66,38, "WARNING");
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
	// 	for (int i = 0; i < 10; i ++) {
	// 		if (str[i][0] == '$')
	// 		u8g2.drawStr(0, 10*(i+1), str[i]);
	// 	}
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
		// u8g22.sendBuffer();

	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	// // HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_Delay(500);
	}

}

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
// 	static int in = 0;
// 	static bool cr = false;
// 	static int ind = 0;
// 	HAL_UART_Transmit(&huart2, uart1_rxbuf, 1, 100);    // 把收到的字节原样发送出去
	// if (huart == &huart1) {
	// 	if (uart1_rxbuf[0] == '$') {
	// 		ind = 0;
	// 	}
	// 	str[in][ind] = uart1_rxbuf[0];
	// 	// HAL_UART_Transmit(&huart1, (uint8_t*)&str[in][ind],1,100);
	// 	if (uart1_rxbuf[0] == '\r') {
	// 		str[in][ind] = '\0';
	// 		cr = true;
	// 	}
	// 	if (cr && uart1_rxbuf[0] == '\n') {
	// 		str[in][ind] = '\0';
	// 		if (str[in][4] == 'G' && str[in][5] == 'A') {
	// 			for (int i = 0; i < ind; i++) {
	// 				str[0][i] = str[in][i];
	// 			}
	// 			in = 0;
	// 			ind = 0;
	// 		}
	// 		cr = false;
	// 		in ++;
	// 		ind = 0;
	// 	}
	// 	ind ++;
	// 	if (in >= 10) in = 0;
	// }
// 	HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
// }

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