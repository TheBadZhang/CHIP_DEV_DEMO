#include "core.h"
#include "common.h"

#include <cstring>
#include <numeric>
#include <algorithm>


#include "oled.h"
char str_buf[128];


#define FFT_F32
#include "arm_math.h"
#include "arm_const_structs.h"
// const int adc_freq = 1000; // 采样频率(Hz)
#define fft_size 2048                // fft长度
#define adc_step_length fft_size
#define adc_size fft_size         // 采样数据长度
uint16_t adc_value[adc_size]; // 采样数据

unsigned char fft_present[200];  // 显示的fft数据
float fft_point_present[200];

#ifdef FFT_F32
float fft_inputbuf[fft_size];
float fft_outputbuf[fft_size];
#else
q15_t fft_inputbuf[fft_size];
q15_t fft_outputbuf[fft_size];
#endif

void fft_calc(void) {

	int ifftFlag = 0;
#ifdef FFT_F32
	float average = 0.0;
#else
	int doBitReverse = 1;
	q15_t average = 0;
#endif

	//? FFT 变换
	//? R（real、实数）FFT变换
#ifdef FFT_F32
	std::transform(adc_value, adc_value+adc_size, fft_inputbuf, [](float x){return x;});
	arm_mean_f32(fft_inputbuf, adc_size, &average);
	std::transform(fft_inputbuf, fft_inputbuf+fft_size, fft_inputbuf, [average](float x){return x-average;});
	arm_rfft_fast_instance_f32 S;
	arm_rfft_fast_init_f32(&S, fft_size);
	arm_rfft_fast_f32(&S, fft_inputbuf, fft_outputbuf, ifftFlag);
	arm_cmplx_mag_f32(fft_inputbuf, fft_outputbuf, fft_size);  // 求解模值
#else
	arm_mean_q15((q15_t*)adc_value, adc_size, &average);
	std::transform(fft_inputbuf, fft_inputbuf+fft_size, fft_inputbuf, [average](float x){return x-average;});
	arm_rfft_instance_q15 S_q;
	arm_rfft_init_q15(&S_q, fft_size, ifftFlag, doBitReverse);
	arm_rfft_q15(&S_q, fft_inputbuf, fft_outputbuf);
	arm_cmplx_mag_q15(fft_inputbuf, fft_outputbuf, fft_size);  // 求解模值
#endif
}


// 自定义字面量
constexpr double operator""pi(long double x) {
	return 3.1415926535*x;
}
constexpr double operator""pi(unsigned long long int x) {
	return 3.1415926535*x;
}
// 分贝函数
constexpr double db(double a, double x) {
	return a*log10(x);
}

