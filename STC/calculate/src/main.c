#define __STC15W4K32S
#define __TBZ_RANDOM_ENABLE_
#include "../inc/myheader.h"
// #include <8052.h>
#include "../inc/keyboard_vk.h"
#include "../inc/nokia5110.h"
#include "../inc/ttp229.h"
#include <stdio.h>


long ans = 0, last_ans = 0, real_ans = 0;
char opr, last_opr = 0;
char calced = 0;

void keyboard (void) __interrupt(TMR1);
void show (void) __interrupt(TMR0);


void main(){
	P0M1 = 0x00;
	P0M0 = 0x00;
	P1M1 = 0x00;
	P1M0 = 0x00;
	/** ��ʱ������ **/
	TMOD = 0x00;        // 0��1 ��ʱ�������� 16 λ��ʱ
	TR0 = 0;            // ��ͣ��ʱ������Ϊ��ʱ��ʱ��Ϊ0ģʽ����ʱ����ͣʱ����ֵͬʱ�ᱻд�� RL_TL0 �� RL_TH0
	TR1 = 0;
	EA = 1;            // ���ж�ʹ��
	ET0 = 1;           // ��ʱ��0 �ж�ʹ��
	ET1 = 1;           // ��ʱ��2 �ж�ʹ��
	ASSIGNMENT16 (TH1, TL1, 0x7000);
	ASSIGNMENT16 (TH0, TL0, 0x0000);
    nokia5110_LCDInit();
    nokia5110_writeString(0,0, (uchar*)" Calculate");
    nokia5110_writeString(0,1, (uchar*)" VER. 2108");
    nokia5110_writeString(0,2, (uchar*)" Updating.");
    // nokia5110_writeString(0,0,"xxxxxxxxxx");
	TR0 = 1;
	TR1 = 1;
	nokia5110_clear ();
    while(1) {
	}

}


void show (void) __interrupt(TMR0) {
	char buf [12];
	sprintf (buf, "%10ld", last_ans);
	nokia5110_writeString (0, 0, (uchar*)buf);
	if (last_opr)
		nokia5110_writeChar (0, 1, last_opr);
	else
		nokia5110_writeString(0, 1, (uchar*)" ");
	sprintf (buf, "%9ld", ans);
	nokia5110_writeString (1, 1, (uchar*)buf);
	if (calced) {
		sprintf (buf, "=9%ld", real_ans);
		nokia5110_writeString (2, 0, (uchar*)buf);
	} else {
		nokia5110_writeString(2, 0, (uchar*)"          ");
	}
}


void keyboard (void) __interrupt(TMR1) {
	uint r = TTP229B_get ();
	signed char input_num = -1;
	char is_opr = 0;

	switch (r) {
		case VK_0: input_num = 0; break;     // ��ȡ��ǰ��������֣�Ȼ�����뵽ans��
		case VK_1: input_num = 1; break;     // ans Ҳ��Ϊ��ʾ����������
		case VK_2: input_num = 2; break;
		case VK_3: input_num = 3; break;
		case VK_4: input_num = 4; break;
		case VK_5: input_num = 5; break;
		case VK_6: input_num = 6; break;
		case VK_7: input_num = 7; break;
		case VK_8: input_num = 8; break;
		case VK_9: input_num = 9; break;

		case VK_A: opr = '+'; is_opr = 1; break;     // +
		case VK_B: opr = '-'; is_opr = 1; break;     // -
		case VK_C: opr = '*'; is_opr = 1; break;     // *
		case VK_D: opr = '/'; is_opr = 1; break;     // /
		case VK_SHARP: opr = '='; is_opr = 1; break;
		case 0x0000: /* not press */ break;
		// default: nokia5110_writeString(0,1,(uchar*)"ErrorInput"); break;
	}

	if (input_num >= 0) {
		// nokia5110_writeString(0, 1, (uchar*)"number!");
		ans = 10*ans + input_num;
		if (opr) last_opr = opr;
	}
	if (is_opr) {    // �������������
		if (ans == 0) {

		} else {
			if (last_opr != 0) {
				switch (last_opr) {
					case '+': last_ans += ans; break; // ���֮ǰ�Ѿ��������������������������㲻�ǵ��ںŵĻ���
					case '-': last_ans -= ans; break; // �ͻ�ֱ��ִ��һ�����㣬���ϴ�����Ľ�� last_ans opr �����������
					case '*': last_ans *= ans; break; // ��������������ǵ��ںŵĻ�����ֱ�Ӽ����������ѽ������ last_ans ��������ʾ
					case '/': last_ans /= ans; break;
					case '=': last_ans = ans; break;
				}
				if (opr == '=') {
					opr = 0;
					last_opr = 0;
				}
				ans = 0;
			} else {
				last_ans = ans;
				last_opr = opr;
				opr = 0;
				ans = 0;
			}
		}
	}

}
