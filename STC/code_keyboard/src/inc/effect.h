#ifndef __TBZ_EFFECT_H_
#define __TBZ_EFFECT_H_
#include "binary.h"
#ifdef __TBZ_INLINE_
// λ����
#define bits2left(bits)  bits=((bits>>1)&B01111111)|((bits<<7)&B10000000)
// λ����
#define bits2right(bits) bits=((bits<<1)&B11111110)|((bits>>7)&B00000001)
/*
#define words2left(words) {                               \
	char __EFFECT_TMP_ = words [0];                        \
	unsigned int __EFFECT_I_ = 1;                          \
	for ( ; __EFFECT_I_ < sizeof (words); ++__EFFECT_I_)   \
		words [__EFFECT_I_-1] = words[__EFFECT_I_];          \
	words [sizeof (words) - 1] = __EFFECT_TMP_;            \
}
*/
#else

/**
 * @brief �ռ�������ʼ��
 * @param __pointer �ռ��е�ָ��
 * @param  __length �ռ�ĳ���
 * @param     value ͳһ�ĳ�ʼ��ֵ
 * @return void
 */
void memset (unsigned char* __pointer, unsigned int __length, unsigned char value);
/**
 * @brief �ռ����ݸ���
 * @param __dst_pointer Ŀ��ռ�Ļ���ַ
 * @param __src_pointer Դ�ռ�Ļ���ַ
 * @param      __length �ռ�Ĵ�С
 * @return void
 */
void copy (unsigned char* __dst_pointer, unsigned char* __src_pointer, unsigned int __length);

/**
 * @brief �ַ�������
 * @param __words ��ͼ�������ַ����Ļ�����
 * @param __words ��ͼ�������ַ����ĳ���
 * @return void
 */
void words2leftEx (char* __words, unsigned int __length);
/**
 * @brief �ַ�������
 * @param __words ��ͼ�������ַ����Ļ�����
 * @param __words ��ͼ�������ַ����ĳ���
 * @return void
 */
void words2rightEx (char* __words, unsigned int __length);
/**
 * @brief �ַ�����ת
 * @param __words ��ͼ��ת���ַ����Ļ�����
 * @param __words ��ͼ��ת���ַ����ĳ���
 * @return void
 */
void wordsReverseEx (char* __words, unsigned int __length);
/**
 * @brief �ֽ�����
 * @param bits ��ͼ�������ֽڵ�ָ��
 * @return void
 */
void bits2left (unsigned char* bits);
/**
 * @brief �ֽ�����
 * @param bits ��ͼ�������ֽڵ�ָ��
 * @return void
 */
void bits2right (unsigned char* bits);


// �ַ�������
#define words2left(words)   words2leftEx  (words, sizeof(words)-1)
// ��������
#define array2left(words)   words2leftEx  (words, sizeof(words))
// �ַ�������
#define words2right(words)  words2rightEx (words, sizeof(words)-1)
// ��������
#define array2right(words)  words2rightEx (words, sizeof(words))
// �ַ�����ת
#define wordsReverse(words) wordsReverseEx(words, sizeof(words)-2)
// ���鷭ת
#define arrayReverse(words) wordsReverseEx(words, sizeof(words)-1)
#endif
#endif