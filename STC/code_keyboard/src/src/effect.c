#include "../inc/effect.h"

/**
 * @brief 空间批量初始化
 * @param __pointer 空间中的指针
 * @param  __length 空间的长度
 * @param     value 统一的初始化值
 * @return void
 */
void memset (unsigned char* __pointer, unsigned int __length, unsigned char value) {
	unsigned int i;
	for (i = 0; i < __length; ++i) {
		*(__pointer + i) = value;
	}
}
/**
 * @brief 空间内容复制
 * @param __dst_pointer 目标空间的基地址
 * @param __src_pointer 源空间的基地址
 * @param      __length 空间的大小
 * @return void
 */
void copy (unsigned char* __dst_pointer, unsigned char* __src_pointer, unsigned int __length) {
	unsigned int i;
	for (i = 0; i < __length; ++i) {
		*(__dst_pointer + i) = *(__src_pointer + i);
	}
}

/**
 * @brief 字符串左旋
 * @param __words 意图左旋的字符串的基坐标
 * @param __words 意图左旋的字符串的长度
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
 * @brief 字符串左旋
 * @param __words 意图右旋的字符串的基坐标
 * @param __words 意图右旋的字符串的长度
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
 * @brief 字符串翻转
 * @param __words 意图翻转的字符串的基坐标
 * @param __words 意图翻转的字符串的长度
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
 * @brief 字节左旋
 * @param bits 意图左旋的字节的指针
 * @return void
 */
void bits2left (unsigned char* bits) {
	*bits = ((*bits>>1)&B01111111)|((*bits<<7)&B10000000);
}
/**
 * @brief 字节右旋
 * @param bits 意图右旋的字节的指针
 * @return void
 */
void bits2right (unsigned char* bits) {
	*bits = ((*bits<<1)&B11111110)|((*bits>>7)&B00000001);
}