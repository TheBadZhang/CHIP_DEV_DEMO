#ifndef __TBZ_SSD1306_H_
#define __TBZ_SSD1306_H_

#include "i2c.h"
#include "math.h"
#include "font.h"

#define OLED_ADDR B01111000
#define OLED_CMD  0x00
#define OLED_DATA 0x40
#define OLED_MODE 0


//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0x10
#define X_WIDTH 	128
#define Y_WIDTH 	64


void Delay_50ms(unsigned int Del_50ms);

void Delay_1ms(unsigned int Del_1ms);


#define OLED_WR_Byte(a,b) I2C_WriteRegister (OLED_ADDR, b, a)


/**
 * @brief ʹ�� filter function �����Ļ
 * @param func ���뵱ǰҳ�͵�ַ(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant);

void OLED_Set_Page (unsigned char page);
//��������
void OLED_Set_Pos(unsigned char x, unsigned char y);
//����OLED��ʾ
void OLED_Display_On(void);
//�ر�OLED��ʾ
void OLED_Display_Off(void);

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);

//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no);

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

//��ʼ��SSD1306
void OLED_Init(void);


#endif