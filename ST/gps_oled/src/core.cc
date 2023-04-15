#include "core.h"
#include "common.h"
#include <cstring>


// char nmea[] = \
// 		"$GNRMC,102219.00,A,2239.11578,N,11406.59325,E,0.009,,291018,,,D*62\r\n"\
// 		"$GNVTG,,T,,M,0.009,N,0.017,K,D*37\r\n"\
// 		"$GNGGA,102220.00,2239.11583,N,11406.59338,E,2,09,1.30,112.7,M,-2.3,M,,0000*52\r\n";
uint8_t nmea[1024];                // 用于存放接收到的数据
NMEA0183 nmea0183;

char screenbuff[1024];
unsigned long wrong_count = 0,right_count = 0;
// #define A(a,b) a*
void core(void) {

	U8G2_SSD1306_128X64_NONAME_F u8g2(U8G2_R0);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)nmea, 1024);
	nmea0183.gpsData.location.lat = 1.0;
	nmea0183.gpsData.location.lng = 1.0;
	while (true) {
		u8g2.clearBuffer();
		sprintf(screenbuff, "W:%f E:%f",
			nmea0183.gpsData.location.lat,
			nmea0183.gpsData.location.lng);
		u8g2.drawStr(0, 10, screenbuff);
		sprintf(screenbuff, "height:%d",
			nmea0183.gpsData.location.alt);
		u8g2.sendBuffer();
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(500);
	}

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
	if (huart -> Instance == USART1) {
		HAL_UART_Transmit(&huart1, (uint8_t*)nmea, strlen((char*)nmea), 1024);
		wrong_count = 0;
		right_count = 0;
		for(unsigned int index=0; index<sizeof(nmea); ++index) {
			if(nmea_decode(&nmea0183, nmea[index])) {
			///解析代码成功
				right_count ++;
			} else {
				wrong_count ++;
			}
		}
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*)nmea, 1024);
		// __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);  // 关闭DMA hite
	}
}