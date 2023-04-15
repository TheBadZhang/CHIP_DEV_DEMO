#ifndef __TBZ_EEPROM_H_
#define __TBZ_EEPROM_H_E


#define EEPROM_ADDR B10100000            // ���ݾ���ĵ�ַ��������

/*

! EEPROM д������ڶ�ʱ����������Ӱ��������������
* �Ѷ�д��д��ǰ�棬�Ϳ��Թ�ܾ��󲿷ֵ����⣬����Ϊ����İ����˳���
* �����˳������н��һֱ��׼ȷ������Ҫ�� EEPROM �����ҳ������е�״̬
*/

/**
 * @brief �� eeprom addr λ�ö�ȡһ���ֽڵ�����
 * @param addr �� eeprom �ж�ȡ���ݵĵ�ַ
 * @return ���ض�ȡ�����ֽ�����
 * @retval
 */
unsigned char eeReadByte (unsigned char addr);
/**
 * @brief �� eeprom addr λ��д��һ���ֽ�����
 * @param addr ��д�� eeprom �ĵ�ַ
 * @param dat ��д�� eeprom ������
 * @return void
 */
void eeWriteByte (unsigned char addr, unsigned char dat);


#endif