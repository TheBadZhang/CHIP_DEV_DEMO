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

bit flag1s = 1;          //1�붨ʱ��־
bit control = 0;		 //����ܵ���ʱ��־
unsigned char index = 16;     //ͼƬˢ������
unsigned char Water_flag = 0;//��ˮ�Ʊ�־
unsigned char num = 5;    //���ڱ���Ӽ������

unsigned char code LedChar[] = {  //�������ʾ�ַ�ת����
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
unsigned char code WaterChar[] = {  //��ˮ����ʾת����
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F
};
unsigned char code image[] = {  // ͼƬ����ģ��
    0xFF,0xFF,0xFF,0xFF,0xC3,0xFB,0xFB,0xC3,
	0xFF,0xE3,0xDB,0xDB,0xDB,0xE3,0xFF,0xC3,
	0xFB,0xFB,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF
};
unsigned char LedBuff[6] = {  //�������ʾ������
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
unsigned char code KeyCodeMap[4][4] = { //���󰴼���ŵ���׼���̼����ӳ���
    { 0x31, 0x32, 0x33, 0x26 }, //���ּ�1�����ּ�2�����ּ�3�����ϼ�
    { 0x34, 0x35, 0x36, 0x25 }, //���ּ�4�����ּ�5�����ּ�6�������
    { 0x37, 0x38, 0x39, 0x28 }, //���ּ�7�����ּ�8�����ּ�9�����¼�
    { 0x30, 0x1B, 0x0D, 0x27 }  //���ּ�0��ESC����  �س����� ���Ҽ�
};
unsigned char KeySta[4][4] = {  //ȫ�����󰴼��ĵ�ǰ״̬
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
	TH0 = 0xFC;		//��ʱ����ʱ 1 ms
	TL0 = 0x67;
	ET0 = 1;
	TR0 = 1;
	LedBuff[5] = LedChar[11];	//�������ʾ b80505
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
			if (control == 1)	//����ܵ���ʱ
			{
				if (num <= 0)
				{
					num = 100;
				}
				num--;
			}
            ShowNumber(num);	//����1��2λ������ϵ�����
        }
		KeyDriver();   //���ð�����������
	}
}

/* ��һ���з��ų����͵�������ʾ��������ϣ�num-����ʾ���� */
void ShowNumber(long num)
{
    signed char i;
    unsigned char buf[2];
    
    for (i=0; i<=1; i++)   //�ѳ�������ת��Ϊ2λʮ���Ƶ�����
    {
        buf[i] = num % 10;
        num = num / 10;
    }
    for (i=1; i>=0; i--)    //ʣ���λ����ʵת��Ϊ�������ʾ�ַ�
    {
        LedBuff[i] = LedChar[buf[i]];
    }
}

/* �����������������ݼ���ִ����Ӧ�Ĳ�����keycode-�������� */
void KeyAction(unsigned char keycode)
{
    if (keycode == 0x26)  //���ϼ������Ӻ�
    {
		control = 0;	//ֹͣ����ʱ
        if (num >= 99)	//���ִ��ڵ��� 99 ʱ��Ϊ 0 ������� 1
        {
            num = 0;
        }
        else
        {
            num += 1;
        }
        ShowNumber(num);	//����1��2λ������ϵ�����
    }
    else if (keycode == 0x28)  //���¼���������
    {
		control = 0;	//ֹͣ����ʱ
        if (num <= 0)	//����С�ڵ��� 0 ʱ��Ϊ 99 ������� 1
        {
            num = 99;
        }
        else
        {
            num -= 1;
        }
        ShowNumber(num);	//����1��2λ������ϵ�����
    }
	else if (keycode == 0x1B) //ESC��������ԭ�ź�	
	{
		control = 1;	 //����ܼ�������ʱ
	}
}

/* ����������������ⰴ��������������Ӧ����������������ѭ���е��� */
void KeyDriver()
{
    unsigned char i, j;
    static unsigned char backup[4][4] = {  //����ֵ���ݣ�����ǰһ�ε�ֵ
        {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1},  {1, 1, 1, 1}
    };
    
    for (i=0; i<4; i++)  //ѭ�����4*4�ľ��󰴼�
    {
        for (j=0; j<4; j++)
        {
            if (backup[i][j] != KeySta[i][j])    //��ⰴ������
            {
                if (backup[i][j] != 0)           //��������ʱִ�ж���
                {
                    KeyAction(KeyCodeMap[i][j]); //���ð�����������
                }
                backup[i][j] = KeySta[i][j];     //ˢ��ǰһ�εı���ֵ
            }
        }
    }
}

