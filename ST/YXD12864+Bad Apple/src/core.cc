#include "core.h"
#include "common.h"
#include <cstring>

// uint8_t uart1_rxbuf[10];                // 用于存放接收到的数据
unsigned char bm[][1024] = {
	#include "data.dat"
};

unsigned char bufffer[2048];




void LCDWriteBus(uint8_t dat) {
	HAL_SPI_Transmit(&hspi1, &dat, 1, 100);
}

void LCDWriteData8 (uint8_t dat) {
	LCDWriteBus(dat);
}

void LCDWriteData(uint16_t dat) {
	LCDWriteData8(dat >> 8);
	LCDWriteData8(dat);
}

void LCDWriteReg(uint8_t reg) {
	clr(DC);
	LCDWriteBus(reg);
	set(DC);
}

void LCDAddressSet(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	LCDWriteReg(0x2a);
	LCDWriteData8(x1+0x19);
	LCDWriteData8(x2+0x19);
	LCDWriteReg(0x2b);
	LCDWriteData8(y1);
	LCDWriteData8(y2);
	LCDWriteReg(0x2c);
}

void LCDInit() {
	// RST 其实不是必须的，但是不能悬空，必须接高电平保证不复位，CS也不是必须的，必须接低电平保持选中
	clr(RST);
	HAL_Delay(100);
	set(RST);
	HAL_Delay(300);

	LCDWriteReg(0x0e2);            			/* soft reset */
	LCDWriteReg(0x0af);		                /* display off */
	// LCDWriteReg(0x040);		                /* set display start line to 0 */

	LCDWriteReg(0x0a1);		                /* ADC set to reverse */
	LCDWriteReg(0x0c0);		                /* common output mode */
	// Flipmode
	//U8X8_C(0x0a0);		                /* ADC set to reverse */
	//U8X8_C(0x0c8);		                /* common output mode */

	LCDWriteReg(0x0a6);		                /* display normal; bit val 0: LCD pixel off. */
	LCDWriteReg(0x0a3);		                /* LCD bias 1/7 */
	/* power on sequence from paxinstruments */
	LCDWriteReg(0x028|4);		                /* all power  control circuits on */
	HAL_Delay(50);
	LCDWriteReg(0x028|6);		                /* all power  control circuits on */
	HAL_Delay(50);
	LCDWriteReg(0x028|7);		                /* all power  control circuits on */
	HAL_Delay(50);

	LCDWriteReg(0x026);		                /* v0 voltage resistor ratio */
	LCDWriteReg(0x081);		/* set contrast; contrast value*/
	LCDWriteData8(50>>2);
	LCDWriteReg(0x0af);		                /* display off */
	LCDWriteReg(0x0a5);		                /* enter powersafe: all pixel on, issue 142 */


	HAL_Delay(120);

}

void LCDFill(uint8_t xsta, uint8_t ysta, uint8_t xend, uint8_t yend, uint8_t color) {
	uint16_t i, j;
	LCDAddressSet(xsta, ysta, xend-1, yend-1);
	for (i = ysta; i <= yend; i++) {
		for (j = xsta; j <= xend; j++) {
			LCDWriteData8(color);
		}
	}
}
void Display_pic1(char ii) {
	uint i,j,adressd=0;

	for(i=0;i<8;i++) {
		clr(CS);
		LCDWriteReg(0xb0+i);
		LCDWriteReg(0x10);
		LCDWriteReg(0x00);

		HAL_SPI_Transmit_DMA(&hspi1,(uint8_t *)(bm[ii]+128*(i)),128);
		while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
		// for(j=0;j<128;j++)
		// {
		// 	LCDWriteData8((uint8_t)bm[ii][adressd++]);
		// 	// adressd++;
		// }
	}
}



