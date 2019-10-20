#include<reg51.h>
#include<lcd_show.h>
#include<key.h>
#include<pid.h>
#include<delay.h>


#define INT_TIME 500

sbit PWM = P2^3;
sbit IN1 = P2^4;
sbit IN2 = P2^5;

uchar timer_cnt1 = 0;
uchar timer_cnt2 = 0;
bit flag_s = 0;
int duty = 0;
extern struct mPID M_Pid;

void Int_T0_T1()
{
	TH0 = (65536- INT_TIME)/256;   //1MS
	TL0 = (65536- INT_TIME)%256;
	TMOD=0x51;	//T1定时 16位 T016位
	ET0=1;
	EA=1;
	TR0=1;
	ET1=1;
	TR1=1;
}

int main()
{	
	L1602_init();
	delay(30);
	Int_T0_T1();
	PID_init();
	speed_set = 200;
	PWM = 1;
	IN1 = 1;
	IN2 = 0;
	L1602_string(0,7,"r/min");
	L1602_string(1,7,"r/min");
	while(1)
	{
		switch (mode)
		{
			case DIS_MAIN: proc_main(); break;
			case SET_KP:
			case SET_KI:
			case SET_KD:
				proc_adj();
				break;
		}
		if (flag_s)
		{
			flag_s = 0;
			get_sv();	//AD转
			if (flag_run)
			{
				duty = PID_realize1(speed_set - speed_cnt);
			}
			switch (mode)
			{
			case DIS_MAIN: dis_main(); break;
			case SET_KP:
			case SET_KI:
			case SET_KD:
				dis_adj();
				break;
			}
		} 
	}
} 
void Timer0_ser () interrupt 1
{
	TH0 = (65536- INT_TIME)/256;
	TL0 = (65536- INT_TIME)%256;
	timer_cnt1++;
	if (timer_cnt1 >= 100)
	{
		timer_cnt1 = 0;
		timer_cnt2++;
		if (timer_cnt2 >= 4)
		{
			timer_cnt2 = 0;
			speed_cnt = 60*(TH1*256 + TL1)/(24*0.43);
			TH1 = 0;
			TL1 = 0;
			flag_s = 1;
		}
	}
	if (flag_run)
	{
		PWM = timer_cnt1 > duty? 0 : 1;
	}
	else
	{
		PWM = 0;
	}
}
/*void timer1 interrupt 3
{
	
} */
