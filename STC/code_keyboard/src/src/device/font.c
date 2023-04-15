#include "./device/font.h"

//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:12*6
/************************************6*8的点阵************************************/
const unsigned char __code font0608 [][6] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// sp
	{0x00, 0x00, 0x00, 0x2f, 0x00, 0x00},// !
	{0x00, 0x00, 0x07, 0x00, 0x07, 0x00},// "
	{0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14},// #
	{0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12},// $
	{0x00, 0x62, 0x64, 0x08, 0x13, 0x23},// %
	{0x00, 0x36, 0x49, 0x55, 0x22, 0x50},// &
	{0x00, 0x00, 0x05, 0x03, 0x00, 0x00},// '
	{0x00, 0x00, 0x1c, 0x22, 0x41, 0x00},// (
	{0x00, 0x00, 0x41, 0x22, 0x1c, 0x00},// )
	{0x00, 0x14, 0x08, 0x3E, 0x08, 0x14},// *
	{0x00, 0x08, 0x08, 0x3E, 0x08, 0x08},// +
	{0x00, 0x00, 0x00, 0xA0, 0x60, 0x00},// ,
	{0x00, 0x08, 0x08, 0x08, 0x08, 0x08},// -
	{0x00, 0x00, 0x60, 0x60, 0x00, 0x00},// .
	{0x00, 0x20, 0x10, 0x08, 0x04, 0x02},// /
	{0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
	{0x00, 0x00, 0x42, 0x7F, 0x40, 0x00},// 1
	{0x00, 0x42, 0x61, 0x51, 0x49, 0x46},// 2
	{0x00, 0x21, 0x41, 0x45, 0x4B, 0x31},// 3
	{0x00, 0x18, 0x14, 0x12, 0x7F, 0x10},// 4
	{0x00, 0x27, 0x45, 0x45, 0x45, 0x39},// 5
	{0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30},// 6
	{0x00, 0x01, 0x71, 0x09, 0x05, 0x03},// 7
	{0x00, 0x36, 0x49, 0x49, 0x49, 0x36},// 8
	{0x00, 0x06, 0x49, 0x49, 0x29, 0x1E},// 9
	{0x00, 0x00, 0x36, 0x36, 0x00, 0x00},// :
	{0x00, 0x00, 0x56, 0x36, 0x00, 0x00},// ;
	{0x00, 0x08, 0x14, 0x22, 0x41, 0x00},// <
	{0x00, 0x14, 0x14, 0x14, 0x14, 0x14},// =
	{0x00, 0x00, 0x41, 0x22, 0x14, 0x08},// >
	{0x00, 0x02, 0x01, 0x51, 0x09, 0x06},// ?
	{0x00, 0x32, 0x49, 0x59, 0x51, 0x3E},// @
	{0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C},// A
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x36},// B
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x22},// C
	{0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C},// D
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x41},// E
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x01},// F
	{0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A},// G
	{0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F},// 0x
	{0x00, 0x00, 0x41, 0x7F, 0x41, 0x00},// I
	{0x00, 0x20, 0x40, 0x41, 0x3F, 0x01},// J
	{0x00, 0x7F, 0x08, 0x14, 0x22, 0x41},// K
	{0x00, 0x7F, 0x40, 0x40, 0x40, 0x40},// L
	{0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F},// M
	{0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F},// N
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E},// O
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x06},// P
	{0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E},// Q
	{0x00, 0x7F, 0x09, 0x19, 0x29, 0x46},// R
	{0x00, 0x46, 0x49, 0x49, 0x49, 0x31},// S
	{0x00, 0x01, 0x01, 0x7F, 0x01, 0x01},// T
	{0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F},// U
	{0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F},// V
	{0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F},// W
	{0x00, 0x63, 0x14, 0x08, 0x14, 0x63},// X
	{0x00, 0x07, 0x08, 0x70, 0x08, 0x07},// Y
	{0x00, 0x61, 0x51, 0x49, 0x45, 0x43},// Z
	{0x00, 0x00, 0x7F, 0x41, 0x41, 0x00},// [
	{0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55},// 55
	{0x00, 0x00, 0x41, 0x41, 0x7F, 0x00},// ]
	{0x00, 0x04, 0x02, 0x01, 0x02, 0x04},// ^
	{0x00, 0x40, 0x40, 0x40, 0x40, 0x40},// _
	{0x00, 0x00, 0x01, 0x02, 0x04, 0x00},// '
	{0x00, 0x20, 0x54, 0x54, 0x54, 0x78},// a
	{0x00, 0x7F, 0x48, 0x44, 0x44, 0x38},// b
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x20},// c
	{0x00, 0x38, 0x44, 0x44, 0x48, 0x7F},// d
	{0x00, 0x38, 0x54, 0x54, 0x54, 0x18},// e
	{0x00, 0x08, 0x7E, 0x09, 0x01, 0x02},// f
	{0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C},// g
	{0x00, 0x7F, 0x08, 0x04, 0x04, 0x78},// 0x
	{0x00, 0x00, 0x44, 0x7D, 0x40, 0x00},// i
	{0x00, 0x40, 0x80, 0x84, 0x7D, 0x00},// j
	{0x00, 0x7F, 0x10, 0x28, 0x44, 0x00},// k
	{0x00, 0x00, 0x41, 0x7F, 0x40, 0x00},// l
	{0x00, 0x7C, 0x04, 0x18, 0x04, 0x78},// m
	{0x00, 0x7C, 0x08, 0x04, 0x04, 0x78},// n
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x38},// o
	{0x00, 0xFC, 0x24, 0x24, 0x24, 0x18},// p
	{0x00, 0x18, 0x24, 0x24, 0x18, 0xFC},// q
	{0x00, 0x7C, 0x08, 0x04, 0x04, 0x08},// r
	{0x00, 0x48, 0x54, 0x54, 0x54, 0x20},// s
	{0x00, 0x04, 0x3F, 0x44, 0x40, 0x20},// t
	{0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C},// u
	{0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C},// v
	{0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C},// w
	{0x00, 0x44, 0x28, 0x10, 0x28, 0x44},// x
	{0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C},// y
	{0x00, 0x44, 0x64, 0x54, 0x4C, 0x44},// z
	{0x14, 0x14, 0x14, 0x14, 0x14, 0x14},// 0xoriz lines
};
/****************************************8*16的点阵************************************/
const unsigned char __code font0816 [] =	{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//0x 40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//0x 72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
};

