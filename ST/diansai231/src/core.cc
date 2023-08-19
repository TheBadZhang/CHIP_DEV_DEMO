#include "core.h"
#include "common.h"
#include <cstring>
#include <cstdio>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "trick.h"
#include "delay.h"
#include "ad9833.h"
#include <cmath>

#define fft_size 4096                // fft长度
#define adc_size fft_size         // 采样数据长度
uint32_t adc_value[adc_size]; // 采样数据
float32_t adc_value_f[adc_size]; // 采样数据
char buf[108];
char str[] = "sfjksldjfkljcxkljvkljxzlv";
const int adc_freq = 1000000; // 采样频率

float32_t fft_inputbuf[fft_size*2];
float32_t fft_outputbuf[fft_size];
// float Phase_Result[fft_size];

uint32_t TIM2_TIMEOUT_COUNT;
uint8_t TIM2_CAPTURE_STA = 0xff;
uint32_t TIM2_CAPTURE_BUF[3] = { 0, 0, 0 };


#define UART2_RX_LEN  128
uint8_t uart2_rx_buf[UART2_RX_LEN];
uint32_t phase_setting = 0;

/*
*********************************************************************************************************
*    函 数 名: PowerPhaseRadians_f32
*    功能说明: 求相位
*    形    参：_usFFTPoints  复数个数，每个复数是两个float32_t数值
*             _uiCmpValue  比较值，需要求出相位的数值
*    返 回 值: 无
*********************************************************************************************************
*/
// void PowerPhaseRadians_f32(uint16_t _usFFTPoints, float32_t _uiCmpValue) {
// 	float32_t lX, lY;
// 	uint32_t i;
// 	float32_t phase;
// 	float32_t mag;


// 	for (i=0; i <_usFFTPoints; i++)
// 	{
// 		lX= s[i].real;       /* 实部 */
// 		lY= s[i].imag;    /* 虚部 */

// 		phase = atan2f(lY, lX);                            /* atan2求解的结果范围是(-pi, pi], 弧度制 */
// 		arm_sqrt_f32((float32_t)(lX*lX+ lY*lY), &mag);   /* 求模 */

// 		if(_uiCmpValue > mag)
// 		{
// 			s[i].real = 0;
// 		}
// 		else
// 		{
// 			s[i].real= phase* 180.0f/3.1415926f;   /* 将求解的结果由弧度转换为角度 */
// 		}
// 	}
// }

struct SIGNAL {
	int freq;
	int amplitude;
	int phase;
	enum TYPE { SINE, TRIANGLE } type;
} signal_A, signal_B;


void print_SIGNAL(SIGNAL* sig, const char* name) {

	double t = (double)(sig->freq)*adc_freq/fft_size;
	int tt = 5*((int)((t+0.5)/5000+0.5));
	int len = sprintf (buf, "[%s]：频率：%4.3lfkHz->%3dkHz\t类型：%s\n", name, t/1000, tt, sig->type==SIGNAL::SINE?"正弦波":"三角波");
	HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 0xffff);
}

