
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
void change_mode(uchar key); //�ı�ģʽ

void dis_main();
void proc_main();

void dis_adj();
void proc_adj();

void set_kp();
void get_sv(void);
//��float �͵�f ת�����ַ���str_ptr ��, С������d λ
uchar *Trans_Data_To_Disp(uchar *str_ptr, float f, uchar d);
float str2f(char str[]);  //�ַ���ת����

#endif
