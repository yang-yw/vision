#ifndef	__HC05_H
#define	__HC05_H

#include	"config.h"

void uart_init(void);
void SendData(uchar dat);
void uart_isr(void);

#endif
