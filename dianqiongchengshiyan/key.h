
#ifndef _KEY_H_
#define _KEY_H_

#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

#define SET_KP 0
#define SET_KI 1
#define SET_KD 2
#define DIS_MAIN 3

extern unsigned char mode;
extern unsigned int speed_set;
extern unsigned int speed_cnt;
extern bit flag_run;

uchar keyscan(void);
void change_mode(uchar key); //改变模式

void dis_main();
void proc_main();

void dis_adj();
void proc_adj();

void set_kp();
void get_sv(void);
//把float 型的f 转换到字符串str_ptr 里, 小数保留d 位
uchar *Trans_Data_To_Disp(uchar *str_ptr, float f, uchar d);
float str2f(char str[]);  //字符串转浮点

#endif
