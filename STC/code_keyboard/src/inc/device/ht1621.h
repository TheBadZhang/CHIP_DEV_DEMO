#ifndef __TBZ_HT1621_H_
#define __TBZ_HT1621_H_

#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"

#define sbi(x,y)  (x |= (1 << y))   /*��λ����x�ĵ�yλ*/
#define cbi(x,y)  (x &= ~(1 <<y ))  /*�������x�ĵ�yλ*/

// �ߵ�λ�������͵�λϨ��

//����HT1621������
#define  ComMode    0x52  // 4COM,1/3bias  1000    010 1001  0
#define  RCosc      0x30  // �ڲ� RC ����(�ϵ�Ĭ��)1000 0011 0000
#define  LCD_on     0x06  // �� LCD ƫѹ������1000     0000 0 11 0
#define  LCD_off    0x04  // �ر� LCD��ʾ
#define  Sys_en     0x02  // ϵͳ������ 1000   0000 0010
#define  CTRl_cmd   0x80  // д��������
#define  Data_cmd   0xa0  // д��������

//����˿�HT1621���ݶ˿�
#define DATA P0_7
#define WR   P0_6   // �����ش���
#define CS   P0_5   // �͵�ƽѡ��

#define write_data_begin WR=0
#define write_data_end   WR=1
#define choose_ht1621    CS=0
#define unchose_ht1621   CS=1

const char ht1621_num [] = {
	0x7D, 0x60, 0x3E, 0x7A, // 0, 1, 2, 3
	0x63, 0x5B, 0x5F, 0x70, // 4, 5, 6, 7
	0x7F, 0x7B, 0x77, 0x4F, // 8, 9, A, b
	0x1D, 0x0E, 0x6E, 0x1F, // C, c, d, E
	0x17, 0x67, 0x47, 0x0D, // F, H, h, L
	0x46, 0x75, 0x37, 0x06, // n, N, o, P
	0x0F, 0x6D, 0x02, 0x00  // r, t, U, -,
};
char ht1621_numbuf [6] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06
};


// sbi(ht1621_numbuf[5],7);   //��ʾ���ͼ�궥��
// cbi(dispnum[5],7); //������ͼ�궥��
// sbi(ht1621_numbuf[4],7);   //��ʾ���ͼ���в�
// cbi(dispnum[4],7); //������ͼ���в�
// sbi(ht1621_numbuf[3],7);   //��ʾ���ͼ��ײ�
// cbi(dispnum[3],7); //������ͼ��ײ�


//��ʱԼ1ms
void ht1621_delay(uint a) {
	uint i;
	while (--a!=0) for(i=600;i>0;i--);   //1T��Ƭ��i=600������12T��Ƭ��i=125
}

/**
 * @brief ��ht1621��������
 * @param sdata ���ݵĸ�λ��д��HT1621����λ��ǰ
 * @param cnt ����д���λ����
 */
void ht1621_writeBits (uchar sdata,uchar cnt) {
	uchar i;
	FOR (i, cnt) {
		write_data_begin;
		DATA = sdata&0x80;
		write_data_end;
		sdata<<=1;
	}
}
//������
void ht1621_sendCMD (uchar command) {
	choose_ht1621;
	ht1621_writeBits (0x80, 4);    //д���־�롰100����9 λcommand �������
	ht1621_writeBits (command, 8); //û��ʹ�е�����ʱ����������Ϊ�˱�̷���
	unchose_ht1621;               //ֱ�ӽ�command �����λд��0��
}
//�����ݺ��������
void ht1621_write (uchar addr,uchar sdata) {
	addr <<= 2;
	choose_ht1621;
	ht1621_writeBits (0xa0, 3);     // д���־�롰101��
	ht1621_writeBits (addr, 6);     // д��addr �ĸ�6λ
	ht1621_writeBits (sdata, 8);    // д��data ��8λ
	unchose_ht1621;
}
/**
 * @brief ht1621 memeset
 */
void ht1621_all (uchar disp) {
	uchar i;
	FOR (i, 16) ht1621_write (2*i, disp);
}

//��ʼ��1621
void ht1621_init (void) {
	ht1621_sendCMD (Sys_en);
	ht1621_sendCMD (RCosc);
	ht1621_sendCMD (ComMode);
	ht1621_sendCMD (LCD_on);
}
 //��ʾ��������pΪС����λ��
void ht1621_setpoint (int p) {
	sbi(ht1621_numbuf[p],7);
}

void ht1621_show (void) {
	uchar i;
	FOR (i, 6) {
		ht1621_write (i*2, ht1621_num[ht1621_numbuf[i]]);
	}
}

/**
 * @brief �������и������
 * @param num ����
 */
void ht1621_t2n (signed long num) { // long ��ΧΪ -2147483648-2147483647
	uchar i;
	memset (ht1621_numbuf, sizeof (ht1621_numbuf), 27);    // ��յ�ǰ����
	if (num) FOR (i,6) {        // �����ݴ浽
		ht1621_numbuf [i] = num % 10;
		num /= 10;
	} else ht1621_numbuf [0] = 0;
}
#undef write_data_begin
#undef write_data_end
#undef choose_ht1621
#undef unchose_ht1621
//����HT1621������
#undef ComMode
#undef RCosc
#undef LCD_on
#undef LCD_off
#undef Sys_en
#undef CTRl_cmd
#undef Data_cmd

#undef DATA
#undef WR
#undef CS

#endif

// https://blog.csdn.net/qq_43188920/article/details/82773994

/** ��������
#define __TBZ_KEYBOARD_ENABLE_
#define __STC15W4K32S
#define __TBZ_EFFECT_ENABLE_
#include "myheader.h"
#include "ht1621.h"

void main() {
	P0M1 = 0x00;
	P0M0 = 0x00;

	ht1621_delay(1);
	ht1621_init ();
	ht1621_all (0xff); //ȫ������1621
	ht1621_delay (1000);
	ht1621_all (0x00); //ȫ��Ϩ��1621
	ht1621_show ();
	int num = 0;
	while(1) {
		ht1621_t2n (num++);
		ht1621_delay (100);
		ht1621_show ();
	}
}

*/

