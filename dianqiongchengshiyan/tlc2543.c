
#include<reg51.h>
#include<tlc2543.h>
#include<delay.h>

uint read2543(uchar port) 
{
	uint ad=0,i;
    CLOCK=0;  
    _CS=0;  
    port<<=4;  
    for(i=0;i<12;i++)   
    {     
	  if(D_OUT)             
			ad|=0x01;     
		D_IN=(bit)(port&0x80);              
		CLOCK=1;       
		delay(10);       
		CLOCK=0;       
		delay(10);       
		port<<=1;       
		ad<<=1;   
	}  
	_CS=1;  
	ad>>=1;  
	return(ad); 
}
