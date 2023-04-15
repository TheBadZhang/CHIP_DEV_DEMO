#include "delay.h"
#include "air32f10x.h"

#define PRINTF_LOG printf

#define GPIO_GROUP_TEST GPIOA  
#define GPIO_MODE_TEST GPIO_Mode_Out_PP
#define GPIO_SPEED_TEST GPIO_Speed_50MHz
#define GPIO_PIN1_TEST GPIO_Pin_2
#define GPIO_PIN2_TEST GPIO_Pin_10
#define GPIO_PIN3_TEST GPIO_Pin_11

/********************************************************************************/
// GPIO输出测试，开发板自带的3个灯依次亮起并熄灭实现跑马灯效果，日志通过串口1发送，波特率为115200
/********************************************************************************/
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_ClocksTypeDef clocks;
	//Delay_Init();				//延时初始化
	//RCC_GetClocksFreq(&clocks); //获取系统时钟频率
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN1_TEST | GPIO_PIN2_TEST | GPIO_PIN3_TEST;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_TEST; //速度50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_TEST;	 //输出模式
	GPIO_Init(GPIO_GROUP_TEST, &GPIO_InitStructure); //初始化GPIOB.2,10,11

	while (1)
	{
		GPIO_SetBits(GPIO_GROUP_TEST, GPIO_PIN1_TEST);
		//Delay_Ms(200);
		GPIO_SetBits(GPIO_GROUP_TEST, GPIO_PIN2_TEST);
		//Delay_Ms(200);
		GPIO_SetBits(GPIO_GROUP_TEST, GPIO_PIN3_TEST);
		//Delay_Ms(200);
		//GPIO_ResetBits(GPIO_GROUP_TEST, GPIO_PIN1_TEST);
		//Delay_Ms(200);
		//GPIO_ResetBits(GPIO_GROUP_TEST, GPIO_PIN2_TEST);
		//Delay_Ms(200);
		//GPIO_ResetBits(GPIO_GROUP_TEST, GPIO_PIN3_TEST);
		//Delay_Ms(200);
	}
}
