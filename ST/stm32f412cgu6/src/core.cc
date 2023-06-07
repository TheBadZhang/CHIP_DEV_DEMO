#include "core.h"
#include "common.h"
#include <cstring>
#include "lua.hpp"
#include "tinyexpr.h"
// uint8_t uart1_rxbuf[10];                // 用于存放接收到的数据
char str[3][60];
#define A(a) ((int)a)/100
#define B(b) ((int)b)%100

const char lua_test[] = {
	"print(\"Hello,I am lua!\\n--this is newline printf\")\n"
	"function foo()\n"
	"  local i = 0\n"
	"  local sum = 1\n"
	"  while i <= 10 do\n"
	"    sum = sum * 2\n"
	"    i = i + 1\n"
	"  end\n"
	"return sum\n"
	"end\n"
	"print(\"sum =\", foo())\n"
	"print(\"and sum = 2^11 =\", 2 ^ 11)\n"
	"print(\"exp(200) =\", math.exp(200))\n"
};


static int do_file_script(void) {
	lua_State *L;
	L = luaL_newstate(); /* 建立Lua运行环境 */
	luaL_openlibs(L);
	luaopen_base(L);
	luaL_dostring(L, lua_test); /* 运行Lua脚本 */
	lua_close(L);
	return 0;
}

void core(void) {

	U8G2_SH1107_64X128_1_HW_I2C u8g2(U8G2_R1);
	u8g2.setFont(u8g2_font_6x13_tf);
	u8g2.begin();

	do_file_script();


    int error;

    int a = (int)te_interp("(5+5)", 0); /* Returns 10. */
    int b = (int)te_interp("(5+5)", &error); /* Returns 10, error is set to 0. */
    int c = (int)te_interp("(5+5", &error);

	while (true) {

		u8g2_SetContrast(&u8g2, 255);
		u8g2.clearBuffer();

		u8g2.sendBuffer();

		HAL_SPI_Transmit(&hspi1, (uint8_t *)str, a, 1000);
		// u8g22.sendBuffer();
		flip(LED);
	}

}