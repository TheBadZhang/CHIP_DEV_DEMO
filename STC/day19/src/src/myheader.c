#include "../inc/myheader.h"


/**
 * @brief һ���򵥵��ӳٺ���
 * @param m ��ʱ m ��ʱ��
 * @return void
 */
void delay(unsigned int m) {
	while (m--);
}
/**
 * @brief һ���򵥵��ӳٺ���
 * @param x10us ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����*10 ��΢��
 * @return void
 */
void delay10us(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}
/**
 * @brief һ���򵥵��ӳٺ���
 * @param x1ms ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����������
 * @return void
 */
void delay1ms(unsigned int a){
	uint i;
	while (--a!=0) for(i=1200;i>0;i--);   //1T��Ƭ��i=600������12T��Ƭ��i=125
}