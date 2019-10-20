
#include<reg51.h>
#include<lcd_show.h>
#include<intrins.h>
#include<delay.h>

 /* 写数据 */

bit Busy()
{
 	bit busy_flag = 0;
	RS = 0;
	RW = 1;
	E = 1;
	delay(5);
	busy_flag = (bit)(P0 & 0x80);
	E = 0;
	return busy_flag;
}

void wdata(uchar del)
{
     while(Busy());
	RS = 1;
	RW = 0;
	E = 0;
	delay(5);
	P0 = del;
	delay(5);
	E = 1;
	delay(5);
	E = 0;
}

 /* 写指令 */
void wcmd(uchar del)
{
    while(Busy());
	RS = 0;
	RW = 0;
	E = 0;
	delay(5);
	P0 = del;
	delay(5);
	E = 1;
	delay(5);
	E = 0;
}
 /* 初始化LCD */
void L1602_init(void)
{
	wcmd(0x38);
	wcmd(0x0c);
	wcmd(0x06);
	wcmd(0x01);
}

void L1602_char(uchar hang,uchar lie,char sign)
{
	uchar a;
	if(hang == 0) a= 0x80;
	else if(hang == 1) a = 0xc0;
	else return;
	a = a + lie;
	wcmd(a);
	wdata(sign);
}

void L1602_string(uchar hang,uchar lie,uchar *p)
{
	uchar a,b=0;
	if(hang == 0) a = 0x80;
	if(hang == 1) a = 0xc0;
	a = a + lie;
	while(1)
	{
		wcmd(a++);
		b++;
		if((*p == '\0')||(b==17)) break;
			wdata(*p);
		p++;
	}
}
void dis_num(uchar hang,uchar lie,uchar digits,int n)
{
	uchar c;
	char i;
	for (i = digits - 1; i >= 0; i--)
	{
		c = n % 10 + '0';
		L1602_char(hang,lie + i,c);
		n /= 10;
	}
}
void LCD_clear(void)
{
//LCD_write_com(0x01);
wcmd(0x01);
delay(5);
}

