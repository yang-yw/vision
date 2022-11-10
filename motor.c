#include "STC15W204S.h"
#include "intrins.h"

sbit D2 = P5^4;    //���ڿ�����߷��������
sbit D3 = P5^5;   //���ڿ����ұ߷��������
sbit IA1 = P1^3;   //���ڿ��Ƶ��1
sbit IB1 = P1^2;   //���ڿ��Ƶ��1
sbit IA2 = P1^1;   //���ڿ��Ƶ��2
sbit IB2 = P1^0;   //���ڿ��Ƶ��2

sbit La = P1^0;    //���ڿ��Ƶ��1
sbit Lb = P1^1;    //���ڿ��Ƶ��1
sbit Ra = P1^3;    //���ڿ��Ƶ��2
sbit Rb = P1^2;    //���ڿ��Ƶ��2

sbit fm = P3^3;
//1����  2���� IA1=Ra  IB1=Rb  IA2=Lb    IB2=La

//�����Ǻ���
//		IA1=0;
//		IB1=1;
//		IA2=1;
//		IB2=0;
//11,10���ұ�

void delay(unsigned int n)//��ʱ
{
	unsigned char i;
	while(n--)
	{
		for(i=0;i<113;i++);
	}
}

void stop(void)//ֹͣ
{
		IA1=0;
		IB1=0;
		IA2=0;
		IB2=0;
	D2=1;
	D3=1;
}

void back(void)//ǰ��
{
		D2=1;
	  D3=1;
		IA1=1;
		IB1=0;
		IA2=0;
		IB2=1;
	delay(100);
}

void go(void)//����
{
		D2=0;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=1;
		IB2=0;
	delay(100);
}

void right(void)//��ת
{
		D2=0;
	D3=1;
		IA1=1;
		IB1=0;
		IA2=1;
		IB2=0;
	delay(100);
}

void left(void)//��ת
{
		D2=1;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=0;
		IB2=1;
	delay(100);
}
void go_stop(void)//ֹͣ
{
		IA1=0;
		IB1=0;
		IA2=0;
		IB2=0;
	D2=1;
	D3=1;
}

void go_back(void)//ǰ��
{
		D2=1;
	  D3=1;
		IA1=1;
		IB1=0;
		IA2=0;
		IB2=1;
	delay(100);
}

void go_up(void)//����
{
		D2=0;
	D3=0;
		IA1=0;
		IB1=1;
		IA2=1;
		IB2=0;
	delay(100);
}

void go_left(void)//ԭ����ת
{
		D2=0;
	D3=1;
		IA1=0;
		IB1=1;
		IA2=0;
		IB2=1;
	delay(100);
}

void go_right(void)//ԭ����ת
{
		D2=1;
	D3=0;
		IA1=1;
		IB1=0;
		IA2=1;
		IB2=0;
	delay(100);
}

void go_backleft(unsigned int n)//ǰ����ƫ
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
void go_backright(unsigned int n)//ǰ����ƫ
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


void go_upleft(unsigned int n)//������ƫ
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
void go_upright(unsigned int n)//������ƫ
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