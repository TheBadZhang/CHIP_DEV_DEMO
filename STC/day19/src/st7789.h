#ifndef __TBZ_ST7789_H_
#define __TBZ_ST7789_H_
#define __TBZ_SPI_ENABLE_
#include "myheader.h"
#include "mystring.h"
#include "device/font.h"


//---------------------------Һ��������˵��-------------------------------------//
//����ǰ��ο�Һ����˵�����10ҳ���Ŷ���
#define BLK P0_7    //��ģ��BL���ţ�������Բ���IO���ƻ���PWM���ƣ�Ҳ����ֱ�ӽӵ��ߵ�ƽ����
#define SCL P1_5    //��ģ��CLK����         ������Pin9_SCL
#define SDA P1_3    //��ģ��DIN/MOSI����    ������Pin8_SDA
#define DC P1_0     //��ģ��D/C����         ������Pin7_A0
#define CS P1_7     //��ģ��CE����          ������Pin12_CS      //! ������Ļû��Ƭѡ���ţ��˴��������⴦��
#define RESET P1_1  //��ģ��RST����         ������Pin6_RES
//---------------------------End ofҺ��������---------------------------------//

//���峣����ɫ
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define WHITE 0xffff
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define GRAY0 0xEF7D
#define GRAY1 0x8410
#define GRAY2 0x4208


//��Һ����дһ��8λ����/ָ��
void lcd_writeDC(uchar Data, uchar cmd);
//��Һ����дһ��16λ����
void lcd_writeWord(unsigned int Data);

void lcd_reset ();
//////////////////////////////////////////////////////////////////////////////////////////////
//Һ������ʼ�� for S6D02A1
void lcd_initial();
/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
void lcd_setRegion(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end);

void lcd_putPixel (uint x_start, uint y_start, uint color);
// ʹ��һ����ɫ�����Ļ
void lcd_clear (int color);

//�������ô��ڷ�������ֿ����ݣ����Gui_DrawFont_GBK16������
void Fast_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s);
//�˷�����溺�ֽ���
void Gui_DrawFont_GBK16(uint x, uint y, uint fc, uint bc, uchar *s);

#endif