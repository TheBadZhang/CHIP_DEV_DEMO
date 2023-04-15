#ifndef __STC8F_H__
#define __STC8F_H__

/////////////////////////////////////////////////

__sfr __at (0xC8) T2CON ;
/* T2CON bits */
__sbit __at (0xC8) T2CON_0 ;
__sbit __at (0xC9) T2CON_1 ;
__sbit __at (0xCA) T2CON_2 ;
__sbit __at (0xCB) T2CON_3 ;
__sbit __at (0xCC) T2CON_4 ;
__sbit __at (0xCD) T2CON_5 ;
__sbit __at (0xCE) T2CON_6 ;
__sbit __at (0xCF) T2CON_7 ;
//内核特殊功能寄存器
__sfr __at (0xe0)   ACC   ;
__sfr __at (0xf0)   B     ;
__sfr __at (0xd0)   PSW   ;
__sbit  __at (PSW+7)   CY  ;
__sbit  __at (PSW+6)   AC  ;
__sbit  __at (PSW+5)   F0  ;
__sbit  __at (PSW+4)   RS1 ;
__sbit  __at (PSW+3)   RS0 ;
__sbit  __at (PSW+2)   OV  ;
__sbit  __at (PSW+1)   F1  ;
__sbit  __at (PSW+0)   P   ;
__sfr __at (0x81)   SP    ;
__sfr __at (0x82)   DPL   ;
__sfr __at (0x83)   DPH   ;
__sfr __at (0xae)   TA    ;
__sfr __at (0xe3)   DPS   ;
__sfr __at (0xe4)   DPL1  ;
__sfr __at (0xe5)   DPH1  ;


//I/O 口特殊功能寄存器
__sfr __at (0x80) P0   ;
__sfr __at (0x90) P1   ;
__sfr __at (0xa0) P2   ;
__sfr __at (0xb0) P3   ;
__sfr __at (0xc0) P4   ;
__sfr __at (0xc8) P5   ;
__sfr __at (0xe8) P6   ;
__sfr __at (0xf8) P7   ;
__sfr __at (0x94) P0M0 ;
__sfr __at (0x93) P0M1 ;
__sfr __at (0x92) P1M0 ;
__sfr __at (0x91) P1M1 ;
__sfr __at (0x96) P2M0 ;
__sfr __at (0x95) P2M1 ;
__sfr __at (0xb2) P3M0 ;
__sfr __at (0xb1) P3M1 ;
__sfr __at (0xb4) P4M0 ;
__sfr __at (0xb3) P4M1 ;
__sfr __at (0xca) P5M0 ;
__sfr __at (0xc9) P5M1 ;
__sfr __at (0xcc) P6M0 ;
__sfr __at (0xcb) P6M1 ;
__sfr __at (0xe2) P7M0 ;
__sfr __at (0xe1) P7M1 ;

