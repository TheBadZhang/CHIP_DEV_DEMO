#ifndef __TBZ_TTP229_H_
#define __TBZ_TTP229_H_

#include "myheader.h"
#include "keyboard_vk.h"
#include "ttp229_vk.h"

#define SDA P1_0
#define SCL P1_1

/**
 * @brief ��ȡ���ؼ��̵�����
 * @return ���ػ�ȡ���İ�������
 * @retval ʮ��λ���Σ�һ��λ��Ӧһ������
 */
uint TTP229B_get (void);

#endif