void core(void) {

	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	// HAL_GPIO_TogglePin(RST_GPIO_Port, RST_Pin);
	// U8G2_SSD1327_MIDAS_128X128_f_4W_HW_SPI u8g22(U8G2_R0);
	// u8g22.setFont(u8g2_font_6x13_tf);
	// u8g22.begin();
	// HAL_Delay(1000);
	U8G2_ST7567_YXD123864_F_4W_SW_SPI u8g2(U8G2_R0);
	u8g2.setFont(u8x8_font_chroma48medium8_r);
	u8g2.begin();

	// MPU6050_Init();
	// __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);// 启用空闲中断
	// HAL_UART_Receive_DMA(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	// HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)bm[0], 1024);
	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
	int iii = 0;
	// LCDInit();
	clr(CS);
	while (true) {
		// LCDWriteReg(0x0a5);
		Display_pic1(iii);
		iii++;
		if (iii == 1) iii = 0;
		// if (iii==(sizeof(bm)/1024)) iii=0;
		// HAL_Delay(100);
	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rxbuf, 1);
		// while(HAL_UART_Receive(&huart1, (uint8_t *)uart1_rxbuf, 1, 1) != HAL_OK);
		// HAL_UART_Transmit(&huart1,(uint8_t *)uart1_rxbuf,1,10);
		// u8g2_SetContrast(&u8g2, 255);
		// u8g2.clearBuffer();
		// for (int i = 0; i < 64; i++) {
		// 	for (int j = 0; j < 128; j++) {
		// 		if ((i^j)%2)
		// 			u8g2.drawPixel(i, j);
		// 	}
		// }
		// MPU6050_Read_Accel();
		// MPU6050_Read_Gyro();
		// MPU6050_Read_Temp();
		// sprintf(str[0],"Ax=%d.%d,Ay=%d.%d,Az=%d.%d\r\n",A(Ax), B(Ax), A(Ay), B(Ay), A(Az), B(Az));
		// sprintf(str[1],"Gx=%d.%d,Gy=%d.%d,Gz=%d.%d\r\n",A(Gx), B(Gx), A(Gy), B(Gy), A(Gz), B(Gz));
		// sprintf (str[2],"Temperature=%d.%d,\r\n",A(Temp), B(Temp));
		// u8g2.drawStr(0,10,str[0]);
		// u8g2.drawStr(0,20,str[1]);
		// u8g2.drawStr(0,30,(str[1]+20));
		// u8g2.drawStr(0,40,str[2]);
		// HAL_UART_Transmit(&huart2, (uint8_t*)str[0], strlen(str[0]),1000);
		// HAL_UART_Transmit(&huart2, (uint8_t*)str[1], strlen(str[1]),1000);
		// HAL_UART_Transmit(&huart2, (uint8_t*)str[2], strlen(str[2]),1000);
		// u8g2_SetContrast(&u8g22, 255);
		// u8g22.clearBuffer();
		// u8g2.drawXBMP(0,0,128,64,bm[iii]);
		// for (int i = 0; i < 128; i++) {
		// 	for (int j = 0; j < 64; j++) {
		// 		if ((i^j)%2)
		// 			u8g2.drawPixel(i, j);
		// 	}
		// }
		// u8g2.drawLine(64, 20, 128, 20);
		// u8g2.drawLine(64, 20, 64, 44);
		// u8g2.drawLine(128,20, 128,44);
		// u8g2.drawLine(64,44,128,44);
		// u8g2.drawStr(10,38, "WARNING");
	// 	const int len = 512;
		// for (int i = 0; i < 20; i++) startpos[i] = 0;
		// for (int i = 0; i < len; i++) str[i] = 0;
		// HAL_UART_Receive(&huart1, (uint8_t*)str, len, 300);
		// int j = 1;
		// for (int i = 0; i < len; i++) {
		// 	if (str[i] == '\r' && str[i+1] == '\n') {
		// 		str[i] = str[i+1] = '\0';
		// 		startpos[j++] = i+2;
		// 	}
		// }
		// if (j > 2)
	// 	for (int i = 0; i < 10; i ++) {
	// 		if (str[i][0] == '$')
	// 		u8g2.drawStr(0, 10*(i+1), str[i]);
	// 	}
		// u8g2.drawStr(0, 10, str);
		// u8g2.drawStr(0, 20, str+len/4+1);
		// u8g2.drawStr(0, 30, str+len/2+1);
		// u8g2.drawStr(0, 40, str+3*len/4+1);
		// 	// u8g2.drawRBox()
		// 	// u8g2.drawBox(64, 20, 64, 24);
		// }
		// u8g2.clearLine()
		// u8g2.drawStr(10, 20, "Hello World");
		// u8g2.sendBuffer();
		// u8g22.sendBuffer();

	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	// HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		// HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		// HAL_Delay(50);
	}

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
	static int in = 0;

	// if (huart -> Instance == USART1) {
	// 	HAL_UART_Transmit(&huart1, uart1_rxbuf, size, 0xff);
	// 	HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rxbuf, 1024);
	// }
	if (huart -> Instance == USART1) {
		// HAL_UART_Transmit(&huart1, uart1_rxbuf, size,0xff);
		// ind = 0;
		// in = 1;
		// // startpos[0] = 0;
		// for (int i = 0; i < size; i++) {
		// 	if (uart1_rxbuf[i] == '\r' && uart1_rxbuf[i+1] == '\n') {
		// 		uart1_rxbuf[i] = '\0';
		// 		ind ++;
		// 		startpos[in++] = i + 2;
		// 		i ++;
		// 	}
		// }
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)bm[0], 1024);
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