__sbit __at (P0+0) P00 ;
__sbit __at (P0+1) P01 ;
__sbit __at (P0+2) P02 ;
__sbit __at (P0+3) P03 ;
__sbit __at (P0+4) P04 ;
__sbit __at (P0+5) P05 ;
__sbit __at (P0+6) P06 ;
__sbit __at (P0+7) P07 ;
__sbit __at (P1+0) P10 ;
__sbit __at (P1+1) P11 ;
__sbit __at (P1+2) P12 ;
__sbit __at (P1+3) P13 ;
__sbit __at (P1+4) P14 ;
__sbit __at (P1+5) P15 ;
__sbit __at (P1+6) P16 ;
__sbit __at (P1+7) P17 ;
__sbit __at (P2+0) P20 ;
__sbit __at (P2+1) P21 ;
__sbit __at (P2+2) P22 ;
__sbit __at (P2+3) P23 ;
__sbit __at (P2+4) P24 ;
__sbit __at (P2+5) P25 ;
__sbit __at (P2+6) P26 ;
__sbit __at (P2+7) P27 ;
__sbit __at (P3+0) P30 ;
__sbit __at (P3+1) P31 ;
__sbit __at (P3+2) P32 ;
__sbit __at (P3+3) P33 ;
__sbit __at (P3+4) P34 ;
__sbit __at (P3+5) P35 ;
__sbit __at (P3+6) P36 ;
__sbit __at (P3+7) P37 ;
__sbit __at (P4+0) P40 ;
__sbit __at (P4+1) P41 ;
__sbit __at (P4+2) P42 ;
__sbit __at (P4+3) P43 ;
__sbit __at (P4+4) P44 ;
__sbit __at (P4+5) P45 ;
__sbit __at (P4+6) P46 ;
__sbit __at (P4+7) P47 ;
__sbit __at (P5+0) P50 ;
__sbit __at (P5+1) P51 ;
__sbit __at (P5+2) P52 ;
__sbit __at (P5+3) P53 ;
__sbit __at (P5+4) P54 ;
__sbit __at (P5+5) P55 ;
__sbit __at (P5+6) P56 ;
__sbit __at (P5+7) P57 ;
__sbit __at (P6+0) P60 ;
__sbit __at (P6+1) P61 ;
__sbit __at (P6+2) P62 ;
__sbit __at (P6+3) P63 ;
__sbit __at (P6+4) P64 ;
__sbit __at (P6+5) P65 ;
__sbit __at (P6+6) P66 ;
__sbit __at (P6+7) P67 ;
__sbit __at (P7+0) P70 ;
__sbit __at (P7+1) P71 ;
__sbit __at (P7+2) P72 ;
__sbit __at (P7+3) P73 ;
__sbit __at (P7+4) P74 ;
__sbit __at (P7+5) P75 ;
__sbit __at (P7+6) P76 ;
__sbit __at (P7+7) P77 ;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define P0PU        (*(unsigned char volatile xdata *)0xfe10)
#define P1PU        (*(unsigned char volatile xdata *)0xfe11)
#define P2PU        (*(unsigned char volatile xdata *)0xfe12)
#define P3PU        (*(unsigned char volatile xdata *)0xfe13)
#define P4PU        (*(unsigned char volatile xdata *)0xfe14)
#define P5PU        (*(unsigned char volatile xdata *)0xfe15)
#define P6PU        (*(unsigned char volatile xdata *)0xfe16)
#define P7PU        (*(unsigned char volatile xdata *)0xfe17)
#define P0NCS       (*(unsigned char volatile xdata *)0xfe18)
#define P1NCS       (*(unsigned char volatile xdata *)0xfe19)
#define P2NCS       (*(unsigned char volatile xdata *)0xfe1a)
#define P3NCS       (*(unsigned char volatile xdata *)0xfe1b)
#define P4NCS       (*(unsigned char volatile xdata *)0xfe1c)
#define P5NCS       (*(unsigned char volatile xdata *)0xfe1d)
#define P6NCS       (*(unsigned char volatile xdata *)0xfe1e)
#define P7NCS       (*(unsigned char volatile xdata *)0xfe1f)

//系统管理特殊功能寄存器
__sfr __at (0x87) PCON ;
#define SMOD        0x80
#define SMOD0       0x40
#define LVDF        0x20
#define POF         0x10
#define GF1         0x08
#define GF0         0x04
#define PD          0x02
#define IDL         0x01
__sfr __at (0x8e) AUXR ;
#define T0x12       0x80
#define T1x12       0x40
#define UART_M0x6   0x20
#define T2R         0x10
#define T2_CT       0x08
#define T2x12       0x04
#define EXTRAM      0x02
#define S1ST2       0x01
__sfr __at (0x97) AUXR2 ;
#define TXLNRX      0x10
__sfr __at (0xa1) BUS_SP;
__sfr __at (0xa2) P_SW1 ;
__sfr __at (0xba) P_SW2 ;
#define EAXFR       0x80
__sfr __at (0xbb) VOCTRL;
__sfr __at (0xff) RSTCFG;

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define CKSEL       (*(unsigned char volatile xdata *)0xfe00)
#define CLKDIV      (*(unsigned char volatile xdata *)0xfe01)
#define IRC24MCR    (*(unsigned char volatile xdata *)0xfe02)
#define XOSCCR      (*(unsigned char volatile xdata *)0xfe03)
#define IRC32KCR    (*(unsigned char volatile xdata *)0xfe04)

