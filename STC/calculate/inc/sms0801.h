#ifndef __TBZ_SMS0801_H_
#define __TBZ_SMS0801_H_

//-------------------------------------------------------------------------------
//SMS0801B��Ʒ����˵��
//PIN1: VSS [��Դ��]
//PIN2: VSS [��Դ��]
//PIN3: CLK [������λ��������]
//PIN4: VDD [��Դ����]
//PIN5: VDD [��Դ����]
//PIN6: DI  [������������]
//-------------------------------------------------------------------------------
#define CLK P1_2   // �����崥��
#define  DI P1_5
#define SMS_DELAY() \
	_nop_();        \
	_nop_();
unsigned char num_ram [8] = {0};
unsigned char num_point = 0x04;   // С�����λ��
//-------------------------------------------------------------------------------
//����ʶζ���:  8�ֵ�������һ�ʶ�ΪA�ʶ�,˳ʱ�뷽������ΪBCDEF�ʶ�,�м����G�ʶ�
//����ʶ�˳��:  D76543210
//               ABCDE GX
unsigned char NUMCODETAB[] = { 0xFC, 0x60, 0xDA, 0xF2,	 // ����0,1,2,3
							   0x66, 0xB6, 0xBE, 0xE0,	 // ����4,5,6,7
							   0xFE, 0xF6, 0x00, 0x02,	 // ����8,9,�ַ��ո�,�ַ�-
							   0x9C, 0xCE, 0x9E, 0x8E }; // �ַ�C,�ַ�P,�ַ�E,�ַ�F
/**
 * @brief �������и������
 * @param num ����
 */
void SMS0801_t2n (signed long num) { // long ��ΧΪ -2147483648-2147483647

	memset (num_ram, sizeof (num_ram), 0xa);    // ��յ�ǰ����
	if (num) for (j = 7; num > 0; -- j){        // �����ݴ浽
		num_ram [j] = num % 10;
		num /= 10;
	}
	else num_ram [7] = 0;
}
/**
 * @brief LCDҺ����ʾ�������ӳ���
 */ 
void transram(void) {
	unsigned char buf;
	unsigned char mask, i, j;

	for (mask = 0x80, i = 0; mask != 0x00; mask >>= 1, i++) {
		buf = 0x00;							  // ��ǰ���������ó�ʼֵ
											  // �������BITΪABCDEFGZλ
		buf |= NUMCODETAB[num_ram[i]] & 0xfe; // ��1��8�ֵ�ABCDEFG�ʶ�����
		if ((num_point & mask) != 0)		  // ��1����־[H1]����
			buf |= 0x01;
		for (j = 0; j < 8; j++) {             // �ӵ͵���λ���ֽ�λ���ݵ�Һ����ʾ������
			DI = (buf>>j) & 0x1;              // �������ݵ����ݿ���DI
			SMS_DELAY ();
			CLK = 1;                          // ��ʹʱ�ӿ��߷�һ��������
			SMS_DELAY ();
			CLK = 0;
			SMS_DELAY ();
			CLK = 1;
		}
	}
}

#endif