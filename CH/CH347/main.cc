#include <Windows.h>
#include "CH347DLL.H"
#include <iostream>
#include <exception>
#include <fmt/core.h>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>

#include <cmath>
#include <cstdlib>
#include <ctime>
ULONG iIndex = 0;
// UCHAR DriverVer[1024];
// UCHAR DLLVer[1024];
// UCHAR bcdDevice[1024];
// UCHAR ChipType[1024];
void getVersion() {
	UCHAR DriverVer = 0, DLLVer = 0, bcdDevice = 0, ChipType = 0;
	// try {
		if (CH347GetVersion(iIndex, &DriverVer, &DLLVer, &bcdDevice, &ChipType) == 1) {
			// printf("%s\n", DriverVer);
			// printf("%x\t%x\t%x\t%x\n", (unsigned long)DriverVer, (unsigned long)DLLVer, (unsigned long)bcdDevice, (unsigned long)ChipType);
			printf("指定操作设备序号：%d\n驱动版本信息: %d\n库版本信息: %d\n设备版本信息: %d\n芯片类型: %d\n",iIndex, DriverVer, DLLVer, bcdDevice, ChipType);
			// std::cout << fmt::format("指定操作设备序号：{:d}\n驱动版本信息: {:x}\n库版本信息: {:x}\n设备版本信息: {:x}\n芯片类型: {:x}\n",
			// 	(int)iIndex, DriverVer, DLLVer, bcdDevice, ChipType);
		} else {
			std::cout << fmt::format("获取版本信息失败\n");
		}
	// } catch (std::exception& e) {
		// std::cout << fmt::format("获取版本信息失败\n");
	// }
}

void getDeviceInfor() {
	mDeviceInforS DeviceInfor;
	if (CH347GetDeviceInfor(iIndex, &DeviceInfor) != 0) {
		std::cout << fmt::format("指定操作设备序号：{}\n设备类型: {:d}\n设备版本信息: {:s}\n设备序列号: {:d}\nUSB产品字符串: {:s}\n",
			iIndex, DeviceInfor.UsbClass, DeviceInfor.DeviceID, DeviceInfor.ChipMode, DeviceInfor.ProductString);
	} else {
		std::cout << fmt::format("获取设备信息失败\n");
	}
}

unsigned char screenBuffer[10240] = {
	#include "pic1.dat"
	// #include "pic2.dat"
};
unsigned char oBuffer[10240] = {0x78,1,2,3,4,5,6,7,8,9,10};
unsigned char iBuffer[10240];

int good_count = 0;
int bad_count = 0;

#define OLED_ADDR 0x78
#define OLED_CMD  0x00
#define OLED_DATA 0x40
#define OLED_MODE 0
// #define OLED_WR_Byte(data, reg) OLED_ADDR, reg, data,

unsigned char init_seq[] = {
	0xAE,//--display off
	0x00,//---set low column address
	0x10,//---set high column address
	0x40,//--set start line address
	0xB0,//--set page address
	0x81,// contract control
	0xFF,//--128
	0xA1,//set segment remap
	0xA6,//--normal / reverse
	0xA8,//--set multiplex ratio(1 to 64)
	0x3F,//--1/32 duty
	0xC8,//Com scan direction
	0xD3,//-set display offset
	0x00,//

	0xD5,//set osc division
	0x80,//

	0xD8,//set area color mode off
	0x05,//

	0xD9,//Set Pre-Charge Period
	0xF1,//

	0xDA,//set com pin configuartion
	0x12,//

	0xDB,//set Vcomh
	0x30,//

	0x8D,//set charge pump enable
	0x14,//

	0xAF//--turn on oled panel
};

void OLED_WriteCmd (unsigned char cmd) {
	oBuffer[0] = OLED_ADDR;
	oBuffer[1] = OLED_CMD;
	oBuffer[2] = cmd;
	if (CH347StreamI2C(iIndex, 3, (PVOID)oBuffer,0, (PVOID)iBuffer) != 0) {
		good_count++;
	} else {
		bad_count++;
	}
}
void OLED_WriteDat (unsigned char dat, unsigned int len = 3) {
	oBuffer[0] = OLED_ADDR;
	oBuffer[1] = OLED_DATA;
	oBuffer[2] = dat;
	if (CH347StreamI2C(iIndex, len, (PVOID)oBuffer,0, (PVOID)iBuffer) != 0) {
		good_count++;
	} else {
		bad_count++;
	}
}
void OLED_WriteDat2 (unsigned char* addr, unsigned int len = 3) {
	oBuffer[0] = OLED_ADDR;
	oBuffer[1] = OLED_DATA;
	for (int i =0; i < len; i++) {
		oBuffer[i+2] = addr[i];
	}
	if (CH347StreamI2C(iIndex, len+2, (PVOID)oBuffer,0, (PVOID)iBuffer) != 0) {
		good_count++;
	} else {
		bad_count++;
	}
}