void fft_calc() {

	int ifftFlag = 0;
	int doBitReverse = 1;


	//? FFT 变换
	//? R（real、实数）FFT变换
	// for (int i = 0; i < fft_size; i++) {
	// 	fft_inputbuf[i] = adc_value[i];
	// }
	// arm_rfft_fast_instance_f32 S;
	// arm_rfft_fast_init_f32(&S, fft_size);
	// arm_rfft_fast_f32(&S, fft_inputbuf, fft_outputbuf, ifftFlag);
	//* 虽然说只有实数的FFT变换较含复数的傅里叶变换更快
	//* 但是调用实数的傅里叶变换会导致程序尺寸过大（虽然没有超过flash大小，但是烧录失败了）
	for (int i = 0; i < adc_size; i++) {
		adc_value_f[i] = adc_value[i];
	}
	float average_f;
	arm_mean_f32(adc_value_f, adc_size, &average_f);

	//? C（complex、复数）FFT变换
	for (int i = 0; i < fft_size; i++) {
		fft_inputbuf[i*2] = adc_value[i]-average_f;
		fft_inputbuf[i*2+1] = 0;
	}
	arm_cfft_f32(&arm_cfft_sR_f32_len4096, fft_inputbuf, ifftFlag, doBitReverse);
	arm_cmplx_mag_f32(fft_inputbuf, fft_outputbuf, fft_size);  // 求解模值




	int index[20];
	int index_i = 0;

	float now;
	float max_value = 0.0;

	for (int i = 1; i < fft_size/2; i++) {
		now = fft_outputbuf[i];
		if (max_value < now) max_value = now;
	}
	const float max_tolerance_ratio = 0.02;
	const float tolerance = max_value*max_tolerance_ratio;
	// const float tolerance = 10000;
	for (int i = 5; i < fft_size/2; i++) {
		now = fft_outputbuf[i];
		// tolerance =
		// if (now > fft_outputbuf[i-1]+tolerance && now > fft_outputbuf[i+1]+tolerance) {
		// if (now > fft_outputbuf[i-1]+tolerance && now > fft_outputbuf[i+1]+tolerance && now > tolerance) {
		if (now > 20000 && now > fft_outputbuf[i-1] && now > fft_outputbuf[i+1]) {
			if (index_i < 20) index[index_i++] = i;
			// printf ("freq[%d]:%lf\n", i, (double)(i-1)*adc_freq/fft_size);
		}
	}


	for (int i = 0; i < index_i; i++) {
		double t = (double)(index[i])*adc_freq/fft_size;
		int tt = 5*((int)((t+0.5)/5000+0.5));
		int len = sprintf (buf, "freq[%d]:%.5lfkHz@%f\n四舍五入后频率为：%dkHz\n", index[i]+1, t/1000, fft_outputbuf[index[i]], tt);
		HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 0xffff);
	}



	if (index_i < 2) {
		//! 信号读取错误，可分析信号少于2个
		; // do nothing
		signal_A.type = SIGNAL::SINE;
		signal_A.freq = index[0];     //? 此处的频率值尚未经过计算
	} else if (index_i == 2) {
		//* 没有高次谐波，所以此处两个信号一定是正弦波
		//* 同时，频率较低者为A信号，频率较高者为B信号
		signal_A.type = SIGNAL::SINE;
		signal_A.freq = index[0];     //? 此处的频率值尚未经过计算
		signal_B.type = SIGNAL::SINE;
		signal_B.freq = index[1];
	} else {
		//* 剩下的情况就是存在高次谐波，需要进一步分析
		//* 一般来说需要高次谐波的数量足够多才可以明确是三角波
		//* 如果只有三个可能会造成误判，这里就不在意数量了
		//* 直接先计算出结果再说
		//? 存在两种情况，正弦波+三角波 或者 三角波+三角波
		//? 如果最大值相差过大，则是前者，反之后者

		float max1 = 0.0, max2 = 0.0;
		int max1_i = 0, max2_i = 0;
		for (int i = 0; i < index_i; i++) {
			if (max1 < fft_outputbuf[index[i]]) {
				max2 = max1;
				max2_i = max1_i;
				max1 = fft_outputbuf[index[i]];
				max1_i = index[i];
			} else if (max2 < fft_outputbuf[index[i]]) {
				max2 = fft_outputbuf[index[i]];
				max2_i = index[i];
			}
		}

		if (max2_i < max1_i) {
			int t = max1_i;
			max1_i = max2_i;
			max2_i = t;
			float tt = max1;
			max1 = max2;
			max2 = tt;
		}
		float a3 = 0.0, a5 = 0.0, b3 = 0.0, b5 = 0.0;
		// 遍历找到的频率，找到其中可能是三角波的谐波
		for (int i = 0; i < index_i; i++) {
			float ta = ((float)index[i]/max1_i);
			if (2.9 < ta && ta < 3.1) a3 = fft_outputbuf[index[i]];
			else if (4.9 < ta && ta < 5.1) a5 = fft_outputbuf[index[i]];
			float tb = ((float)index[i]/max2_i);
			if (2.9 < tb && tb < 3.1) b3 = fft_outputbuf[index[i]];
			else if (4.9 < tb && tb < 5.1) b5 = fft_outputbuf[index[i]];
		}
		if ( a3 > 20000 && a5 > 20000 || max1_i > 143 && a3 > 20000) {
			// max1 是三角波
			signal_A.type = SIGNAL::TRIANGLE;
			signal_A.freq = max1_i;
		} else {
			// max1 是正弦波
			signal_A.type = SIGNAL::SINE;
			signal_A.freq = max1_i;
		}

		if ( b3 > 20000 && b5 > 20000 || max2_i > 143 && b3 > 20000) {
			// max2 是三角波
			signal_B.type = SIGNAL::TRIANGLE;
			signal_B.freq = max2_i;
		} else {
			// max2 是正弦波
			signal_B.type = SIGNAL::SINE;
			signal_B.freq = max2_i;
		}

/*
		const float triangle_sine_tolerance_ratio = 0.06;
		bool big_diff = abs(max1-max2) > max1*triangle_sine_tolerance_ratio;
		if (max1 < 1000000 && max2 > 1000000 || max1 > 1000000 && max2 < 1000000) {
			//* 三角波+正弦波
			if (max1_i < max2_i) {
				signal_A.type = SIGNAL::SINE;
				signal_A.freq = max1_i;
				signal_B.type = SIGNAL::TRIANGLE;
				signal_B.freq = max2_i;
			} else {
				signal_A.type = SIGNAL::TRIANGLE;
				signal_A.freq = max2_i;
				signal_B.type = SIGNAL::SINE;
				signal_B.freq = max1_i;
			}
		} else {
			//* 三角波+三角波
			signal_A.type = SIGNAL::TRIANGLE;
			signal_B.type = SIGNAL::TRIANGLE;
			if (max1_i < max2_i) {
				signal_A.freq = max1_i;
				signal_B.freq = max2_i;
			} else {
				signal_A.freq = max2_i;
				signal_B.freq = max1_i;
			}
		}
*/
	}


	print_SIGNAL(&signal_A, "signal_A");
	double t = round((double)(signal_A.freq)*adc_freq/fft_size);
	double tt = 5.0*((int)((t+0.5)/5000+0.5));
	print_SIGNAL(&signal_B, "signal_B");
	double t2 = round((double)(signal_B.freq)*adc_freq/fft_size);
	double tt2 = 5.0*((int)((t2+0.5)/5000+0.5));
	AD9833_WaveSeting(1, tt*1000.0,0,signal_A.type == SIGNAL::SINE ? SIN_WAVE : TRI_WAVE, 0);
	AD9833_WaveSeting(2, tt2*1000.0,0,signal_B.type == SIGNAL::SINE ? SIN_WAVE : TRI_WAVE, 0);
	// 求相频
	// PowerPhase
	// for (int i = 0; i < fft_size; i++) {
	// 	int len = sprintf(buf, "%f,", fft_outputbuf[i]);
	// 	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	// }
}