//汉字取模
unsigned char __code font_chinese [][32] = {

	{0x00,0xFE,0x22,0x5A,0x86,0x08,0x88,0x68,0x18,0x0F,0xE8,0x08,0x08,0x08,0x08,0x00},
	{0x00,0xFF,0x04,0x08,0x07,0x20,0x11,0x0D,0x41,0x81,0x7F,0x01,0x05,0x09,0x30,0x00},//"陈",0
	{0x20,0x10,0x4C,0x47,0x4C,0x54,0x44,0xD4,0x28,0x27,0x24,0x2C,0x14,0x04,0x04,0x00},
	{0x82,0x82,0x42,0x42,0x22,0x12,0x0A,0x07,0x0A,0x12,0x22,0x42,0x42,0x82,0x82,0x00},//"笑",1
	{0x02,0xE2,0x22,0x22,0x3E,0x80,0x80,0xFF,0x80,0xA0,0x90,0x88,0x86,0x80,0x80,0x00},
	{0x00,0x43,0x82,0x42,0x3E,0x00,0x00,0xFF,0x40,0x21,0x06,0x08,0x10,0x20,0x40,0x00},//"张",2
	{0x00,0x00,0xE0,0x9C,0x84,0x84,0x84,0xF4,0x82,0x82,0x83,0x82,0x80,0x80,0x00,0x00},
	{0x00,0x20,0x10,0x08,0x06,0x40,0x80,0x7F,0x00,0x00,0x02,0x04,0x08,0x30,0x00,0x00},//"乐",3
	{0x44,0x58,0xC0,0x7F,0xD0,0x48,0x26,0x22,0xE2,0x3A,0xA2,0x22,0x22,0x2A,0x06,0x00},
	{0x80,0x60,0x1F,0x00,0x7F,0x20,0x10,0x13,0x12,0x12,0xFF,0x12,0x12,0x12,0x10,0x00},//"辉",4
	{0x02,0xE2,0x22,0x22,0x3E,0x80,0x80,0x80,0xFE,0xAA,0xAA,0xAA,0xAA,0x82,0x80,0x00},
	{0x00,0x43,0x82,0x42,0x3E,0x00,0x00,0xFF,0x40,0x21,0x06,0x08,0x14,0x22,0x40,0x00},//"張",5
	{0xD8,0xB4,0x93,0xC8,0x00,0xFC,0x26,0x25,0x24,0xFC,0x00,0xD8,0xB4,0x93,0xC8,0x00},
	{0x44,0x44,0x24,0x25,0x14,0x0D,0x05,0xFF,0x05,0x0D,0x14,0x24,0x24,0x44,0x45,0x00},//"樂",6
	{0x44,0x58,0xC0,0x7F,0xD0,0x48,0x16,0xD2,0x52,0x52,0xFE,0x52,0x52,0xD2,0x16,0x00},
	{0x80,0x60,0x1F,0x00,0x7F,0x20,0x10,0x17,0x15,0x15,0xFF,0x15,0x15,0x17,0x10,0x00},//"輝",7
	{0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x20,0x40,0x80,0x00,0x00},
	{0x08,0x04,0x03,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x01,0x0E,0x00},//"小",8
	{0x00,0x04,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x00},
	{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00},//"三",9
	{0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00},
	{0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00},//"学",10
	{0x80,0x80,0x80,0xBE,0xA2,0xA2,0xA2,0xA2,0xA2,0xA2,0xA2,0xBE,0x80,0x80,0x80,0x00},
	{0x00,0x00,0x00,0x06,0x05,0x04,0x04,0x04,0x44,0x84,0x44,0x3C,0x00,0x00,0x00,0x00},//"号",11
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//"：",12
};

