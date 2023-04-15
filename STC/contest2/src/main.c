
// ���� 51 ��Ƭ���ж���ŵĶ���
#ifdef __SDCC
	#include <8052.h>
	#define        sbit __sbit
	#define         bit __bit
	#define   interrupt __interrupt
	// #define  sfr
#else
	#include <reg52.h>
	#define      __sbit sbit
	#define       __bit bit
	#define __interrupt interrupt
#endif

// �����﷨

#define _nop_() __asm nop __endasm
#define FOR(i,x) for (i = 0; i < x; ++i)
#define DO  {
#define END }

#define HIGH 1
#define LOW  0
#define set(v) v = HIGH
#define clr(v) v = LOW

#define true 1
#define True 1
#define TRUE 1
#define false 0
#define False 0
#define FALSE 0
#define bool __bit


#define u32 unsigned long
#define u16 unsigned short
#define u8  unsigned char
#define uc  unsigned char


/**
 * @brief һ���򵥵��ӳٺ���
 * @param x10us ��ʱ��ʱ��
 * 	��ʱʱ���൱�� ����*10 ��΢��
 * @return void
 */
void delay(unsigned int x10us){
	unsigned int x, y;
	for(x = x10us; x > 0; --x)
		for(y = 11; y > 0; --y);
}

#define STC_EEPROM_ADDR 0x2000
#define STC_EEPROM_END_ADDR 0x33FF
__sfr __at(0xE1) isp_wdt     ;
__sfr __at(0xE2) isp_data    ;
__sfr __at(0xE3) isp_addrh   ;
__sfr __at(0xE4) isp_addrl   ;
__sfr __at(0xE5) isp_cmd     ;
__sfr __at(0xE6) isp_trig    ;
__sfr __at(0xE7) isp_contr   ;
//"��",0
//"Ц",1
//"��",2
//"��",3
//"��",4
//"��",5
//"��",6
//"�x",7
//"С",8
//"��",9
//"ѧ",10
//"��",11
//"��",12
//"��",13
//"��",14
//"��",15
//"��",16
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

#ifndef __TBZ_I2C_H_
#define __TBZ_I2C_H_


/*

._________
/ sdlfkj  \  
\_________/


*/

/**
 * @brief I2C ��ʱ����
 * @note ��Ϊ I2C �е��٣����٣���������ģʽ
 */
// #define I2C_Delay() { _nop_(); _nop_(); _nop_(); _nop_(); }
// #define I2C_Delay I2C_WaitAck
#define I2C_Delay()
// I2C SCL ����
#define I2C_SCL P1_1
// I2C SDA ����
#define I2C_SDA P1_0
/**
 * @brief i2c ��ʼ�źţ�SDA SCL ��ʼ�ߣ������� SDA�������� SCL�����������ʼ�ź�
 */
void I2C_Start () {
	I2C_SDA = HIGH;
	I2C_SCL = HIGH; // SDA, SCL ��ʼ�ߵ�ƽ
	I2C_Delay ();
	I2C_SDA = LOW;  // ���� SDA
	I2C_Delay ();
	I2C_SCL = LOW;  // ���� SCL
}
/**
 * @brief i2c ��ֹ�źţ�SDA SCL ��ʼ�ͣ������� SCL�������� SDA�����������ֹ�ź�
 */
void I2C_Stop () {
	I2C_SCL = LOW;
	I2C_SDA = LOW;  // ����ȷ�� SDA��SCL ���ǵ͵�ƽ
	I2C_Delay ();
	I2C_SCL = HIGH; // ������ SCL
	I2C_Delay ();
	I2C_SDA = HIGH; // ������ SDA
	I2C_Delay ();
}


void I2C_NAK () {
	I2C_SDA = HIGH;        // 8 λ���ݷ���������� SDA�� ���ͷ�Ӧ���ź�
	I2C_Delay ();
	I2C_SCL = HIGH;        // ���� SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // ���� SCL ��ɷ�Ӧ��λ��������ס����
}
void I2C_ACK () {
	I2C_SDA = LOW;         // 8 λ���ݷ���������� SDA�� ���ͷ�Ӧ���ź�
	I2C_Delay ();
	I2C_SCL = HIGH;        // ���� SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // ���� SCL ��ɷ�Ӧ��λ��������ס����
}

