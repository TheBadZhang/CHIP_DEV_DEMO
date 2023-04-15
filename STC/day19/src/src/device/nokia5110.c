#include "device/nokia5110.h"
#include "device/font.h"
#include "binary.h"


#define HEIGHT 6
#define WIDTH 84

// �� D/C Ϊ 0����� //
/*************************************************/
#define FUNCTION_SET B00100000  // ����ģʽ/����ģʽ/��չָ�����ã�H��
				   // 00100PVH
#define P   B00000100    // 0 оƬ�ǻ�� 1 оƬ���ڵ���״̬
#define V   B00000010    // 0 ˮƽѰַ 1 ��ֱѰַ
#define H   B00000001    // 0 ʹ�û���ָ� 1 ʹ����չָ�
/*************************************************/
// when not H  //
/*************************************************/
#define DISPLAY_SET B00001000   // ������ʾ����
				//   00001D0E
#define DE_BLANK B00000000    // ��ʾ�հ�
#define DE_NORMAL B00000100   // ��ͨģʽ
#define DE_ALL B00000001      // ��������ʾ��
#define DE_INVERT B00000101   // ��תӳ��ģʽ
/*************************************************/
#define RAM_Y B01000000  // ���� RAM �� Y ��ַ [0,5]
			// 01000YYY
#define RAM_X B10000000  // ���� RAM �� X ��ַ [0,83]
			// 1XXXXXXX
/*************************************************/
// when H //
/*************************************************/
#define TEMP_K B00000100
#define TC0 B00000000
#define TC1 B00000001
#define TC2 B00000010
#define TC3 B00000011
/*************************************************/
#define BIAS B00010000     // ����Һ��ƫ��
#define BS0  B00010000
#define BS1  B00010001
#define BS2  B00010010
#define BS3  B00010011
#define BS4  B00010100
#define BS5  B00010101
#define BS6  B00010110
#define BS7  B00010111
/*************************************************/
// �� D/C Ϊ 1�����ݣ�

/**
 * @brief д��һ���ֽ�(���ݻ�ָ��)
 * @param wByte ��д�������
 * @param datOrCmd
 *           1-����
 *           0-ָ��
 */
void nokia5110_writeByte(uchar wByte, uchar datOrCmd) {
	unsigned char i = 8;

	CS = 0;         // ѡƬ
	DC = datOrCmd;  // 1-����  //0-ָ��
	while (i) {     // 8λ����, �ȸߺ��
		--i;
		DIN = (wByte >> i) & 0x01;
		CLK = 0;
		delay (1);
		CLK = 1;    //������д��
	}
	CS = 1;         // ��ֹ
}

/**
 * @brief �����Ļ�����е����ݣ���Ϊ0��
 */
void nokia5110_clear() {
	unsigned int i;               // ��ҪΪ����ָ�ʱ
	nokia5110_moveTo (0, 0);
	FOR (i, WIDTH*HEIGHT)         // ���� 5110 ��ÿһ���ֽ�
		nokia5110_writeDat(0x00);           // ������RAMд0

}

/**
 * @brief ����д����λ��
 * @param x [0,83]
 * @param y [0, 5]
 */
void nokia5110_moveTo(uchar x, uchar y) {
	nokia5110_writeCmd(RAM_X|x);         // ���� Y ����
	nokia5110_writeCmd(RAM_Y|y);         // ���� X ����
}

/**
 * @brief дһ���ַ�
 * @param x [0,9]
 * @param y [0,2]
 */
void nokia5110_writeChar(uchar x, uchar y, uchar c) {

	unsigned char i, j;
	c -= 32;
	x <<= 3;
	y <<= 1;
	FOR (j, 2) {
		nokia5110_moveTo(x, (y + j));
		FOR (i, 8) nokia5110_writeDat(font_Fixedsys[c][8 * j + i]);
	}
}

/**
 * @brief дһ���ַ���
 * @param x [0,9]
 * @param y [0,2]
 */
void nokia5110_writeString(uchar x, uchar y, uchar *str) {
	while(*str && x < 10) {
		nokia5110_writeChar(x++, y, *str++);
	}
}

void nokia5110_LCDInit(void) {
	RST = 0;
	RST = 1;           //Ӳ����λ

	nokia5110_writeCmd (FUNCTION_SET|H);        // ����ģʽ, ˮƽѰַ, ��չָ��
	nokia5110_writeCmd (TEMP_K|TC0);            // VLCD �¶�ϵ��,����0x04~0x07,ԽСԽ��
	nokia5110_writeCmd (BIAS|BS3);              // ����ƫ��ϵͳ(BSx) 1:48,����Ϊ0x10~0x17
	nokia5110_writeCmd (128+65);                // ���õ�ѹVLCD = 3.06 + 0.06*Vop, �Աȶȵ���,����Ϊ0x80~0xff;128+(0~127)

	nokia5110_writeCmd (FUNCTION_SET);          // ����ģʽ, ˮƽѰַ, ����ָ��
	nokia5110_writeCmd (DISPLAY_SET|DE_NORMAL); // ��ͨģʽ

	nokia5110_moveTo (0, 0);
	nokia5110_clear ();                         // ��ȫ��
}