//中断特殊功能寄存器
__sfr __at (0xa8) IE ;
__sbit __at (IE+7) EA   ;
__sbit __at (IE+6) ELVD ;
__sbit __at (IE+5) EADC ;
__sbit __at (IE+4) ES   ;
__sbit __at (IE+3) ET1  ;
__sbit __at (IE+2) EX1  ;
__sbit __at (IE+1) ET0  ;
__sbit __at (IE+0) EX0  ;
__sfr __at (0xaf) IE2 ;
#define ET4         0x40
#define ET3         0x20
#define ES4         0x10
#define ES3         0x08
#define ET2         0x04
#define ESPI        0x02
#define ES2         0x01
sfr IP          =   0xb8;
sbit PPCA       =   IP^7;
sbit PLVD       =   IP^6;
sbit PADC       =   IP^5;
sbit PS         =   IP^4;
sbit PT1        =   IP^3;
sbit PX1        =   IP^2;
sbit PT0        =   IP^1;
sbit PX0        =   IP^0;
sfr IP2         =   0xb5;
#define PI2C        0x40
#define PCMP        0x20
#define PX4         0x10
#define PPWMFD      0x08
#define PPWM        0x04
#define PSPI        0x02
#define PS2         0x01
sfr IPH         =   0xb7;
#define PPCAH       0x80
#define PLVDH       0x40
#define PADCH       0x20
#define PSH         0x10
#define PT1H        0x08
#define PX1H        0x04
#define PT0H        0x02
#define PX0H        0x01
sfr IP2H        =   0xb6;
#define PI2CH       0x40
#define PCMPH       0x20
#define PX4H        0x10
#define PPWMFDH     0x08
#define PPWMH       0x04
#define PSPIH       0x02
#define PS2H        0x01
sfr INTCLKO     =   0x8f;
#define EX4         0x40
#define EX3         0x20
#define EX2         0x10
#define T2CLKO      0x04
#define T1CLKO      0x02
#define T0CLKO      0x01
sfr AUXINTIF    =   0xef;
#define INT4IF      0x40
#define INT3IF      0x20
#define INT2IF      0x10
#define T4IF        0x04
#define T3IF        0x02
#define T2IF        0x01

//定时器特殊功能寄存器
sfr TCON        =   0x88;
sbit TF1        =   TCON^7;
sbit TR1        =   TCON^6;
sbit TF0        =   TCON^5;
sbit TR0        =   TCON^4;
sbit IE1        =   TCON^3;
sbit IT1        =   TCON^2;
sbit IE0        =   TCON^1;
sbit IT0        =   TCON^0;
sfr TMOD        =   0x89;
#define T1_GATE     0x80
#define T1_CT       0x40
#define T1_M1       0x20
#define T1_M0       0x10
#define T0_GATE     0x08
#define T0_CT       0x04
#define T0_M1       0x02
#define T0_M0       0x01
sfr TL0         =   0x8a;
sfr TL1         =   0x8b;
sfr TH0         =   0x8c;
sfr TH1         =   0x8d;
sfr T4T3M       =   0xd1;
#define T4R         0x80
#define T4_CT       0x40
#define T4x12       0x20
#define T4CLKO      0x10
#define T3R         0x08
#define T3_CT       0x04
#define T3x12       0x02
#define T3CLKO      0x01
sfr T4H         =   0xd2;
sfr T4L         =   0xd3;
sfr T3H         =   0xd4;
sfr T3L         =   0xd5;
sfr T2H         =   0xd6;
sfr T2L         =   0xd7;
sfr TH4         =   0xd2;
sfr TL4         =   0xd3;
sfr TH3         =   0xd4;
sfr TL3         =   0xd5;
sfr TH2         =   0xd6;
sfr TL2         =   0xd7;
sfr WKTCL       =   0xaa;
sfr WKTCH       =   0xab;
#define WKTEN       0x80
sfr WDT_CONTR   =   0xc1;
#define WDT_FLAG    0x80
#define EN_WDT      0x20
#define CLR_WDT     0x10
#define IDL_WDT     0x08