/* ����ɨ�躯�������ڶ�ʱ�ж��е��ã��Ƽ����ü��1ms */
void KeyScan()
{
    unsigned char i;
    static unsigned char keyout = 0;   //���󰴼�ɨ���������
    static unsigned char keybuf[4][4] = {  //���󰴼�ɨ�軺����
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF}
    };

    //��һ�е�4������ֵ���뻺����
    keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
    keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
    keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
    keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
    //��������°���״̬
    for (i=0; i<4; i++)  //ÿ��4������������ѭ��4��
    {
        if ((keybuf[keyout][i] & 0x0F) == 0x00)
        {   //����4��ɨ��ֵΪ0����4*4ms�ڶ��ǰ���״̬ʱ������Ϊ�������ȶ��İ���
            KeySta[keyout][i] = 0;
        }
        else if ((keybuf[keyout][i] & 0x0F) == 0x0F)
        {   //����4��ɨ��ֵΪ1����4*4ms�ڶ��ǵ���״̬ʱ������Ϊ�������ȶ��ĵ���
            KeySta[keyout][i] = 1;
        }
    }
    //ִ����һ�ε�ɨ�����
    keyout++;                //�����������
    keyout = keyout & 0x03;  //����ֵ�ӵ�4������
    switch (keyout)          //�����������ͷŵ�ǰ������ţ������´ε��������
    {
        case 0: KEY_OUT_4 = 1; KEY_OUT_1 = 0; break;
        case 1: KEY_OUT_1 = 1; KEY_OUT_2 = 0; break;
        case 2: KEY_OUT_2 = 1; KEY_OUT_3 = 0; break;
        case 3: KEY_OUT_3 = 1; KEY_OUT_4 = 0; break;
        default: break;
    }
}

/* ����ܶ�̬ɨ��ˢ�º��������ڶ�ʱ�ж��е��� */
void LedScan()
{
    static unsigned char i = 0;  //��̬ɨ�������
    
    P0 = 0xFF;   //��ʾ����
    switch (i)
    {
        //���󲿷�
        case 0: ADDR3 = 0; ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=image[index+0]; break;
        case 1: ADDR3 = 0; ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=image[index+1]; break;
        case 2: ADDR3 = 0; ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=image[index+2]; break;
        case 3: ADDR3 = 0; ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=image[index+3]; break;
        case 4: ADDR3 = 0; ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=image[index+4]; break;
        case 5: ADDR3 = 0; ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=image[index+5]; break;
        case 6: ADDR3 = 0; ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=image[index+6]; break;
        case 7: ADDR3 = 0; ADDR2=1; ADDR1=1; ADDR0=1; i++; P0=image[index+7]; break;
        //����ܲ���
        case 8:  ADDR3 = 1; ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=LedBuff[0]; break;
        case 9:  ADDR3 = 1; ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=LedBuff[1]; break;
        case 10: ADDR3 = 1; ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=LedBuff[2]; break;
        case 11: ADDR3 = 1; ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=LedBuff[3]; break;
        case 12: ADDR3 = 1; ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=LedBuff[4]; break;
        case 13: ADDR3 = 1; ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=LedBuff[5]; break;
        //��ˮ�Ʋ���
        case 14: ADDR3 = 1; ADDR2=1; ADDR1=1; ADDR0=0; i=0; P0=WaterChar[Water_flag]; break;
        default: break;
    }
}
/* T0�жϷ������������������ʾɨ���밴��ɨ�� */
void InterruptTimer0() interrupt 1
{
	static unsigned int tmr1 = 0;  //1�붨ʱ��
	static unsigned int tmr2 = 0;  //250ms��ʱ��
    
    tmr1++;
    tmr2++;
    
    if (tmr1 >= 1000)
    {
		flag1s = 1;		//1�붨ʱ��־��1
        tmr1 = 0;
        switch (Water_flag)	//��ˮ���л�
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
        if (index <= 0) // ͼƬ�������� 0 ��ԭ
        {
            index = 16;
        }
    }
    
    TH0 = 0xFC;  //���¼��س�ֵ
    TL0 = 0x67;
    LedScan();   //�����������ʾɨ�躯��
    KeyScan();   //���ð���ɨ�躯��
}
