#include "avoid.h"
       
extern void delay(unsigned int n);
extern void go_stop(void);
extern void go_up(void);
extern void go_back(void);
extern void go_left(void);
extern void go_upleft(unsigned int n);
extern void go_upright(unsigned int n);
extern void go_backleft(unsigned int n);
extern void go_backright(unsigned int n);

sbit fm = P3^3;   //”√”⁄øÿ÷∆∑‰√˘∆˜

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 4;
	j = 4;
	k = 4;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}





void auto_avoid()
{
	fm = 1;
	if(aoutA==1 && aoutB==1)//Œﬁ’œ∞≠
	{
		go_up();
	}
	else if(aoutA==0 && aoutB==1)//”“±ﬂ”–’œ∞≠
		{
			go_backright(1);
				fm=0;
	Delay500ms();
	fm=1;
		}
	else if(aoutA==1 && aoutB==0)//◊Û±ﬂ”–’œ∞≠
		{
			go_backleft(1);
				fm=0;
	Delay500ms();
	fm=1;
		}
	else if(aoutA==0 && aoutB==0)//◊Û”“∂º”–’œ∞≠
		{
			go_stop();
				fm=0;
	Delay500ms();
	fm=1;
		}
		
}