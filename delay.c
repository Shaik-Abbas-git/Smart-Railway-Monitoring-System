#include<LPC21xx.h>
void delay_ms(volatile unsigned int ms)
{
	volatile unsigned int cnt;
	while(ms>0)
	{
		cnt=4630;
		while(cnt>0)
		{
			cnt--;
		}
		ms--;
	}
}
void delay_us(volatile unsigned int us)
{
	volatile unsigned int cnt;
	while(us>0)
	{
		cnt=4;
		while(cnt>0)
		{
			cnt--;
		}
		us--;
	}
}
