#ifndef LCD_H
#define LCD_H

#include "myheader.h"

#define nokia5110_writeCmd(cmd)   nokia5110_writeByte(cmd, 0)   //д��ָ��
#define nokia5110_writeDat(dat)   nokia5110_writeByte(dat, 1)   //д������

#define nokia5110_showBlank()     nokia5110_writeCmd(0x08)      //��ʾ�հ�
#define nokia5110_showNormal()    nokia5110_writeCmd(0x0c)      //������ʾ
#define nokia5110_showBlack()     nokia5110_writeCmd(0x09)      //��ʾȫ��
#define nokia5110_showReverse()   nokia5110_writeCmd(0x0d)      //��ɫ��ʾ

#define CLK P0_4     //����ʱ��         //������д������
#define DIN P0_3     //������������       //�ȸߺ��
#define DC  P0_2     //����ָ����ƶ�  //�ߵ�ƽ���ݣ��͵�ƽָ��
#define CS  P0_1     //Ƭѡʹ��         //�͵�ƽ��Ч
#define RST P0_0     //LCD��λ��       //�͵�ƽ��λ
#define LED P1_5    //����ƿ��ƶ�      //�ߵ�ƽ��LED

extern void nokia5110_writeByte(unsigned char wByte, unsigned char datOrCmd);
extern void nokia5110_clear();//����
extern void nokia5110_moveTo(unsigned char x, unsigned char y);
extern void nokia5110_writeChar(unsigned char x, unsigned char y, unsigned char c);
extern void nokia5110_writeString(unsigned char x, unsigned char y, unsigned char *str);
extern void nokia5110_LCDInit(void);

#endif