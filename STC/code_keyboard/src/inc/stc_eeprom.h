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
	isp_addrh = (STC_EEPROM_ADDR+read_addr)>>8;  //送地址高字节
	isp_addrl = (STC_EEPROM_ADDR+read_addr)&0xff;  //送地址低字节(从0开始到num-1为止）
	EA =  0;                     /* 关中断 */
	isp_contr = 0x81;      
	isp_cmd = 2;                //送扇区命令
	isp_trig = 0x46;
	isp_trig = 0xb9;
	_nop_();
	_nop_();
	isp_contr = 0;              
	isp_cmd = 0;
	isp_trig = 0;
	isp_addrh = 0;
	isp_addrl = 0;        
	EA = 1;                    /* 开中断 */
}
unsigned char STC89CXX_EEPROM_Char_Read(unsigned short read_addr) {
	unsigned char Read_isp_data;

	isp_addrh = (STC_EEPROM_ADDR+read_addr)>>8;  //送地址高字节
	isp_addrl = (STC_EEPROM_ADDR+read_addr)&0xff;  //送地址低字节(从0开始到num-1为止）
	EA = 0;                /* 关中断 */
	isp_contr = 0x81;      /*20M，是0x80 orl 1 */
	isp_cmd = 1;           // 1表示字节读
	isp_trig = 0x46;       //先送0x46再送 0xb9 ISP/IAP 触发寄存器，每次都需要如此
	isp_trig = 0xb9;       //送完0xb9后 ISP/IAP 立即被触发启动
	_nop_();               //空指令
	_nop_();               //空指令
	isp_contr = 0;         //禁止ISP/IAP 操作
	isp_cmd = 0;           //去除ISP/IAP 命令
	isp_trig = 0;          //防止 ISP/IAP 命令误触发
	isp_addrh = 0;         //地址指向非EEPROM地址区，防止误操作
	isp_addrl = 0;        
	EA = 1;                            /* 开中断 */
	Read_isp_data=isp_data;
	return(Read_isp_data);

} 
#define readBYTE(addr) STC89CXX_EEPROM_Char_Read(addr)
#define writeBYTE(addr,data) STC89CXX_EEPROM_Char_Write(addr,data)



#endif