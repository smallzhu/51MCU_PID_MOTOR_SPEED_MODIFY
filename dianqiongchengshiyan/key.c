#include<reg51.H>
#include<key.h>
#include<string.h>
#include<stdio.h>
#include<lcd_show.h>
#include<pid.h>
#include<tlc2543.h>
#include<delay.h>

data char str[10];
uchar p_pos; //ָ��λ��
uint speed_set = 0;
uint speed_cnt = 0;
int test = 333;
uchar mode = 3;
bit flag_run = 0;
float *pst;
extern struct mPID M_Pid;

#define P_KEY P1
uchar keyscan(void)
{
	uchar key_val;
	uchar key_r,key_c;
	uchar temp;
	P_KEY = 0X0F;
	temp = P_KEY & 0X0F;
	if (temp != 0x0f)
	{
		delay(3);
		temp = P_KEY & 0X0F;
		if (temp != 0x0f)
		{
			key_r = temp;
			P_KEY = 0XF0;
			delay(1);
			temp = P_KEY & 0XF0;
			key_c = temp;
			if ( key_c == 0x70 ) //���һ��
			{
				switch (key_r)
				{
				case 0x0e: key_val = 16; break;
				case 0x0d: key_val = 15; break;
				case 0x0b: key_val = 14; break;
				case 0x07: key_val = 13; break;
				}
			}
			else
			{
				switch (key_c)
				{
				case 0xe0: key_val = 1; break;
				case 0xd0: key_val = 2; break;
				case 0xb0: key_val = 3; break;
				case 0x70: key_val = 4; break;
				}
				switch (key_r)
				{
				case 0x0e: key_val += 0; break;
				case 0x0d: key_val += 3; break;
				case 0x0b: key_val += 6; break;
				case 0x07: key_val += 9; break;
				}
			}
			while (temp != 0xf0) //���ּ��
			{
			temp = P_KEY & 0xf0;
			}
			return key_val;
		}
	}
	return 0;
}
void change_mode(uchar key)
{
	LCD_clear();
	switch (key)
	{
		case 16: mode = SET_KP;
			pst = &M_Pid.Kp;
			L1602_string(0,0,"KP:");
			break;
		case 15: mode = SET_KI;
			pst = &M_Pid.Ki;
			L1602_string(0,0,"KI:");
			break;
		case 14: mode = SET_KD;
			pst = &M_Pid.Kd;
			L1602_string(0,0,"KD:");
			break;
		case 12: mode = DIS_MAIN;
			L1602_string(0,8,"r/min");
			L1602_string(1,8,"r/min");
			break;
	}
	if (mode != DIS_MAIN)
	{
		Trans_Data_To_Disp(str, *pst, 3);
		
		L1602_string(1,0,"OLD:");
		L1602_string(1,5,str);
		p_pos = 0;
	}
	memset(str,0,17);
}

void dis_main()
{
	L1602_string(0,0,"SV: ");
	L1602_string(1,0,"PV: ");
	dis_num(0,3,4,speed_set);
	dis_num(1,3,4,speed_set);
}

void proc_main()
{
	uchar key;
	key = keyscan();
	switch (key)
	{
		case 16:
		case 15:
		case 14: change_mode(key); break;
		case 13: flag_run = 1; break;
		case 12: flag_run = 0; break;
	}
}

void dis_adj()
{
	L1602_string(0,4,str);
}
void proc_adj()
{
	uchar key;
	key = keyscan();
	if (key > 0 && key < 10)
	{
		str[p_pos] = key + '0';
		p_pos ++;
	}
	else
	{
		switch (key)
		{
			case 10: str[p_pos] = '0'; p_pos++; break;
			case 11: str[p_pos] = '.'; p_pos++; break;
			case 16:
			case 15:
			case 14: change_mode(key); break;
			case 13:
				*pst = str2f(str);
				//PID_init();
			case 12:
				change_mode(12);
				break;
		}
	}
}

/*void set_kp()
{
	uchar key;
	L1602_string(0,0,"set Kp");
	key = keyscan();
	if (key > 0 && key < 10)
	{
		str[p_pos] = key + '0';
		p_pos ++;
	}
	else
	{
		switch (key)
		{
			case 10: str[p_pos] = '0'; p_pos++; break;
			case 11: str[p_pos] = '.'; p_pos++; break;
			case 16:
			case 15:
			case 14: change_mode(key); break;
			case 13: break;
		}
	}
}*/
void get_sv(void)
{
	uint d;
	d = read2543(0);
	speed_set = d/20;
}

//����: ��float �͵�f ת�����ַ���str_ptr ��, С������d λ
// d=0, ȥβ
//����: f=12.3456 �� С��λ��d=3 -> "12.345"
/*************************************************************************/
#define STR_END '\0'
uchar *Trans_Data_To_Disp(uchar *str_ptr, float f, uchar d)
{
	uint integral_part=0; //��������
	float decimal_part=0; //С������
	uint temp;
	uchar i,n;
	//��������
	integral_part = (uint)(f);
	temp=integral_part;
	n=0;
	do
	{
		n++;
		temp=(uint)(temp/10); //�õ���������λ��n
	}while(temp!=0);
	temp=integral_part;
	for( i=0; (i<n)&&(i<20); i++)
	{
		*(str_ptr + n-1-i)=(uchar)(temp%10) +'0'; //�ӵ�λ(str_ptr + n-1)��ʼ����ȡ��Ӧλ
		temp=(uint)(temp/10);
	}
	//��:ԭ���Ƕ�Ӧ��lcd 20*2����ʾ��,������20���ַ�������,ʵ����float�ﲻ���������
	if( (d==0) || (i==20) )
	{
		*(str_ptr + i) = STR_END; //��ʱ i = n ��20
		return str_ptr;
	}
	else
	{
		*(str_ptr + i) = '.'; //��ʱ i = n ,��n < 20
	}
	//С������
	decimal_part = f - integral_part;
	for(i=n+1; (i<d+n+1)&&(i<20); i++)
	{
		decimal_part = decimal_part * 10;
		*(str_ptr + i) = (uchar)(decimal_part) +'0'; //�Ӹ�λ(str_ptr + n+1)��ʼ����ȡ��Ӧλ
		decimal_part = decimal_part - (uchar)(decimal_part);
	}
	*(str_ptr + i) = STR_END; //��ʱ i = d+n+1 ��20
	return str_ptr;
}

//�ַ���ת����
float str2f(char str[])
{
	float out=0;
	float tmp = 0.1;
	char* pt = str;
	char ngflag = 0;
	while((*pt>'9' || *pt < '1') && *pt!= 0 && *pt != '.')
	{
		if(*pt == '-')
		ngflag = 1;
		pt++;
	}
	while( *pt <= '9' && *pt >= '0')
	{
		out *= 10;
		out += *pt-'0';
		pt++;
	}
	if( *pt == '.')
	{
		pt++;
		while(*pt <= '9' && *pt >= '0')
		{
			out += (*pt-'0')*tmp;
			tmp *= 0.1;
			pt++;
		}
	}
	if(ngflag)
	out = -out;
	return out;
}

