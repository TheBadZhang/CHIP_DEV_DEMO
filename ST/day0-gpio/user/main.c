 #include "stm32f10x.h"                  // Device header
#include "sys.h"
int main (void) {

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
	while (1) {
	}

}

