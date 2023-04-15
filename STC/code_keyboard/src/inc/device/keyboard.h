#ifndef __TBZ_KEYBOARD_H_
#define __TBZ_KEYBOARD_H_
#include "keyboard_vk.h"

// ��������һֱ�е������ǣ�����д�ö��Ǹ���ʹ�� switch
// �����ַ�ʽӪ����һ�� α ���� �ĳ���,ÿһ�ΰ�����ȡ������Ҫ�ܾ�
// �����������Ҫ�Ĵν����жϺ����ſ�����ȷ�ض���һ������
// �ô��ǶԳ����Ĳ���Ӱ���С
#ifdef __SDCC
/**
 * @brief ��ȡ��ǰ���������ϵ���ɨ��
 * @return ���ص�ǰ�İ���ֵ
 */
unsigned char keystate (void) {
	P2 = 0xff;
	P2_3 = 0; 
	if (!P2_4) return VK_1;   // ����ط����ƣ���д�� VK0������� bug ���˰��졭��
	if (!P2_5) return VK_2;
	if (!P2_6) return VK_3;
	if (!P2_7) return VK_UP;
	P2_3 = 1;
	P2_2 = 0;
	if (!P2_4) return VK_4   ;
	if (!P2_5) return VK_5   ;
	if (!P2_6) return VK_6   ;
	if (!P2_7) return VK_LEFT;
	P2_2 = 1;
	P2_1 = 0;
	if (!P2_4) return VK_7   ;
	if (!P2_5) return VK_8   ;
	if (!P2_6) return VK_9   ;
	if (!P2_7) return VK_DOWN;
	P2_1 = 1;
	P2_0 = 0;
	if (!P2_4) return VK_0    ;
	if (!P2_5) return VK_ESC  ;
	if (!P2_6) return VK_ENTER;
	if (!P2_7) return VK_RIGHT;
	P2_0 = 1;
	return 0xff;
}
#else
/**
 * @brief ��ȡ��ǰ���������ϵ���ɨ��
 * @return ���ص�ǰ�İ���ֵ
 */
unsigned char keystate (void) {
	P2 = 0xff;
	P2^3 = 0; 
	if (!P2^4) return VK_1;   // ����ط����ƣ���д�� VK0������� bug ���˰��졭��
	if (!P2^5) return VK_2;
	if (!P2^6) return VK_3;
	if (!P2^7) return VK_UP;
	P2^3 = 1;
	P2^2 = 0;
	if (!P2^4) return VK_4   ;
	if (!P2^5) return VK_5   ;
	if (!P2^6) return VK_6   ;
	if (!P2^7) return VK_LEFT;
	P2^2 = 1;
	P2^1 = 0;
	if (!P2^4) return VK_7   ;
	if (!P2^5) return VK_8   ;
	if (!P2^6) return VK_9   ;
	if (!P2^7) return VK_DOWN;
	P2^1 = 1;
	P2^0 = 0;
	if (!P2^4) return VK_0    ;
	if (!P2^5) return VK_ESC  ;
	if (!P2^6) return VK_ENTER;
	if (!P2^7) return VK_RIGHT;
	P2^0 = 1;
	return 0xff;
}
#endif


#endif