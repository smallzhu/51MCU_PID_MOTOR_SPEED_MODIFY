#ifndef _PID_H_
#define _PID_H_

#include<reg51.h>

typedef struct mPID
{
	float err;//����ƫ��ֵ
	float err_last;//������һ��ƫ��ֵ
	float err_prev;//����ǰһ����ƫ��ֵ
	float Kp, Ki, Kd;//������������֡�΢��ϵ��
};

void PID_init();
int PID_realize1(int speed);


#endif