#include <8052.h>

void configUART (unsigned int baud) {
    SCON  = 0x50;
    TMOD &= 0x0f;
    TMOD |= 0x20;
    TH1 = 0xff - (11059200/12/32)/baud;
    TL1 = TH1;
    ET1 = 0;
    ES = 1;
    TR1 = 1;
}

void main () {
    EA = 1;
    configUART (9600);
    while (1);
}

void interruptUART (void) __interrupt 4 {
    if (RI) {
        RI = 0;
        SBUF = SBUF + 1;
    }
    if (TI) {
        TI = 0;
    }
}