#include <graphics.h>

#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff

#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f

unsigned short RGB888ToRGB565(unsigned int n888Color) {
	unsigned short n565Color = 0;

	// 获取RGB单色，并截取高位
	unsigned char cRed   = (n888Color & RGB888_RED)   >> 19;
	unsigned char cGreen = (n888Color & RGB888_GREEN) >> 10;
	unsigned char cBlue  = (n888Color & RGB888_BLUE)  >> 3;

	// 连接
	n565Color = (cRed << 11) | (cGreen << 5) | (cBlue << 0);
	return n565Color;
}

unsigned int RGB565ToRGB888(unsigned short n565Color) {
	unsigned int n888Color = 0;

	// 获取RGB单色，并填充低位
	unsigned char cRed   = (n565Color & RGB565_RED)    >> 8;
	unsigned char cGreen = (n565Color & RGB565_GREEN)  >> 3;
	unsigned char cBlue  = (n565Color & RGB565_BLUE)   << 3;

	// 连接
	n888Color = (cRed << 16) | (cGreen << 8) | (cBlue << 0);
	return n888Color;
}



#define _RGB8BIT332(r,g,b) ((r&0xe0)|((g>>3)&0x1c)|((b>>6)&0x03))
