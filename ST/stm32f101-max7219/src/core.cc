#include "core.h"
#include "common.h"

#define io_in 0x00
#define io_out 0x03
#define WPR(reg,m,n) {reg&=~(0xf<<(4*n));reg|=m<<(4*n);}
#define IO1_i() WPR(GPIOA->CRL, io_in, 4)
#define IO1_o() WPR(GPIOA->CRL, io_out,  4)
#define IO2_i() WPR(GPIOA->CRL, io_in, 7)
#define IO2_o() WPR(GPIOA->CRL, io_out,  7)
#define IO3_i() WPR(GPIOA->CRL, io_in, 6)
#define IO3_o() WPR(GPIOA->CRL, io_out,  6)
#define IO4_i() WPR(GPIOA->CRL, io_in, 5)
#define IO4_o() WPR(GPIOA->CRL, io_out,  5)
#define IO5_i() WPR(GPIOA->CRL, io_in, 3)
#define IO5_o() WPR(GPIOA->CRL, io_out,  3)
#define IO6_i() WPR(GPIOA->CRL, io_in, 2)
#define IO6_o() WPR(GPIOA->CRL, io_out,  2)
#define IO7_i() WPR(GPIOA->CRL, io_in, 1)
#define IO7_o() WPR(GPIOA->CRL, io_out,  1)
#define IO8_i() WPR(GPIOA->CRL, io_in, 0)
#define IO8_o() WPR(GPIOA->CRL, io_out,  0)

#define IO_i(n) IO##n##_i()
#define IO_o(n) IO##n##_o()

