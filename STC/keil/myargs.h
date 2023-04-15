#ifndef __TBZ_ARGS_H_
#define __TBZ_ARGS_H_

typedef char* va_list;

// 把 n 圆整到 sizeof (int) 的倍数
#define _INTSIZEOF(n)       ( (sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1) )

// 初始化 ap 指针，使其指向第一个可变参数。v 是变参列表的钱一个参数
#define va_start(ap, v)      ( ap = (va_list)&v + _INTSIZEOF(v) )

// 该宏返回当前变参值，使 ap 指向列表中的下个变参
#define va_arg(ap, type)    ( *(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)) )

// 将指针 ap 置为无效，结束变参的获取
#define va_end(ap)             ( ap = (va_list)0 )

#endif