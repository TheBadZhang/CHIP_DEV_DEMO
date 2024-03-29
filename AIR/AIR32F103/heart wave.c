/*
1.ϵͳʱ������Ϊ T1 = 1/72000000
2.��ʱ��TIM2 �������� T2 = (20)*(1*T1)
3.���Ҳ���������ʱ��T3 = T2*32
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "air32f10x.h"

#define PRINTF_LOG 	printf

#define DAC1_DHR12RD_ADDRESS		(DAC_BASE+0x00000008+DAC_Align_12b_R)
#define DAC2_DHR12RD_ADDRESS		(DAC_BASE+0x00000014+DAC_Align_12b_R)

//���Ҳ��������ڵĵ���
// #define POINT_NUM 32

/* �������� */
/*
uint16_t Sine12bit[POINT_NUM] = {
2048	, 2460	, 2856	, 3218	, 3532	, 3786	, 3969	, 4072	,
4093	, 4031	, 3887	, 3668	, 3382	, 3042	, 2661	, 2255	,
1841	, 1435	, 1054	, 714	, 428	, 209	, 65	, 3	,
24		, 127	, 310	, 564	, 878	, 1240	, 1636	, 2048
};*/

uint32_t DAC_Sin[128];
uint16_t Sine12bit[] = {
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4d,0xb4b,0xad6,0xa53,0x9fe,0xa03,0xa6f,0xb2d,0xc0d,
0xcca,0xd27,0xcfd,0xc4b,0xb39,0xa0b,0x915,0x89f,0x8d1,0x9a6,
0xaeb,0xc4a,0xd64,0xde7,0xda6,0xcaa,0xb31,0x99b,0x854,0x7b9,
0x7f7,0x904,0xa9d,0xc57,0xdb9,0xe60,0xe19,0xcf1,0xb2f,0x94a,
0x7c1,0x701,0x73f,0x871,0xa48,0xc48,0xde7,0xeb3,0xe70,0xd29,
0xb31,0x90c,0x749,0x664,0x69c,0x7e6,0x9ed,0xc27,0xdfd,0xeec,
0xeb2,0xd58,0xb36,0x8da,0x6e5,0x5db,0x608,0x761,0x98c,0xbf8,
0xdfe,0xf11,0xee4,0xd7e,0xb3b,0x8b2,0x68e,0x561,0x57e,0x6de,
0x927,0xbbc,0xdee,0xf23,0xf08,0xd9d,0xb41,0x891,0x642,0x4f3,
0x4fd,0x65f,0x8bd,0xb75,0xdcf,0xf27,0xf1e,0xdb4,0xb45,0x874,
0x600,0x48e,0x483,0x5e2,0x84f,0xb25,0xda3,0xf1c,0xf29,0xdc4,
0xb48,0x85b,0x5c3,0x431,0x40e,0x566,0x7dd,0xacc,0xd6a,0xf02,
0xf27,0xdca,0xb46,0x843,0x58c,0x3da,0x39f,0x4eb,0x767,0xa69,
0xd24,0xedb,0xf18,0xdc8,0xb40,0x82b,0x558,0x387,0x332,0x470,
0x6ed,0x9fe,0xcd1,0xea6,0xefc,0xdba,0xb33,0x810,0x524,0x336,
0x2c7,0x3f4,0x66c,0x988,0xc71,0xe61,0xed0,0xd9f,0xb1c,0x7ef,
0x4ee,0x2e4,0x25a,0x373,0x5e4,0x905,0xc01,0xe09,0xe91,0xd73,
0xaf8,0x7c5,0x4b1,0x28d,0x1e7,0x2ea,0x54f,0x872,0xb7b,0xd99,
0xe3a,0xd2f,0xabd,0x787,0x464,0x226,0x163,0x24c,0x4a0,0x7bf,
0xacf,0xcff,0xdb4,0xcbc,0xa52,0x718,0x3e2,0x185,0x9d,0x15d,
0x388,0x655,0x9d5,0xc4a,0xd44,0xc8c,0xa5a,0x74a,0x433,0x1ea,
0x111,0x1e3,0x42f,0x75a,0xa92,0xcfe,0xdff,0xd53,0xb2c,0x81e,
0x4fc,0x29f,0x1a8,0x25c,0x48e,0x7a9,0xade,0xd55,0xe69,0xdd5,
0xbc1,0x8be,0x59c,0x330,0x222,0x2ba,0x4d1,0x7dc,0xb0c,0xd8c,
0xeb3,0xe37,0xc3b,0x948,0x629,0x3b4,0x291,0x30d,0x50a,0x800,
0xb29,0xdae,0xee8,0xe85,0xca3,0x9c4,0x6ad,0x432,0x2fc,0x35e,
0x53e,0x81e,0xb3a,0xdc2,0xf0c,0xec2,0xcfc,0xa35,0x72b,0x4ae,
0x368,0x3b0,0x572,0x837,0xb44,0xdca,0xf21,0xef1,0xd48,0xa9c,
0x7a3,0x529,0x3d6,0x405,0x5a7,0x84f,0xb47,0xdc8,0xf2a,0xf11,
0xd88,0xafa,0x817,0x5a4,0x448,0x45f,0x5e1,0x867,0xb47,0xdbd,
0xf25,0xf23,0xdba,0xb4f,0x886,0x620,0x4bf,0x4bf,0x620,0x882,
0xb43,0xdaa,0xf15,0xf27,0xde0,0xb9a,0x8f2,0x69e,0x53c,0x529,
0x667,0x8a1,0xb3e,0xd8f,0xef7,0xf1c,0xdf8,0xbdb,0x95a,0x71f,
0x5c2,0x59d,0x6b8,0x8c5,0xb39,0xd6c,0xecd,0xf01,0xdff,0xc11,
0x9bd,0x7a3,0x651,0x61e,0x715,0x8f2,0xb33,0xd42,0xe93,0xed3,
0xdf5,0xc3a,0xa1b,0x82b,0x6ec,0x6b0,0x783,0x929,0xb30,0xd0e,
0xe47,0xe8d,0xdd4,0xc52,0xa74,0x8ba,0x798,0x758,0x807,0x96f,
0xb30,0xcd0,0xde4,0xe29,0xd94,0xc55,0xac5,0x953,0x85e,0x824,
0x8ad,0x9ce,0xb34,0xc80,0xd5b,0xd94,0xd24,0xc35,0xb0e,0xa02,
0x957,0x933,0x997,0xa5b,0xb40,0xc06,0xc78,0xc83,0xc34,0xbb7,
0xb49,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,
0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a,0xb4a
};

	const int POINT_NUM = sizeof(Sine12bit)/sizeof(uint16_t);

