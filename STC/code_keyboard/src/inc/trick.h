#ifndef __TBZ_TRICK_H_
#define __TBZ_TRICK_H_
// �����﷨

/**
 * @brief ��д�� for ѭ��
 * @param i Ҫ��ѭ���ı���
 * @param x ѭ������ [0,x)
 */
#define FOR(i,x) for (i = 0; i < x; ++i)
#define DO  {
#define END }

#define HIGH 1
#define LOW  0

/**
 * @brief ����һ������Ϊ�ߵ�λ
 * @param v Ҫ���õ�����
 */
#define set(v) v = HIGH
/**
 * @brief ����һ������Ϊ�͵�λ
 * @param v Ҫ���õ�����
 */
#define clr(v) v = LOW


// ��Ϊ c ���Բ�֧��������������
// Ϊ�˷�����д�����ú�ķ�ʽ�����������
#define __TBZ_BINARY_ENABLE_
#ifdef __TBZ_BINARY_ENABLE_
	#include "binary.h"
#endif

#define INT0 0
#define TMR0 1
#define INT1 2
#define TMR1 3
#define TMR2 5

#include "mytype.h"

/**
 * @brief �߼���
 */
#define AND(a,b) ((a)&&(b))
/**
 * @brief �߼���
 */
#define OR(a,b) ((a)||(b))
/**
 * @brief �߼���
 */
#define NOT(x) (!(x))



/**
 * @brief ʲôҲ������һ�����
 */
#define _nop_() __asm nop __endasm
/**
 * @brief ��һ��int�����ݸ�ֵ���ߵ������ֽ�
 * @param high ���ֽ�
 * @param low ���ֽ�
 * @param value 16-bit ������
 */
#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);
/**
 * @brief ���ߵ������ֽڵ����ݺϳ�Ϊ�����ֽڵ�int
 * @param high ���ֽ�
 * @param low ���ֽ�
 */
#define BIND2BYTE(high, low)\
	(high << 8) | low

#endif