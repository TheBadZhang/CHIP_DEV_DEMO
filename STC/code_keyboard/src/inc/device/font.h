#ifndef __TBZ_FONT_0x_
#define __TBZ_FONT_0x_

//����ASCII��
//ƫ����32
//ASCII�ַ���
//ƫ����32
//��С:12*6
/************************************6*8�ĵ���************************************/
extern const unsigned char __code font0608[][6];
/****************************************8*16�ĵ���************************************/
extern const unsigned char __code font0816[];
/*--------------------------------------------------------------*/
//    ����:   Fixedsys
//ȡ�����: ��λ��ǰ, ����ɨ��, ����(1-��, 0-��)
//�����: Ҫ��ʾ��ASCII��-32�Ϳ��Եõ��ֿ����ָ��
extern unsigned char __code font_Fixedsys[][16];

//����ȡģ
extern unsigned char __code font_chinese[][32];
typedef struct typFNT_GBK16 {
       unsigned char index[2];
       char mask[32];
} typFNT_GBK16_t;
//����5��
//������ʾ����ȫ�����ӻ�ӭ����Ϊרҵ����ע��
extern typFNT_GBK16_t __code hz16[];
#endif
