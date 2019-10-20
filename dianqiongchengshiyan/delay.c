#include<reg51.h>
#include<delay.h>

void delay(uint x)
{
    uint i, j;
     for (i = x; i > 0; i--)
         for (j = 10; j > 0; j--);
}

/*void delay_ms(uint ms)
{
	uint i,j;
	for(i = ms;i>0;i--)
		for(j = 110;j>0;j--);
}
  */