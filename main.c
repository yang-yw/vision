#include "STC15W204S.h"
#include "intrins.h"
#include "avoid.h"
#include "follow.h"
//0  ֹͣ
//1  ǰ��
//2  ����
//3  ��ת
//4  ��ת
//5  ����
//6  ѭ������ֽ����


sbit D2 = P5^4;  //���ڿ�����߷��������
sbit D3 = P5^5;   //���ڿ����ұ߷��������
sbit IA1 = P1^3;   //���ڿ��Ƶ��1
sbit IB1 = P1^2;   //���ڿ��Ƶ��1
sbit IA2 = P1^1;   //���ڿ��Ƶ��2
sbit IB2 = P1^0;   //���ڿ��Ƶ��2
sbit key = P3^2;   //����
sbit fm = P3^3;   //���ڿ��Ʒ�����
int  nm = 0;

extern void delay(unsigned int n);
extern void go_stop(void);
extern void go_up(void);
extern void go_back(void);
extern void go_left(void);
extern void go_right(void);
extern void go_upleft(unsigned int n);
extern void go_backleft(unsigned int n);
extern void go_backright(unsigned int n);

/*
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
/*
void keynum(void)//ͨ������ѡ����
{
		if(key == 0)
		{
			Delay500ms();			Delay500ms();			
			
			nm++;
			if(nm>5)
			{
				nm=0;
			}
		}
}
*/

void main(void)
{

	while(1)
	{

		//keynum();
		auto_avoid();
		auto_follow();
	}
}
		/*if(nm==0)
		{
			go_stop();
		}
		if(nm==1)
		{
			go_up();
		}
		if(nm==2)
		{
			go_back();
		}
		if(nm==3)
		{
			go_left();
		}
		if(nm==4)
		{
			go_right();
		}
		if(nm==5)
		{
			auto_avoid();
		}
		//if(nm==6)
		//{
			//auto_follow();
		//}

  }
	
}
*/