const int wave_value_half_size = 30;
const int wave_value_size = 2*wave_value_half_size;
const uint16_t wave_value_a[wave_value_size] = {
	2474,2881,3252,3570,3822,3996,4085,4085,3996,3822,3570,3252,2881,2474,2049,1623,1216,845,527,275,101,12,12,101,275,527,845,1216,1623,2048,
	2474,2881,3252,3570,3822,3996,4085,4085,3996,3822,3570,3252,2881,2474,2049,1623,1216,845,527,275,101,12,12,101,275,527,845,1216,1623,2048
};
void gen_sine_wave(uint16_t* wave_value) {
	//? 生成正弦波
	for (int i = 0; i < wave_value_size; i++) {
		wave_value[i] = (uint16_t)(2048 + 2048 * sin(2*PI*i/wave_value_half_size));
	}
	//? 生成三角波
	// for (int i = 0; i < wave_value_size; i++) {
	// 	wave_value[i] = (uint16_t)(4096 * i / wave_value_size);
	// }
}

int get_counter_from_freq(int freq) {
	return 120000 / (32*freq) - 1;
}

void core(void) {

	//? 这里虽然是64位的正弦波，其实是两个周期，通过调整dma设定的初始位置就可以调整相位
	// const uint16_t CH_value[64] = { 2448,2832,3186,3496,3751,3940,4057,4095,
	// 								4057,3940,3751,3496,3186,2832,2448,2048,
	// 								1648,1264,910,600,345,156,39,0,39,156,345,
	// 								600,910,1264,1648,2048, 2448,2832,3186,3496,3751,3940,4057,4095,
	// 								4057,3940,3751,3496,3186,2832,2448,2048,
	// 								1648,1264,910,600,345,156,39,0,39,156,345,
	// 								600,910,1264,1648,2048};

	//* ADC 采样一次
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, adc_size);

	// HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);

	//* 高速 DAC 输出
	HAL_OPAMP_Start(&hopamp3);
	HAL_TIM_Base_Start(&htim6);
	HAL_DAC_Start_DMA(&hdac3, DAC_CHANNEL_2, (uint32_t*)wave_value_a, 30, DAC_ALIGN_12B_R);
	// HAL_DAC_Start_DMA(&hdac3, DAC_CHANNEL_2, (uint32_t*)adc_value, 1, DAC_ALIGN_12B_R);


	// print_SIGNAL(&signal_A, "signal_A");
	// print_SIGNAL(&signal_B, "signal_B");


	// HAL_TIM_Base_Start_IT(&htim2);
	// HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	// HAL_TIM_Base_Start_IT(&htim17);
	// AD9833_WaveSeting(1, 50000.5,0,SIN_WAVE, 0);
	// AD9833_WaveSeting(2, 50000.5,0,TRI_WAVE, 0);

	HAL_UARTEx_ReceiveToIdle_DMA (&huart2, (uint8_t*)uart2_rx_buf, UART2_RX_LEN);

	while (true) {
		// flip(LED);
		// DAC3 -> DHR12R2 = adc_value[0];
		// HAL_DAC_SetValue(&hdac3, DAC_CHANNEL_2, DAC_ALIGN_12B_R, adc_value[0]);
		// HAL_DAC_Start(&hdac3, DAC_CHANNEL_2);
		// HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, adc_value[0]);
		// delay_us(10);
		// HAL_UART_Transmit(&huart1, (uint8_t *)str, 7, 1000);
		HAL_Delay(1000);
	}

}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	// 关闭DMA，以便下一次开启，如果不关闭则会出现DMA忙的情况
	HAL_ADC_Stop_DMA(&hadc1);

	auto c = arm_sin_f32(3.14159265/6);
	int d = c*100;
	int len = sprintf(buf, "%f\r\n", c);
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);

	// for (int i = 0; i < adc_size; i++) {
	// 	// adc_data[i] = adc_value[i];
	// 	len = sprintf(buf, "%d,", adc_value[i]);
	// 	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	// }

	HAL_UART_Transmit(&huart1, (uint8_t *)"\n\n\n\n", 4, 1000);

	fft_calc();
	// HAL_UART_Transmit(&huart1, (uint8_t*)adc_value, adc_size, 1000);
}


