#include<reg51.h>	
#define GPIO_KEY P1
#define LCD1602_DATAPINS P0

typedef	 unsigned int	  uint;
typedef unsigned char	 uchar;

unsigned char KeyValue;
//?????????
unsigned char KeyState;
//???????
unsigned char PuZh[]=" DianKe1904yyw:D";
unsigned char dat[]="0123456789ABCDEF";

sbit LCD1602_E=P3^7;
sbit LCD1602_RW=P3^6;
sbit LCD1602_RS=P3^5;

void DelayMs(unsigned int x);
void Delay10ms();   //?50us
void KeyDown();		 //?????
void LcdInit();
void LcdWriteData(uchar dat);
void LcdWriteCom(uchar com);


void main(void)
{
	unsigned char i;
	LcdInit();
	KeyState=0;
	
	for(i=0;i<16;i++)
	{
//		LcdWriteCom(0x80);
		LcdWriteData(PuZh[i]);	
	}
	
	while(1)
	{
		KeyDown();
	 	LcdWriteCom(0xc0);
		LcdWriteData(dat[KeyValue]);

		/*
		if(KeyState==0)	//	 ???????,????
		{

			KeyState=1;
			LcdWriteCom(0xc0);
			LcdWriteData(dat[KeyValue]);

		}
		*/
	}				
}

void KeyDown(void)
{
	char a;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Delay10ms();
		if(GPIO_KEY!=0x0f)
		{
			KeyState=0;
			//??
			GPIO_KEY=0X0F;
// 			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
//				default:	KeyValue=17;	//?????17???????????
			}
			//??
			GPIO_KEY=0XF0;
			Delay10ms();
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
//				default:	KeyValue=17;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //???????
			{
				Delay10ms();
				a++;
			}
			a=0;
		}
	}
}

void Delay10ms(void)   //? 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void DelayMs(unsigned int x)   //0.14ms?? 0us
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++)
 {}
 }
}


void LcdWriteCom(uchar com)	  //???
{
	LCD1602_E = 0;    //?
	LCD1602_RS = 0;	   //?????
	LCD1602_RW = 0;	   //???
	
	LCD1602_DATAPINS = com;     //???
	DelayMs(1);		//?????

	LCD1602_E = 1;	          //???
	DelayMs(5);	  //???
	LCD1602_E = 0;
}

void LcdWriteData(uchar dat)			//???
{
	LCD1602_E = 0;	//???
	LCD1602_RS = 1;	//?????
	LCD1602_RW = 0;	//???

	LCD1602_DATAPINS = dat; //???
	DelayMs(1);

	LCD1602_E = 1;   //???
	DelayMs(5);   //???
	LCD1602_E = 0;
}

void LcdInit()						  //LCD??????
{
 	LcdWriteCom(0x38);  //??
	LcdWriteCom(0x0c);  //???????
	LcdWriteCom(0x06);  //?????1
	LcdWriteCom(0x01);  //?
	LcdWriteCom(0x80);  //???????
}
