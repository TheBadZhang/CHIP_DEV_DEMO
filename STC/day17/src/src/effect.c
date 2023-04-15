#include "../inc/effect.h"

/**
 * @brief �ռ�������ʼ��
 * @param __pointer �ռ��е�ָ��
 * @param  __length �ռ�ĳ���
 * @param     value ͳһ�ĳ�ʼ��ֵ
 * @return void
 */
void memset (unsigned char* __pointer, unsigned int __length, unsigned char value) {
	unsigned int i;
	for (i = 0; i < __length; ++i) {
		*(__pointer + i) = value;
	}
}
/**
 * @brief �ռ����ݸ���
 * @param __dst_pointer Ŀ��ռ�Ļ���ַ
 * @param __src_pointer Դ�ռ�Ļ���ַ
 * @param      __length �ռ�Ĵ�С
 * @return void
 */
void copy (unsigned char* __dst_pointer, unsigned char* __src_pointer, unsigned int __length) {
	unsigned int i;
	for (i = 0; i < __length; ++i) {
		*(__dst_pointer + i) = *(__src_pointer + i);
	}
}

/**
 * @brief �ַ�������
 * @param __words ��ͼ�������ַ����Ļ�����
 * @param __words ��ͼ�������ַ����ĳ���
 * @return void
 */
void words2leftEx (char* __words, unsigned int __length) {
	unsigned int i;
	char tmp = __words[0];
	for (i = 1; i < __length; ++ i) {
		__words [i-1] = __words[i];
	}
	__words [__length-1] = tmp;
}
/**
 * @brief �ַ�������
 * @param __words ��ͼ�������ַ����Ļ�����
 * @param __words ��ͼ�������ַ����ĳ���
 * @return void
 */
void words2rightEx (char* __words, unsigned int __length) {
	unsigned int i;
	char tmp = __words[__length-1];
	for (i = __length-1; i > 0; -- i) {
		__words [i] = __words[i-1];
	}
	__words [0] = tmp;
}
/**
 * @brief �ַ�����ת
 * @param __words ��ͼ��ת���ַ����Ļ�����
 * @param __words ��ͼ��ת���ַ����ĳ���
 * @return void
 */
void wordsReverseEx (char* __words, unsigned int __length) {
	char tmp;
	for (int i = 0; i <= __length/2; ++i) {
		tmp = __words[i];
		__words [i] = __words [__length-i];
		__words [__length-i] = tmp;
	}
}
/**
 * @brief �ֽ�����
 * @param bits ��ͼ�������ֽڵ�ָ��
 * @return void
 */
void bits2left (unsigned char* bits) {
	*bits = ((*bits>>1)&B01111111)|((*bits<<7)&B10000000);
}
/**
 * @brief �ֽ�����
 * @param bits ��ͼ�������ֽڵ�ָ��
 * @return void
 */
void bits2right (unsigned char* bits) {
	*bits = ((*bits<<1)&B11111110)|((*bits>>7)&B00000001);
}