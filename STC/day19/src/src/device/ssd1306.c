#include "i2c.h"
#include "math.h"
#include "device/ssd1306.h"
#include "device/font.h"

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

/*
OLED���Դ�
��Ÿ�ʽ����.
[0]0 1 2 3 ... 127
[1]0 1 2 3 ... 127
[2]0 1 2 3 ... 127
[3]0 1 2 3 ... 127
[4]0 1 2 3 ... 127
[5]0 1 2 3 ... 127
[6]0 1 2 3 ... 127
[7]0 1 2 3 ... 127
*/


void Delay_50ms(unsigned int Del_50ms) {
	unsigned int m;
	while(Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms) {
	unsigned char j;
	while(Del_1ms--)
		for(j=0;j<123;j++);
}

#define OLED_WR_Byte(a,b) I2C_WriteRegister (OLED_ADDR, b, a)


/**
 * @brief ʹ�� filter function �����Ļ
 * @param func ���뵱ǰҳ�͵�ַ(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant) {
	unsigned char m,n;
	FOR (m, 8) {
		OLED_WR_Byte(0xb0+m,OLED_CMD);		// ҳ 0-7
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		FOR (n, 128) OLED_WR_Byte ((*func)(n, m), OLED_DATA);
	}
}


void OLED_Set_Page (unsigned char page) {
	OLED_WR_Byte(0xb0+page,OLED_CMD);
}
//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//����OLED��ʾ
void OLED_Display_On(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//�ر�OLED��ʾ
void OLED_Display_Off(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size) {
	unsigned char i = 0, c = chr - ' ';//�õ�ƫ�ƺ��ֵ

	if (x > Max_Column - 1) { x = 0; y += 2; }
	OLED_Set_Pos (x, y);
	if (Char_Size >= 16) {
		FOR (i, 8) OLED_WR_Byte (font0816 [c*16+i], OLED_DATA);

		OLED_Set_Pos (x, y+1);
		FOR (i, 8) OLED_WR_Byte (font0816 [c*16+i+8], OLED_DATA);
	} else {
		FOR (i, 6) OLED_WR_Byte (font0608 [c][i], OLED_DATA);
	}
}


//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size) {
	unsigned char j = 0;
	while (chr[j]!='\0') {
		OLED_ShowChar (x, y, chr[j++], Char_Size);
		x += 8;
		if (x > 120) { x = 0; y += 2; }
	}
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2) {
	u8 t,temp;
	u8 enshow=0;
	FOR (t, len) {
		temp=(num/pow (10,len-t-1))%10;
		if(enshow==0&&t<(len-1)) {
			if(temp==0) {
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			} else enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
	}
}


//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no) {
	u8 t;
	OLED_Set_Pos(x, y);
	FOR (t, 16) OLED_WR_Byte(font_chinese[2*no][t],OLED_DATA);
	OLED_Set_Pos(x, y+1);
	FOR (t, 16) OLED_WR_Byte(font_chinese[2*no+1][t],OLED_DATA);
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]) {
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0) y=y1/8;
	else y=y1/8+1;

	for(y=y0;y<y1;y++) {
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++) {
			OLED_WR_Byte(BMP[j++],OLED_DATA);
		}
	}
}

//��ʼ��SSD1306
void OLED_Init(void) {
	unsigned char __code code [] =  {
		0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1,
		0xA6, 0xA8, 0x3F, 0xC8, 0xD3, 0x00,
		0xD5, 0x80,
		0xD8, 0x05,
		0xD9, 0xF1,
		0xDA, 0x12,
		0xDB, 0x30,
		0x8D, 0x14,
		0xAF
	}, i;
	FOR (i,sizeof (code)) {
		OLED_WR_Byte (code[i], OLED_CMD);
	}



	// OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	// OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	// OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	// OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
	// OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	// OLED_WR_Byte(0x81,OLED_CMD);// contract control
	// OLED_WR_Byte(0xFF,OLED_CMD);//--128
	// OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
	// OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	// OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	// OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	// OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	// OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	// OLED_WR_Byte(0x00,OLED_CMD);//

	// OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	// OLED_WR_Byte(0x80,OLED_CMD);//

	// OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	// OLED_WR_Byte(0x05,OLED_CMD);//

	// OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	// OLED_WR_Byte(0xF1,OLED_CMD);//

	// OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	// OLED_WR_Byte(0x12,OLED_CMD);//

	// OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	// OLED_WR_Byte(0x30,OLED_CMD);//

	// OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	// OLED_WR_Byte(0x14,OLED_CMD);//

	// OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}

