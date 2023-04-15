#ifndef __oled_H
#define __oled_H

#include "main.h"
#include "u8g2.h"
#include "U8g2lib.h"
#ifdef __cplusplus
extern "C"
{
#endif


#define MAX_LEN 128		  //
#define OLED_ADDRESS 0x78 // oledģ��ӻ���ַ
#define OLED_CMD 0x00	  // д����
#define OLED_DATA 0x40	  // д����

// uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

class U8G2_SSD1327_128X128_NONAME_F : public U8G2 {
public:
	U8G2_SSD1327_128X128_NONAME_F(const u8g2_cb_t *rotation) : U8G2() {
		u8g2_Setup_ssd1327_midas_128x128_f(&u8g2, rotation, u8x8_byte_4wire_hw_spi, u8x8_gpio_and_delay);
		u8g2_InitDisplay(&u8g2);
		u8g2_SetPowerSave(&u8g2, 0);
		u8g2_ClearBuffer(&u8g2);
	}
};
class U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI : public U8X8 {
	public: U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI(const u8g2_cb_t *rotation) : U8X8() {
		u8x8_Setup(getU8x8(), u8x8_d_ssd1327_midas_128x128, u8x8_cad_001, u8x8_byte_arduino_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
		u8x8_SetPin_4Wire_SW_SPI(getU8x8(), clock, data, cs, dc, reset);
	}
};

#ifdef __cplusplus
}
#endif
#endif