/*--------------------------------------------------------------*/
//    字体:   Fixedsys
//取码规则: 低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//查表方法: 要显示的ASCII码-32就可以得到字库码的指针
unsigned char __code font_Fixedsys [][16] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},// 0
	{0x00,0x00,0x70,0xF8,0xF8,0x70,0x00,0x00,0x00,0x00,0x00,0x0D,0x0D,0x00,0x00,0x00},//!1
	{0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//"2
	{0x00,0x20,0xF8,0xF8,0x20,0xF8,0xF8,0x20,0x00,0x02,0x0F,0x0F,0x02,0x0F,0x0F,0x02},//#3
	{0x00,0x30,0x78,0xCE,0x8E,0x18,0x10,0x00,0x00,0x04,0x0C,0x38,0x39,0x0F,0x06,0x00},//$4
	{0x18,0x3C,0x24,0xBC,0xD8,0x60,0x30,0x00,0x00,0x06,0x03,0x0D,0x1E,0x12,0x1E,0x0C},//%5
	{0x00,0xB0,0xF8,0x48,0x78,0x30,0x00,0x00,0x00,0x07,0x0F,0x08,0x09,0x07,0x0F,0x09},//&6
	{0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//'7
	{0x00,0x00,0xC0,0xF0,0x38,0x08,0x00,0x00,0x00,0x00,0x07,0x1F,0x38,0x20,0x00,0x00},//(8
	{0x00,0x00,0x08,0x38,0xF0,0xC0,0x00,0x00,0x00,0x00,0x20,0x38,0x1F,0x07,0x00,0x00},//)9
	{0x00,0x80,0xA0,0xE0,0xC0,0xE0,0xA0,0x80,0x00,0x00,0x02,0x03,0x01,0x03,0x02,0x00},//*10
	{0x00,0x80,0x80,0xE0,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00},//+11
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x3C,0x1C,0x00,0x00},//,12
	{0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//-13
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x00,0x00},//.14
	{0x00,0x00,0x00,0x80,0xE0,0x78,0x18,0x00,0x00,0x18,0x1E,0x07,0x01,0x00,0x00,0x00},///15
	{0x00,0x00,0xF0,0xF8,0x08,0x68,0xF8,0xF0,0x00,0x00,0x07,0x0F,0x0B,0x08,0x0F,0x07},//016
	{0x00,0x20,0x20,0x30,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00},//117
	{0x00,0x30,0x38,0x08,0x88,0xF8,0x70,0x00,0x00,0x0C,0x0E,0x0B,0x09,0x08,0x08,0x00},//218
	{0x00,0x30,0x38,0x88,0x88,0xF8,0x70,0x00,0x00,0x06,0x0E,0x08,0x08,0x0F,0x07,0x00},//319
	{0x00,0x00,0xF8,0xF8,0x00,0xE0,0xE0,0x00,0x00,0x03,0x03,0x02,0x02,0x0F,0x0F,0x02},//420
	{0x00,0xF8,0xF8,0x88,0x88,0x88,0x08,0x00,0x00,0x08,0x08,0x08,0x0C,0x07,0x03,0x00},//521
	{0x00,0xC0,0xE0,0x78,0x58,0xC8,0x80,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00},//622
	{0x00,0x08,0x08,0x88,0xE8,0x78,0x18,0x00,0x00,0x00,0x0E,0x0F,0x01,0x00,0x00,0x00},//723
	{0x00,0x70,0xF8,0xC8,0x88,0xF8,0x70,0x00,0x00,0x07,0x0F,0x08,0x09,0x0F,0x07,0x00},//824
	{0x00,0xF0,0xF8,0x08,0x08,0xF8,0xF0,0x00,0x00,0x00,0x09,0x0D,0x0F,0x03,0x01,0x00},//925
	{0x00,0x00,0x00,0x60,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x00,0x00},//:26
	{0x00,0x00,0x00,0x60,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x2C,0x3C,0x1C,0x00,0x00},//;27
	{0x00,0x80,0xC0,0x60,0x30,0x18,0x08,0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x08,0x00},//<28
	{0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00},//=29
	{0x00,0x08,0x18,0x30,0x60,0xC0,0x80,0x00,0x00,0x08,0x0C,0x06,0x03,0x01,0x00,0x00},//>30
	{0x00,0x30,0x38,0x88,0xC8,0x78,0x30,0x00,0x00,0x00,0x00,0x0D,0x0D,0x00,0x00,0x00},//?31
	{0xF0,0xF8,0x08,0x88,0xC8,0x48,0xF8,0xF0,0x07,0x0F,0x08,0x09,0x0B,0x0A,0x0B,0x0B},//@32
	{0x00,0xE0,0xF0,0x18,0x18,0xF0,0xE0,0x00,0x00,0x0F,0x0F,0x01,0x01,0x0F,0x0F,0x00},//A33
	{0x00,0xF8,0xF8,0x88,0x88,0xF8,0x70,0x00,0x00,0x0F,0x0F,0x08,0x08,0x0F,0x07,0x00},//B34
	{0x00,0xF0,0xF8,0x08,0x08,0x38,0x30,0x00,0x00,0x07,0x0F,0x08,0x08,0x0E,0x06,0x00},//C35
	{0x00,0xF8,0xF8,0x08,0x18,0xF0,0xE0,0x00,0x00,0x0F,0x0F,0x08,0x0C,0x07,0x03,0x00},//D36
	{0x00,0xF8,0xF8,0x88,0x88,0x88,0x08,0x00,0x00,0x0F,0x0F,0x08,0x08,0x08,0x08,0x00},//E37
	{0x00,0xF8,0xF8,0x88,0x88,0x88,0x08,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00},//F38
	{0x00,0xF0,0xF8,0x08,0x08,0x38,0x30,0x00,0x00,0x07,0x0F,0x08,0x09,0x0F,0x0F,0x00},//G39
	{0x00,0xF8,0xF8,0x80,0x80,0xF8,0xF8,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00},//H40
	{0x00,0x00,0x08,0xF8,0xF8,0x08,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00},//I41
	{0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x06,0x0E,0x08,0x08,0x0F,0x07,0x00},//J42
	{0x00,0xF8,0xF8,0x80,0xE0,0x78,0x18,0x00,0x00,0x0F,0x0F,0x00,0x03,0x0F,0x0C,0x00},//K43
	{0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x08,0x08,0x08,0x08,0x00},//L44
	{0x00,0xF8,0xF8,0x20,0xC0,0x20,0xF8,0xF8,0x00,0x0F,0x0F,0x00,0x01,0x00,0x0F,0x0F},//M45
	{0x00,0xF8,0xF8,0x60,0xC0,0x80,0xF8,0xF8,0x00,0x0F,0x0F,0x00,0x00,0x01,0x0F,0x0F},//N46
	{0x00,0xF0,0xF8,0x08,0x08,0xF8,0xF0,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00},//O47
	{0x00,0xF8,0xF8,0x88,0x88,0xF8,0x70,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00},//P48
	{0x00,0xF0,0xF8,0x08,0x08,0xF8,0xF0,0x00,0x00,0x07,0x0F,0x08,0x18,0x3F,0x27,0x00},//Q49
	{0x00,0xF8,0xF8,0x88,0x88,0xF8,0x70,0x00,0x00,0x0F,0x0F,0x00,0x01,0x0F,0x0E,0x00},//R50
	{0x00,0x30,0x78,0xC8,0x88,0x18,0x10,0x00,0x00,0x04,0x0C,0x08,0x09,0x0F,0x06,0x00},//S51
	{0x00,0x08,0x08,0xF8,0xF8,0x08,0x08,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00},//T52
	{0x00,0xF8,0xF8,0x00,0x00,0xF8,0xF8,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00},//U53
	{0x00,0xF8,0xF8,0x00,0x00,0xF8,0xF8,0x00,0x00,0x03,0x07,0x0C,0x0C,0x07,0x03,0x00},//V54
	{0x00,0xF8,0xF8,0x00,0xC0,0x00,0xF8,0xF8,0x00,0x01,0x0F,0x0E,0x01,0x0E,0x0F,0x01},//W55
	{0x00,0x18,0x38,0xE0,0xC0,0x38,0x18,0x00,0x00,0x0E,0x0F,0x00,0x01,0x0F,0x0E,0x00},//X56
	{0x00,0x78,0xF8,0x80,0x80,0xF8,0x78,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00},//Y57
	{0x00,0x08,0x08,0x88,0xC8,0x78,0x38,0x00,0x00,0x0E,0x0F,0x09,0x08,0x08,0x08,0x00},//Z58
	{0x00,0x00,0xF8,0xF8,0x08,0x08,0x00,0x00,0x00,0x00,0x7F,0x7F,0x40,0x40,0x00,0x00},//[59
	{0x00,0x18,0x78,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x1E,0x18,0x00},//\60
	{0x00,0x00,0x08,0x08,0xF8,0xF8,0x00,0x00,0x00,0x00,0x40,0x40,0x7F,0x7F,0x00,0x00},//]61
	{0x00,0x08,0x0C,0x06,0x06,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//^62
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40},//_63
	{0x00,0x00,0x02,0x06,0x0E,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//`64
	{0x00,0x00,0x20,0x20,0x20,0xE0,0xC0,0x00,0x00,0x06,0x0F,0x09,0x09,0x0F,0x0F,0x00},//a65
	{0x00,0xF8,0xF8,0x20,0x20,0xE0,0xC0,0x00,0x00,0x0F,0x0F,0x08,0x08,0x0F,0x07,0x00},//b66
	{0x00,0xC0,0xE0,0x20,0x20,0x60,0x40,0x00,0x00,0x07,0x0F,0x08,0x08,0x0C,0x04,0x00},//c67
	{0x00,0xC0,0xE0,0x20,0x20,0xF8,0xF8,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x0F,0x00},//d68
	{0x00,0xC0,0xE0,0x20,0x20,0xE0,0xC0,0x00,0x00,0x07,0x0F,0x09,0x09,0x09,0x01,0x00},//e69
	{0x00,0x80,0xF0,0xF8,0x88,0x88,0x88,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00},//f70
	{0x00,0xC0,0xE0,0x20,0x20,0xE0,0xE0,0x00,0x00,0x47,0x4F,0x48,0x48,0x7F,0x3F,0x00},//g71
	{0x00,0xF8,0xF8,0x20,0x20,0xE0,0xC0,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00},//h72
	{0x00,0x20,0x20,0xEC,0xEC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00},//i73
	{0x00,0x00,0x20,0x20,0xEC,0xEC,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x3F,0x00,0x00},//j74
	{0x00,0xF8,0xF8,0x00,0x80,0xE0,0x60,0x00,0x00,0x0F,0x0F,0x01,0x03,0x0E,0x0C,0x00},//k75
	{0x00,0x08,0x08,0xF8,0xF8,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00},//l76
	{0x00,0xE0,0xE0,0x20,0xE0,0x20,0xE0,0xC0,0x00,0x0F,0x0F,0x00,0x07,0x00,0x0F,0x0F},//m77
	{0x00,0xE0,0xE0,0x20,0x20,0xE0,0xC0,0x00,0x00,0x0F,0x0F,0x00,0x00,0x0F,0x0F,0x00},//n78
	{0x00,0xC0,0xE0,0x20,0x20,0xE0,0xC0,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x07,0x00},//o79
	{0x00,0xE0,0xE0,0x20,0x20,0xE0,0xC0,0x00,0x00,0x7F,0x7F,0x08,0x08,0x0F,0x07,0x00},//p80
	{0x00,0xC0,0xE0,0x20,0x20,0xE0,0xE0,0x00,0x00,0x07,0x0F,0x08,0x08,0x7F,0x7F,0x00},//q81
	{0x00,0xE0,0xE0,0x80,0x40,0x60,0x60,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00},//r82
	{0x00,0xC0,0xE0,0x20,0x20,0x20,0x20,0x00,0x00,0x08,0x09,0x09,0x09,0x0F,0x06,0x00},//s83
	{0x00,0x20,0xF8,0xF8,0x20,0x20,0x20,0x00,0x00,0x00,0x07,0x0F,0x08,0x08,0x08,0x00},//t84
	{0x00,0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,0x00,0x07,0x0F,0x08,0x08,0x0F,0x0F,0x00},//u85
	{0x00,0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,0x00,0x03,0x07,0x0C,0x0C,0x07,0x03,0x00},//v86
	{0x00,0xE0,0xE0,0x00,0xC0,0x00,0xE0,0xE0,0x00,0x03,0x0F,0x0C,0x03,0x0C,0x0F,0x03},//w87
	{0x00,0x60,0xE0,0x80,0x80,0xE0,0x60,0x00,0x00,0x0C,0x0E,0x03,0x03,0x0E,0x0C,0x00},//x88
	{0x00,0xE0,0xE0,0x00,0x00,0xE0,0xE0,0x00,0x40,0x47,0x4F,0x68,0x38,0x1F,0x07,0x00},//y89
	{0x00,0x20,0x20,0x20,0xA0,0xE0,0x60,0x00,0x00,0x0C,0x0E,0x0B,0x09,0x08,0x08,0x00},//z90
	{0x00,0x00,0x80,0xF0,0x78,0x08,0x00,0x00,0x00,0x01,0x03,0x1E,0x3C,0x20,0x00,0x00},//{91
	{0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00},//|92
	{0x00,0x00,0x08,0x78,0xF0,0x80,0x00,0x00,0x00,0x00,0x20,0x3C,0x1E,0x03,0x01,0x00},//}93
	{0x30,0x18,0x08,0x18,0x30,0x20,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}//~94
};



//中文显示测试全动电子欢迎您因为专业所以注　
typFNT_GBK16_t __code hz16[] = {
	{{"中"},{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
	0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00}},
	{{"文"},{0x02,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x10,0x10,0x10,0x10,0x08,0x20,0x08,0x20,
	0x04,0x40,0x02,0x80,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06}},
	{{"显"},{0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,
	0x04,0x40,0x44,0x44,0x24,0x44,0x14,0x48,0x14,0x50,0x04,0x40,0xFF,0xFE,0x00,0x00}},
	{{"示"},{0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x01,0x00,
	0x01,0x00,0x11,0x10,0x11,0x08,0x21,0x04,0x41,0x02,0x81,0x02,0x05,0x00,0x02,0x00}},
	{{"测"},{0x00,0x04,0x27,0xC4,0x14,0x44,0x14,0x54,0x85,0x54,0x45,0x54,0x45,0x54,0x15,0x54,
	0x15,0x54,0x25,0x54,0xE5,0x54,0x21,0x04,0x22,0x84,0x22,0x44,0x24,0x14,0x08,0x08}},
	{{"试"},{0x00,0x28,0x20,0x24,0x10,0x24,0x10,0x20,0x07,0xFE,0x00,0x20,0xF0,0x20,0x17,0xE0,
	0x11,0x20,0x11,0x10,0x11,0x10,0x15,0x10,0x19,0xCA,0x17,0x0A,0x02,0x06,0x00,0x02}},
	{{"全"},{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x10,0x10,0x2F,0xE8,0xC1,0x06,
	0x01,0x00,0x01,0x00,0x1F,0xF0,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x00,0x00}},
	{{"动"},{0x00,0x40,0x00,0x40,0x7C,0x40,0x00,0x40,0x01,0xFC,0x00,0x44,0xFE,0x44,0x20,0x44,
	0x20,0x44,0x20,0x84,0x48,0x84,0x44,0x84,0xFD,0x04,0x45,0x04,0x02,0x28,0x04,0x10}},
	{{"电"},{0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,
	0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x0A,0x01,0x02,0x01,0x02,0x00,0xFE}},
	{{"子"},{0x00,0x00,0x7F,0xF8,0x00,0x10,0x00,0x20,0x00,0x40,0x01,0x80,0x01,0x00,0xFF,0xFE,
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00}},
	{{"欢"},{0x00,0x80,0x00,0x80,0xFC,0x80,0x04,0xFC,0x05,0x04,0x49,0x08,0x2A,0x40,0x14,0x40,
	0x10,0x40,0x28,0xA0,0x24,0xA0,0x45,0x10,0x81,0x10,0x02,0x08,0x04,0x04,0x08,0x02}},
	{{"迎"},{0x00,0x00,0x20,0x80,0x13,0x3C,0x12,0x24,0x02,0x24,0x02,0x24,0xF2,0x24,0x12,0x24,
	0x12,0x24,0x12,0xB4,0x13,0x28,0x12,0x20,0x10,0x20,0x28,0x20,0x47,0xFE,0x00,0x00}},
	{{"您"},{0x09,0x00,0x09,0x00,0x11,0xFC,0x32,0x04,0x54,0x48,0x99,0x50,0x11,0x48,0x12,0x44,
	0x14,0x44,0x11,0x40,0x10,0x80,0x02,0x00,0x51,0x04,0x51,0x12,0x90,0x12,0x0F,0xF0}},
	{{"因"},{0x00,0x00,0x7F,0xFC,0x40,0x04,0x41,0x04,0x41,0x04,0x41,0x04,0x5F,0xF4,0x41,0x04,
	0x42,0x84,0x42,0x44,0x44,0x24,0x48,0x14,0x50,0x14,0x40,0x04,0x7F,0xFC,0x40,0x04}},
	{{"为"},{0x01,0x00,0x21,0x00,0x11,0x00,0x11,0x00,0x01,0x00,0x7F,0xF8,0x02,0x08,0x02,0x08,
	0x02,0x88,0x04,0x48,0x04,0x48,0x08,0x08,0x10,0x08,0x20,0x08,0x40,0x50,0x80,0x20}},
	{{"专"},{0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x02,0x00,0x02,0x00,0xFF,0xFE,0x04,0x00,
	0x08,0x00,0x0F,0xF0,0x00,0x10,0x00,0x20,0x06,0x40,0x01,0x80,0x00,0x40,0x00,0x20}},
	{{"业"},{0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x40,0x44,0x44,0x24,0x44,0x24,0x48,0x14,0x48,
	0x14,0x50,0x14,0x60,0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x40,0xFF,0xFE,0x00,0x00}},
	{{"所"},{0x02,0x08,0x07,0x1C,0x38,0xE0,0x20,0x80,0x20,0x80,0x3E,0x80,0x22,0xFE,0x22,0x88,
	0x22,0x88,0x3E,0x88,0x20,0x88,0x20,0x88,0x41,0x08,0x41,0x08,0x82,0x08,0x04,0x08}},
	{{"以"},{0x00,0x10,0x04,0x10,0x22,0x10,0x21,0x10,0x21,0x10,0x20,0x10,0x20,0x10,0x20,0x20,
	0x20,0x20,0x20,0x20,0x24,0x40,0x28,0x50,0x30,0x88,0x21,0x04,0x02,0x02,0x04,0x02}},
	{{"注"},{0x00,0x80,0x20,0x40,0x10,0x00,0x17,0xFC,0x80,0x40,0x40,0x40,0x40,0x40,0x10,0x40,
	0x13,0xFC,0x20,0x40,0xE0,0x40,0x20,0x40,0x20,0x40,0x20,0x40,0x2F,0xFE,0x00,0x00}},
	{{"　"},{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
};