uint32_t DualSine12bit[POINT_NUM];

USART_TypeDef* USART_TEST = USART1;
RCC_ClocksTypeDef clocks;

void UART_Configuration(uint32_t bound);
void GPIO_Configuration(void);
void DAC_Configuration(void);
void TIM_Configuration(void);
void DMA_Configuration(void);

int main(void)
{
	uint32_t i;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
	Delay_Init();
	UART_Configuration(115200);
	RCC_GetClocksFreq(&clocks);

	PRINTF_LOG("\n");
	PRINTF_LOG("SYSCLK: %3.1fMhz, HCLK: %3.1fMhz, PCLK1: %3.1fMhz, PCLK2: %3.1fMhz, ADCCLK: %3.1fMhz\n", \
	(float)clocks.SYSCLK_Frequency/1000000, (float)clocks.HCLK_Frequency/1000000, \
	(float)clocks.PCLK1_Frequency/1000000, (float)clocks.PCLK2_Frequency / 1000000, (float)clocks.ADCCLK_Frequency / 1000000);

	PRINTF_LOG("AIR32F103 DAC Out Software Sine Wave.\n");

	GPIO_Configuration();
	DAC_Configuration();
	TIM_Configuration();

	for (i = 0; i < POINT_NUM; i++)
	{
		DualSine12bit[i] = (Sine12bit[i] << 16) + (Sine12bit[i]);
	}

	DMA_Configuration();

	while(1);
}

void DMA_Configuration(void)
{
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC2_DHR12RD_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DualSine12bit;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = POINT_NUM;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(DMA2_Channel4, &DMA_InitStructure);
	DMA_Cmd(DMA2_Channel4, ENABLE);

	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC1_DHR12RD_ADDRESS;
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);
	DMA_Cmd(DMA2_Channel3, ENABLE);
}

void TIM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = (20-1);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

	TIM_Cmd(TIM2, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DAC_Configuration(void)
{
	DAC_InitTypeDef	DAC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);

	DAC_DMACmd(DAC_Channel_1, ENABLE);
	DAC_DMACmd(DAC_Channel_2, ENABLE);
}

 void UART_Configuration(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART_TEST, &USART_InitStructure);
	USART_Cmd(USART_TEST, ENABLE);
}


int SER_PutChar (int ch)
{
	while(!USART_GetFlagStatus(USART_TEST,USART_FLAG_TC));
	USART_SendData(USART_TEST, (uint8_t) ch);

	return ch;
}

int fputc(int c, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	if (c == '\n')
	{
		SER_PutChar('\r');
	}
	return (SER_PutChar(c));
}

