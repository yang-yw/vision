#include "stc15W204S.h"
#include "hc05.h"
#include "config.h"
#define uchar unsigned char
#define uint  unsigned int

sbit OUTAB=P1^4;
sbit OUTBB=P1^5;
sbit OUTAX=P3^6;
sbit OUTBX=P3^7;
sbit K1=P3^2;
sbit D2=P5^4;
sbit D3=P5^5;
sbit IA1=P1^3;
sbit IB1=P1^2;
sbit IA2=P1^1;
sbit IB2=P1^0;
extern uchar recv;
extern void delay(unsigned int n);
extern void stop(void);
extern void go(void);
extern void back(void);
extern void left(void);
extern void right(void);
extern void backleft(void);
extern void backright(void);

	
void uart_init(void)
{
	SCON = 0x50;                
	T2L = (65536 - (MAIN_Fosc/4/BAUD));  
	T2H = (65536 - (MAIN_Fosc/4/BAUD))>>8;
	AUXR = 0x14;       
	AUXR |= 0x01;             
	ES = 1;         
	EA = 1;
}



void SendData(uchar dat)
{
  SBUF = dat;
	while(TI == 0);
	TI = 0;
}


void uart_isr(void)  interrupt 	4 
{
	
	if(RI == 1)
	{
		RI = 0;
		recv = SBUF;
		SendData(recv);
		
		}			
	
	
}



void main()
{

	uart_init();		
	
	while(1)
	{
		EA=0;
		if(RI==1)
		{
			RI=0;
			
		IA1=0;
		IB1=0;
		IA2=0;
		IB2=0;
	  D2=0;
	  D3=0;
		recv = SBUF;
		switch(recv)
		{
			
			case ('1'):
				left();
	
			break;
			case ('2'):
				back();
			
			break;
			case ('3'):
				right();
			
			break;
			case ('4'):
				go();
			break;
			case ('0'):
				stop();
			
			break;
			
		}
	}
		EA=1;
	
}
	}
			
			
			
			
			/*case 1:
				D2=0;
			break;
			case 2:
				D3=0;
			break;
		}
	}
}
			
			
			/*
			case ('1'):
				go();break;
			case ('2'):
				back();break;
			case ('3'):
				left();break;
			case ('4'):
				right();break;
			case ('0'):
				stop();break;
		}			
	}

	
}*/
