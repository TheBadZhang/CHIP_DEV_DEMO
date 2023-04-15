#include "common.h"
#define U8G2_SPI

#ifdef U8G2_SPI
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr) {

	switch (msg) {
		case U8X8_MSG_BYTE_SEND: {
			HAL_SPI_Transmit(&hspi1,(uint8_t *)arg_ptr,arg_int,200);
		} break;
		case U8X8_MSG_BYTE_SET_DC: /*����DC����,�������͵������ݻ�������*/
			if (arg_int) HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
			break;
		default:
			return 0;
	}
	return 1;
}
#endif

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
	switch (msg) {
		case U8X8_MSG_GPIO_AND_DELAY_INIT:
			HAL_Delay(1);
			break;
		case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
			HAL_Delay(arg_int);
			break;
		case U8X8_MSG_GPIO_DC: /*����DC����,�������͵������ݻ�������*/
			if (arg_int) HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
			break;
		case U8X8_MSG_GPIO_CS: /*Ƭѡ�ź�*/
			if (arg_int) HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
			break;
		case U8X8_MSG_GPIO_RESET:
			if (arg_int) HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
			break;
		default:
			u8x8_SetGPIOResult(u8x8, 1); // default return value
			break;
	}
	return 1;
}
// void u8g2Init(u8g2_t *u8g2) {
// 	// u8g2_Setup_sh1107_i2c_64x128_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
// 	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay); // ��ʼ�� u8g2 �ṹ��
// 	u8g2_InitDisplay(u8g2);                                                                       // ������ѡ��оƬ���г�ʼ����������ʼ����ɺ���ʾ�����ڹر�״̬
// 	u8g2_SetPowerSave(u8g2, 0);                                                                   // ����ʾ��
// 	u8g2_ClearBuffer(u8g2);
// }