#define IO(a,n) { \
	if(a[n-1] == 0) {IO_o(n); clr(IO##n);} \
	else if (a[n-1] == 1) {IO_o(n); set(IO##n);} \
	else {IO_i(n);} \
	}

#define disp_(a) \
	IO(a,1);IO(a,2);IO(a,3);IO(a,4); \
	IO(a,5);IO(a,6);IO(a,7);IO(a,8);

char img[8][8] = {
	{0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 1, 0, 1, 1, 1},
	{0, 0, 1, 0, 0, 0, 1, 0}
};

char IOS [8][8] = {
	{1, 2, 2, 2, 2, 2, 2, 0},
	{0, 1, 2, 2, 2, 2, 2, 2},
	{2, 0, 1, 2, 0, 2, 2, 2},
	{2, 0, 2, 1, 2, 2, 2, 2},
	{2, 0, 2, 2, 1, 2, 2, 2},
	{2, 0, 2, 2, 2, 1, 2, 2},
	{2, 0, 2, 2, 2, 2, 1, 2},
	{2, 0, 2, 2, 2, 2, 2, 1}
};

void img2ios (void) {
	for(int i = 0; i < 8; i++) {
		// for(int j = 0; j < 7; j++) IOS[i][j] = 2;
		IOS[i][i] = 1;
		for(int j = 1; j < 8; j++) {
			if (j == i) {
				IOS[i][0] = img[i][j] == 1? 0 : 2;
			} else {
				IOS[i][j] = img[i][j] == 1? 0 : 2;
			}
		}
	}
}



/*   MAX7219 寄存器地址与功能

寄存器名称      寄存器地址
-------------------------
不操作          0x00
digit[0-7]      0x01 - 0x08
解码模式        0x09
	不解码              B00000000    //? 选择哪位，就给哪位进行 BCD 解码
	为 digit0 解码      B00000001    //? 点阵屏无需 BCD 解码
	为 digit[0-3] 解码  B00001111    //? 译码器只对数据的低四位进行译码（D3-D0），D4-D6 为无效位
	为 digt [0-7] 解码  B11111111    //? D7 位用来设置小数点，不受译码器的控制且为高电平
显示亮度               0x0a          //? 总共有 16 级亮度，但是最亮不是最亮，最暗不是关掉
	亮度0               0x00
	亮度1               0x01
	亮度2               0x02
	....
	亮度15              0x0f
扫描限制               0x0b      //? 选择哪些 ditgit 会被显示
	digit0              0x00
	digit0&1            0x01
	digit0&1&2          0x02
	....
	digit0&1&2&3&4&5&6&7 0x07
掉电模式（停机模式）   0x0c       //? 默认掉电模式是开启的
	掉电模式            0x00
	正常模式            0x01
屏幕测试               0x0f
	正常模式            0x00
	测试模式            0x01

*/

// MAX7219 中的寄存器和对应的名称
enum class REG {
	NOP = 0x00, DIGIT0, DIGIT1, DIGIT2, DIGIT3, DIGIT4, DIGIT5, DIGIT6, DIGIT7,
	DECODE_MODE, BRIGHTNESS, SCAN_LIMITE, POWER_MODE, SCREEN_TEST = 0x0f
};
enum class DECODE_MODE {
	NO_DECODE = 0x00, DIGIT00, DIGIT01 = 0x02, DIGIT02 = 0x03, DIGIT03 = 0x04, DIGIT04 = 0x05, DIGIT05 = 0x06, DIGIT06 = 0x07, DIGIT07 = 0x08,
};
enum class BRIGHTNESS {
	L0 = 0x00, L1, L2, L3, L4 = 0x04, L5 = 0x05, L6 = 0x06, L7 = 0x07, L8 = 0x08, L9 = 0x09,
	L10 = 0x0a, L11 = 0x0b, L12 = 0x0c, L13 = 0x0d, L14 = 0x0e, L15 = 0x0f
};
enum class SCAN_LIMITE {
	DIGIT00 = 0x00, DIGIT01, DIGIT02 = 0x02, DIGIT03 = 0x03, DIGIT04 = 0x04, DIGIT05 = 0x05, DIGIT06 = 0x06, DIGIT07 = 0x07
};
enum class POWER_MODE {
	POWER_DOWN = 0x00, NORMAL = 0x01
};
enum class SCREEN_TEST {
	OFF = 0x00, ON = 0x01
};


uchar max7219_disp [38][8]={
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
	{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
	{0x7E,0x02,0x02,0x7E,0x40,0x40,0x40,0x7E},//2
	{0x3E,0x02,0x02,0x3E,0x02,0x02,0x3E,0x00},//3
	{0x08,0x18,0x28,0x48,0xFE,0x08,0x08,0x08},//4
	{0x3C,0x20,0x20,0x3C,0x04,0x04,0x3C,0x00},//5
	{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x00},//6
	{0x3E,0x22,0x04,0x08,0x08,0x08,0x08,0x08},//7
	{0x00,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
	{0x3E,0x22,0x22,0x3E,0x02,0x02,0x02,0x3E},//9
	{0x08,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
	{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x00},//B
	{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x00},//C
	{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x00},//D
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
	{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
	{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
	{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
	{0x3C,0x08,0x08,0x08,0x08,0x08,0x48,0x30},//J
	{0x00,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
	{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
	{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
	{0x00,0x42,0x62,0x52,0x4A,0x46,0x42,0x00},//N
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
	{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
	{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
	{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
	{0x00,0x1E,0x20,0x20,0x3E,0x02,0x02,0x3C},//S
	{0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08},//T
	{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
	{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
	{0x00,0x49,0x49,0x49,0x49,0x2A,0x1C,0x00},//W
	{0x00,0x41,0x22,0x14,0x08,0x14,0x22,0x41},//X
	{0x41,0x22,0x14,0x08,0x08,0x08,0x08,0x08},//Y
	{0x00,0x7F,0x02,0x04,0x08,0x10,0x20,0x7F},//Z
	{0x08,0x7F,0x49,0x49,0x7F,0x08,0x08,0x08},//中
	{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//国
};

static const unsigned char bitmap_bytes[] = {
	0x00,0x20,0x10,0x10,0x00,0x00,0xf7,0x10,
	0x40,0x40,0x40,0x40,0x40,0x40,0xfe,0x40,
	0x10,0x10,0x10,0x10,0x14,0x18,0x10,0x00,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40
};

static const unsigned char heart[] = {
	0b11111111,
	0b11001100,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11100001,
	0b11110011
};



#define SPI

#define max7219_Write(addr,dat) max7219_MultiWrite(0,addr,dat)

#define cs_high() HAL_GPIO_WritePin(SS1_GPIO_Port, SS1_Pin, GPIO_PIN_SET)
#define cs_low() HAL_GPIO_WritePin(SS1_GPIO_Port, SS1_Pin, GPIO_PIN_RESET)
#ifndef SPI
#define clk_high() HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET)
#define clk_low() HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)
#define din_high() HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_SET)
#define din_low() HAL_GPIO_WritePin(DIN_GPIO_Port, DIN_Pin, GPIO_PIN_RESET)
#endif

/**
 * @brief 向MAX7219(U3)写入字节
 *
 * @param DATA
 */
void max7219_WriteByte(uchar DATA) {
#ifdef SPI
	HAL_SPI_Transmit(&hspi1, &DATA, 1, 1000);
#else
	cs_low();
	for(uchar i=8;i>=1;i--) {
		clk_low();
		// Max7219_pinDIN=DATA&0x80;
		if (DATA&0x80) {
			din_high();
		} else {
			din_low();
		}
		DATA=DATA<<1;
		clk_high();
	}
#endif
}
#define WRE
#ifdef WRE
/**
 * @brief 写两个字节数据的spi
 *
 * @param regdata
 */
void max7219_WriteRegData(uint16_t regdata) {
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&regdata, 2, 1000);
}
#endif

/**
 * @brief 向MAX7219的寄存器写入数据
 * @param piece 第几块芯片
 * @param addr 寄存器地址
 * @param dat 待写入的数据
 */
void max7219_MultiWrite (uchar piece, uchar addr, uchar dat) {
	cs_low();
#ifdef WRE
	max7219_WriteRegData (addr|dat<<8);     // 写入地址和数据
#else
	max7219_WriteByte (addr);     // 写入地址
	max7219_WriteByte (dat);      // 写入数据
#endif
	// clk_high();
	for (uchar i = 0; i < piece; i++) {                 // 级联时，NO-OP，操作是在这个地方写的，当片选变成1时，
#ifdef WRE
		max7219_WriteRegData(0x00);
#else
		max7219_WriteByte (0x00);    // 级联的选片就失效了，一定是连续写入，不停止的那种
		max7219_WriteByte (0x00);
#endif
	}
	cs_high();
}
/**
 * @brief 初始化
 */
void max7219_Init (void) {
	for (int i = 0; i < 1; i++) {
		max7219_MultiWrite(i, (uchar)REG::DECODE_MODE, (uchar)DECODE_MODE::NO_DECODE);
		max7219_MultiWrite(i, (uchar)REG::BRIGHTNESS,  (uchar)BRIGHTNESS::L3);
		max7219_MultiWrite(i, (uchar)REG::SCAN_LIMITE, (uchar)SCAN_LIMITE::DIGIT07);
		max7219_MultiWrite(i, (uchar)REG::POWER_MODE,  (uchar)POWER_MODE::NORMAL);
		max7219_MultiWrite(i, (uchar)REG::SCREEN_TEST, (uchar)SCREEN_TEST::OFF);
	}
}




void core(void) {

	// HAL_TIM_Base_Start_IT(&htim4);
	// bool flag = false;
	// img2ios();
	// int in = 0;
	max7219_Init();
	// int cc =0;
	while (true) {

		for(int i = 0; i < 8; i++) {
			max7219_MultiWrite(0,i+1,~heart[7-i]);
		}
		// cc++;
		// cc %= 30;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(500);
	}

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static int in = 0;
	if (htim == (&htim4)) {
		disp_(IOS[in]);
		in ++;
		in %= 8;
	}
}