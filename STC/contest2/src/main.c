
// 引入 51 单片机中对针脚的定义
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

// 特殊语法

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
 * @brief 一个简单的延迟函数
 * @param x10us 延时的时间
 * 	延时时间相当于 参数*10 个微秒
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
//"陈",0
//"笑",1
//"张",2
//"乐",3
//"辉",4
//"張",5
//"樂",6
//"輝",7
//"小",8
//"三",9
//"学",10
//"号",11
//"：",12
//"倾",13
//"力",14
//"贡",15
//"献",16
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

#ifndef __TBZ_I2C_H_
#define __TBZ_I2C_H_


/*

._________
/ sdlfkj  \  
\_________/


*/

/**
 * @brief I2C 延时函数
 * @note 因为 I2C 有低速，快速，高速三种模式
 */
// #define I2C_Delay() { _nop_(); _nop_(); _nop_(); _nop_(); }
// #define I2C_Delay I2C_WaitAck
#define I2C_Delay()
// I2C SCL 引脚
#define I2C_SCL P1_1
// I2C SDA 引脚
#define I2C_SDA P1_0
/**
 * @brief i2c 起始信号，SDA SCL 起始高，先拉低 SDA，再拉低 SCL，即可完成起始信号
 */
void I2C_Start () {
	I2C_SDA = HIGH;
	I2C_SCL = HIGH; // SDA, SCL 起始高电平
	I2C_Delay ();
	I2C_SDA = LOW;  // 拉低 SDA
	I2C_Delay ();
	I2C_SCL = LOW;  // 拉低 SCL
}
/**
 * @brief i2c 终止信号，SDA SCL 起始低，先拉高 SCL，再拉高 SDA，即可完成终止信号
 */
void I2C_Stop () {
	I2C_SCL = LOW;
	I2C_SDA = LOW;  // 首先确保 SDA、SCL 都是低电平
	I2C_Delay ();
	I2C_SCL = HIGH; // 先拉高 SCL
	I2C_Delay ();
	I2C_SDA = HIGH; // 再拉高 SDA
	I2C_Delay ();
}


void I2C_NAK () {
	I2C_SDA = HIGH;        // 8 位数据发送完后，拉高 SDA， 发送非应答信号
	I2C_Delay ();
	I2C_SCL = HIGH;        // 拉高 SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // 拉低 SCL 完成非应答位，并保持住总线
}
void I2C_ACK () {
	I2C_SDA = LOW;         // 8 位数据发送完后，拉高 SDA， 发送非应答信号
	I2C_Delay ();
	I2C_SCL = HIGH;        // 拉高 SCL
	I2C_Delay ();
	I2C_SCL = LOW;         // 拉低 SCL 完成非应答位，并保持住总线
}

void I2C_WaitAck() {
	I2C_SCL = HIGH ;
	I2C_SCL = LOW ;
}


/**
 * @brief I2C 写入一个字节的数据
 * @param dat 欲写入的数据
 * @return __bit（一个位）
 * @retval 1 表示有应答
 *         0 表示无应答
 */
__bit I2C_Write (unsigned char dat) {
	__bit ack;  // 暂存应答位的值
	unsigned char mask;  // 用于探测字节内某一位值的掩码变量

	for (mask = 0x80; mask != 0; mask >>= 1) {
						 // 从高位到低位依次进行
		I2C_SDA = (mask&dat) != 0; // 把该位的值赋值到 SDA 上
		I2C_Delay ();
		I2C_SCL = HIGH;  // 拉高 SCL
		I2C_Delay ();
		I2C_SCL = LOW;   // 拉低 SCL，完成一个位周期
	}
	I2C_SDA = HIGH;      // 8 位数据发送完后，主机释放 SDA，以检测从机应答
	I2C_Delay ();
	I2C_SCL = LOW;       // 拉高 SCL
	I2C_Delay ();
	ack = I2C_SDA;       // 读取此时的从机应答值
	I2C_Delay ();
	I2C_SCL = HIGH;      // 拉低 SCL 完成应答，保持总线

	return (!ack);       // 返回符合逻辑的应答值
						 // 0: 不存在或忙活写入失败，1: 存在且空闲或成功写入
}


