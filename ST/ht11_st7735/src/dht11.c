#include "dht11.h"
#include "core.h"

/**
	* @brief DHT11 输出模式
	*/
static void DHT11_Mode_OUT_PP(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = DHT11_Pin,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Speed = GPIO_SPEED_FREQ_HIGH,
		.Pull = GPIO_NOPULL
	};
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

/**
	* @brief DHT11 输入模式
	*/
static void DHT11_Mode_IN_NP(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = DHT11_Pin,
		.Mode = GPIO_MODE_INPUT,
		.Speed = GPIO_SPEED_FREQ_HIGH,
		.Pull = GPIO_NOPULL
	};
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

/**
	* @brief DHT11 读取字节
	*/
uint8_t DHT11_ReadByte(void) {
	uint8_t i, temp = 0;

	for (i = 0; i < 8; i++) {
		while (DHT11_IN == GPIO_PIN_RESET);    // 等待低电平结束

		// 经过测试，这个值最好是 40 ~ 60，这里我选择 50 us
		delay_us(50);     // 至少延时 40 微秒  低电平为 0 ，高电平为 1

		if (DHT11_IN == GPIO_PIN_SET) {
			while (DHT11_IN == 1);	// 等待高电平结束
			temp |= (uint8_t)(0X01 << (7 - i));	    // 先发送高位 MSB
		} else {
			temp &= (uint8_t)~(0X01 << (7 - i));
		}
	}
	return temp;
}


/**
	* @brief DHT11 读取一次数据
	*/
uint8_t DHT11_ReadData(DHT11_Data_TypeDef *DHT11_Data) {
	DHT11_Mode_OUT_PP();		// 主机输出，主机拉低
	DHT11_OUT_0;
	HAL_Delay(18);					// 延时 18 ms

	DHT11_OUT_1;						// 主机拉高，延时 30 us
	bsp_delay_us(30);

	DHT11_Mode_IN_NP();			// 主机输入，获取 DHT11 数据

	if (DHT11_IN == 0) {			// 收到从机应答

		while (DHT11_IN == 0);		// 等待从机应答的低电平结束

		while (DHT11_IN == 1);		// 等待从机应答的高电平结束

		/*开始接收数据*/
		DHT11_Data->humi_int  = DHT11_ReadByte();
		DHT11_Data->humi_deci = DHT11_ReadByte();
		DHT11_Data->temp_int  = DHT11_ReadByte();
		DHT11_Data->temp_deci = DHT11_ReadByte();
		DHT11_Data->check_sum = DHT11_ReadByte();

		DHT11_Mode_OUT_PP();		// 读取结束，主机拉高
		DHT11_OUT_1;

		// 数据校验
		if (DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci +
				DHT11_Data->temp_int + DHT11_Data->temp_deci) {
			return 1;
		} else {
			return 0;
		}
	} else {		// 未收到从机应答
		return 0;
	}
}

