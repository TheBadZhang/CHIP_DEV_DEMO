#ifndef __TBZ_EFFECT_H_
#define __TBZ_EFFECT_H_
#include "binary.h"
#ifdef __TBZ_INLINE_
// Î»×óÐý
#define bits2left(bits)  bits=((bits>>1)&B01111111)|((bits<<7)&B10000000)
// Î»ÓÒÐý
#define bits2right(bits) bits=((bits<<1)&B11111110)|((bits>>7)&B00000001)
/*
#define words2left(words){                               \
	char __EFFECT_TMP_ = words [0];                        \
	unsigned int __EFFECT_I_ = 1;                          \
	for ( ; __EFFECT_I_ < sizeof (words); ++__EFFECT_I_)   \
		words [__EFFECT_I_-1] = words[__EFFECT_I_];          \
	words [sizeof (words) - 1] = __EFFECT_TMP_;            \
}           
*/
#else
// ×Ö·û´®×óÐý
void words2leftEx (char *__words, unsigned int __length) {
	char tmp = __words[0];
	unsigned int i;
	for (i = 1; i < __length; ++ i) {
		__words [i-1] = __words[i];
	}
	__words [__length-1] = tmp;
}
// ×Ö·û´®ÓÒÐý
void words2rightEx (char *__words, unsigned int __length) {
	char tmp = __words[__length-1];
	unsigned int i;
	for (i = __length-1; i > 0; -- i) {
		__words [i] = __words[i-1];
	}
	__words [0] = tmp;
}
// Î»×óÐý
void bits2left (char *bits) {
	*bits = ((*bits>>1)&B01111111)|((*bits<<7)&B10000000);
}
// Î»ÓÒÐý
void bits2right (char *bits) {
	*bits = ((*bits<<1)&B11111110)|((*bits>>7)&B00000001);
}


// Ò»¸ö¼òµ¥µÄÑÓ³Ùº¯Êý
void delay(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}
#define words2left(words)  words2leftEx (words, sizeof(words)-1)
#define array2left(words)  words2leftEx (words, sizeof(words))
#define words2right(words) words2rightEx(words, sizeof(words)-1)
#define array2right(words) words2rightEx (words, sizeof(words))

#endif
#endif