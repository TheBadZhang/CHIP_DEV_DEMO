#ifndef __TBZ_MATH_H_
#define __TBZ_MATH_H_

#include "myheader.h"
//m^nº¯Êý
u32 pow (u8 m,u8 n) {
	u32 result = 1;	 
	while (n--)
        result *= m;    
	return result;
}


#endif