#include<reg51.h>	
#define GPIO_KEY P1
#define LCD1602_DATAPINS P0

typedef	 unsigned int	  uint;
typedef unsigned char	 uchar;


unsigned char KeyValue;

unsigned char KeyState;

unsigned char PuZh[]=" DianKe1904yyw:D ";
unsigned char dat[]="0123456789ABCDEF";
uchar num;
unsigned char i,receivedata;

sbit LCD1602_E=P3^7;
sbit LCD1602_RW=P3^6;
sbit LCD1602_RS=P3^5;

void DelayMs(unsigned int x);
void Delay10ms();  	 
void LcdInit();
void LcdWriteData(uchar dat);
void LcdWriteCom(uchar com);
void InitUART  (void);  


void InitUART  (void)
{

    SCON  = 0x50;		          
    TMOD  = 0x20;               
    TH1   = 0xFD;               
    TR1   = 1;                                          
    EA    = 1;                  
    ES    = 1;                  
} 



void Delay10ms(void)   
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void DelayMs(unsigned int x)  
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++)
 {}
 }
}


void LcdWriteCom(uchar com)	 
{
	LCD1602_E = 0;     
	LCD1602_RS = 0;	   
	LCD1602_RW = 0;	   
	
	LCD1602_DATAPINS = com;     
	DelayMs(1);		

	LCD1602_E = 1;	          
	DelayMs(5);	  
	LCD1602_E = 0;
}

void LcdWriteData(uchar dat)			
{
	LCD1602_E = 0;	
	LCD1602_RS = 1;	
	LCD1602_RW = 0;	

	LCD1602_DATAPINS = dat; 
	DelayMs(1);

	LCD1602_E = 1;   
	DelayMs(5);   
	LCD1602_E = 0;
}

void LcdInit()						 
{
 	LcdWriteCom(0x38);  
	LcdWriteCom(0x0c);  
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80);  
}




/*void Usart()interrupt 4
{
	
	if(RI)
	{
		RI=0;
		
	  receivedata=(int)SBUF;
	}
}
*/


void main(void)
{
	InitUART();
	LcdInit();
	
	for(i=0;i<16;i++)
	{

		LcdWriteData(PuZh[i]);	
	
	}


	while(1)
	{
		
		if(RI)
	{
		RI=0;
	  receivedata=(int)SBUF;
	}
		LcdWriteCom(0xc0);
		LcdWriteData(dat[receivedata]);
	}
}
