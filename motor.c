#include "STC15W204S.h"
#include "intrins.h"

sbit D2 = P5^4;    //用于控制左边发光二极管
sbit D3 = P5^5;   //用于控制右边发光二极管
sbit IA1 = P1^3;   //用于控制电机1
sbit IB1 = P1^2;   //用于控制电机1
sbit IA2 = P1^1;   //用于控制电机2
sbit IB2 = P1^0;   //用于控制电机2

sbit La = P1^0;    //用于控制电机1
sbit Lb = P1^1;    //用于控制电机1
sbit Ra = P1^3;    //用于控制电机2
sbit Rb = P1^2;    //用于控制电机2

sbit fm = P3^3;
//1右轮  2左轮 IA1=Ra  IB1=Rb  IA2=Lb    IB2=La

//这样是后退
//		IA1=0;
//		IB1=1;
//		IA2=1;
//		IB2=0;
//11,10是右边

void delay(unsigned int n)//延时
{
	unsigned char i;
	while(n--)
	{
		for(i=0;i<113;i++);
	}
}

void stop(void)//停止
{
		IA1=0;
		IB1=0;
		IA2=0;
		IB2=0;
	D2=1;
	D3=1;
}

void back(void)//前进
{
		D2=1;
	  D3=1;
		IA1=1;
		IB1=0;
		IA2=0;
		IB2=1;
	delay(100);
}

void go(void)//后退
{
		D2=0;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=1;
		IB2=0;
	delay(100);
}

void right(void)//左转
{
		D2=0;
	D3=1;
		IA1=1;
		IB1=0;
		IA2=1;
		IB2=0;
	delay(100);
}

void left(void)//右转
{
		D2=1;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=0;
		IB2=1;
	delay(100);
}
void go_stop(void)//停止
{
		IA1=0;
		IB1=0;
		IA2=0;
		IB2=0;
	D2=1;
	D3=1;
}

void go_back(void)//前进
{
		D2=1;
	  D3=1;
		IA1=1;
		IB1=0;
		IA2=0;
		IB2=1;
	delay(100);
}

void go_up(void)//后退
{
		D2=0;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=1;
		IB2=0;
	delay(100);
}

void go_left(void)//原地左转
{
		D2=0;
	D3=1;
		IA1=0;
		IB1=1;
		IA2=0;
		IB2=1;
	delay(100);
}

void go_right(void)//原地右转
{
		D2=1;
	D3=0;
		IA1=1;
		IB1=0;
		IA2=1;
		IB2=0;
	delay(100);
}

void go_backleft(unsigned int n)//前进左偏
{
	unsigned int i=30;
	D2=0;
	D3=1;

	IA2 = 0;
	IB2 = 1;
	IA1 = 1;
	while(i--)
	{
		IB1 = 0;
		delay(n);
		IB1 = 1;
		delay(10-n);
	}
}
void go_backright(unsigned int n)//前进右偏
{
	unsigned int i=30;
	D2=1;
	D3=0;
	IA1 = 1;
	IB1 = 0;
	IA2 = 1;
	while(i--)
	{
		IB2 = 0;
		delay(n);
		IB2 = 1;
		delay(10-n);
	}
}


void go_upleft(unsigned int n)//后退左偏
{
	unsigned int i=200;
	D2=0;
	D3=1;
	Ra = 0;
	Rb = 1;
	Lb = 1;
	while(i--)
	{
		La = 0;
		delay(n);
		La = 1;
		delay(10-n);
	}
}
void go_upright(unsigned int n)//后退右偏
{
	unsigned int i=200;
		D2=1;
	D3=0;
	La = 0;
	Lb = 1;
	Rb = 1;
	while(i--)
	{
		Ra = 0;
		delay(n);
		Ra = 1;
		delay(10-n);
	}
}