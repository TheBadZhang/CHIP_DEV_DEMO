#include "stm32f10x.h"                  // Device header
#include "sys.h"
int main (void) {

	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Init(GPIOC, {
		.GPIO_Pin = GPIO_Pin_12,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	});
	GPIO_InitTypeDef GPIO_InitStructure = {
		.GPIO_Pin   = GPIO_Pin_12,         // 十二脚
		.GPIO_Speed = GPIO_Speed_50MHz,    //
		.GPIO_Mode  = GPIO_Mode_Out_OD     // 开漏输出
	};
	GPIO_Init (GPIOB, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd (RCC_APB2ENR_AFIOEN, ENABLE);

	EXTI_InitTypeDef a = {
		.
	}

	// GPIO_ResetBits (GPIOB, GPIO_Pin_12);
	// 等价于
	PBin (12);
	while (1) {
	}

}

