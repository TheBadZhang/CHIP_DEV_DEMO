#ifndef __oled_H
#define __oled_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "u8g2.h"
#include "U8g2lib.h"

#define u8 unsigned char  // ?unsigned char ????
#define MAX_LEN 128		  //
#define OLED_ADDRESS 0x78 // oledģ��ӻ���ַ
#define OLED_CMD 0x00	  // д����
#define OLED_DATA 0x40	  // д����

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

class U8G2_SSD1306_128X64_NONAME_F : public U8G2 {
public:
	U8G2_SSD1306_128X64_NONAME_F(const u8g2_cb_t *rotation) : U8G2() {
		u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, rotation, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
		u8g2_InitDisplay(&u8g2);
		u8g2_SetPowerSave(&u8g2, 0);
		u8g2_ClearBuffer(&u8g2);
	}
};

#ifdef __cplusplus
}
#endif
#endif
