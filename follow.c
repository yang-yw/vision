#include "follow.h"

extern void delay(unsigned int n);
extern void go(void);
extern void stop(void);
extern void back(void);
extern void left(void);
extern void right(void);
//extern void upleft(unsigned int n);
//extern void upright(unsigned int n);
extern void backleft(unsigned int n);
extern void backright(unsigned int n);



void auto_follow()
{
	if(aoutAA==0 && aoutBB==0)
		{
			go();
		}
	else if(aoutAA==0 && aoutBB==1)
		{
			backright(1);
		}
	else if(aoutAA==1 && aoutBB==0)
		{
			backleft(1);
		}
	else if(aoutAA==0 && aoutBB==0)
		{
			stop();
		}
		
}