void I2C_WaitAck() {
	I2C_SCL = HIGH ;
	I2C_SCL = LOW ;
}


/**
 * @brief I2C д��һ���ֽڵ�����
 * @param dat ��д�������
 * @return __bit��һ��λ��
 * @retval 1 ��ʾ��Ӧ��
 *         0 ��ʾ��Ӧ��
 */
__bit I2C_Write (unsigned char dat) {
	__bit ack;  // �ݴ�Ӧ��λ��ֵ
	unsigned char mask;  // ����̽���ֽ���ĳһλֵ���������

	for (mask = 0x80; mask != 0; mask >>= 1) {
						 // �Ӹ�λ����λ���ν���
		I2C_SDA = (mask&dat) != 0; // �Ѹ�λ��ֵ��ֵ�� SDA ��
		I2C_Delay ();
		I2C_SCL = HIGH;  // ���� SCL
		I2C_Delay ();
		I2C_SCL = LOW;   // ���� SCL�����һ��λ����
	}
	I2C_SDA = HIGH;      // 8 λ���ݷ�����������ͷ� SDA���Լ��ӻ�Ӧ��
	I2C_Delay ();
	I2C_SCL = LOW;       // ���� SCL
	I2C_Delay ();
	ack = I2C_SDA;       // ��ȡ��ʱ�Ĵӻ�Ӧ��ֵ
	I2C_Delay ();
	I2C_SCL = HIGH;      // ���� SCL ���Ӧ�𣬱�������

	return (!ack);       // ���ط����߼���Ӧ��ֵ
						 // 0: �����ڻ�æ��д��ʧ�ܣ�1: �����ҿ��л�ɹ�д��
}


/**
 * @brief ��
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_Read () {
	unsigned char mask;
	unsigned char dat = 0;

	I2C_SDA = HIGH;         // �����ͷ� SDA
	// while (i--) {
	for (mask = 0x80; mask != 0; mask >>= 1) {
		I2C_Delay ();
		I2C_SCL = HIGH;     // ���� SCL
		if (I2C_SDA == 0) {
			dat &= (char)~mask;
		} else {
			dat |= mask;
		}
		// dat |= I2C_SDA;  // �� SDA ���ݸ��ӵ� dat ĩβ
		// dat <<= 1;       // ���� dat
		I2C_Delay ();
		I2C_SCL = LOW;     // ���� SCL����ʹ�ӻ����ͳ���һλ
	}

	return dat;          // ��������
}


/**
 * @brief Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadACK () {
	unsigned char dat = I2C_Read ();
	I2C_ACK ();
	return dat;          // ��������
}

/**
 * @brief ��Ӧ���
 * @return dat
 * @retval ���ض�ȡ������
 */
unsigned char I2C_ReadNAK () {
	unsigned char dat = I2C_Read ();
	I2C_NAK ();
	return dat;          // ��������
}


void I2C_WriteRegister (unsigned char addr, unsigned char register_addr, unsigned char dat) {
	I2C_Start ();
	I2C_Write (addr);
	I2C_WaitAck ();
	I2C_Write (register_addr);
	I2C_WaitAck ();
	I2C_Write (dat);
	I2C_WaitAck ();
	I2C_Stop ();
}
unsigned char I2C_ReadRegister (unsigned char addr, unsigned char register_addr) {
	I2C_Start ();
	I2C_Write (addr);
	I2C_Write (register_addr);
	I2C_Start ();
	I2C_Write (addr|0x01);
	unsigned char r = I2C_Read ();
	I2C_Stop ();
	return r;
}


/**
 * @brief I2C Ԫ����ַ��ѯ
 * @return __bit
 * @retval 0 ��ʾ������
 *         1 ��ʾ����
 */
__bit I2C_Addressing (unsigned char addr) {
	__bit ack;
	I2C_Start ();
	ack = I2C_Write (addr << 1);
	I2C_Stop ();

	return ack;
}

#endif

#ifndef __TBZ_MATH_H_
#define __TBZ_MATH_H_

//m^n����
u32 pow (u8 m,u8 n) {
	u32 result = 1;	 
	while (n--)
        result *= m;    
	return result;
}


#endif


#ifndef __TBZ_SSD1306_H_
#define __TBZ_SSD1306_H_


