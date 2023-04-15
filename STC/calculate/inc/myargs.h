#ifndef __TBZ_ARGS_H_
#define __TBZ_ARGS_H_

typedef char* va_list;

// �� n Բ���� sizeof (int) �ı���
#define _INTSIZEOF(n)       ( (sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1) )

// ��ʼ�� ap ָ�룬ʹ��ָ���һ���ɱ������v �Ǳ���б��Ǯһ������
#define va_start(ap, v)      ( ap = (va_list)&v + _INTSIZEOF(v) )

// �ú귵�ص�ǰ���ֵ��ʹ ap ָ���б��е��¸����
#define va_arg(ap, type)    ( *(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)) )

// ��ָ�� ap ��Ϊ��Ч��������εĻ�ȡ
#define va_end(ap)             ( ap = (va_list)0 )

#endif