//串行口特殊功能寄存器
sfr SCON        =   0x98;
sbit SM0        =   SCON^7;
sbit SM1        =   SCON^6;
sbit SM2        =   SCON^5;
sbit REN        =   SCON^4;
sbit TB8        =   SCON^3;
sbit RB8        =   SCON^2;
sbit TI         =   SCON^1;
sbit RI         =   SCON^0;
sfr SBUF        =   0x99;
sfr S2CON       =   0x9a;
#define S2SM0       0x80
#define S2ST4       0x40
#define S2SM2       0x20
#define S2REN       0x10
#define S2TB8       0x08
#define S2RB8       0x04
#define S2TI        0x02
#define S2RI        0x01
sfr S2BUF       =   0x9b;
sfr S3CON       =   0xac;
#define S3SM0       0x80
#define S3ST4       0x40
#define S3SM2       0x20
#define S3REN       0x10
#define S3TB8       0x08
#define S3RB8       0x04
#define S3TI        0x02
#define S3RI        0x01
sfr S3BUF       =   0xad;
sfr S4CON       =   0x84;
#define S4SM0       0x80
#define S4ST4       0x40
#define S4SM2       0x20
#define S4REN       0x10
#define S4TB8       0x08
#define S4RB8       0x04
#define S4TI        0x02
#define S4RI        0x01
sfr S4BUF       =   0x85;
sfr SADDR       =   0xa9;
sfr SADEN       =   0xb9;

//ADC 特殊功能寄存器
sfr ADC_CONTR   =   0xbc;
#define ADC_POWER   0x80
#define ADC_START   0x40
#define ADC_FLAG    0x20
sfr ADC_RES     =   0xbd;
sfr ADC_RESL    =   0xbe;
sfr ADCCFG      =   0xde;
#define ADC_RESFMT  0x20

//SPI 特殊功能寄存器
sfr SPSTAT      =   0xcd;
#define SPIF        0x80
#define WCOL        0x40
sfr SPCTL       =   0xce;
#define SSIG        0x80
#define SPEN        0x40
#define DORD        0x20
#define MSTR        0x10
#define CPOL        0x08
#define CPHA        0x04
sfr SPDAT       =   0xcf;

//IAP/ISP 特殊功能寄存器
sfr IAP_DATA    =   0xc2;
sfr IAP_ADDRH   =   0xc3;
sfr IAP_ADDRL   =   0xc4;
sfr IAP_CMD     =   0xc5;
#define IAP_IDL     0x00
#define IAP_READ    0x01
#define IAP_WRITE   0x02
#define IAP_ERASE   0x03
sfr IAP_TRIG    =   0xc6;
sfr IAP_CONTR   =   0xc7;
#define IAPEN       0x80
#define SWBS        0x40
#define SWRST       0x20
#define CMD_FAIL    0x10
sfr ISP_DATA    =   0xc2;
sfr ISP_ADDRH   =   0xc3;
sfr ISP_ADDRL   =   0xc4;
sfr ISP_CMD     =   0xc5;
sfr ISP_TRIG    =   0xc6;
sfr ISP_CONTR   =   0xc7;

//比较器特殊功能寄存器
sfr CMPCR1      =   0xe6;
#define CMPEN       0x80
#define CMPIF       0x40
#define PIE         0x20
#define NIE         0x10
#define PIS         0x08
#define NIS         0x04
#define CMPOE       0x02
#define CMPRES      0x01
sfr CMPCR2      =   0xe7;
#define INVCMPO     0x80
#define DISFLT      0x40

//PCA/PWM 特殊功能寄存器
sfr CCON        =   0xd8;
sbit CF         =   CCON^7;
sbit CR         =   CCON^6;
sbit CCF3       =   CCON^3;
sbit CCF2       =   CCON^2;
sbit CCF1       =   CCON^1;
sbit CCF0       =   CCON^0;
sfr CMOD        =   0xd9;
#define CIDL        0x80
#define ECF         0x01
sfr CL          =   0xe9;
sfr CH          =   0xf9;
sfr CCAPM0      =   0xda;
#define ECOM0       0x40
#define CCAPP0      0x20
#define CCAPN0      0x10
#define MAT0        0x08
#define TOG0        0x04
#define PWM0        0x02
#define ECCF0       0x01
sfr CCAPM1      =   0xdb;
#define ECOM1       0x40
#define CCAPP1      0x20
#define CCAPN1      0x10
#define MAT1        0x08
#define TOG1        0x04
#define PWM1        0x02
#define ECCF1       0x01
sfr CCAPM2      =   0xdc;
#define ECOM2       0x40
#define CCAPP2      0x20
#define CCAPN2      0x10
#define MAT2        0x08
#define TOG2        0x04
#define PWM2        0x02
#define ECCF2       0x01
sfr CCAPM3      =   0xdd;
#define ECOM3       0x40
#define CCAPP3      0x20
#define CCAPN3      0x10
#define MAT3        0x08
#define TOG3        0x04
#define PWM3        0x02
#define ECCF3       0x01
sfr CCAP0L      =   0xea;
sfr CCAP1L      =   0xeb;
sfr CCAP2L      =   0xec;
sfr CCAP3L      =   0xed;
sfr CCAP0H      =   0xfa;
sfr CCAP1H      =   0xfb;
sfr CCAP2H      =   0xfc;
sfr CCAP3H      =   0xfd;
sfr PCA_PWM0    =   0xf2;
sfr PCA_PWM1    =   0xf3;
sfr PCA_PWM2    =   0xf4;
sfr PCA_PWM3    =   0xf5;