void core(void) {
	set(LED);

	// 屏幕驱动
	U8G2_UC1609_SLG19264_1_4W_SW_SPI u8g2(U8G2_R2);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	// 屏幕背光 PWM
	__HAL_TIM_SET_COMPARE(&htim11, TIM_CHANNEL_1, 99);
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);

	// ADC 定时采集
	HAL_TIM_Base_Start_IT(&htim10);

	// 变量初始化
	std::fill(fft_point_present, fft_point_present+200, 4);

	int index = 0;
	while (true) {
		u8g2.clearBuffer();

		// 找出平均值后，通过平均值寻找波形零点
		// 其实不应该每个循环都做，应该等一百个数据之后再做，但是懒得改了
		q15_t average;
		int index_of_zero_point = adc_size/2;
		arm_mean_q15((q15_t*)adc_value, adc_size, &average);
		for (int i = adc_size/2; i < adc_size; i++) {
			if (adc_value[i] > average && adc_value[i-1] < average) {
				index_of_zero_point = i;
				break;
			}
		}


		// 遍历屏幕上每个一横坐标
		for (int i = 0; i < 192; i++) {
			// u8g2.drawHLine(i, 0, adc_value[i]/32);
			// u8g2.drawLine(i, 0, i, adc_value[i]/32);
			// 3.46v
			// u8g2.setDrawColor(0);
#define getpx(a,i) ((a)/2+16-(adc_value[(i)+index_of_zero_point-96]*(a)/4096))
#define drawpx(a) u8g2.drawPixel(i, getpx(a,i));
#define drawline(a) u8g2.drawLine(i, getpx(a,i), i, getpx(a,i+1));
			// 对坐标进行限幅
			int p1 = getpx(64, i);
			int p2 = getpx(64, i+1);
			if (p1 < 0) p1 = 0;
			if (p2 < 0) p2 = 0;
			if (p1 == 0 && p2 == 0) goto skip;
			// 绘制波形
			u8g2.drawLine(i, p1, i+1, p2);
			skip:
			// drawline(64);
			// drawpx(256);
			// u8g2.drawPixel(i, 64-(adc_value[i]*64/4096));
			// u8g2.drawPixel(i, 96-(adc_value[i]*128/4096));
			// u8g2.drawPixel(i, 160-(adc_value[i]*256/4096));
			// u8g2.drawPixel(i, 284-(adc_value[i]*512/4096));
#undef drawpx
#undef drawline
#undef getpx

			// u8g2.setDrawColor(1);
			// u8g2.drawPixel(i, 64-fft_outputbuf[i]/2048*64);

			// 对 fft 结果进行限幅
			int fft_v = db(db(10pi, sqrt(i)+1), fft_outputbuf[i]/4096);

			// 使频谱具有一定的持续性
			if (fft_v > fft_present[i]) fft_present[i] = fft_v;
			else if (fft_present[i] > 1) fft_present[i]-=2;
			u8g2.drawVLine(i, 64-fft_present[i], fft_present[i]);
			// u8g2.drawLine(i, 65-fft_present[i], i+1, 65-fft_present[i+1]);

			// 频谱上面跳动的小点
			if (fft_present[i] > fft_point_present[i]) {
				fft_point_present[i] = fft_present[i] + 2*(fft_present[i]-fft_point_present[i]);
				if (fft_point_present[i] > 64) fft_point_present[i] = 64;
			} else if (fft_point_present[i] > 0) fft_point_present[i]-=0.75;
			u8g2.drawPixel(i, 64-fft_point_present[i]);

			// float ttt = fft_inputbuf[i]*64/1024;
			// if (ttt < 0.0) u8g2.drawVLine(i, 32, -ttt);
			// else u8g2.drawVLine(i, 33-ttt, ttt);
		}
		// u8g2.drawStr(0, 10, "3.1415926");
		// for (int i = 0; i < 192; i++) {
		// 	for (int j = 0; j < 64; j++) {
		// 		if ((i^j)%2)
		// 			u8g2.drawPixel(i, j);
		// 	}
		// }
		u8g2.sendBuffer();
		// flip(LED);
		// HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, adc_step_length);
		// HAL_ADC_Start_DMA(&hadc1, (uint32_t*)(adc_value+adc_size-adc_step_length), adc_step_length);
		// 差不多 60fps
		HAL_Delay(15);
		// fft_calc();
	}
}


// void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
// 	// 关闭DMA，以便下一次开启，如果不关闭则会出现DMA忙的情况
// 	HAL_ADC_Stop_DMA(&hadc1);
// 	for (int i = 0; i < adc_size-adc_step_length; i++) {
// 		adc_value[i] = adc_value[i+adc_step_length];
// 	}
// 	fft_calc();
// 	// HAL_ADC_Start_DMA(&hadc1, (uint32_t*)(adc_value+adc_size-adc_step_length), adc_step_length);
// }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static unsigned int cnt = 0;
	if (htim == (&htim10)) {
		if (cnt == adc_size) {
			cnt = 0;
			fft_calc();
		}
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)(adc_value+cnt), 1);
		cnt++;
	}
}
