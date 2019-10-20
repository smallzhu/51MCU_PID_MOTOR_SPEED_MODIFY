
#ifndef _TLC2543_H_
#define _TLC2543_H_

#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit CLOCK=P3^3; /*2543 时钟*/ 
sbit D_IN= P2^7; /*2543 输入*/ 
sbit D_OUT= P2^6; /*2543 输出*/ 
sbit _CS= P3^2; /*2543 片选*/ 

uint read2543(uchar port);

#endif