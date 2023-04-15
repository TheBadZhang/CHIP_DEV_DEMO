#ifndef __TBZ_EFFECT_H_
#define __TBZ_EFFECT_H_
#include "binary.h"
#ifdef __TBZ_INLINE_
// 位左旋
#define bits2left(bits)  bits=((bits>>1)&B01111111)|((bits<<7)&B10000000)
// 位右旋
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
 * @brief 空间批量初始化
 * @param __pointer 空间中的指针
 * @param  __length 空间的长度
 * @param     value 统一的初始化值
 * @return void
 */
void memset (unsigned char* __pointer, unsigned int __length, unsigned char value);
/**
 * @brief 空间内容复制
 * @param __dst_pointer 目标空间的基地址
 * @param __src_pointer 源空间的基地址
 * @param      __length 空间的大小
 * @return void
 */
void copy (unsigned char* __dst_pointer, unsigned char* __src_pointer, unsigned int __length);

/**
 * @brief 字符串左旋
 * @param __words 意图左旋的字符串的基坐标
 * @param __words 意图左旋的字符串的长度
 * @return void
 */
void words2leftEx (char* __words, unsigned int __length);
/**
 * @brief 字符串左旋
 * @param __words 意图右旋的字符串的基坐标
 * @param __words 意图右旋的字符串的长度
 * @return void
 */
void words2rightEx (char* __words, unsigned int __length);
/**
 * @brief 字符串翻转
 * @param __words 意图翻转的字符串的基坐标
 * @param __words 意图翻转的字符串的长度
 * @return void
 */
void wordsReverseEx (char* __words, unsigned int __length);
/**
 * @brief 字节左旋
 * @param bits 意图左旋的字节的指针
 * @return void
 */
void bits2left (unsigned char* bits);
/**
 * @brief 字节右旋
 * @param bits 意图右旋的字节的指针
 * @return void
 */
void bits2right (unsigned char* bits);


// 字符串左移
#define words2left(words)   words2leftEx  (words, sizeof(words)-1)
// 数组左移
#define array2left(words)   words2leftEx  (words, sizeof(words))
// 字符串右移
#define words2right(words)  words2rightEx (words, sizeof(words)-1)
// 数组右移
#define array2right(words)  words2rightEx (words, sizeof(words))
// 字符串翻转
#define wordsReverse(words) wordsReverseEx(words, sizeof(words)-2)
// 数组翻转
#define arrayReverse(words) wordsReverseEx(words, sizeof(words)-1)
#endif
#endif