// static int Phase = (350)/2.0/3.14159265*4096;
int Phase = 4069;  // 350 度差不多是原本的零相位
// static int Phase = 651.8986469 * (3.141592653)/2;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim2)) {
		TIM2_TIMEOUT_COUNT++;
	} else if (htim == (&htim17)) {
		Phase += 10;
		if (Phase > 4096) {
			Phase = 0;
		}

		int len = sprintf(buf, "%d\r\n", Phase);
		HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
		// 触发一次中断（实际上对于这个程序来说是不需要这个步骤的，
		// 应该只采样一次数据，然后直接在中断中处理就可以了
		// 现在看起来需要这个程序来做一定的延时了
		// 因为在刚启动的时候adc的采样并不是很精确（？
		// auto ret = HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, adc_size);
		// if (ret == HAL_OK) {
		// 	HAL_UART_Transmit(&huart1, (uint8_t *)"ok\n", 3, 1000);
		// } else if (ret == HAL_BUSY) {
		// 	// 没有手动关闭 DMA，这里总会陷入忙状态
		// 	HAL_UART_Transmit(&huart1, (uint8_t *)"busy\n", 5, 1000);
		// }
		// HAL_UART_Transmit(&huart1, (uint8_t *)str, 7, 1000);
	} else if (htim == (&htim15)) {
		// i++;
		// if (i == 360) i = 0;
		// AD9833_WaveSeting(1, 40000,0,SIN_WAVE, 0);
		// AD9833_WaveSeting(2, 40000,0,TRI_WAVE, 0);



		double t = round((double)(signal_A.freq)*adc_freq/fft_size);
		double tt = 5.0*((int)((t+0.5)/5000+0.5));
		double t2 = round((double)(signal_B.freq)*adc_freq/fft_size);
		double tt2 = 5.0*((int)((t2+0.5)/5000+0.5));
		AD9833_WaveSeting(1, tt*1000.0,0,signal_A.type == SIGNAL::SINE ? SIN_WAVE : TRI_WAVE, 0);
		AD9833_WaveSeting(2, tt2*1000.0,0,signal_B.type == SIGNAL::SINE ? SIN_WAVE : TRI_WAVE, 0);
		AD9833_Write(1, 0x0100); //复位AD9833,即RESET位为1
		AD9833_Write(1, 0x2002);
		// AD9833_Write(2, 0xC000);	//设置相位
		AD9833_Write(2, 0x0100); //复位AD9833,即RESET位为1
		AD9833_Write(2, (Phase%4096)|0xC000);	//设置相位
		// AD9833_Write(2, Phase|0xC000);	//设置相位
		AD9833_Write(2, 0x2000);


		// int len = sprintf(buf, "%d\n", i);
		// HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	}
}


