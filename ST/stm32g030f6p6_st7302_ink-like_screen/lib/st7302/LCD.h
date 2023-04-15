#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif
#include "sys.h"
#include "common.h"


void LCD_Fill(u8 dat);
void LCD_Refresh(void);
u32 LCD_pow(u8 m,u8 n);
void LCD_DrawPoint(u16 x,u16 y,u8 mode);
void LCD_ClearPoint(u16 x,u16 y);
void LCD_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawCircle(u8 x,u8 y,u8 r);

void LCD_ShowChinese(u16 x,u16 y,u8 *s,u8 sizey,u8 mode);//显示汉字串
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u8 sizey,u8 mode);//显示单个12x12汉字
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u8 sizey,u8 mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u8 sizey,u8 mode);//显示单个24x24汉字
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u8 sizey,u8 mode);//显示单个32x32汉字

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 sizey,u8 mode);//显示一个字符
void LCD_ShowString(u16 x,u16 y,const u8 *p,u8 sizey,u8 mode);//显示字符串
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u8 sizey,u8 mode);//显示整数变量
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u8 sizey,u8 pre,u8 mode);//显示小数变量
void LCD_ShowPicture(u16 x,u16 y,u16 sizex,u16 sizey,u8 BMP[],u8 mode);

#ifdef __cplusplus
}
#endif
#endif


