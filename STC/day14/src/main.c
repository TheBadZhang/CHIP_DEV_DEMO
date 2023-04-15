// #define __TBZ_SSD1306_ENABLE_
#define __TBZ_EFFECT_ENABLE_
#define __TBZ_KEYBOARD_ENABLE_
#define __TBZ_I2C_ENABLE_
#define __TBZ_LED7SEG_ENABLE_
#define __TBZ_SSD1306_ENABLE_
#include "myheader.h"

char toUp = 1;
char addr = OLED_ADDR;
int result = 0;
unsigned char func (char x, char y) __reentrant {
	if (y&1) return rand ();
	else return 0x00;
}

void main () {
		u8 t;
	 	t=' ';
	OLED_Init ();
	// OLED_Display_On ();
	// P1=0xe;
	while (1) {
		// OLED_Fill (func);
		OLED_Fill (func);
	// 		OLED_ShowString(0,0,"I T",16); 
	// 		OLED_ShowCHinese(30,0,0);//陈
	// 		OLED_ShowCHinese(46,0,1);//笑
	// 		OLED_ShowCHinese(62,0,1);//笑
	// 		// OLED_ShowCHinese(30,16,5);//張
	// 		// OLED_ShowCHinese(46,16,6);//樂
	// 		// OLED_ShowCHinese(62,16,7);//輝
		
	// 		OLED_ShowString(0,3,"0.96' OLED",16);
	// 		OLED_ShowString(0,6,"ASCII:",16);  
	// 		OLED_ShowString(63,6,"CODE:",16);  
	// 		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
	// 		t++;
	// 		if(t>'~')
	// 		{
	// 				t=' ';
	// 		}
			
	// 		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			Delay_1ms(100);
	}
}