#define OLED_ADDR 0x78
#define OLED_CMD  0x00
#define OLED_DATA 0x40
#define OLED_MODE 0


//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0x10
#define X_WIDTH 	128
#define Y_WIDTH 	64
#define font_6x8    0
#define font_8X16   552
#define font_Chinese     2072

/*
OLED���Դ�
��Ÿ�ʽ����.
[0]0 1 2 3 ... 127
[1]0 1 2 3 ... 127
[2]0 1 2 3 ... 127
[3]0 1 2 3 ... 127
[4]0 1 2 3 ... 127
[5]0 1 2 3 ... 127
[6]0 1 2 3 ... 127
[7]0 1 2 3 ... 127
*/


void Delay_50ms(unsigned int Del_50ms) {
	unsigned int m;
	while(Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms) {
	unsigned char j;
	while(Del_1ms--)
		for(j=0;j<123;j++);
}


#define OLED_WR_Byte(a,b) I2C_WriteRegister (OLED_ADDR, b, a)


/**
 * @brief ʹ�� filter function �����Ļ
 * @param func ���뵱ǰҳ�͵�ַ(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant) {
	unsigned char m,n;
	FOR (m, 8) {
		OLED_WR_Byte(0xb0+m,OLED_CMD);		// ҳ 0-7
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		FOR (n, 128) OLED_WR_Byte ((*func)(n, m), OLED_DATA);
	}
}


void OLED_Set_Page (unsigned char page) {
	OLED_WR_Byte(0xb0+page,OLED_CMD);
}
//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//����OLED��ʾ
void OLED_Display_On(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//�ر�OLED��ʾ
void OLED_Display_Off(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size) {
	unsigned char i = 0, c = chr - ' ';//�õ�ƫ�ƺ��ֵ

	if (x > Max_Column - 1) { x = 0; y += 2; }
	OLED_Set_Pos (x, y);
	if (Char_Size >= 16) {
		FOR (i, 8) OLED_WR_Byte (readBYTE(font_8X16+c*16+i), OLED_DATA);

		OLED_Set_Pos (x, y+1);
		FOR (i, 8) OLED_WR_Byte (readBYTE(font_8X16+c*16+i+8), OLED_DATA);
	} else {
		FOR (i, 6) OLED_WR_Byte (readBYTE(font_6x8+c*6+i), OLED_DATA);
	}
}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size) {
	unsigned char j = 0;
	while (chr[j]!='\0') {
		OLED_ShowChar (x, y, chr[j++], Char_Size);
		if (Char_Size == 16)
			x += 8;
		else
			x += 8;
		if (x > 120) { x = 0; y += 2; }
	}
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2) {
	u8 t,temp;
	u8 enshow=0;
	FOR (t, len) {
		temp=(num/pow (10,len-t-1))%10;
		if(enshow==0&&t<(len-1)) {
			if(temp==0) {
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			} else enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
	}
}


//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no) {
	u8 t;
	OLED_Set_Pos(x, y);
	FOR (t, 16) OLED_WR_Byte(readBYTE(font_Chinese+2*no*16+t),OLED_DATA);
	OLED_Set_Pos(x, y+1);
	FOR (t, 16) OLED_WR_Byte(readBYTE(font_Chinese+2*no*16+16+t),OLED_DATA);
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]) {
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0) y=y1/8;
	else y=y1/8+1;

	for(y=y0;y<y1;y++) {
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++) {
			OLED_WR_Byte(BMP[j++],OLED_DATA);
		}
	}
}

//��ʼ��SSD1306
void OLED_Init(void) {

	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD);// contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//

	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//

	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//

	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//

	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//

	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//

	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//

	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}



#endif



/**************************/
// ��������
#define VK_NULL  '\0'
#define VK_UP    0x26
#define VK_LEFT  0x25
#define VK_DOWN  0x28
#define VK_ESC   0x1b
#define VK_ENTER 0x0d
#define VK_RIGHT 0x27
/**
 * @brief ��ȡ��ǰ���������ϵ���ɨ��
 * @return ���ص�ǰ�İ���ֵ
 */
unsigned char keystate (void) { 
	P2 = 0x7e;
	if (!P2_1) return VK_LEFT ;
	if (!P2_2) return VK_DOWN ;
	if (!P2_3) return VK_RIGHT;
	if (!P2_4) return VK_ESC  ;
	if (!P2_5) return VK_UP   ;
	if (!P2_6) return VK_ENTER;
	return VK_NULL;
}
char isUp = 1;   // ֻ��Ӧһ��
/******************************/

// char addr = OLED_ADDR;
// ���ڱ�ʾ��ǰ������ö�ٱ���
enum SCENE {
	START,
	MAIN,
	LIGHT_CONTROL,
	PWM_CONTROL,
	SAVE_STATUS,
	INFORMATION_QUERY,
	EXIT
} scene = START;
unsigned char LED = 0;
int result = 0;
unsigned char query = 0;
unsigned char oled_clear (char x, char y) __reentrant {
	return 0x00;
}
unsigned int number = 7140;
signed char option = 0;                // ѡ�����õı���
// signed char light_value [8] = { 0, 2, 6, 10, 12, 14,16, 20 };   // LED �Ƶ� ռ�ձȣ��ٷ�����
signed char light_value [8] = { 0 };   // LED �Ƶ� ռ�ձȣ��ٷ�����
unsigned int freq = 200;      // Ƶ�ʣ�һ�����ж��ٸ����ڣ�
unsigned int timeDuration;    // ��ǰƵ���¶�ʱ������Ҫ����ֵ
unsigned int keyboard_timeDuration;
unsigned int OLED_timeDuration;
signed char duty_max = 20;  // һ���ڶ�ʱ����Ӧ�Ĵ��������ڿ�������
                              // ����Ӧ���ֶ����㵱ǰ�������ʱʱ��
							  // ������ΪҪͬʱ���ư�յ�Ƶ�������ֻ������ duty_max ��
char tick;
int ii, jj;   // FOR ѭ�����ñ���
unsigned int calcCurrentDuration (unsigned int freq, unsigned int duty_max) {
                              // ���ڼ��㵱ǰ��
	return 0xffff-(11059200/freq/duty_max);
}

#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);

void draw (void);        // ���ƽ��棬��ʾ OLED ����
void keyboard (void);    // �������룬��������ת�������Ĵ���
void KEY_INPUT (void) __interrupt (1);     // ��ʱ�������봦����
void LED_SHOWUP (void) __interrupt (3);    // LED PWM ���ⶨʱ������
void OLED_SHOWUP (void) __interrupt (5);   // OLED ��ʱˢ��
void main () {
	/**********��ʼ������*************/
    // �ڵ�Ƭ���ϵ����߸�λ�����һ��
	TMOD = 0x00;         // 0��1 ��ʱ�������� 16 λ��ʱ
	EXEN2 = 0x00;
	// PT2 = 0;
	IP = 0x0a;
	EA = 1;              // ���ж�ʹ��

	timeDuration = calcCurrentDuration (freq, duty_max);  // PWM һ���ڶ�Ӧ�ļ�ʱ����ֵ
	keyboard_timeDuration = 10204;    // ÿ 5ms ����һ�ΰ���
	OLED_timeDuration = 10204;

	ET0 = 1;        // ��ʱ��0 �ж�ʹ��
	ET1 = 1;        // ��ʱ��1 �ж�ʹ��
	ET2 = 1;        // ��ʱ��2 �ж�ʹ��

	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
	ASSIGNMENT16 (TH1, TL1, timeDuration);
	ASSIGNMENT16 (TH2, TL2, OLED_timeDuration);

	OLED_Init ();         // ��ʼ�� OLED ��Ļ
	OLED_Fill (oled_clear);

	FOR(ii, 8) light_value[ii] = readBYTE (STC_EEPROM_END_ADDR-ii); // ��Ƭ�� eeprom �����ݶ���


	TR0 = 1;        // ���� ��ʱ��0
	TR1 = 1;        // ���� ��ʱ��1
	TR2 = 1;        // ���� ��ʱ��2


	while (1);      // ʹ���򲻶�����


}

void KEY_INPUT (void) __interrupt (1) {
	unsigned char k = keystate();    // ���ص�һ����ɨ�赽�İ�����û�в������ϵ�����
	static unsigned int flag = 0;    // 0 ����ǰ�ǵ�һ�ζ��������������Ҫ����һ���ٽ��д���
	static int fi = 20;
	flag ++;
	if (flag > 130) isUp = 1;
	if (k == VK_NULL) {              // ���ʲôҲû�а��£���ʾ��ǰΪ����״̬
		isUp = 1;
		flag = 0;
		fi = 20;
	} else if (isUp == 1) {          // �����ǰ�ǵ���״̬
		if (flag > 1) {
			if (flag > 130) {
				if (flag % fi) goto end;
				else fi--;
				if (fi < 1) fi = 1;
			}
			isUp = 0;                // ��Ϊ�а��������£����Ա�ǵ�ǰΪ����״̬
			switch (scene) {
				case START: {
					scene = MAIN;
					OLED_Fill (oled_clear);
				} break;
				case MAIN: {
					switch (k) {
						case VK_UP: {
							if (--option < 0) option = 3;
						} break;
						case VK_DOWN: {
							if (++option > 3) option = 0;
						} break;
						case VK_ENTER:
						case VK_RIGHT: {
							switch (option) { 
								case 0: scene = LIGHT_CONTROL    ; break;
								case 1: scene = PWM_CONTROL      ; break;
								case 2: scene = SAVE_STATUS      ; break;
								case 3: scene = INFORMATION_QUERY; break;
							}
							option = 0; 
						} break;
					}
				} break;
				case PWM_CONTROL: {
					switch (k) {
						case VK_LEFT: {
							if (option == 0) {
								freq --;
								if (freq < 1) freq = 1;
							} else {
								duty_max --;
								if (duty_max < 1) duty_max = 1;
							}
						} break;
						case VK_RIGHT: {
							if (option == 0) {
								freq ++;
								if (freq > 20000) freq = 20000;
							} else {
								duty_max ++;
								if (duty_max > 100) duty_max = 100;
							}
						} break;
						case VK_UP: {
							option ++;
							if (option > 1) option = 0;
						} break;
						case VK_DOWN: {
							option --;
							if (option < 0) option = 1;
						} break;
						case VK_ENTER:
						case VK_ESC: {
							scene = MAIN;
						} break;
					}
					timeDuration = calcCurrentDuration(freq, duty_max);
				} break;
				case INFORMATION_QUERY: {
					switch (k) {
						case VK_ENTER: {
							query = 1;
						} break;
						case VK_UP: {
							switch (option) {
								case 0: number += 1; break;
								case 1: number += 10; break;
								case 2: number += 100; break;
								case 3: number += 1000; break;
							}
							if (number > 9999) number = 9999;
						} break;
						case VK_DOWN: {
							switch (option) {
								case 0: number -= 1; break;
								case 1: number -= 10; break;
								case 2: number -= 100; break;
								case 3: number -= 1000; break;
							}
							if (number < 1000) number = 1000;
						} break;
						case VK_LEFT: {
							option ++;
							if (option > 3) option = 0;
						} break;
						case VK_RIGHT: {
							option --;
							if (option < 0) option = 3;
						} break;
						case VK_ESC: {
							if (query) query = 0;
							else scene = MAIN;
						} break;
					}
				} break;
				case LIGHT_CONTROL: {
					switch (k) {
						case VK_UP: {
							option --;
							if (option < 0) option = 7;
						} break;
						case VK_DOWN: {
							option ++;
							if (option > 7) option = 0;
						} break;
						case VK_RIGHT: {
							light_value [option] ++;
							if (light_value[option] > duty_max)
								light_value[option] = duty_max;
						} break;
						case VK_LEFT: {
							light_value [option] --;
							if (light_value[option] < 0)
								light_value[option] = 0;
						} break;
						case VK_ENTER:
						case VK_ESC: {
							scene = MAIN;
							option = 0;
							OLED_Fill (oled_clear);
						} break;
					}
				} break;
				case SAVE_STATUS: {
					FOR(ii, 8) writeBYTE (STC_EEPROM_END_ADDR-ii, light_value[ii]);
				} break;
			}

		}
	}
end:
	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
}


void LED_SHOWUP (void) __interrupt (3) {
	static signed char count = 0;       // ռ�ձȼ���
	if (count >= duty_max) count = 0;   // �ﵽ�趨�Ĵ��������¼���

	P0_0 = count >= light_value[0];     // �����ǰ С���趨ֵ��������������
	P0_1 = count >= light_value[1];
	P0_2 = count >= light_value[2];
	P0_3 = count >= light_value[3];
	P0_4 = count >= light_value[4];
	P0_5 = count >= light_value[5];
	P0_6 = count >= light_value[6];
	P0_7 = count >= light_value[7];
	count ++;
	ASSIGNMENT16 (TH1, TL1, timeDuration);
}

void OLED_SHOWUP (void) __interrupt (5) {
	static int i = 0;
	i++;
	if (i > 16) {
		switch (scene) {
			case START: {
				OLED_ShowCHinese (16,  1, 0);//��
				OLED_ShowCHinese (32,  1, 1);//Ц
				OLED_ShowCHinese (48,  1, 1);//Ц
				OLED_ShowChar    (64,  1, '&',16);
				OLED_ShowCHinese (64+8,1, 5);//��
				OLED_ShowCHinese (80+8,1, 6);//��
				OLED_ShowCHinese (96+8,1, 7);//�x
				OLED_ShowCHinese (40-4,  3, 13);//��
				OLED_ShowCHinese (56-4,  3, 14);//��
				OLED_ShowCHinese (72-4,  3, 15);//��
				OLED_ShowCHinese (88-4,  3, 16);//��
				OLED_ShowString (32, 6, "finished on", 8);
				OLED_ShowString (0, 7, "2021/06/17.", 8);
				if (scene == MAIN) OLED_Fill (oled_clear);
			} break;
			case MAIN: {

				OLED_ShowString (0, 0, "   LED Control", 16);
				OLED_ShowString (0, 2, "   PWM Control", 16);
				OLED_ShowString (0, 4, "   Save Status", 16);
				OLED_ShowString (0, 6, "   information", 8);
				OLED_ShowString (0, 7, "      query", 8);
				OLED_ShowChar (7, 2*option, '+', 16);

				if (scene != MAIN) {
					OLED_Fill (oled_clear);
					switch (scene) {
						case LIGHT_CONTROL: {

							FOR(jj,8) {
								OLED_Set_Pos (20, jj);
								FOR (ii, 5*light_value[jj])
									OLED_WR_Byte (0xfe, OLED_DATA);
								for (ii = 5*light_value[jj]; ii < 128-20; ii++)
									OLED_WR_Byte (0x00, OLED_DATA);
							}
						} break;

						case INFORMATION_QUERY: {
							OLED_ShowCHinese (0,0,10);
							OLED_ShowCHinese (16,0,11);
						} break;
					}
				}
			} break;
			case PWM_CONTROL: {
				OLED_ShowNum (32,0,freq, 5, 16);
				OLED_ShowNum (32, 2, duty_max, 3, 16);
			} break;
			case INFORMATION_QUERY: {
				if (query) {
					switch (number) {
						case 7140: {
							OLED_ShowCHinese (30, 3, 5);
							OLED_ShowCHinese (46, 3, 6);
							OLED_ShowCHinese (62, 3, 7);
						} break;
						case 7203: {
							OLED_ShowCHinese (30, 3, 0);
							OLED_ShowCHinese (46, 3, 1);
							OLED_ShowCHinese (62, 3, 1);
						} break;
						default: {
							OLED_ShowString (23, 3, "Not Found!", 16);
						}
					}
				} else {
					OLED_ShowString (20,3,"2010-",16);
					if (tick){
						OLED_ShowChar (59+8*(3-option),3,' ',16);
						tick = 0;
					} else {
						OLED_ShowNum (59, 3, number, 4, 16);
						tick = 1;
					}
				}
			} break;
			case LIGHT_CONTROL: {
				OLED_ShowNum (0, 0, option,1,16);
				OLED_ShowNum (0, 2, light_value[option],2,16);
				OLED_Set_Pos (20, option);
				FOR (ii, 5*light_value[option])
					OLED_WR_Byte (0xfe, OLED_DATA);
				for (ii = 5*light_value[option]; ii < 128-20; ii++)
					OLED_WR_Byte (0x00, OLED_DATA);
			} break;
		}
	}
	ASSIGNMENT16 (TH2, TL2, OLED_timeDuration);
}

