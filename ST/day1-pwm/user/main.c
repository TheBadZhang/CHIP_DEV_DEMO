#include "stm32f10x.h"	// Device header
#include "sys.h"
#include "delay.h"

typedef u16 u16_t;
typedef u8 u8_t;

void timer4_ch4_pwm_init(u16_t arr, u16_t psc) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // 启用定时器4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	// 启用 GPIO_B 和 GPIO_B的端口复用功能

	// GPIO_PinAFConfig (GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);

	GPIO_InitTypeDef GPIO_InitStructure = {
		.GPIO_Pin = GPIO_Pin_9,			// 8脚
		.GPIO_Mode = GPIO_Mode_AF_PP,	// 复用推挽输出
		.GPIO_Speed = GPIO_Speed_50MHz	// 频率
	};

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {
		.TIM_Period = arr,	   // 计时器重载值
		.TIM_Prescaler = psc,  // 时钟频率预分频值
		.TIM_CounterMode = TIM_CounterMode_Up,
		// 向上计数
		.TIM_ClockDivision = 0
		// .TIM_RepetitionCounter =
	};
	TIM_OCInitTypeDef TIM_OCInitStructure = {
		.TIM_OCMode = TIM_OCMode_PWM2,				  // PWM模式2
		.TIM_OutputState = TIM_OutputState_Enable,	  // 启用比较输出
		.TIM_OutputNState = TIM_OutputNState_Enable,  // 比较输出
		// .TIM_Pulse = 0, // 用于比较的值
		.TIM_OCPolarity = TIM_OCPolarity_Low,
		// .TIM_OCNPolarity = TIM_OCNPolarity_Low,
		// .TIM_OCIdleState =
		// .TIM_OCNIdleState
	};

	GPIO_Init(GPIOB, &GPIO_InitStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  // channel 4

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
}
void Servo_Control(uint16_t angle) {
	float temp = 1;
	double t = 2;
	temp = (1.0 / 9.0) * angle + 5.0;		//寄存器值 = 1/9 * 角度 + 5
	TIM_SetCompare4(TIM4, (uint16_t)temp);	//将角度值写入比较寄存器
}

#define PULM GPIO_Pin_8
#define PUL PBout (8)
#define DIRM GPIO_Pin_10
#define DIR PAout(10)
#define ENAM GPIO_Pin_9
#define EN PAout(9)

void TIM4_CH3_PWM_Init (u16_t arr, u16_t psc) {

	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure = {
		.GPIO_Pin   = PULM,
		.GPIO_Mode  = GPIO_Mode_AF_PP,
		.GPIO_Speed = GPIO_Speed_50MHz
	};

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {
		.TIM_Period = arr,
		.TIM_Prescaler = psc,
		.TIM_ClockDivision = 0,
		.TIM_CounterMode = TIM_CounterMode_Up
	};

	TIM_OCInitTypeDef TIM_OCInitStructure = {
		.TIM_OCMode   = TIM_OCMode_PWM2,
		.TIM_OutputState = TIM_OutputState_Enable,
		.TIM_OutputNState = TIM_OutputNState_Enable,
		.TIM_OCPolarity = TIM_OCPolarity_Low
	};

	GPIO_Init (GPIOB, &GPIO_InitStructure);
	TIM_TimeBaseInit (TIM4, &TIM_TimeBaseStructure);
	TIM_OC3Init (TIM4, &TIM_OCInitStructure);

	TIM_Cmd (TIM4, ENABLE);
}

void motorInit (void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure = {
		.GPIO_Mode  = GPIO_Mode_Out_PP,
		.GPIO_Pin   = ENAM | DIRM,
		.GPIO_Speed = GPIO_Speed_50MHz
	};
	GPIO_Init (GPIOA, &GPIO_InitStructure);
}

void delay(u16 num) {
	u16 i, j;
	for (i = 0; i < num; i++)
		for (j = 0; j < 0x800; j++)
			;
}


int main(void) {
	/*
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure = {
		.GPIO_Pin   = GPIO_Pin_12,         // 十二脚
		.GPIO_Speed = GPIO_Speed_50MHz,    //
		.GPIO_Mode  = GPIO_Mode_Out_OD     // 开漏输出
	};
	GPIO_Init (GPIOB, &GPIO_InitStructure);
	// GPIO_ResetBits (GPIOB, GPIO_Pin_12);
	// 等价于
	PBin (12);
	*/

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// GPIO_InitTypeDef GPIO_InitStructure = {
	// 	.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5,
	// 	.GPIO_Speed = GPIO_Speed_50MHz,
	// 	.GPIO_Mode = GPIO_Mode_Out_OD
	// };

	// GPIO_Init(GPIOA, &GPIO_InitStructure);

	// timer4_ch4_pwm_init(199, 7199);
	// // delay_ms (40);
	// // TIM_SetCompare4 (TIM4, 15);
	// Servo_Control(144);
	// delay(8000);
	// Servo_Control(60);
	// delay(8000);
	// Servo_Control(144);


	delay_init();	    	                            //ÑÓÊ±º¯Êý³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃNVICÖÐ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	TIM4_CH3_PWM_Init(1000, 71);
	motorInit();
	TIM_SetCompare3(TIM4, 1000);
	DIR = 1;
	EN = 0;
	while (1) {
		EN = 0;
		delay_ms (2000);
		EN = 1;
		delay_ms (2000);
	}
}
