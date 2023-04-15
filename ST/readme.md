
为了缩减代码库体积，我将所有可生成的文件都删除了
其中 main.c 中需要添加 `#include "core.h"` 并在 `while(true)` 前添加 `core();`
才能够正常编译

需要手动在 eide 中链接生成的 .ld 文件（这一步可能不需要，eide项目文件中保留了这部分的配置
并将 .s 文件放入 Driver 文件夹中