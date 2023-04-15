#ifndef __TBZ_MAX7219_H_
#define __TBZ_MAX7219_H_

//����Max7219�˿�
#define max7219_CLK P0_2
#define max7219_CS  P0_1
#define max7219_DIN P0_0


extern uchar __code max7219_disp [38][8];
/**
 * @brief ��MAX7219(U3)д���ֽ�
 * @param DATA ��д����ֽ�����
 */
void max7219_WriteByte (uchar DATA);
/**
 * @brief ��MAX7219�ļĴ���д������
 * @param addr �Ĵ�����ַ
 * @param dat ��д�������
 */
#define max7219_Write(addr,dat) max7219_MultiWrite(0,addr,dat)
/**
 * @brief ��MAX7219�ļĴ���д������
 * @param piece �ڼ���оƬ
 * @param addr �Ĵ�����ַ
 * @param dat ��д�������
 */
void max7219_MultiWrite (uchar piece, uchar addr, uchar dat);
/**
 * @brief ��ʼ��
 */
void max7219_Init (void);


// demo
/*

max7219_Init ();
int i,j = 8, k;
while (1) {
	FOR (j, 38) {
		FOR (k, 4) FOR (i, 8)
			max7219_Write (i+1,max7219_disp[j][i]);
		delay1ms (5000);
	}
}

*/



#endif