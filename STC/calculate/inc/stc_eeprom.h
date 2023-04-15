#ifndef __TBZ_STC_EEPROM_H_
#define __TBZ_STC_EEPROM_H_


#define STC_EEPROM_ADDR 0x2000
#define STC_EEPROM_END_ADDR 0x33FF

__sfr __at(0xE1) isp_wdt     ;
__sfr __at(0xE2) isp_data    ;
__sfr __at(0xE3) isp_addrh   ;
__sfr __at(0xE4) isp_addrl   ;
__sfr __at(0xE5) isp_cmd     ;
__sfr __at(0xE6) isp_trig    ;
__sfr __at(0xE7) isp_contr   ;

void STC89CXX_EEPROM_Char_Write(unsigned short read_addr, unsigned char write_data) {
	isp_data  = write_data;
	isp_addrh = (STC_EEPROM_ADDR+read_addr)>>8;  //�͵�ַ���ֽ�
	isp_addrl = (STC_EEPROM_ADDR+read_addr)&0xff;  //�͵�ַ���ֽ�(��0��ʼ��num-1Ϊֹ��
	EA =  0;                     /* ���ж� */
	isp_contr = 0x81;      
	isp_cmd = 2;                //����������
	isp_trig = 0x46;
	isp_trig = 0xb9;
	_nop_();
	_nop_();
	isp_contr = 0;              
	isp_cmd = 0;
	isp_trig = 0;
	isp_addrh = 0;
	isp_addrl = 0;        
	EA = 1;                    /* ���ж� */
}
unsigned char STC89CXX_EEPROM_Char_Read(unsigned short read_addr) {
	unsigned char Read_isp_data;

	isp_addrh = (STC_EEPROM_ADDR+read_addr)>>8;  //�͵�ַ���ֽ�
	isp_addrl = (STC_EEPROM_ADDR+read_addr)&0xff;  //�͵�ַ���ֽ�(��0��ʼ��num-1Ϊֹ��
	EA = 0;                /* ���ж� */
	isp_contr = 0x81;      /*20M����0x80 orl 1 */
	isp_cmd = 1;           // 1��ʾ�ֽڶ�
	isp_trig = 0x46;       //����0x46���� 0xb9 ISP/IAP �����Ĵ�����ÿ�ζ���Ҫ���
	isp_trig = 0xb9;       //����0xb9�� ISP/IAP ��������������
	_nop_();               //��ָ��
	_nop_();               //��ָ��
	isp_contr = 0;         //��ֹISP/IAP ����
	isp_cmd = 0;           //ȥ��ISP/IAP ����
	isp_trig = 0;          //��ֹ ISP/IAP �����󴥷�
	isp_addrh = 0;         //��ַָ���EEPROM��ַ������ֹ�����
	isp_addrl = 0;        
	EA = 1;                            /* ���ж� */
	Read_isp_data=isp_data;
	return(Read_isp_data);

} 
#define readBYTE(addr) STC89CXX_EEPROM_Char_Read(addr)
#define writeBYTE(addr,data) STC89CXX_EEPROM_Char_Write(addr,data)



#endif