void TIM2_SetCapturePolarity(uint32_t TIM_ICPolarity) {
	TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	TIM2->CCER |= (TIM_ICPolarity << TIM_CHANNEL_1);
}

void print(const char* str) {
	HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 1000);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim2))
	{
		switch (TIM2_CAPTURE_STA)
		{
		case 1:
		{
			print("准备捕获下降沿...\r\n");
			TIM2_CAPTURE_BUF[0] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM2_TIMEOUT_COUNT * 0xFFFF;
			TIM2_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_FALLING);					// 设置为下降沿触发
			TIM2_CAPTURE_STA++;
			break;
		}
		case 2:
		{
			print("准备捕获下个上升沿...\r\n");
			TIM2_CAPTURE_BUF[1] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM2_TIMEOUT_COUNT * 0xFFFF;
			TIM2_SetCapturePolarity(TIM_INPUTCHANNELPOLARITY_RISING);					// 设置为上升沿触发
			TIM2_CAPTURE_STA++;
			break;
		}
		case 3:
		{
			print("捕获结束...\r\n");
			print("# end ----------------------------------------------------\r\n");
			TIM2_CAPTURE_BUF[2] = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) + TIM2_TIMEOUT_COUNT * 0xFFFF;
			HAL_TIM_IC_Stop_IT(htim, TIM_CHANNEL_1);									// 停止捕获
			HAL_TIM_Base_Stop_IT(&htim2);												// 停止定时器更新中断
			TIM2_CAPTURE_STA++;
			break;
		}
		default:
			break;
		}
	}
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size) {
	if (huart == (&huart2)) {
		HAL_TIM_Base_Start_IT(&htim15);
		// sscanf((char*)uart2_rx_buf, "%d", &phase_setting);
		phase_setting = uart2_rx_buf[0] + uart2_rx_buf[1] * 256 + uart2_rx_buf[2] * 256 * 256 + uart2_rx_buf[3] * 256 * 256 * 256;

		int len = sprintf((char*)buf, "phase_setting:%d\n", phase_setting);
		HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 1000);
		phase_setting = (phase_setting) % 360;
		len = sprintf((char*)buf, "phase_setting2:%d\n", phase_setting/360.0*4096);
		HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 1000);
		Phase = (4069+phase_setting/360.0*4096);
		Phase %= 4096;
		len = sprintf((char*)buf, "Phase:%d\n", Phase);
		HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 1000);
		// AD9833_Write(2, phase_setting|0xC000);	//设置相位
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, uart2_rx_buf, UART2_RX_LEN);
	}
}

