extern void UartAction(unsigned char *buf, unsigned char len);
/* �������ú�����baud-ͨ�Ų����� */
void ConfigUART(unsigned int baud) {
	RS485_DIR = 0;							 //RS485 ����Ϊ���շ���
	SCON = 0x50;							 //���ô���Ϊģʽ 1
	TMOD &= 0x0F;							 //���� T1 �Ŀ���λ
	TMOD |= 0x20;							 //���� T1 Ϊģʽ 2
	TH1 = 256 - (11059200 / 12 / 32) / baud; //���� T1 ����ֵ
	TL1 = TH1;								 //��ֵ��������ֵ
	ET1 = 0;								 //��ֹ T1 �ж�
	ES = 1;									 //ʹ�ܴ����ж�
	TR1 = 1;								 //���� T1
}
/* ��������д�룬�����ڷ��ͺ�����buf-���������ݵ�ָ�룬len-ָ���ķ��ͳ��� */
void UartWrite(unsigned char *buf, unsigned char len) {
	RS485_DIR = 1; //RS485 ����Ϊ����
	while (len--) { //ѭ�����������ֽ�

		flagTxd = 0;   //���㷢�ͱ�־
		SBUF = *buf++; //����һ���ֽ�����
		while (!flagTxd)
			; //�ȴ����ֽڷ������
	}
	delay(5); //�ȴ�����ֹͣλ��ɣ���ʱʱ���ɲ����ʾ���
	RS485_DIR = 0; //RS485 ����Ϊ����
}
/* �������ݶ�ȡ������buf-����ָ�룬len-ָ���Ķ�ȡ���ȣ�����ֵ-ʵ�ʶ����ĳ��� */
unsigned char UartRead(unsigned char *buf, unsigned char len) {

	unsigned char i;
	if (len > cntRxd) {//ָ����ȡ���ȴ���ʵ�ʽ��յ������ݳ���ʱ��
					  //��ȡ��������Ϊʵ�ʽ��յ������ݳ���
		len = cntRxd;
	}
	FOR (i,len) {//�������յ������ݵ�����ָ����
		*buf++ = bufRxd[i];
	}
	cntRxd = 0; //���ռ���������
	return len; //����ʵ�ʶ�ȡ����
}
/* ���ڽ��ռ�أ��ɿ���ʱ���ж�֡���������ڶ�ʱ�ж��е��ã�ms-��ʱ��� */
void UartRxMonitor(unsigned char ms) {
	static unsigned char cntbkp = 0;
	static unsigned char idletmr = 0;
	if (cntRxd > 0) {//���ռ�����������ʱ��������߿���ʱ��
		if (cntbkp != cntRxd) {//���ռ������ı䣬���ս��յ�����ʱ��������м�ʱ
			cntbkp = cntRxd;
			idletmr = 0;
		} else {//���ռ�����δ�ı䣬�����߿���ʱ���ۻ�����ʱ��
			if (idletmr < 30) {//���м�ʱС�� 30ms ʱ�������ۼ�
				idletmr += ms;
				if (idletmr >= 30) {//����ʱ��ﵽ 30ms ʱ�����ж�Ϊһ֡�������
					flagFrame = 1; //����֡������ɱ�־
				}
			}
		}
	} else {
		cntbkp = 0;
	}
}
/* ���������������������֡�Ľ��գ����ȹ��ܺ�����������ѭ���е��� */
void UartDriver() {
	unsigned char len;
	unsigned char pdata buf[40];
	if (flagFrame) {//�������ʱ����ȡ����������
		flagFrame = 0;
		len = UartRead(buf, sizeof(buf) - 2); //�����յ��������ȡ����������
		UartAction(buf, len);				  //��������֡�����ö���ִ�к���
	}
}
/* �����жϷ����� */
void InterruptUART() interrupt 4 {

	if (RI) {//���յ����ֽ�
		RI = 0;						 //��������жϱ�־λ
		if (cntRxd < sizeof(bufRxd)) {//���ջ�������δ����ʱ��
									 //��������ֽڣ�������������
			bufRxd[cntRxd++] = SBUF;
		}
	}
	if (TI) {//�ֽڷ������
		TI = 0;		 //���㷢���жϱ�־λ
		flagTxd = 1; //�����ֽڷ�����ɱ�־
	}
}