#ifndef __TBZ_CH9329_H_
#define __TBZ_CH9329_H_

#define CMD_GET_INFO  0x01
/*获取芯片版本等信息
通过该命令向芯片获取版本号、
USB 枚举状态、键盘大小写指示灯
状态等信息*/
#define CMD_SEND_KB_GENERAL_DATA  0x02
发送 B USB  键盘普通数据 通过该命令向芯片发送普通键盘数据包，模拟普通按键按下或释放 动作
#define CMD_SEND_KB_MEDIA_DATA  0x03
发送 B USB  键盘多媒体数据通过该命令向芯片发送多媒体键盘数据包，模拟多媒体按键按下或释放动作
#define CMD_SEND_MS_ABS_DATA  0x04
发送 B USB  绝对鼠标数据通过该命令向芯片发送绝对鼠标数据包，模拟绝对鼠标相关动作
#define CMD_SEND_MS_REL_DATA  0x05
发送 B USB  相对鼠标数据通过该命令向芯片发送相对鼠标数据包，模拟相对鼠标相关动作
#define CMD_SEND_MY_HID_DATA  0x06
发送 B USB  自定义 D HID  设备数据通过该命令向芯片发送自定义 HID类设备数据包
#define CMD_READ_MY_HID_DATA  0x87
读取 B USB  自定义 D HID  设备数据通过该命令从芯片读取自定义 HID类设备数据包注：PC 机向芯片下传 1 包自定义HID 数据包后，由芯片串口自动打包发送给外围串口设备
#define CMD_GET_PARA_CFG  0x08
获取参数配置通过该命令向芯片获取当前参数配置信息
#define CMD_SET_PARA_CFG  0x09
设置参数配置通过该命令向芯片设置当前参数配置信息
#define CMD_GET_USB_STRING  0x0A
获取字符串描述符配置通过该命令向芯片获取当前所使用的 USB 字符串描述符配置
#define CMD_SET_USB_STRING  0x0B  设置字符串描述符配置通过该命令向芯片设置当前所使用的 USB 字符串描述符配置
#define CMD_SET_DEFAULT_CFG  0x0C恢复出厂默认配置通过该命令将芯片的参数配置及字符串配置信息恢复到出厂默认设置
#define CMD_RESET  0x0F复位芯片通过该命令控制芯片进行软件复位控制

#endif