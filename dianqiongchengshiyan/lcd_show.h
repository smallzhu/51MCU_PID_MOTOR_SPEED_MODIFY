
#ifndef __LCD_SHOW_H__   
#define __LCD_SHOW_H__

#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int


sbit RS = P2 ^ 0;
sbit RW = P2 ^ 1;
sbit E = P2 ^ 2;

void wdata(uchar del);
void wcmd(uchar del);
void L1602_init();
bit Busy();//判断液晶忙，如果忙则等待
void L1602_char(uchar hang,uchar lie,char sign);
void dis_num(uchar hang,uchar lie,uchar digits,int n);
void L1602_string(uchar hang,uchar lie,uchar *p);
void LCD_clear();
#endif

