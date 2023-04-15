#include "i2c.h"
#include "math.h"
#include "device/ssd1306.h"
#include "device/font.h"

//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0x10
#define X_WIDTH 	128
#define Y_WIDTH 	64

/*
OLED的显存
存放格式如下.
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
 * @brief 使用 filter function 填充屏幕
 * @param func 传入当前页和地址(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant) {
	unsigned char m,n;
	FOR (m, 8) {
		OLED_WR_Byte(0xb0+m,OLED_CMD);		// 页 0-7
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		FOR (n, 128) OLED_WR_Byte ((*func)(n, m), OLED_DATA);
	}
}


void OLED_Set_Page (unsigned char page) {
	OLED_WR_Byte(0xb0+page,OLED_CMD);
}
//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//开启OLED显示
void OLED_Display_On(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示
void OLED_Display_Off(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size) {
	unsigned char i = 0, c = chr - ' ';//得到偏移后的值

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


//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size) {
	unsigned char j = 0;
	while (chr[j]!='\0') {
		OLED_ShowChar (x, y, chr[j++], Char_Size);
		x += 8;
		if (x > 120) { x = 0; y += 2; }
	}
}
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
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


//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no) {
	u8 t;
	OLED_Set_Pos(x, y);
	FOR (t, 16) OLED_WR_Byte(font_chinese[2*no][t],OLED_DATA);
	OLED_Set_Pos(x, y+1);
	FOR (t, 16) OLED_WR_Byte(font_chinese[2*no+1][t],OLED_DATA);
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
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

//初始化SSD1306
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