//增强型PWM波形发生器特殊功能寄存器
sfr PWMCFG      =   0xf1;
#define CBIF        0x80
#define ETADC       0x40
sfr PWMIF       =   0xf6;
#define C7IF        0x80
#define C6IF        0x40
#define C5IF        0x20
#define C4IF        0x10
#define C3IF        0x08
#define C2IF        0x04
#define C1IF        0x02
#define C0IF        0x01
sfr PWMFDCR     =   0xf7;
#define INVCMP      0x80
#define INVIO       0x40
#define ENFD        0x20
#define FLTFLIO     0x10
#define EFDI        0x08
#define FDCMP       0x04
#define FDIO        0x02
#define FDIF        0x01
sfr PWMCR       =   0xfe;
#define ENPWM       0x80
#define ECBI        0x40

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define PWMC        (*(unsigned int  volatile xdata *)0xfff0)
#define PWMCH       (*(unsigned char volatile xdata *)0xfff0)
#define PWMCL       (*(unsigned char volatile xdata *)0xfff1)
#define PWMCKS      (*(unsigned char volatile xdata *)0xfff2)
#define TADCP       (*(unsigned char volatile xdata *)0xfff3)
#define TADCPH      (*(unsigned char volatile xdata *)0xfff3)
#define TADCPL      (*(unsigned char volatile xdata *)0xfff4)
#define PWM0T1      (*(unsigned int  volatile xdata *)0xff00)
#define PWM0T1H     (*(unsigned char volatile xdata *)0xff00)
#define PWM0T1L     (*(unsigned char volatile xdata *)0xff01)
#define PWM0T2      (*(unsigned int  volatile xdata *)0xff02)
#define PWM0T2H     (*(unsigned char volatile xdata *)0xff02)
#define PWM0T2L     (*(unsigned char volatile xdata *)0xff03)
#define PWM0CR      (*(unsigned char volatile xdata *)0xff04)
#define PWM0HLD     (*(unsigned char volatile xdata *)0xff05)
#define PWM1T1      (*(unsigned int  volatile xdata *)0xff10)
#define PWM1T1H     (*(unsigned char volatile xdata *)0xff10)
#define PWM1T1L     (*(unsigned char volatile xdata *)0xff11)
#define PWM1T2      (*(unsigned int  volatile xdata *)0xff12)
#define PWM1T2H     (*(unsigned char volatile xdata *)0xff12)
#define PWM1T2L     (*(unsigned char volatile xdata *)0xff13)
#define PWM1CR      (*(unsigned char volatile xdata *)0xff14)
#define PWM1HLD     (*(unsigned char volatile xdata *)0xff15)
#define PWM2T1      (*(unsigned int  volatile xdata *)0xff20)
#define PWM2T1H     (*(unsigned char volatile xdata *)0xff20)
#define PWM2T1L     (*(unsigned char volatile xdata *)0xff21)
#define PWM2T2      (*(unsigned int  volatile xdata *)0xff22)
#define PWM2T2H     (*(unsigned char volatile xdata *)0xff22)
#define PWM2T2L     (*(unsigned char volatile xdata *)0xff23)
#define PWM2CR      (*(unsigned char volatile xdata *)0xff24)
#define PWM2HLD     (*(unsigned char volatile xdata *)0xff25)
#define PWM3T1      (*(unsigned int  volatile xdata *)0xff30)
#define PWM3T1H     (*(unsigned char volatile xdata *)0xff30)
#define PWM3T1L     (*(unsigned char volatile xdata *)0xff31)
#define PWM3T2      (*(unsigned int  volatile xdata *)0xff32)
#define PWM3T2H     (*(unsigned char volatile xdata *)0xff32)
#define PWM3T2L     (*(unsigned char volatile xdata *)0xff33)
#define PWM3CR      (*(unsigned char volatile xdata *)0xff34)
#define PWM3HLD     (*(unsigned char volatile xdata *)0xff35)
#define PWM4T1      (*(unsigned int  volatile xdata *)0xff40)
#define PWM4T1H     (*(unsigned char volatile xdata *)0xff40)
#define PWM4T1L     (*(unsigned char volatile xdata *)0xff41)
#define PWM4T2      (*(unsigned int  volatile xdata *)0xff42)
#define PWM4T2H     (*(unsigned char volatile xdata *)0xff42)
#define PWM4T2L     (*(unsigned char volatile xdata *)0xff43)
#define PWM4CR      (*(unsigned char volatile xdata *)0xff44)
#define PWM4HLD     (*(unsigned char volatile xdata *)0xff45)
#define PWM5T1      (*(unsigned int  volatile xdata *)0xff50)
#define PWM5T1H     (*(unsigned char volatile xdata *)0xff50)
#define PWM5T1L     (*(unsigned char volatile xdata *)0xff51)
#define PWM5T2      (*(unsigned int  volatile xdata *)0xff52)
#define PWM5T2H     (*(unsigned char volatile xdata *)0xff52)
#define PWM5T2L     (*(unsigned char volatile xdata *)0xff53)
#define PWM5CR      (*(unsigned char volatile xdata *)0xff54)
#define PWM5HLD     (*(unsigned char volatile xdata *)0xff55)
#define PWM6T1      (*(unsigned int  volatile xdata *)0xff60)
#define PWM6T1H     (*(unsigned char volatile xdata *)0xff60)
#define PWM6T1L     (*(unsigned char volatile xdata *)0xff61)
#define PWM6T2      (*(unsigned int  volatile xdata *)0xff62)
#define PWM6T2H     (*(unsigned char volatile xdata *)0xff62)
#define PWM6T2L     (*(unsigned char volatile xdata *)0xff63)
#define PWM6CR      (*(unsigned char volatile xdata *)0xff64)
#define PWM6HLD     (*(unsigned char volatile xdata *)0xff65)
#define PWM7T1      (*(unsigned int  volatile xdata *)0xff70)
#define PWM7T1H     (*(unsigned char volatile xdata *)0xff70)
#define PWM7T1L     (*(unsigned char volatile xdata *)0xff71)
#define PWM7T2      (*(unsigned int  volatile xdata *)0xff72)
#define PWM7T2H     (*(unsigned char volatile xdata *)0xff72)
#define PWM7T2L     (*(unsigned char volatile xdata *)0xff73)
#define PWM7CR      (*(unsigned char volatile xdata *)0xff74)
#define PWM7HLD     (*(unsigned char volatile xdata *)0xff75)

