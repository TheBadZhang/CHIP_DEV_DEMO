
#include <8052.h>

#define PIN_RXD P3_0  //�������Ŷ���
#define PIN_TXD P3_1  //�������Ŷ���

char RxdOrTxd = 0;  //ָʾ��ǰ״̬Ϊ���ջ��Ƿ���
char RxdEnd = 0;    //���ս�����־
char TxdEnd = 0;    //���ͽ�����־
unsigned char RxdBuf = 0;  //���ջ�����
unsigned char TxdBuf = 0;  //���ͻ�����
void InterruptTimer0(void) __interrupt (1);
void ConfigUART(unsigned int baud);
void StartTXD(unsigned char dat);
void StartRXD();

void main()
{
    EA = 1;   //�����ж�
    ConfigUART(9600);  //���ò�����Ϊ9600
    
    while (1)
    {
        while (PIN_RXD);    //�ȴ��������ų��ֵ͵�ƽ������ʼλ
        StartRXD();         //��������
        while (!RxdEnd);    //�ȴ��������
        StartTXD(RxdBuf+1); //���յ�������+1�󣬷��ͻ�ȥ
        while (!TxdEnd);    //�ȴ��������
    }
}
/* �������ú�����baud-ͨ�Ų����� */
void ConfigUART(unsigned int baud)
{
    TMOD &= 0xF0;   //����T0�Ŀ���λ
    TMOD |= 0x02;   //����T0Ϊģʽ2
    TH0 = 256 - (11059200/12)/baud;  //����T0����ֵ
}
/* �������н��� */
void StartRXD()
{
    TL0 = 256 - ((256-TH0)>>1);  //��������ʱ��T0��ʱΪ�������������
    ET0 = 1;        //ʹ��T0�ж�
    TR0 = 1;        //����T0
    RxdEnd = 0;     //������ս�����־
    RxdOrTxd = 0;   //���õ�ǰ״̬Ϊ����
}
/* �������з��ͣ�dat-�������ֽ����� */
void StartTXD(unsigned char dat)
{
    TxdBuf = dat;   //���������ݱ��浽���ͻ�����
    TL0 = TH0;      //T0������ֵΪ����ֵ
    ET0 = 1;        //ʹ��T0�ж�
    TR0 = 1;        //����T0
    PIN_TXD = 0;    //������ʼλ
    TxdEnd = 0;     //���㷢�ͽ�����־
    RxdOrTxd = 1;   //���õ�ǰ״̬Ϊ����
}
/* T0�жϷ������������з��ͺͽ��� */
void InterruptTimer0() __interrupt 1
{
    static unsigned char cnt = 0; //λ���ջ��ͼ���
	// P1 = 0;
	// P0 = 0;
    if (RxdOrTxd)  //���з��ʹ���
    {
        cnt++;
        if (cnt <= 8)  //��λ�������η���8bit����λ
        {
            PIN_TXD = TxdBuf & 0x01;
            TxdBuf >>= 1;
        }
        else if (cnt == 9)  //����ֹͣλ
        {
            PIN_TXD = 1;
        }
        else  //���ͽ���
        {
            cnt = 0;    //��λbit������
            TR0 = 0;    //�ر�T0
            TxdEnd = 1; //�÷��ͽ�����־
        }
    }
    else  //���н��մ���
    {
        if (cnt == 0)     //������ʼλ
        {
            if (!PIN_RXD) //��ʼλΪ0ʱ��������ջ�������׼����������λ
            {
                RxdBuf = 0;
                cnt++;
            }
            else          //��ʼλ��Ϊ0ʱ����ֹ����
            {
                TR0 = 0;  //�ر�T0
            }
        }
        else if (cnt <= 8)   //����8λ����λ
        {
            RxdBuf >>= 1;    //��λ���ȣ����Խ�֮ǰ���յ�λ������
            if (PIN_RXD)     //���ս�Ϊ1ʱ�����������λ��1��
            {                //��Ϊ0ʱ�������Ա�����λ���0
                RxdBuf |= 0x80;
            }
            cnt++;
        }
        else  //ֹͣλ����
        {
            cnt = 0;         //��λbit������
            TR0 = 0;         //�ر�T0
            if (PIN_RXD)     //ֹͣλΪ1ʱ��������Ϊ������Ч
            {
                RxdEnd = 1;  //�ý��ս�����־
            }
        }
    }
}
