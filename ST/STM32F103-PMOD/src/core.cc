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


void core(void) {

	// HAL_TIM_Base_Start_IT(&htim4);
	// bool flag = false;
	// img2ios();
	// int in = 0;
	while (true) {
		flip(LED2);
		HAL_Delay(600);
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