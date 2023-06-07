#include "core.h"
#include "common.h"
// #include "blua.h"
#include "lua.hpp"
#include <cstring>
#include "tinyexpr.h"
#include "trick.h"


int lua_flip_LED1(lua_State *L) {
	flip(LED);
	return 0;
}

int another_delay (lua_State *L) {
	int n = luaL_checkinteger(L, 1); /* get argument */
	HAL_Delay(n);
	return 0;
}

int uart_send(lua_State* L) {
	char* str = (char*)luaL_checkstring(L, 1);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 0xffff);
	return 0;
}
void core(void) {

	auto L = luaL_newstate();
	// bLua::reg_global_func(L, "flip_LED1", lua_flip_LED1);
	// bLua::reg_global_func(L, "delay", HAL_Delay);
	luaL_openlibs(L);

	lua_register(L, "flip_LED1", lua_flip_LED1);
	lua_register(L, "delay", another_delay);
	lua_register(L, "uart_send", uart_send);

	const char* test = "flip_LED1()" \
	" uart_send(string.format(\"%f\",math.log(12)))" \
	" delay(500)" \
	;

    // int error;

	// char result[100] = "hello world\n";

	// 如果真的在单片机里面嵌入了 lua 语言，那为什么我还需要 tinyexpr 呢
	// 应当是单独使用 tinyexpr 才有一定的意义
    // int a = (int)te_interp("(5+5)", 0); /* Returns 10. */
    // int b = (int)te_interp("(5+5)", &error); /* Returns 10, error is set to 0. */
    // int c = (int)te_interp("(5+5", &error);
	// sprintf(result, "%d\n",(int)te_interp("(5+5)", 0));
	while (true) {
		// flip(LED);
		if (luaL_dostring(L, test) != LUA_OK) {
			char* err = (char*)lua_tostring(L, -1);
			HAL_UART_Transmit(&huart1, (uint8_t*)err, strlen(err), 0xffff);
			HAL_UART_Transmit(&huart1, (uint8_t*)"\n", 1, 0xffff);
		}
		// HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		// HAL_UART_Transmit(&huart1, (uint8_t*)result, strlen(result), 0xffff);
		// HAL_Delay(500);
	}
}