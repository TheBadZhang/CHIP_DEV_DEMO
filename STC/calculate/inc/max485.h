extern void UartAction(unsigned char *buf, unsigned char len);
/* 串口配置函数，baud-通信波特率 */
void ConfigUART(unsigned int baud) {
	RS485_DIR = 0;							 //RS485 设置为接收方向
	SCON = 0x50;							 //配置串口为模式 1
	TMOD &= 0x0F;							 //清零 T1 的控制位
	TMOD |= 0x20;							 //配置 T1 为模式 2
	TH1 = 256 - (11059200 / 12 / 32) / baud; //计算 T1 重载值
	TL1 = TH1;								 //初值等于重载值
	ET1 = 0;								 //禁止 T1 中断
	ES = 1;									 //使能串口中断
	TR1 = 1;								 //启动 T1
}
/* 串口数据写入，即串口发送函数，buf-待发送数据的指针，len-指定的发送长度 */
void UartWrite(unsigned char *buf, unsigned char len) {
	RS485_DIR = 1; //RS485 设置为发送
	while (len--) { //循环发送所有字节

		flagTxd = 0;   //清零发送标志
		SBUF = *buf++; //发送一个字节数据
		while (!flagTxd)
			; //等待该字节发送完成
	}
	delay(5); //等待最后的停止位完成，延时时间由波特率决定
	RS485_DIR = 0; //RS485 设置为接收
}
/* 串口数据读取函数，buf-接收指针，len-指定的读取长度，返回值-实际读到的长度 */
unsigned char UartRead(unsigned char *buf, unsigned char len) {

	unsigned char i;
	if (len > cntRxd) {//指定读取长度大于实际接收到的数据长度时，
					  //读取长度设置为实际接收到的数据长度
		len = cntRxd;
	}
	FOR (i,len) {//拷贝接收到的数据到接收指针上
		*buf++ = bufRxd[i];
	}
	cntRxd = 0; //接收计数器清零
	return len; //返回实际读取长度
}
/* 串口接收监控，由空闲时间判定帧结束，需在定时中断中调用，ms-定时间隔 */
void UartRxMonitor(unsigned char ms) {
	static unsigned char cntbkp = 0;
	static unsigned char idletmr = 0;
	if (cntRxd > 0) {//接收计数器大于零时，监控总线空闲时间
		if (cntbkp != cntRxd) {//接收计数器改变，即刚接收到数据时，清零空闲计时
			cntbkp = cntRxd;
			idletmr = 0;
		} else {//接收计数器未改变，即总线空闲时，累积空闲时间
			if (idletmr < 30) {//空闲计时小于 30ms 时，持续累加
				idletmr += ms;
				if (idletmr >= 30) {//空闲时间达到 30ms 时，即判定为一帧接收完毕
					flagFrame = 1; //设置帧接收完成标志
				}
			}
		}
	} else {
		cntbkp = 0;
	}
}
/* 串口驱动函数，监测数据帧的接收，调度功能函数，需在主循环中调用 */
void UartDriver() {
	unsigned char len;
	unsigned char pdata buf[40];
	if (flagFrame) {//有命令到达时，读取处理该命令
		flagFrame = 0;
		len = UartRead(buf, sizeof(buf) - 2); //将接收到的命令读取到缓冲区中
		UartAction(buf, len);				  //传递数据帧，调用动作执行函数
	}
}
/* 串口中断服务函数 */
void InterruptUART() interrupt 4 {

	if (RI) {//接收到新字节
		RI = 0;						 //清零接收中断标志位
		if (cntRxd < sizeof(bufRxd)) {//接收缓冲区尚未用完时，
									 //保存接收字节，并递增计数器
			bufRxd[cntRxd++] = SBUF;
		}
	}
	if (TI) {//字节发送完毕
		TI = 0;		 //清零发送中断标志位
		flagTxd = 1; //设置字节发送完成标志
	}
}