void OLED_Fill (void) {
	unsigned char m,n;
	for (int m = 0; m < 8; m++) {
		// OLED_WR_Byte(0xb0+m,OLED_CMD);		// ? 0-7
		// OLED_WR_Byte(0x00,OLED_CMD);
		// OLED_WR_Byte(0x10,OLED_CMD);
		// FOR (n, 128) OLED_WR_Byte ((*func)(n, m), OLED_DATA);
		OLED_WriteCmd(0xb0+m);
		OLED_WriteCmd(0x00);
		OLED_WriteCmd(0x10);
		int step = 32;
		for (int n = 0; n < 128/step; n++) {
			// OLED_WriteDat(screenBuffer[m*128+n*step]);
			OLED_WriteDat2(screenBuffer+m*128+n*step,step);
		}
		// OLED_WriteDat2(96);
		// for (int n = 0; n < 128; n++) {
		// 	oBuffer[n] = 0x78;
		// }
		// CH347StreamI2C(iIndex, 128, oBuffer, 0, iBuffer);
	}
}


uint8_t saturated_add(uint8_t val1, int8_t val2) {
	int16_t val1_int = val1;
	int16_t val2_int = val2;
	int16_t tmp = val1_int + val2_int;

	if(tmp > 255) {
		return 255;
	} else if(tmp < 0) {
		return 0;
	} else {
		return tmp;
	}
}


int main () {
	srand(time(NULL));
	// std::cout << "Hello World" << std::endl;
	// while(t)
	// for (int i = 0; i < 1024; i++) {
	// 	screenBuffer[i] = rand()%256;
	// }
	// for (int i = 0; i < 10; i++) {
		// iIndex = i;
		if ((CH347OpenDevice(iIndex) != INVALID_HANDLE_VALUE)) {
			// iIndex = ret;
			// std::cout << " " << std::endl;
			std::cout << fmt::format("打开 CH347T 成功，设备号为{:d}\n", iIndex);
			// CH347CloseDevice(iIndex);
			getVersion();
			getDeviceInfor();
			CH347SetTimeout(iIndex, 2000,2000);
			if (CH347I2C_Set(iIndex, 0b00000011) != 0) {
				std::cout << fmt::format("设置 I2C 成功\n");
			} else {
				std::cout << fmt::format("设置 I2C 失败\n");
			}
			if (CH347I2C_SetDelaymS(iIndex, 1000) != 0) {
				std::cout << fmt::format("设置 I2C 延时成功\n");
			} else {
				std::cout << fmt::format("设置 I2C 延时失败\n");
			}
			// if (CH347StreamI2C(iIndex, 10, (PVOID)oBuffer,0, (PVOID)iBuffer) == 1) {
			// 	std::cout << fmt::format("写入数据成功\n");
			// } else {
			// 	std::cout << fmt::format("写入数据失败\n");
			// }
			for (int i = 0; i < sizeof(init_seq); i++) {
				OLED_WriteCmd(init_seq[i]);
			}
			OLED_Fill();
			std::cout << fmt::format("写入数据成功次数：{:d}\n", good_count);
			std::cout << fmt::format("写入数据失败次数：{:d}\n", bad_count);

			// cv::VideoCapture cap(0);
			cv::VideoCapture cap("./bad_apple.mp4");
			while (true) {
				cv::Mat frame, dithImg;
				cap >> frame;
				cv::resize(frame, frame, cv::Size(128, 64));
				// cv::flip(frame,frame,1);
				// cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);



				cv::cvtColor(frame, dithImg, cv::COLOR_BGR2GRAY);
				int imgWidth = frame.cols;
				int imgHeight = frame.rows;
				int err;
				int8_t a,b,c,d;

				for(int i=0; i<imgHeight; i++)
				{
					for(int j=0; j<imgWidth; j++)
					{
					if(dithImg.at<uint8_t>(i,j) > 127)
					{
						err = dithImg.at<uint8_t>(i,j) - 255;
						dithImg.at<uint8_t>(i,j) = 255;
					}
					else
					{
						err = dithImg.at<uint8_t>(i,j) - 0;
						dithImg.at<uint8_t>(i,j) = 0;
					}

					a = (err * 7) / 16;
					b = (err * 1) / 16;
					c = (err * 5) / 16;
					d = (err * 3) / 16;

					if((i != (imgHeight-1)) && (j != 0) && (j != (imgWidth - 1)))
					{
						dithImg.at<uint8_t>(i+0,j+1) = saturated_add(dithImg.at<uint8_t>(i+0,j+1),a);
						dithImg.at<uint8_t>(i+1,j+1) = saturated_add(dithImg.at<uint8_t>(i+1,j+1),b);
						dithImg.at<uint8_t>(i+1,j+0) = saturated_add(dithImg.at<uint8_t>(i+1,j+0),c);
						dithImg.at<uint8_t>(i+1,j-1) = saturated_add(dithImg.at<uint8_t>(i+1,j-1),d);
					}
					}
				}



				cv::imshow("frame", dithImg);

				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 128; j++) {
						unsigned char c = 0;
						for (int k = 0; k < 8; k++) {
							c |= (dithImg.at<unsigned char>(i*8+k, j) == 0xff) << (k);
						}
						// c = dithImg.at<unsigned char>(i, j);
						screenBuffer[i*128+j] = c;
					}
				}
				OLED_Fill();

				cv::waitKey(10);
			}
			// break;
			CH347CloseDevice(iIndex);
		}
	// }







	return 0;
}