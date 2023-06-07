#include "LCD.h"
#include "LCDfont.h"
#include "LCD_Init.h"

u8 LCD_GRAM[4125];

void LCD_Fill(u8 dat)
{
	u16 i,j;
	u32 k;
	for(i=0;i<33;i++)
	{
		for(j=0;j<125;j++)
		{
			k=j+i*125;
			LCD_GRAM[k]=dat;
		}
	}
	LCD_Refresh();
}

void LCD_Refresh()
{
	u16 i,j,k;
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2A);
		LCD_WR_DATA8(0x19);
		LCD_WR_DATA8(0x23);
		LCD_WR_REG(0x2B);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x7C);
		LCD_WR_REG(0x2C);
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2A);
		LCD_WR_DATA8(0x19);
		LCD_WR_DATA8(0x23);
		LCD_WR_REG(0x2B);
		LCD_WR_DATA8(0x4B);
		LCD_WR_DATA8(0xC7);
		LCD_WR_REG(0x2C);
	}
	for(i=0;i<33;i++)
	{
		for(j=0;j<125;j++)
		{
			LCD_WR_DATA8(LCD_GRAM[k]);
			k++;
		}
	}
}

u32 LCD_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--) result*=m;
	return result;
}

void LCD_DrawPoint(u16 x,u16 y,u8 mode)
{
	u16 x1,y1,n,y2;
	x1=x/2;
	y1=y/4;

	y2=y-y1*4;
	n=LCD_pow(4,(3-y2));
	if(x-x1*2==0)n*=2;
	if(mode==0)
	{
	 LCD_GRAM[x1*0x21+y1]|=n;
	}
	else
	{
	  LCD_GRAM[x1*0x21+y1]|=n;
	  LCD_GRAM[x1*0x21+y1]=~LCD_GRAM[x1*0x21+y1];
   	LCD_GRAM[x1*0x21+y1]|=n;
	  LCD_GRAM[x1*0x21+y1]=~LCD_GRAM[x1*0x21+y1];
	}
}

void LCD_ClearPoint(u16 x,u16 y)
{
	u16 x1,y1,n,y2;
	x1=x/2;
	y1=y/4;
	y2=y-y1*4;
	n=LCD_pow(4,(3-y2));
	if(x-x1*2==0)n*=2;
	LCD_GRAM[x1*0x21+y1]|=n;
	LCD_GRAM[x1*0x21+y1]=~LCD_GRAM[x1*0x21+y1];
	LCD_GRAM[x1*0x21+y1]|=n;
	LCD_GRAM[x1*0x21+y1]=~LCD_GRAM[x1*0x21+y1];
}


void LCD_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ�������
	else if (delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ��
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,0);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawCircle(u8 x,u8 y,u8 r)
{
	int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)
    {
        LCD_DrawPoint(x + a, y - b,0);
        LCD_DrawPoint(x - a, y - b,0);
        LCD_DrawPoint(x - a, y + b,0);
        LCD_DrawPoint(x + a, y + b,0);

        LCD_DrawPoint(x + b, y + a,0);
        LCD_DrawPoint(x + b, y - a,0);
        LCD_DrawPoint(x - b, y - a,0);
        LCD_DrawPoint(x - b, y + a,0);
        a++;
        num = (a * a + b * b) - r*r;//���㻭�ĵ���Բ�ĵľ���
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}





/******************************************************************************
      ����˵������ʾ���ִ�
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ��ִ�
                sizey �ֺ� ��ѡ 16 24 32
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 *s,u8 sizey,u8 mode)
{
	while(*s!=0)
	{
		if(sizey==12) LCD_ShowChinese12x12(x,y,s,sizey,mode);
		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,sizey,mode);
		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,sizey,mode);
		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,sizey,mode);
		else return;
		s+=2;
		x+=sizey;
	}
}

/******************************************************************************
      ����˵������ʾ����12x12����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++)
	{
		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
		{
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{
						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,mode);//��һ����
				   	else LCD_DrawPoint(x,y,!mode);
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
				}
			}
		}
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
}

/******************************************************************************
      ����˵������ʾ����16x16����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++)
	{
		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
		{
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{
						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,mode);//��һ����
					  else LCD_DrawPoint(x,y,!mode);
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
				}
			}
		}
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
}


/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++)
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{
						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,mode);//��һ����
					  else LCD_DrawPoint(x,y,!mode);
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
				}
			}
		}
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
}

/******************************************************************************
      ����˵������ʾ����32x32����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++)
	{
		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
		{
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{
						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,mode);//��һ����
				    else LCD_DrawPoint(x,y,!mode);
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
				}
			}
		}
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
}


/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 sizey,u8 mode)
{
	u8 temp,sizex,t;
	u16 i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	for(i=0;i<TypefaceNum;i++)
	{
		if(sizey==12)temp=ascii_1206[num][i];		       //����6x12����
		else if(sizey==16)temp=ascii_1608[num][i];		 //����8x16����
		else if(sizey==24)temp=ascii_2412[num][i];		 //����12x24����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,mode);//��һ����
				else LCD_DrawPoint(x,y,!mode);
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
		}
	}
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u8 sizey,u8 mode)
{
	while(*p!='\0')
	{
		LCD_ShowChar(x,y,*p,sizey,mode);
		x+=sizey/2;
		p++;
	}
}



/******************************************************************************
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u8 sizey,u8 mode)
{
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',sizey,mode);
				continue;
			}else enshow=1;

		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,sizey,mode);
	}
}


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u8 sizey,u8 pre,u8 mode)
{
	u8 t,temp,sizex;
	u16 num1;
	sizex=sizey/2;
	num1=num*LCD_pow(10,pre);
	for(t=0;t<len;t++)
	{
		temp=(num1/LCD_pow(10,len-t-1))%10;
		if(t==(len-pre))
		{
			LCD_ShowChar(x+(len-pre)*sizex,y,'.',sizey,mode);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,sizey,mode);
	}
}

//x,y���������
//sizex,sizey,ͼƬ����
//BMP[]��Ҫд���ͼƬ����
void LCD_ShowPicture(u16 x,u16 y,u16 sizex,u16 sizey,u8 BMP[],u8 mode)
{
	u16 j=0;
	u16 i,n,temp,m;
	u16 x0=x,y0=y;
	sizey=sizey/8+((sizey%8)?1:0);
	for(n=0;n<sizey;n++)
	{
		 for(i=0;i<sizex;i++)
		 {
				temp=BMP[j];
				j++;
				for(m=0;m<8;m++)
				{
					if(temp&0x01)LCD_DrawPoint(x,y,mode);
					else LCD_DrawPoint(x,y,!mode);
					temp>>=1;
					y++;
				}
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y0=y0+8;
				}
				y=y0;
     }
	 }
}