//I2C特殊功能寄存器
//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写
#define I2CCFG      (*(unsigned char volatile xdata *)0xfe80)
#define ENI2C       0x80
#define MSSL        0x40
#define I2CMSCR     (*(unsigned char volatile xdata *)0xfe81)
#define EMSI        0x80
#define I2CMSST     (*(unsigned char volatile xdata *)0xfe82)
#define MSBUSY      0x80
#define MSIF        0x40
#define MSACKI      0x02
#define MSACKO      0x01
#define I2CSLCR     (*(unsigned char volatile xdata *)0xfe83)
#define ESTAI       0x40
#define ERXI        0x20
#define ETXI        0x10
#define ESTOI       0x08
#define SLRST       0x01
#define I2CSLST     (*(unsigned char volatile xdata *)0xfe84)
#define SLBUSY      0x80
#define STAIF       0x40
#define RXIF        0x20
#define TXIF        0x10
#define STOIF       0x08
#define TXING       0x04
#define SLACKI      0x02
#define SLACKO      0x01
#define I2CSLADR    (*(unsigned char volatile xdata *)0xfe85)
#define I2CTXD      (*(unsigned char volatile xdata *)0xfe86)
#define I2CRXD      (*(unsigned char volatile xdata *)0xfe87)

/////////////////////////////////////////////////

#endif

