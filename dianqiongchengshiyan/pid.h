#ifndef _PID_H_
#define _PID_H_

#include<reg51.h>

typedef struct mPID
{
	float err;//定义偏差值
	float err_last;//定义上一个偏差值
	float err_prev;//定义前一个的偏差值
	float Kp, Ki, Kd;//定义比例、积分、微分系数
};

void PID_init();
int PID_realize1(int speed);


#endif