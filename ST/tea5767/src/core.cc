#include "core.h"
#include "common.h"
#include <cstring>





#define max_freq 108000
#define min_freq 87500
unsigned char radio_write_data[5]={0x29,0xc2,0x20,0x11,0x00};        //要写入TEA5767的数据
unsigned char radio_read_data[5];        //TEA5767读出的状态
unsigned int pll=0x29c2;//0x29f9;        //默认存台的pll,87.8MHz
unsigned int frequency = 0;
//unsigned int max_pll=0x339b;            //108MHz时的pll,
//unsigned int min_pll=9000;            //70MHz时的pll
char tai[100];
void radio_write(void) {
	// unsigned char i;
	// iic_start();
	// iic_write8bit(0xc0);        //TEA5767写地址
	// if(!iic_testack()) {
	// 	for(i=0;i<5;i++) {
	// 		iic_write8bit(radio_write_data[i]);
	// 		iic_ack();
	// 	}
	// }
	// iic_stop();
	HAL_I2C_Master_Transmit(&hi2c2, 0xc0, (uint8_t*)radio_write_data, sizeof(radio_write_data), 1000);
}

//读TEA5767状态,并转换成频率
void radio_read(void) {
	unsigned char i;
	unsigned char temp_l,temp_h;
	pll=0;
	// iic_start();
	// iic_write8bit(0xc1);        //TEA5767读地址
	// if(!iic_testack()) {
	// 	for(i=0;i<5;i++) {
	// 		radio_read_data[i]=iic_read8bit();
	// 		iic_ack();
	// 	}
	// }
	// iic_stop();
	HAL_I2C_Master_Receive(&hi2c2, 0xc0, (uint8_t*)radio_read_data, sizeof(radio_read_data), 1000);
	temp_l=radio_read_data[1];
	temp_h=radio_read_data[0];
	temp_h&=0x3f;
	pll=temp_h*256+temp_l;
	// get_frequency();
	frequency = (((radio_read_data[0]&0x3F)<<8)+radio_read_data[1])*32768/4-225000;
}

//由频率计算PLL
void get_pll(void) {
	unsigned char hlsi;
	unsigned int twpll=0;
	hlsi=radio_write_data[2]&0x10;
	if (hlsi)
		pll=(unsigned int)((float)((frequency+225)*4)/(float)32.768);    //频率单位:k
	else
		pll=(unsigned int)((float)((frequency-225)*4)/(float)32.768);    //频率单位:k
}
//由PLL计算频率
void get_frequency(void) {
	unsigned char hlsi;
	unsigned int npll=0;
	npll=pll;
	hlsi=radio_write_data[2]&0x10;
	if (hlsi)
		frequency=(unsigned long)((float)(npll)*(float)8.192-225);    //频率单位:KHz
	else
		frequency=(unsigned long)((float)(npll)*(float)8.192+225);    //频率单位:KHz
}

void TEA5767SetFrequency(float fFrequency) {
	unsigned int nFrequency;

	nFrequency = (unsigned int)((fFrequency * 1000000 + 225000) / 32768 * 4);
	radio_write_data[0] = (unsigned char)(nFrequency >> 8);
	radio_write_data[1] = (unsigned char)(nFrequency & 0xff);
	radio_write_data[2] = 0xb0;
	radio_write_data[3] = 0x10;
	radio_write_data[4] = 0x0;
	radio_write();
}

//手动设置频率,mode=1,+0.1MHz; mode=0:-0.1MHz ,不用考虑TEA5767用于搜台的相关位:SM,SUD
void search(bool mode) {
	radio_read();
	if(mode) {
		frequency+=100;
		if(frequency>max_freq)
			frequency=min_freq;
	} else {
		frequency-=100;
		if(frequency<min_freq)
			frequency=max_freq;
	}
	get_pll();
	radio_write_data[0]=pll/256;
	radio_write_data[1]=pll%256;
	radio_write_data[2]=0x20;
	radio_write_data[3]=0x11;
	radio_write_data[4]=0x00;
	radio_write();
}

//自动搜台,mode=1,频率增加搜台; mode=0:频率减小搜台,不过这个好像不能循环搜台
void auto_search(bool mode) {
	radio_read();
	get_pll();
	if(mode)
		radio_write_data[2]=0xa0;
	else
		radio_write_data[2]=0x20;
	radio_write_data[0]=pll/256+0x40;
	radio_write_data[1]=pll%256;
	radio_write_data[3]=0x11;
	radio_write_data[4]=0x00;
	radio_write();
	radio_read();
	while(!(radio_read_data[0]&0x80)) {    //搜台成功标志
		radio_read();
		// disp_freq(9,1);
		sprintf(tai, "%dMHz", frequency/1024);
	}
}




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
	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	// MPU6050_Init();
	// __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);// 启用空闲中断
	// HAL_UART_Receive_DMA(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	// HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t*)uart1_rxbuf, 1024);
	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
	// bool flag = true;
	TEA5767SetFrequency(87.5);
	// TEA5767SetFrequency(93);
	char flag = 1;
	while (true) {

	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rxbuf, 1);
		// while(HAL_UART_Receive(&huart1, (uint8_t *)uart1_rxbuf, 1, 1) != HAL_OK);
		// HAL_UART_Transmit(&huart1,(uint8_t *)uart1_rxbuf,1,10);
		// u8g2_SetContrast(&u8g2, 255);
		u8g2.clearBuffer();
		// for (int i = 0; i < 128; i++) {
		// 	for (int j = 0; j < 64; j++) {
		// 		if ((i^j)%2 == flag)
		// 			u8g2.drawPixel(i, j);
		// 	}
		// }
		// auto_search(1);
		u8g2.drawStr(10,10,tai);
		flag = 1-flag;
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
		// for (int i = 0; i < 128; i++) {
		// 	for (int j = 0; j < 128; j++) {
		// 		if ((i^j)%2)
		// 			u8g22.drawPixel(i, j);
		// 	}
		// }
			// u8g2.drawLine(64, 20, 128, 20);
			// u8g2.drawLine(64, 20, 64, 44);
			// u8g2.drawLine(128,20, 128,44);
			// u8g2.drawLine(64,44,128,44);
		// 	u8g2.drawStr(66,38, "WARNING");
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
		u8g2.sendBuffer();
		// u8g22.sendBuffer();

	// HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart1_rxbuf, 1);
	// HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);
		// HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		// HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_Delay(1000);
	}

}

// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
// 	static int in = 0;

// 	// if (huart -> Instance == USART1) {
// 	// 	HAL_UART_Transmit(&huart1, uart1_rxbuf, size, 0xff);
// 	// 	HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rxbuf, 1024);
// 	// }
// 	if (huart -> Instance == USART1) {
// 		HAL_UART_Transmit(&huart1, uart1_rxbuf, size,0xff);
// 		ind = 0;
// 		in = 1;
// 		// startpos[0] = 0;
// 		for (int i = 0; i < size; i++) {
// 			if (uart1_rxbuf[i] == '\r' && uart1_rxbuf[i+1] == '\n') {
// 				uart1_rxbuf[i] = '\0';
// 				ind ++;
// 				startpos[in++] = i + 2;
// 				i ++;
// 			}
// 		}
// 		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart1_rxbuf, 1024);
// 		// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
// 	}
// }
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