## 说明

**本例程仅适用于 STM32F10x 高密度系列，外部晶振 8MHz**

本例程所用的 STM32 C++ 库：https://github.com/andysworkshop/stm32plus

该项目中 C++ 库已编译成静态库文件(sdk/static_lib/libstm32plus-xx-xx-8000000e.a)，因此此项目中没有关于库的源码

***

### 编译工具

arm-none-eabi-gcc **9-2019-q4**

***

### 用法

- 示例程序位于 examples 目录

- 打开项目资源，将 examples 目录下的示例源文件添加到 Application 中，并移除旧的源文件，重新编译即可

***

### 静态库

项目的 sdk/static_lib 目录下存在 3 种已经编译过的 C++ 库，它们使用了不同的优化指数：

- `libstm32plus-normal-f1hd-8000000e`: -O0 优化

- `libstm32plus-fast-f1hd-8000000e`: -O3 优化

- `libstm32plus-small-f1hd-8000000e`: -Os 优化

可以根据需要选择不同的库，默认为 `libstm32plus-normal-f1hd-8000000e`

要更改所使用的库，请到 `编译器选项 -> Linker` 中更改 `链接库选项`，参数格式：`-l<库名称>`
