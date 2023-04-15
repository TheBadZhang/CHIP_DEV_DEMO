/**
 * 软件 UART：
 *      TX 引脚：P31
 *      波特率：9600
*/

// #include "config.h"
// #include "soft_uart.h"
// #include "delay.h"

#include <8052.h>


__sfr __at (0x91) P1M1 ;
__sfr __at (0x92) P1M0 ;
__sfr __at (0x93) P0M1 ;
__sfr __at (0x94) P0M0 ;

delay (int x) {
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < 10000; j++);
    }
}

void main()
{
    P0M1 = 0x00;
    P0M0 = 0xff;
    P1M1 = 0x00;
    P1M0 = 0xff;
    P0 = 0x01;
    P1 = 0x01;
    while (1)
    {
        // LOG("Hello, STC15F104W\n");
        P0 <<= 1;
        P1 <<= 1;
        if (P0 == 0x00) P0 = 0x01;
        if (P1 == 0x00) P1 = 0x01;
        delay (100);
    }
}
