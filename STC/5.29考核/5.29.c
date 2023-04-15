#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit KEY_IN_1  = P2^4;
sbit KEY_IN_2  = P2^5;
sbit KEY_IN_3  = P2^6;
sbit KEY_IN_4  = P2^7;
sbit KEY_OUT_1 = P2^3;
sbit KEY_OUT_2 = P2^2;
sbit KEY_OUT_3 = P2^1;
sbit KEY_OUT_4 = P2^0;

bit flag1s = 1;          //1秒定时标志
bit control = 0;		 //数码管倒计时标志
unsigned char index = 16;     //图片刷新索引
unsigned char Water_flag = 0;//流水灯标志
unsigned char num = 5;    //用于保存加减运算符

unsigned char code LedChar[] = {  //数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
unsigned char code WaterChar[] = {  //流水灯显示转换表
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F
};
unsigned char code image[] = {  // 图片的字模表
    0xFF,0xFF,0xFF,0xFF,0xC3,0xFB,0xFB,0xC3,
	0xFF,0xE3,0xDB,0xDB,0xDB,0xE3,0xFF,0xC3,
	0xFB,0xFB,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF
};
unsigned char LedBuff[6] = {  //数码管显示缓冲区
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
unsigned char code KeyCodeMap[4][4] = { //矩阵按键编号到标准键盘键码的映射表
    { 0x31, 0x32, 0x33, 0x26 }, //数字键1、数字键2、数字键3、向上键
    { 0x34, 0x35, 0x36, 0x25 }, //数字键4、数字键5、数字键6、向左键
    { 0x37, 0x38, 0x39, 0x28 }, //数字键7、数字键8、数字键9、向下键
    { 0x30, 0x1B, 0x0D, 0x27 }  //数字键0、ESC键、  回车键、 向右键
};
unsigned char KeySta[4][4] = {  //全部矩阵按键的当前状态
    {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1}
};

void KeyDriver();
void ShowNumber(long num);

void main()
{
	EA = 1;
	ENLED = 0;
	ADDR3 = 1;
	TMOD = 0x01;
	TH0 = 0xFC;		//定时器定时 1 ms
	TL0 = 0x67;
	ET0 = 1;
	TR0 = 1;
	LedBuff[5] = LedChar[11];	//数码管显示 b80505
	LedBuff[4] = LedChar[8];
	LedBuff[3] = LedChar[0];
	LedBuff[2] = LedChar[5];
	LedBuff[1] = LedChar[0];
	LedBuff[0] = LedChar[5];
	while(1)
	{
		if (flag1s)
        {
            flag1s = 0;
			if (control == 1)	//数码管倒计时
			{
				if (num <= 0)
				{
					num = 100;
				}
				num--;
			}
            ShowNumber(num);	//更新1、2位数码管上的数字
        }
		KeyDriver();   //调用按键驱动函数
	}
}

/* 将一个有符号长整型的数字显示到数码管上，num-待显示数字 */
void ShowNumber(long num)
{
    signed char i;
    unsigned char buf[2];
    
    for (i=0; i<=1; i++)   //把长整型数转换为2位十进制的数组
    {
        buf[i] = num % 10;
        num = num / 10;
    }
    for (i=1; i>=0; i--)    //剩余低位都如实转换为数码管显示字符
    {
        LedBuff[i] = LedChar[buf[i]];
    }
}

/* 按键动作函数，根据键码执行相应的操作，keycode-按键键码 */
void KeyAction(unsigned char keycode)
{
    if (keycode == 0x26)  //向上键用作加号
    {
		control = 0;	//停止倒计时
        if (num >= 99)	//数字大于等于 99 时变为 0 ，否则加 1
        {
            num = 0;
        }
        else
        {
            num += 1;
        }
        ShowNumber(num);	//更新1、2位数码管上的数字
    }
    else if (keycode == 0x28)  //向下键用作减号
    {
		control = 0;	//停止倒计时
        if (num <= 0)	//数字小于等于 0 时变为 99 ，否则减 1
        {
            num = 99;
        }
        else
        {
            num -= 1;
        }
        ShowNumber(num);	//更新1、2位数码管上的数字
    }
	else if (keycode == 0x1B) //ESC键用作复原信号	
	{
		control = 1;	 //数码管继续倒计时
	}
}

/* 按键驱动函数，检测按键动作，调度相应动作函数，需在主循环中调用 */
void KeyDriver()
{
    unsigned char i, j;
    static unsigned char backup[4][4] = {  //按键值备份，保存前一次的值
        {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1}
    };
    
    for (i=0; i<4; i++)  //循环检测4*4的矩阵按键
    {
        for (j=0; j<4; j++)
        {
            if (backup[i][j] != KeySta[i][j])    //检测按键动作
            {
                if (backup[i][j] != 0)           //按键按下时执行动作
                {
                    KeyAction(KeyCodeMap[i][j]); //调用按键动作函数
                }
                backup[i][j] = KeySta[i][j];     //刷新前一次的备份值
            }
        }
    }
}

/* 按键扫描函数，需在定时中断中调用，推荐调用间隔1ms */
void KeyScan()
{
    unsigned char i;
    static unsigned char keyout = 0;   //矩阵按键扫描输出索引
    static unsigned char keybuf[4][4] = {  //矩阵按键扫描缓冲区
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF}
    };

    //将一行的4个按键值移入缓冲区
    keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
    keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
    keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
    keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
    //消抖后更新按键状态
    for (i=0; i<4; i++)  //每行4个按键，所以循环4次
    {
        if ((keybuf[keyout][i] & 0x0F) == 0x00)
        {   //连续4次扫描值为0，即4*4ms内都是按下状态时，可认为按键已稳定的按下
            KeySta[keyout][i] = 0;
        }
        else if ((keybuf[keyout][i] & 0x0F) == 0x0F)
        {   //连续4次扫描值为1，即4*4ms内都是弹起状态时，可认为按键已稳定的弹起
            KeySta[keyout][i] = 1;
        }
    }
    //执行下一次的扫描输出
    keyout++;                //输出索引递增
    keyout = keyout & 0x03;  //索引值加到4即归零
    switch (keyout)          //根据索引，释放当前输出引脚，拉低下次的输出引脚
    {
        case 0: KEY_OUT_4 = 1; KEY_OUT_1 = 0; break;
        case 1: KEY_OUT_1 = 1; KEY_OUT_2 = 0; break;
        case 2: KEY_OUT_2 = 1; KEY_OUT_3 = 0; break;
        case 3: KEY_OUT_3 = 1; KEY_OUT_4 = 0; break;
        default: break;
    }
}

/* 数码管动态扫描刷新函数，需在定时中断中调用 */
void LedScan()
{
    static unsigned char i = 0;  //动态扫描的索引
    
    P0 = 0xFF;   //显示消隐
    switch (i)
    {
        //点阵部分
        case 0: ADDR3 = 0; ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=image[index+0]; break;
        case 1: ADDR3 = 0; ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=image[index+1]; break;
        case 2: ADDR3 = 0; ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=image[index+2]; break;
        case 3: ADDR3 = 0; ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=image[index+3]; break;
        case 4: ADDR3 = 0; ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=image[index+4]; break;
        case 5: ADDR3 = 0; ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=image[index+5]; break;
        case 6: ADDR3 = 0; ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=image[index+6]; break;
        case 7: ADDR3 = 0; ADDR2=1; ADDR1=1; ADDR0=1; i++; P0=image[index+7]; break;
        //数码管部分
        case 8:  ADDR3 = 1; ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=LedBuff[0]; break;
        case 9:  ADDR3 = 1; ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=LedBuff[1]; break;
        case 10: ADDR3 = 1; ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=LedBuff[2]; break;
        case 11: ADDR3 = 1; ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=LedBuff[3]; break;
        case 12: ADDR3 = 1; ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=LedBuff[4]; break;
        case 13: ADDR3 = 1; ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=LedBuff[5]; break;
        //流水灯部分
        case 14: ADDR3 = 1; ADDR2=1; ADDR1=1; ADDR0=0; i=0; P0=WaterChar[Water_flag]; break;
        default: break;
    }
}
/* T0中断服务函数，用于数码管显示扫描与按键扫描 */
void InterruptTimer0() interrupt 1
{
	static unsigned int tmr1 = 0;  //1秒定时器
	static unsigned int tmr2 = 0;  //250ms定时器
    
    tmr1++;
    tmr2++;
    
    if (tmr1 >= 1000)
    {
		flag1s = 1;		//1秒定时标志赋1
        tmr1 = 0;
        switch (Water_flag)	//流水灯切换
        {
            case 0: Water_flag = 7; break;
            case 2: Water_flag = 5; break;
            case 3: Water_flag = 4; break;
            case 4: Water_flag = 0; break;
            case 5: Water_flag = 3; break;
            case 7: Water_flag = 2; break;
            default: break;
        }
    }
    if (tmr2 >= 250)
    {
        tmr2 = 0;
        index--;
        if (index <= 0) // 图片索引减到 0 后复原
        {
            index = 16;
        }
    }
    
    TH0 = 0xFC;  //重新加载初值
    TL0 = 0x67;
    LedScan();   //调用数码管显示扫描函数
    KeyScan();   //调用按键扫描函数
}