/**
 * @brief 读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_Read () {
	unsigned char mask;
	unsigned char dat = 0;

	I2C_SDA = HIGH;         // 主机释放 SDA
	// while (i--) {
	for (mask = 0x80; mask != 0; mask >>= 1) {
		I2C_Delay ();
		I2C_SCL = HIGH;     // 拉高 SCL
		if (I2C_SDA == 0) {
			dat &= (char)~mask;
		} else {
			dat |= mask;
		}
		// dat |= I2C_SDA;  // 将 SDA 数据附加到 dat 末尾
		// dat <<= 1;       // 左移 dat
		I2C_Delay ();
		I2C_SCL = LOW;     // 拉低 SCL，以使从机发送出下一位
	}

	return dat;          // 返回数据
}


/**
 * @brief 应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadACK () {
	unsigned char dat = I2C_Read ();
	I2C_ACK ();
	return dat;          // 返回数据
}

/**
 * @brief 非应答读
 * @return dat
 * @retval 返回读取的数据
 */
unsigned char I2C_ReadNAK () {
	unsigned char dat = I2C_Read ();
	I2C_NAK ();
	return dat;          // 返回数据
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
 * @brief I2C 元件地址查询
 * @return __bit
 * @retval 0 表示不存在
 *         1 表示存在
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

//m^n函数
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


//OLED模式设置
//0:4线串行模式
//1:并行8080模式

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
OLED的显存
存放格式如下.
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
 * @brief 使用 filter function 填充屏幕
 * @param func 传入当前页和地址(must be __reentrant)
 * @return
 */
void OLED_Fill (unsigned char (*func)(char x, char y) __reentrant) {
	unsigned char m,n;
	FOR (m, 8) {
		OLED_WR_Byte(0xb0+m,OLED_CMD);		// 页 0-7
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		FOR (n, 128) OLED_WR_Byte ((*func)(n, m), OLED_DATA);
	}
}


void OLED_Set_Page (unsigned char page) {
	OLED_WR_Byte(0xb0+page,OLED_CMD);
}
//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//开启OLED显示
void OLED_Display_On(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示
void OLED_Display_Off(void) {
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size) {
	unsigned char i = 0, c = chr - ' ';//得到偏移后的值

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

//显示一个字符号串
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
//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
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


//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no) {
	u8 t;
	OLED_Set_Pos(x, y);
	FOR (t, 16) OLED_WR_Byte(readBYTE(font_Chinese+2*no*16+t),OLED_DATA);
	OLED_Set_Pos(x, y+1);
	FOR (t, 16) OLED_WR_Byte(readBYTE(font_Chinese+2*no*16+16+t),OLED_DATA);
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
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

//初始化SSD1306
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
// 按键处理
#define VK_NULL  '\0'
#define VK_UP    0x26
#define VK_LEFT  0x25
#define VK_DOWN  0x28
#define VK_ESC   0x1b
#define VK_ENTER 0x0d
#define VK_RIGHT 0x27
/**
 * @brief 获取当前按键，从上到下扫描
 * @return 返回当前的按键值
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
char isUp = 1;   // 只响应一次
/******************************/

// char addr = OLED_ADDR;
// 用于表示当前场景的枚举变量
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
signed char option = 0;                // 选项所用的变量
// signed char light_value [8] = { 0, 2, 6, 10, 12, 14,16, 20 };   // LED 灯的 占空比（百分数）
signed char light_value [8] = { 0 };   // LED 灯的 占空比（百分数）
unsigned int freq = 200;      // 频率（一秒中有多少个周期）
unsigned int timeDuration;    // 当前频率下定时器所需要的数值
unsigned int keyboard_timeDuration;
unsigned int OLED_timeDuration;
signed char duty_max = 20;  // 一周期定时器响应的次数（用于控制亮灭
                              // 否则应当手动计算当前所需的延时时长
							  // 但是因为要同时控制八盏灯的亮暗，只能做满 duty_max 次
char tick;
int ii, jj;   // FOR 循环所用变量
unsigned int calcCurrentDuration (unsigned int freq, unsigned int duty_max) {
                              // 用于计算当前的
	return 0xffff-(11059200/freq/duty_max);
}

#define ASSIGNMENT16(high, low, value) \
	high = (unsigned char)(value >> 8);\
	low  = (unsigned char)(value & 0xff);

void draw (void);        // 绘制界面，显示 OLED 内容
void keyboard (void);    // 按键输入，不包括旋转编码器的处理
void KEY_INPUT (void) __interrupt (1);     // 定时按键输入处理（？
void LED_SHOWUP (void) __interrupt (3);    // LED PWM 调光定时器函数
void OLED_SHOWUP (void) __interrupt (5);   // OLED 定时刷新
void main () {
	/**********初始化部分*************/
    // 在单片机上电后或者复位后调用一次
	TMOD = 0x00;         // 0、1 定时器都采用 16 位计时
	EXEN2 = 0x00;
	// PT2 = 0;
	IP = 0x0a;
	EA = 1;              // 总中断使能

	timeDuration = calcCurrentDuration (freq, duty_max);  // PWM 一周期对应的计时器数值
	keyboard_timeDuration = 10204;    // 每 5ms 处理一次按键
	OLED_timeDuration = 10204;

	ET0 = 1;        // 定时器0 中断使能
	ET1 = 1;        // 定时器1 中断使能
	ET2 = 1;        // 定时器2 中断使能

	ASSIGNMENT16 (TH0, TL0, keyboard_timeDuration);
	ASSIGNMENT16 (TH1, TL1, timeDuration);
	ASSIGNMENT16 (TH2, TL2, OLED_timeDuration);

	OLED_Init ();         // 初始化 OLED 屏幕
	OLED_Fill (oled_clear);

	FOR(ii, 8) light_value[ii] = readBYTE (STC_EEPROM_END_ADDR-ii); // 将片内 eeprom 的数据读出


	TR0 = 1;        // 启动 定时器0
	TR1 = 1;        // 启动 定时器1
	TR2 = 1;        // 启动 定时器2


	while (1);      // 使程序不断运行


}

void KEY_INPUT (void) __interrupt (1) {
	unsigned char k = keystate();    // 返回第一个被扫描到的按键（没有采用书上的做法
	static unsigned int flag = 0;    // 0 代表当前是第一次读到这个按键，需要在下一次再进行处理
	static int fi = 20;
	flag ++;
	if (flag > 130) isUp = 1;
	if (k == VK_NULL) {              // 如果什么也没有按下，表示当前为弹起状态
		isUp = 1;
		flag = 0;
		fi = 20;
	} else if (isUp == 1) {          // 如果当前是弹起状态
		if (flag > 1) {
			if (flag > 130) {
				if (flag % fi) goto end;
				else fi--;
				if (fi < 1) fi = 1;
			}
			isUp = 0;                // 因为有按键被按下，所以标记当前为按下状态
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
	static signed char count = 0;       // 占空比计数
	if (count >= duty_max) count = 0;   // 达到设定的次数后重新计数

	P0_0 = count >= light_value[0];     // 如果当前 小于设定值，灯亮，否则，灭
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
				OLED_ShowCHinese (16,  1, 0);//陈
				OLED_ShowCHinese (32,  1, 1);//笑
				OLED_ShowCHinese (48,  1, 1);//笑
				OLED_ShowChar    (64,  1, '&',16);
				OLED_ShowCHinese (64+8,1, 5);//張
				OLED_ShowCHinese (80+8,1, 6);//樂
				OLED_ShowCHinese (96+8,1, 7);//輝
				OLED_ShowCHinese (40-4,  3, 13);//倾
				OLED_ShowCHinese (56-4,  3, 14);//力
				OLED_ShowCHinese (72-4,  3, 15);//贡
				OLED_ShowCHinese (88-4,  3, 16);//献
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

