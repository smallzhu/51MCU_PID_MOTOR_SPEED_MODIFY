#include<reg51.h>
#include<pid.h>

struct mPID M_Pid;

int Motor_Max = 100;
int Motor_Min = 0;

int PID_realize1(int speed) 
{    
	float incrementValue;
	M_Pid.err = speed;
	//增量式pid公式
	incrementValue = M_Pid.Kp*(M_Pid.err - M_Pid.err_last) 
		+ M_Pid.Ki*M_Pid.err + 
		M_Pid.Kd*(M_Pid.err - 2 * M_Pid.err_last + M_Pid.err_prev);

	M_Pid.err_prev = M_Pid.err_last;
	M_Pid.err_last = M_Pid.err;
	
	if(incrementValue > Motor_Max)       
		incrementValue = Motor_Max; 
	else if( incrementValue < Motor_Min)     
		incrementValue = Motor_Min;    
				     
	return incrementValue;       
} 

void PID_init() 
{   //KP = 2 ki =5 kd = 2
	M_Pid.err = 0.0;
	M_Pid.err_prev = 0.0;
	M_Pid.err_last = 0.0;
	M_Pid.Kp = 0;
	M_Pid.Ki = 0;
	M_Pid.Kd = 0;
} 


